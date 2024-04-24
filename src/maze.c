#include "maze.h"


// Funkcje dla działania na tablice bitowej dwuwymiarowej. Tablica jest maksymalnego rozmiaru, dlatego jeden wiersz to 2049 znaków
// 1 - ścieżka , 0 - ściana
void  SetBit(unsigned int A[],  int x ,int y,int rowSize ) 
{
    x+=rowSize*y;
    A[x/32] |= 1 << (x%32);
}
void  ClearBit(unsigned int A[],  int x ,int y,int rowSize )                
{
    x+=rowSize*y;
    A[x/32] &= ~(1 << (x%32));
}
int TestBit(unsigned int A[],  int x ,int y,int rowSize )
{
    x+=rowSize*y;
    return ( (A[x/32] & (1 << (x%32) )) != 0 ) ;     
}
// 0 - lewo, 1 - prawo, 2 - dół, 3 - góra 
// funkcja zwraca w postaci bitowego wektoru dostępne kierunki
unsigned int availableDirections(mazeParams params,cords moveCords){
    unsigned int directions=0;

    if(moveCords.y+1<params.rows && TestBit(params.maze,moveCords.x,moveCords.y+1,params.cols)){
        SetBit(&directions,2,0,0);
    }
    if(moveCords.y-1>=0 && TestBit(params.maze,moveCords.x,moveCords.y-1,params.cols)){
        SetBit(&directions,3,0,0);

    }
    if(moveCords.x-1>=0 && TestBit(params.maze,moveCords.x-1,moveCords.y,params.cols)){
        SetBit(&directions,0,0,0);

    }

    if(moveCords.x+1<params.cols && TestBit(params.maze,moveCords.x+1,moveCords.y,params.cols)){
        SetBit(&directions,1,0,0);

    }
    return directions;
}
int getBits(int * a ,int length){
    int count=0;
    for (int i = 0; i < length; i++)
    {
        if(TestBit(a,i,0,0)){
            count++;
        }
    }
    return count;
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
    params.maze = (int*) calloc((params.cols*params.rows/32)+1,sizeof(int));
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            ClearBit(params.maze,j,i,params.cols);   
        }
    }    
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
    params.maze = (int*) calloc((params.cols*params.rows/32)+1,sizeof(int));
    for (int i = 0; i < params.rows; i++)
    {
        for (int j = 0; j < params.cols; j++)
        {
            ClearBit(params.maze,j,i,params.cols); 
        }
    }
    
    return params;
}

