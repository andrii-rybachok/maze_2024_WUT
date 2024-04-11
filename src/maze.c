#include "maze.h"


// Funkcje dla działania na tablice bitowej dwuwymiarowej. Tablica jest maksymalnego rozmiaru, dlatego jeden wiersz to 2049 znaków
// 1 - ścieżka , 0 - ściana
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
        return -1; 
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
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    char buff[MAZE_SIZE_X];
    fgets(buff, MAZE_SIZE_X, file);
    int count = 0;
    for (int i = 0; buff[i]==MAZE_WALL || buff[i]==MAZE_START || buff[i]==MAZE_END; i++)
    {
        count=i+1;   
    }
    
    fclose(file);
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
            elCords.y++;
            elCords.x=0; 
        } else {
            elCords.x++;
        }
    }
    elCords.x=-1;
    elCords.y=-1;
    fclose(file);
    return elCords;
}

void checkMazeParams(mazeParams params){
    if(params.endCords.x==-1 || params.endCords.y==-1 || params.startCords.x==-1 || params.startCords.y==-1){
        handleError(3);
    }
}


mazeParams initializeParams(char* originFileName){

    mazeParams params;
    params.cols=countCharsInFirstLine(originFileName); // obliczenie liczby kolumn poprzez wewnętrzną funkcję 
    if(params.cols==-1){
        handleError(2);
    }
    params.rows=count_lines(originFileName); // obliczenie liczby wierzy poprzez wewnętrzną funkcję 
    params.originFileName=originFileName;
    params.endCords = getElemCords(MAZE_END,originFileName); // wyszukiwanie i zapisywanie położeń końca i początka
    params.startCords = getElemCords(MAZE_START,originFileName); 
    checkMazeParams(params);
    return params;
}

mazeParams initializeParamsBin(char* originFileName){

    mazeParams params;
    binHeader header= getFileHeader(originFileName); // pobierania z modułu binaryAdapter file headera
    params.cols=header.columns; // adaptacja informacji z headera
    params.rows=header.lines;
    params.originFileName=originFileName;  
    params.endCords.x=header.exit_x-1;
    params.endCords.y=header.exit_y-1;
    params.startCords.x=header.entry_x-1;
    params.startCords.y=header.entry_y-1;

    checkMazeParams(params);

    return params;
}

void readMazeFromBinFile(unsigned int maze[],mazeParams params){
    FILE *file = fopen(params.originFileName, "rb");
    if (file == NULL) {
        handleError(2);
        return;
    }
    binHeader header;
    fread(&header, sizeof(binHeader), 1, file); // wyczytujemy header
    mazeKeys key;
    int readedLines=0; // inaczej y

    while (readedLines!=header.lines-1)
    {
        int readColumns=0; // przeczytane kolumny
        int x=0;
        while (readColumns!=header.columns ) // czytamy wiersz i sprawdzamy ile już przeczytaliśmy w tym wierszu
        {
           
            fread(&key,sizeof(mazeKeys), 1, file); // czytamy jeden kłucz
            int size=key.count+1; // dodajemy jedynkę , bo tu liczymy od jednego. Robimy nową zmienę , ponieważ maksymalnie możemy na raz przeczytać 256 znaków, a char mieści tylko 255
            for (int i = 0; i < size; i++)
            {
                if(header.path==key.value){
                    SetBit(maze,x,readedLines); // zapisujemy przeczytane do pliku
                }
                x++;
            }
            readColumns+=size; // odświeżamy liczbę przeczytanych kolumn

        }
        readedLines++; // odświeżamy igrek
        
    }
    fclose(file);
}

