#include "help.h"
#include <stdio.h>

void displayHelp() {
    printf("Program invocation arguments\n");
    printf("-r	Reading a maze from a text/binary file\n");
    printf("-w	Saving the maze to a text/binary file\n");
    printf("-s	Solving the maze, finding the shortest path\n");
    printf("\n");
    printf("Error Messages\n");
    printf("The program is designed to detect errors both in the input provided by the user and during command execution. In case of an error, the program displays an appropriate message in the console, informing about the cause of the problem and possible steps to resolve it.\n");
    printf("\n");
    printf("Error: unknown command-line argument or incorrect usage of invoked arguments.\n");
    printf("This message indicates that the user provided a command-line argument that is not supported by the program or incorrectly used the given arguments. To display the description and usage of each argument, use the -h argument.\n");
    printf("\n");
    printf("Error: unable to open <maze.txt>.\n");
    printf("This message indicates that the program cannot read the file containing the maze provided by the user. This may be due to an incorrect file name, the absence of the file in the specified location, or insufficient permissions to read the file. Check the correctness of the file name, whether the file exists in the specified location, and whether you have the necessary permissions to read it.\n");
    printf("\n");
    printf("Error: the file <maze.txt> has an invalid format.\n");
    printf("This message informs that the file containing the maze provided by the user does not comply with the required format. Verify whether the maze file is compliant with the format and, if necessary, rewrite it according to the specified format.\n");
    printf("\n");
    printf("Error: the maze from the file <maze.txt> is unsolvable.\n");
    printf("This message indicates that the program is unable to find a solution for the maze defined by the user. This may be due to the lack of entrances and exits, too many walls, or no connection between entrance and exit points. Check if the maze is written in the correct format and if there is a possibility to navigate from the entrance to the exit.\n");
}