void readMazeFromBinFile(mazeParams* params){
    FILE *file = fopen(params->originFileName, "rb");
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
                    SetBit(params->maze,x,readedLines,params->cols); // zapisujemy przeczytane do pliku
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
int readMazeFromFile(mazeParams* params) {
    FILE *in = fopen(params->originFileName, "r");
    if (in == NULL) {
        handleError(2);
        return;
    }
    int currRow = 0;

    char buff[MAZE_SIZE_X];
    int lines = count_lines(params->originFileName);
    // // przeczytujemy plik po jednej linijce i zapisujemy do tablicy
    int i=0;
    while (fgets(buff, MAZE_SIZE_X, in)) {
      
        for (int i = 0; i <strlen(buff); i++)
        {
            // printf("%d",strlen(buff));
            if(buff[i]==MAZE_PATH || buff[i]==MAZE_END || buff[i]==MAZE_START){
                SetBit(params->maze,i,currRow,params->cols);

            }
        }     
        currRow++;
        i++;
    }
    fclose(in);

}



// Funkcja sprawdzająca, i usuwająca ślepy zaułek

void isDeadEnd(mazeParams * params, int x, int y,int maxDeep) {
    int walls = 0;
    maxDeep++;
    // maxdeep - sztuczne upowielnianie programu, ponieważ w dużych labiryntach zżera dużo RAM, bo jest to funkcja rekurencyjna. Gdy usunięmy maxDeep , program działa odpowiednie szybciej
    if (!TestBit(params->maze,x,y,params->cols) || maxDeep==2000) // jeżeli jest ścianą , przerwij
    {
        return;
    }
    int currX=0;
    int currY=0;    
    // Funckja jest napisana trochę topornie prze if else, ponieważ jest rekurencyjna i zżera dużo staku. 
    // Zasada jest prosta, dla każdego kierunku punktu sprawdzamy czy ma on tam ścieżke, jeżeli tak to zapisujemy ten punkt dla przyszłej rekurencji
    // jeżeli nie to dodajemy +1 to liczby ścian 
    if (x>0&&TestBit(params->maze,x-1,y,params->cols)){
        
        currX=x-1;
        currY=y;      
    } 
    else{
        walls++;
    }

    if (x<params->cols&&TestBit(params->maze,x+1,y,params->cols)){
        currX=x+1;
        currY=y;
        
    } else{
        walls++;
    }
    if (y>0&&TestBit(params->maze,x,y-1,params->cols)) {
        currX=x;
        currY=y-1;
        
    } else{
        walls++;
    }
    if (y<params->rows&&TestBit(params->maze,x,y+1,params->cols)) {
        currX=x;
        currY=y+1;
       
    } else{
        walls++;
    }
    // Jeżeli punkt ma 3 i więcej ścian, to uważamy że jest on ślepym zaułkiem
    if (walls>=3)
    {
        ClearBit(params->maze,x,y,params->cols); // usuwanie ślepego zaułku
        isDeadEnd(params,currX,currY,maxDeep); // przejście do następnego ślepego zaułku, punkt którego wcześniej zapisaliśmy
    }
}
//sprawdzanie czy labirynt ma ślepy zaułek
int checkForDeadEnd(mazeParams* params){
    cords current;

    for (int i = 1; i < params->rows-1; i++) {    
        current.y=i;             
        for (int j = 1; j< params->cols-1; j++) {
            if(TestBit(params->maze,j,i,params->cols)){
                current.x=j;
                unsigned int directions=availableDirections(*params,current);
                
                if((current.x==params->endCords.x&&current.y==params->endCords.y )||(current.x==params->startCords.x&&current.y==params->startCords.y)){
                    continue;
                }
                if(getBits(&directions,4)==1){
                    // printf("dead end x %d , y%d",current.x,current.y);
                    return 1;
                }          
            }
        }
    }
    return 0;
}
// Funkcja usuwania ślepych zaułków z labiryntu
void removeDeadEnds(mazeParams* params) {
    int hasDead=checkForDeadEnd(params);
    // dopóki labirynt ma ślepy zaułek
    while (hasDead!=0)
    {
        
        for (int i = 1; i < params->rows-1; i++) {                 
            for (int j = 1; j< params->cols-1; j++) {
                isDeadEnd(params,j,i,0);             
            }
        }
        hasDead=checkForDeadEnd(params);
    }
}

// 0 - lewo, 1 - prawo, 2 - dół, 3 - góra 
// robi jeden krok w wybranym kierunku i zmienia odpowiednie koordynaty
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
// zwraca przeciwny kierunek
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
    case -1:
        return -1;
        break;
    default:
        break;
    }
}
int move(mazeParams params,cords * moveCords,int * backDirection,node ** head,int startDirection){
    int countOfMoves=0;
    int countOfSteps=0;
    // robienie jednego kroku w zadanym kierunku 
    if(startDirection!=-1){
        makeStep(moveCords,startDirection);
        countOfSteps++;
        push_back(head,countOfSteps,startDirection);
        *backDirection=getAlternateDirection(startDirection);
        countOfMoves++;
    }
    countOfSteps=0;
    int direction=-1;

    int possibleDirections=0;
    do
    {
        //liczba dostępnych kierunków
        possibleDirections=0;
        // otrzymywanie bitowego wektoru z dostępnymi kierunkami
        unsigned int directions=availableDirections(params,*moveCords);
        for (int i = 0; i < 4; i++)
        {
            // obliczanie liczby dostępnych kierunków poprzez sprawdzanie czy nie byliśmy już w nim
            if(i!=*backDirection && TestBit(&directions,i,0,0)){
                direction = i;
                possibleDirections++;
            }
            
        }
        // jeżeli mamy dokładnie jeden dostępny kierunek , robimy jeden krok w go stronę
        if(possibleDirections==1 ){        
            makeStep(moveCords,direction);

            countOfSteps++;
            *backDirection=getAlternateDirection(direction);
        }
        // aktualizacja dostępnych kierunków
        directions =availableDirections(params,*moveCords);
        possibleDirections=0;
        for (int i = 0; i < 4; i++)
        {
            if(i!=*backDirection && TestBit(&directions,i,0,0)){
                possibleDirections++;
            }
            
        }
        // sprawdzanie czy jesteśmy w skręcie, jeżeli tak to zapizujemy kroki do listy
        if(possibleDirections<=1&&(TestBit(&directions,0,0,0)!=TestBit(&directions,1,0,0)) || (TestBit(&directions,2,0,0)!=TestBit(&directions,3,0,0))){

            countOfMoves++;

            push_back(head,countOfSteps,direction);

            countOfSteps=0;
        }
    } while (possibleDirections==1);
    clearCache(head);
    // zwracanie iłości kroków
    return countOfMoves; 
}



