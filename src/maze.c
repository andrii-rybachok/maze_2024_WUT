#include "maze.h"
// 0 - wall, 1 - path

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



void  SetBit(unsigned int A[],  int x ,int y )
{

    x+=MAZE_SIZE_X*y;
    A[x/32] |= 1 << (x%32);
}
void  ClearBit(unsigned int A[],  int x ,int y )                
{
    x+=MAZE_SIZE_X*y;
    A[x/32] &= ~(1 << (x%32));
}
int TestBit(unsigned int A[],  int x ,int y )
{
    x+=MAZE_SIZE_X*y;
    return ( (A[x/32] & (1 << (x%32) )) != 0 ) ;     
}

int count_lines(char* fileName)
{
     FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1; // Return -1 to indicate error
    }

    int count = 1;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    fclose(file);
    return count;
}
int countCharsInFirstLine(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open file in read mode
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return -1; // Error opening file
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        count++; // Increment count for each character until newline or EOF
    }

    fclose(file); // Close the file
    return count;
}
cords getElemCords(char target,char* fileName ){
    cords elCords;
    int ch;
    elCords.x=0;
    elCords.y=0;
    FILE* file = fopen(fileName,"r");
    while ((ch = fgetc(file)) != EOF) {
        if (ch == target) {
            fclose(file);
            return elCords;
        }
        if (ch == '\n') {
            // Move to the next line
            elCords.y++;
            elCords.x=0; // Reset column count
        } else {
            elCords.x++;
        }
    }
    elCords.x=-1;
    elCords.y=-1;
    fclose(file);
    return elCords;
}


mazeParams initializeParams(char* originFileName,char* ourFileName){

    mazeParams params;
    params.cols=count_lines(originFileName);
    params.rows=countCharsInFirstLine(originFileName);
    params.originFileName=originFileName;
    params.ourFileName=ourFileName;
    params.endCords = getElemCords(MAZE_END,originFileName);
    params.startCords = getElemCords(MAZE_START,originFileName);

    return params;
}



// Funkcja odczytująca labirynt z pliku do tablicy dwuwymiarowej
int readMazeFromFile(unsigned int maze[], mazeParams params) {
    FILE *in = fopen(params.originFileName, "r");
    if (in == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    int currRow = 0;

    char buff[MAZE_SIZE_X+2];

    while (fgets(buff, MAZE_SIZE_X+2, in)) {
      
        for (int i = 0; buff[i]!='\0'; i++)
        {
            if(buff[i]==MAZE_PATH || buff[i]==MAZE_END || buff[i]==MAZE_START){
                SetBit(maze,i,currRow);

            }
        }     
        currRow++;
    }
   
    fclose(in);

}

// Funkcja zapisu zaktualizowanej tablicy do pliku
void writeMazeToFile(unsigned int maze[],mazeParams params) {
    FILE * fp;
    fp = fopen(params.ourFileName, "w");
   

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < params.rows ; i++) {
        
        for (int j = 0; j < params.cols; j++)
        {
            if(i==params.startCords.y&&j==params.startCords.x){
                fputc(MAZE_START,fp);
            }
            else if(i==params.endCords.y&&j==params.endCords.x){
                fputc(MAZE_END,fp);
            }
            else if(TestBit(maze,j,i)){
                fputc(MAZE_PATH, fp);
            }
            else{
                fputc(MAZE_WALL,fp);
            }
        }
        fputc('\n',fp);
    }
    fclose(fp);
}

// Funkcja sprawdzająca, czy punkt jest ślepym zaułkiem
void isDeadEnd(unsigned int maze[], int x, int y) {
    int walls = 0;
    if (!TestBit(maze,x,y))
    {
        return;
    }
    int currX=0;
    int currY=0;    
    if (TestBit(maze,x-1,y)){
        
        currX=x-1;
        currY=y;      
    } 
    else{
        walls++;
    }

    if (TestBit(maze,x+1,y)){
        currX=x+1;
        currY=y;
        
    } else{
        walls++;
    }
    if (TestBit(maze,x,y-1)) {
        currX=x;
        currY=y-1;
        
    } else{
        walls++;
    }
    if (TestBit(maze,x,y+1)) {
        currX=x;
        currY=y+1;
       
    } else{
        walls++;
    }
    if (walls>=3)
    {
        ClearBit(maze,x,y);
        isDeadEnd(maze,currX,currY);   
    }


}

// Funkcja usuwania ślepych zaułków z labiryntu
void removeDeadEnds(unsigned int maze[],mazeParams params) {
   
    for (int i = 1; i < params.rows-1; i++) {                 
        for (int j = 1; j<params.cols-1; j++) {
            isDeadEnd(maze,j,i);             
        }
        
    }
    
}


//-1 - start, 0 - lewo, 1 - prawo, 2 - dół, 3 - góra 

