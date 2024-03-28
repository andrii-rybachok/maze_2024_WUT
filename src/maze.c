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
    printf("%s: %d\n",fileName, countOfVertices);

    fclose(fp);
    return countOfVertices;
}

int getCountOfDeadEnds(char * fileName){
    FILE *fp = fopen(fileName, "r");
    char top[2050], middle[2050], bottom[2050];
    int countOfEnds=0;
    int linesCount=0;
    int totalLines=0;

    //czytamy pierwsze 3 linii
    fscanf(fp, "%2050[^\n]%*c%2050[^\n]%*c%2050[^\n]%*c", top, middle, bottom);
    countOfEnds += getDeadEndsFromLines(top,middle,bottom);
    // tu zapisujemy średnią i niżną linię , które przeczytaliśmy z pliku
    char  beforeMiddle[2050];
    char  beforeBottom[2050];

    strcpy(beforeMiddle, middle);
    strcpy(beforeBottom,bottom);


    while((linesCount= fscanf(fp, "%2050[^\n]%*c%2050[^\n]%*c%2050[^\n]%*c", top, middle, bottom))!=EOF){

        switch (linesCount)
        {
            case 2:
                countOfEnds += getDeadEndsFromLines(beforeMiddle,beforeBottom,top);
                countOfEnds += getDeadEndsFromLines(beforeMiddle, top,middle);
                break;
            case 3:
                // wykorzystujemy zeszłe linie żeby przeczytać przeszły dół
                countOfEnds += getDeadEndsFromLines(beforeMiddle,beforeBottom,top);
                // wykorzystujemy zeszłe linie żeby przeczytać terażniejszy top
                countOfEnds += getDeadEndsFromLines(beforeBottom,top,middle);

                countOfEnds += getDeadEndsFromLines(top,middle,bottom);
                strcpy(beforeMiddle, middle);
                strcpy(beforeBottom,bottom);
                break;
            case 1:
                countOfEnds += getDeadEndsFromLines(beforeMiddle,beforeBottom,top);
                break;
        default:
            break;
        }
    }
    printf("%s: %d\n",fileName, countOfEnds);

    fclose(fp);
    return countOfEnds;
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
int getDeadEndsFromLines(char* top, char* middle, char* bot){
    int ends=0;
       
    for (int i = 0; middle[i]!= '\0'; i++)
    {
        if(middle[i]==MAZE_PATH){

            int walls=0;
            // tu podajemy otoczenie chara
            char surronding[5] = {top[i],middle[i+1],bot[i],middle[i-1],'\0'};

            for (int j = 0; j < 4; j++)
            {
                if (surronding[j]==MAZE_WALL)
                {
                    walls++;
                }
                
            }
            if (walls==3)
            {
                ends++;
            }
        }
        

    }


    return ends;
    
}


void removeDeadEndsFromLines(char* top, char* middle, char* bot){
    for (int i = 1; middle[i+1]!= '\0'; i++)
    {
        int walls=0;
        char surronding[] = {top[i],middle[i+1],bot[i],middle[i-1]};
    // printf("lssss ");

        for (int j = 0; j < 4; j++)
        {
            if (surronding[j]==MAZE_WALL)
            {
                walls++;
            }
            
        }
        if (walls>=3)
        {
            middle[i]=MAZE_WALL;
        }
    }
}
// Funkcja odczytująca labirynt z pliku do tablicy dwuwymiarowej
int readMazeFromFile(char maze[][MAZE_SIZE_X], char *filename,int startRowIndex,char* firstLine,char* lastLine) {
    FILE *in = fopen(filename, "r");
    if (in == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    int currRow = 1;
    int readLines = 0;

    char buff[MAZE_SIZE_X];

    while (currRow < startRowIndex && fgets(buff, sizeof(buff), in)) {

        if(firstLine!=NULL&&currRow+1==startRowIndex){
            strcpy(firstLine,buff);
        }
        currRow++;
    }

    while (readLines < MAZE_SIZE_Y && fgets(buff, MAZE_SIZE_X, in)!=NULL) {
        strcpy(maze[readLines],buff);        
        readLines++;

    }
    if (lastLine!=NULL&&fgets(buff, MAZE_SIZE_X, in)!=NULL)
    {
        strcpy(lastLine,buff);
    }
    fclose(in);
    return currRow+readLines;

}

// Funkcja zapisu zaktualizowanej tablicy do pliku
void writeMazeToFile(char maze[][MAZE_SIZE_X], char *filename, int startRowIndex,int fileRowSize) {
    FILE * fp;
    if (startRowIndex==1)
    {
        fp = fopen(filename, "w");
    }
    else{
        fp = fopen(filename, "a");
    }

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    int rowsToRide = fileRowSize-startRowIndex>=MAZE_SIZE_Y?MAZE_SIZE_Y:(fileRowSize-startRowIndex+1);
    
    if(rowsToRide==0){
        rowsToRide++;
    }
    for (int i = 0; i < rowsToRide ; i++) {
        
        fputs(maze[i], fp);
    }
    fclose(fp);
}
int isEnd(char maze[][MAZE_SIZE_X], int x, int y){
    int walls=0;
    
    if (maze[y][x]==MAZE_WALL)
    {
        return 0;
    }
    if (maze[y][x+1] == MAZE_WALL){
        printf("1,%c ",maze[y][x+1]);
        walls++;
    }
    if (maze[y][x-1] == MAZE_WALL){
        printf("2,%c ",maze[y][x-1]);

        walls++;
    } 
    if (maze[y-1][x] == MAZE_WALL) {
        printf("3,%c ",maze[y-1][x]);

        walls++;
    }
    if (maze[y+1][x] == MAZE_WALL) {
        printf("4,%c ",maze[y+1][x]);

       walls++;
    }
    return walls>=3;
}
// Funkcja sprawdzająca, czy punkt jest ślepym zaułkiem
void isDeadEnd(char maze[][MAZE_SIZE_X], int x, int y) {
    int walls = 0;
    if (maze[y][x]==MAZE_WALL )
    {
        return;
    }
    int currX=0;
    int currY=0;    
    if (maze[y][x-1] != MAZE_WALL){
        
        currX=x-1;
        currY=y;      
    } 
    else{
        walls++;
    }

    if (maze[y][x+1] != MAZE_WALL){
        currX=x+1;
        currY=y;
        
    } else{
        walls++;
    }
    if (maze[y-1][x] != MAZE_WALL) {
        currX=x;
        currY=y-1;
        
    } else{
        walls++;
    }
    if (maze[y+1][x] != MAZE_WALL) {
        currX=x;
        currY=y+1;
       
    } else{
        walls++;
    }
    if (walls>=3)
    {
        maze[y][x]=MAZE_WALL;
        isDeadEnd(maze,currX,currY);   
    }


}

// Funkcja usuwania ślepych zaułków z labiryntu
void removeDeadEnds(char maze[][MAZE_SIZE_X],char * firstLine,char* lastLine) {
    for (int i = 1; i < MAZE_SIZE_Y && maze[i+1][0]!='\0'; i++) {                 
        for (int j = 1; maze[i][j+1]!='\0'; j++) {
            isDeadEnd(maze,j,i);             
        }
    }
    if (firstLine!=NULL && strlen(firstLine)>1)
    {
        removeDeadEndsFromLines(firstLine,maze[0],maze[1]);
    }
    if (lastLine!=NULL && strlen(lastLine)>1)
    {
        removeDeadEndsFromLines(maze[MAZE_SIZE_Y-2],maze[MAZE_SIZE_Y-1],lastLine);
    }
}