// funkcja rekurencyjna do poszukiwania najkrótszej ścieżki
// ważne parametry : params - do zapisywania najkrótszej ścieżki w minSteps, head- głowa listy liniowej zapisującej kroki,
// backDirection - kierunek z którego 'przyszliśmy'
void goByPath(mazeParams * params,node ** head,cords  currentCords,int backDirection){
    cords tmp = currentCords;
    int countOfMoves = move(*(params),&currentCords,&backDirection,head,getAlternateDirection(backDirection)); // przejście do najbliższego  rozgałęzienia za pomocą funkcji pomocniczej

    int steps= abs(tmp.x-currentCords.x)!=0?abs(tmp.x-currentCords.x):abs(tmp.y-currentCords.y); // wyliczanie liczby zrobionych kroków
    // Jeżeli doszliśmy do końca
    if(params->endCords.x==currentCords.x && currentCords.y==params->endCords.y){

        int listSteps=getSolutionSteps(); // wyliczanie liczby kroków w liście
        // sprawdzanie czy jest ścieżka najktótsza
        if(listSteps<params->minSteps || params->minSteps==0){
            params->minSteps=listSteps; // zapisywanie aktualnej najkrótszej ścieżki
            saveSolution(*params); // zapisywanie rozwiązania do pliku
        }
        // usuwanie kroków które zrobiliśmy dokąd szliśmy do tego rozgałęzienia
        pop_back(head,countOfMoves);
        return ;
    }
    // direction wszkazuje kierunek do względem do którego szliśmy, jeżeli jest równy -1 to nie zrobiliśmy żadnego kroku
    unsigned int directions=availableDirections(*(params),currentCords); // wyliczanie dostępnych kierunków jako tablice bitów [4]
    if(getBits(&directions,4)==2){

        return ;
    }

    // dfs 
    for (int i = 3; i >= 0; i--)
    {
        // cykl , w którym chodzimy w każdym kierunku , oprócz z którego przyszliśmy
        if(i!=backDirection && TestBit(&directions,i,0,params->cols)){
            
            tmp = currentCords;
            ClearBit(params->maze,currentCords.x,currentCords.y,params->cols); // oznaczenie odwiedzonego rozgałęzienia

            goByPath(params,head,tmp,getAlternateDirection(i)); // wywołanie rekurencji, jako backDirection dajemy przeciwny kierunek w którym zrobiliśmy jeden krok

            SetBit(params->maze,currentCords.x,currentCords.y,params->cols); // usuwanie oznaczenia odwiedzonego rozgałęzienia

        }
    }
    // usuwanie kroków które zrobiliśmy dokąd szliśmy do tego rozgałęzienia
    pop_back(head,countOfMoves);
}   
void printMaze(mazeParams params){
    for (int i = 0; i < params.rows; i++) {                 
        for (int j = 0; j<params.cols; j++) {
            if(TestBit(params.maze,j,i,params.cols)){
                printf(" ");
            }            
            else{
                printf("X");
            }
        }
        printf("\n");
    }
}
// znależienie rozwiązania labiryntu
void findSolution(mazeParams * params){
    params->minSteps=0;
    node* head = NULL;
    goByPath(params,&head,params->startCords,-1);
    if(params->minSteps==0){
        handleError(4);
    }
    else{
        printf("iłość kroków %d\n",params->minSteps);
    }    
}