unsigned int availableDirections(unsigned int maze[],mazeParams params,cords moveCords){
    unsigned int directions=0;
    
    if(moveCords.y+1<params.rows && TestBit(maze,moveCords.x,moveCords.y+1)){
        SetBit(&directions,2,0);
    }
    if(moveCords.y-1<params.rows && TestBit(maze,moveCords.x,moveCords.y-1)){
        SetBit(&directions,3,0);

    }
     if(moveCords.x-1<params.rows && TestBit(maze,moveCords.x-1,moveCords.y)){
        SetBit(&directions,0,0);

    }
     if(moveCords.x+1<params.rows && TestBit(maze,moveCords.x+1,moveCords.y)){
        SetBit(&directions,1,0);

    }
    return directions;
}
void makeStep(cords * moveCords,int direction){
    switch (direction)
    {
    case 0:
        moveCords->x--;
        break;
    case 1:
        moveCords->x++;
        break;
    case 2:
        moveCords->y++;
        break;
    case 3:
        moveCords->y--;
        break;
    default:
        break;
    }
}
int getAlternateDirection(int direction){
    switch (direction)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 0;
        break;
    case 2:
        return 3;
        break;
    case 3:
        return 2;
        break;
    default:
        break;
    }
}
int move(unsigned int maze[],mazeParams params,cords * moveCords,int * backDirection){
   
    int direction=-1;
    int possibleDirections=0;

    do
    {
        possibleDirections=0;
        unsigned int directions=availableDirections(maze,params,*moveCords);
        for (int i = 0; i < 4; i++)
        {
            if(i!=*backDirection && TestBit(&directions,i,0)){
                possibleDirections++;
            }
        }
        if(possibleDirections==1 ){
            if(direction==-1){
                for (int i = 0; i < 4; i++)
                {
                    if(i!=*backDirection && TestBit(&directions,i,0)){
                            makeStep(moveCords,i);
                            direction=i;
                            *backDirection=getAlternateDirection(direction);
                        break;
                    }
                }
            }
            else if (!TestBit(&directions,direction,0)){
                possibleDirections=0;
            }
            else{
                makeStep(moveCords,direction);
            }
        }

    } while (possibleDirections==1);
    
    
    return direction; 
}
int getBits(int * a ,int length){
    int count=0;
    for (int i = 0; i < length; i++)
    {
        if(TestBit(a,i,0)){
            count++;
        }
    }
    return count;
}

void goByPath(unsigned int maze[],mazeParams * params,node ** head,cords  currentCords,int backDirection){

    cords tmp = currentCords;
    int direction = move(maze,*(params),&currentCords,&backDirection);

    int steps= abs(tmp.x-currentCords.x)!=0?abs(tmp.x-currentCords.x):abs(tmp.y-currentCords.y);

    if(params->endCords.x==currentCords.x && currentCords.y==params->endCords.y){

        push_back(head,steps+1,getAlternateDirection(backDirection));

        int listSteps=getListSteps(*head);
        if(listSteps<params->minSteps || params->minSteps==0){
            params->minSteps=listSteps;
            printSolution("dane/solution.txt",*head);
        }
        pop_back(head);

        return ;
    }
    if(direction==-1){

        return ;
    }

    push_back(head,steps+1,direction);
  
    unsigned int directions=availableDirections( maze, *(params),currentCords);

    int isWining=0;
    for (int i = 3; i >= 0; i--)
    {
        if(i!=backDirection && TestBit(&directions,i,0)){
            tmp = currentCords;
            ClearBit(maze,currentCords.x,currentCords.y);
            makeStep(&tmp,i);
            goByPath(maze,params,head,tmp,getAlternateDirection(i));
            SetBit(maze,currentCords.x,currentCords.y);

        }
    }
    pop_back(head);
}   
void printMaze(unsigned int maze[],mazeParams params){
    for (int i = 0; i < params.rows; i++) {                 
        for (int j = 0; j<params.cols; j++) {
            if(TestBit(maze,j,i)){
                printf(" ");
            }            
            else{
                printf("X");
            }
        }
        printf("\n");
    }
}
void findSolution(unsigned int maze[],mazeParams * params){

    params->minSteps=0;
 
    node* head = NULL;
    goByPath(maze,params,&head,params->startCords,-1);
    writeMazeToFile(maze,*(params));
    printf("min steps %d",params->minSteps);

    
}

int readMazeFromFileBinarny(unsigned int maze[], mazeParams params) {
    FILE *in = fopen(params.originFileName, "rb");
    if (in == NULL) {
        printf("Error opening file.\n");
        return -1;
    }
    
    BinaryMazeHeader header;
    fread(&header, sizeof(BinaryMazeHeader), 1, in);

    fclose(in);
    return 0;
}


void writeMazeToFileBinarny(unsigned int maze[], mazeParams params) {
    FILE *out = fopen(params.ourFileName, "wb");
    if (out == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    BinaryMazeHeader header;
    header.fileId = FILE_ID;
    header.escape = ESCAPE_CHAR;
    header.columns = params.cols;
    header.lines = params.rows;
    header.entryX = params.startCords.x;
    header.entryY = params.startCords.y;
    header.exitX = params.endCords.x;
    header.exitY = params.endCords.y;
    header.reserved = 0;

    fwrite(&header, sizeof(BinaryMazeHeader), 1, out);

    fclose(out);
}

void findSolutionBinarny(FILE *out, unsigned int maze[], mazeParams *params) {
    params->minSteps = 0;
 
    node* head = NULL;
    goByPath(maze, params, &head, params->startCords, -1);

    if (out != NULL) {

        fwrite(&(params->minSteps), sizeof(int), 1, out);


        node *current = head;
        while (current != NULL) {

            unsigned char buffer[2];

            buffer[0] = current->direction;
            buffer[1] = current->countOfSteps;

            fwrite(buffer, sizeof(buffer), 1, out);

            current = current->next;
        }
    } else {
        printf("Error: Could not open file for writing.\n");
    }

    freeList(&head);

    printf("min steps %d\n", params->minSteps);
}

void freeList(node **head) {
    node *current = *head;
    node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}
