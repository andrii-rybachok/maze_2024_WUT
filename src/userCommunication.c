#include "userCommunication.h"


// Wyświetla komunikat na podany typ(kod) błędu i przerywa działąnie programu
void handleError(int errorType){
    switch (errorType)
    {
        case 1:
            fprintf(stderr,"1.Błąd: nieznany argument wywołania lub nieprawidłowe wykorzystanie wywołanych argumentów.");
            break; 
        case 2:
            fprintf(stderr,"2.Błąd: nie można otworzyć plik labiryntu");
            break; 
        case 3:
            fprintf(stderr,"3.Błąd: plik labiryntu ma nieprawidłowy format.u");
            break; 
        case 4:
            fprintf(stderr,"4. Błąd: labirynt jest nierozwiązywalny");
            break;
        case 5:
            fprintf(stderr,"5. Nie można otwórzyć lub stworzyć plik rozwiązania");
            break;  
        case 6:
            fprintf(stderr,"6. Podane rozszerzenie pliku rozwiązania jest nieobsługiwane");
            break;
        case 7:
            fprintf(stderr,"7. Podane rozszerzenie pliku labiryntu jest nieobsługiwane");
            break;
    default:
        break;
    }
    printf("\n");
    exit(EXIT_FAILURE);
}
void printHelp(){
    printf("Tu użytkownik dostanie pomóc przy nieprawidłowym uruchamianiu programu lub podaniu argumentu -h \n");
}