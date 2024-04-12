typedef struct cords
{
    int x;
    int y;
} cords;
typedef struct mazeParams
{
    unsigned int * maze;
    int cols; //liczba kolumn(od 1)
    int rows; //liczba wierszy (od 1)
    cords endCords; // koordynaty końca (od 0)
    cords startCords;// koordynaty początku (od 0)
    int minSteps; // minimalna liczba kroków do rozwiązania labiryntu, jest wykorzystana przy wyszukiwaniu najkrótszej ścieżki
    
    char* originFileName; // nazwa pliku labiryntu
    char* solutionFileName; // nazwa pliku rozwiązania
    char solutionType; // typ rozwiązania
} mazeParams;