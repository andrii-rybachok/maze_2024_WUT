#include "maze.h"


// 0 - znak nad, 1 - znak z prawa , 2- znak pod, 3 - znak z lewa 
// sprawdzamy czy punkt jest węzłem
bool isVertice(char* points){
    for (int i = 0; points[i]!= '\0'; i++)
    {
       if (points[i]==MAZE_END || points[i]==MAZE_START)
       {
            points[i]=' ';
       }
    }
        
    return (points[1]!=points[3] || points[0]!=points[2]);
    
}
// sprawdzamy czy punkt jest ślepym zauelkiem
bool isEnd(char* points){
    int countOfWalls=0;
    for (int i = 0; points[i]!= '\0'; i++)
    {
       if (points[i]==MAZE_WALL)
       {
            countOfWalls++;
       }
    }
    return countOfWalls==3;
}
int getCountOfVertices(char * fileName){
    FILE *fp = fopen(fileName, "r");
    char top[2050], middle[2050], bottom[2050];
    int countOfVertices=0;
    int linesCount=0;
    int totalLines=0;

    //czytamy pierwsze 3 linii
    fscanf(fp, "%2050[^\n]%*c%2050[^\n]%*c%2050[^\n]%*c", top, middle, bottom);
    countOfVertices += getVerticesFromLines(top,middle,bottom);
    if (strchr(top,MAZE_START) || strchr(top,MAZE_END))
    {
        countOfVertices++;
    }
    // tu zapisujemy średnią i niżną linię , które przeczytaliśmy z pliku
    char  beforeMiddle[2050];
    char  beforeBottom[2050];

    strcpy(beforeMiddle, middle);
    strcpy(beforeBottom,bottom);


    while((linesCount= fscanf(fp, "%2050[^\n]%*c%2050[^\n]%*c%2050[^\n]%*c", top, middle, bottom))!=EOF){

        switch (linesCount)
        {
            case 2:
                countOfVertices += getVerticesFromLines(beforeMiddle,beforeBottom,top);
                countOfVertices += getVerticesFromLines(beforeMiddle, top,middle);

                if (strstr(middle,"K") || strstr(middle,"P"))
                {
                    countOfVertices++;
                }
                break;
            case 3:
                // wykorzystujemy zeszłe linie żeby przeczytać przeszły dół
                countOfVertices += getVerticesFromLines(beforeMiddle,beforeBottom,top);
                // wykorzystujemy zeszłe linie żeby przeczytać terażniejszy top
                countOfVertices += getVerticesFromLines(beforeBottom,top,middle);

                countOfVertices += getVerticesFromLines(top,middle,bottom);
                strcpy(beforeMiddle, middle);
                strcpy(beforeBottom,bottom);
                break;
            case 1:
                countOfVertices += getVerticesFromLines(beforeMiddle,beforeBottom,top);
                if (strchr(top,MAZE_START) || strchr(top,MAZE_END))
                {

                    countOfVertices++;
                }
                break;
        default:
            break;
        }
    }
    printf("test: %d\n", countOfVertices);

    fclose(fp);
    return countOfVertices;
}
// w tej funkcji czytamy jednocześńie jakby 3 linie na raz i podajemy to sprawdzenia otoczenie przeczytanego jednego chara ( czyli char można wyobrazić jak osobę a otoczenie to wierzch,dół lewo i prawo w 2d)
int getVerticesFromLines(char* top, char* middle, char* bot){
    int vertices=0;

       
    for (int i = 0; middle[i]!= '\0'; i++)
    {
        // tu podajemy otoczenie chara
        char surronding[5] = {top[i],middle[i+1],bot[i],middle[i-1],'\0'};

        if((middle[i]==MAZE_END || middle[i]==MAZE_START) || (middle[i] == MAZE_PATH &&  isVertice(surronding)))
        {
            vertices++;
        }

    }


    return vertices;
    
}

// Funkcja odczytująca labirynt z pliku do tablicy dwuwymiarowej
void readMazeFromFile(char maze[][MAZE_SIZE_Y], char *filename) {
    FILE *in = fopen(filename, "r");
    if (in == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    int row = 0;
    while (fgets(maze[row], MAZE_SIZE_Y, in) != NULL) {
        row++;
    }
    
    fclose(in);
}

// Funkcja zapisu zaktualizowanej tablicy do pliku
void writeMazeToFile(char maze[][MAZE_SIZE_Y], char *filename, int rows) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    for (int i = 0; i < rows; i++) {
        fputs(maze[i], fp);
    }
    
    fclose(fp);
}

// Funkcja sprawdzająca, czy punkt jest ślepym zaułkiem
int isDeadEnd(char maze[][MAZE_SIZE_Y], int x, int y) {
    int walls = 0;
    
    if (maze[x][y] == MAZE_WALL)
        return 0;

    if (maze[x-1][y] == MAZE_WALL) walls++;
    if (maze[x+1][y] == MAZE_WALL) walls++;
    if (maze[x][y-1] == MAZE_WALL) walls++;
    if (maze[x][y+1] == MAZE_WALL) walls++;
    
    return walls >= 3;
}

// Funkcja usuwania ślepych zaułków z labiryntu
void removeDeadEnds(char maze[][MAZE_SIZE_Y], int rows, int cols) {
    int changed;
    do {
        changed = 0;
        for (int i = 1; i < rows - 1; i++) {
            for (int j = 1; j < cols - 1; j++) {
                if (isDeadEnd(maze, i, j)) {
                    maze[i][j] = MAZE_WALL;
                    changed = 1;
                }
            }
        }
    } while (changed);
}