// Funkcja odczytująca labirynt z pliku do tablicy dwuwymiarowej bitowej
int readMazeFromFile(unsigned int maze[], mazeParams params) {
    FILE *in = fopen(params.originFileName, "r");
    if (in == NULL) {
        handleError(2);
        return;
    }
    
    int currRow = 0;

    char buff[MAZE_SIZE_X+2];
    // przeczytujemy plik po jednej linijce i zapisujemy do tablicy
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



// Funkcja sprawdzająca, i usuwająca ślepy zaułek
void isDeadEnd(unsigned int maze[], int x, int y) {
    int walls = 0;
    if (!TestBit(maze,x,y)) // jeżeli jest ścianą , przerwij
    {
        return;
    }
    int currX=0;
    int currY=0;    
    // Funckja jest napisana trochę topornie prze if else, ponieważ jest rekurencyjna i zżera dużo staku. 
    // Zasada jest prosta, dla każdego kierunku punktu sprawdzamy czy ma on tam ścieżke, jeżeli tak to zapisujemy ten punkt dla przyszłej rekurencji
    // jeżeli nie to dodajemy +1 to liczby ścian 
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
    // Jeżeli punkt ma 3 i więcej ścian, to uważamy że jest on ślepym zaułkiem
    if (walls>=3)
    {
        ClearBit(maze,x,y); // usuwanie ślepego zaułku
        isDeadEnd(maze,currX,currY); // przejście do następnego ślepego zaułku, punkt którego wcześniej zapisaliśmy
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


// 0 - lewo, 1 - prawo, 2 - dół, 3 - góra 

unsigned int availableDirections(unsigned int maze[],mazeParams params,cords moveCords){
    unsigned int directions=0;

    if(moveCords.y+1<params.rows && TestBit(maze,moveCords.x,moveCords.y+1)){
        SetBit(&directions,2,0);
    }
    if(moveCords.y-1<params.rows && TestBit(maze,moveCords.x,moveCords.y-1)){
        SetBit(&directions,3,0);

    }
     if(moveCords.x-1<params.cols && TestBit(maze,moveCords.x-1,moveCords.y)){
        SetBit(&directions,0,0);

    }

     if(moveCords.x+1<params.cols && TestBit(maze,moveCords.x+1,moveCords.y)){
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


// funkcja rekurencyjna do poszukiwania najkrótszej ścieżki
// ważne parametry : params - do zapisywania najkrótszej ścieżki w minSteps, head- głowa listy liniowej zapisującej kroki,
// backDirection - kierunek z którego 'przyszliśmy'
void goByPath(unsigned int maze[],mazeParams * params,node ** head,cords  currentCords,int backDirection){
    
    cords tmp = currentCords;
    int direction = move(maze,*(params),&currentCords,&backDirection); // przejście do najbliższego skrętu lub rozgałęzienia za pomocą funkcji pomocniczej

    int steps= abs(tmp.x-currentCords.x)!=0?abs(tmp.x-currentCords.x):abs(tmp.y-currentCords.y); // wyliczanie liczby zrobionych kroków

    // Jeżeli doszliśmy do końca
    if(params->endCords.x==currentCords.x && currentCords.y==params->endCords.y){
        
        push_back(head,steps+1,getAlternateDirection(backDirection));// dodanie kroków do listy
        
        int listSteps=getListSteps(*head); // wyliczanie liczby kroków w liście
        // sprawdzanie czy jest ścieżka najktótsza
        if(listSteps<params->minSteps || params->minSteps==0){
            params->minSteps=listSteps; // zapisywanie aktualnej najkrótszej ścieżki
            saveSolution(*head,*params); // zapisywanie rozwiązania do pliku
        }
        pop_back(head);

        return ;
    }
    // direction wszkazuje kierunek do względem do którego szliśmy, jeżeli jest równy -1 to nie zrobiliśmy żadnego kroku
    if(direction==-1){

        return ;
    }

    push_back(head,steps+1,direction);// dodanie kroków do listy
  
    unsigned int directions=availableDirections( maze, *(params),currentCords); // wyliczanie dostępnych kierunków jako tablice bitów [4]
    // dfs 
    for (int i = 3; i >= 0; i--)
    {
        // cykl , w którym chodzimy w każdym kierunku , oprócz z którego przyszliśmy
        if(i!=backDirection && TestBit(&directions,i,0)){
            tmp = currentCords;
            ClearBit(maze,currentCords.x,currentCords.y); // oznaczenie odwiedzonego skrętu
            makeStep(&tmp,i); // robimy jeden krok w stonę current kierunku
            goByPath(maze,params,head,tmp,getAlternateDirection(i)); // wywołanie rekurencji, jako backDirection dajemy przeciwny kierunek w którym zrobiliśmy jeden krok
            SetBit(maze,currentCords.x,currentCords.y); // usuwanie oznaczenia odwiedzonego skrętu

        }
    }
    pop_back(head); // usuwanie z końca kroku
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
    if(params->minSteps==0){
        handleError(4);
    }    
}

