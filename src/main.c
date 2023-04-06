#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "../inc/wordle.h"

#define MAX_NUM_OF_WORDS 100

/*
 * NOTE: Follow this example to use ANSI colours at the terminal:
 * https://www.theurbanpenguin.com/4184-2/
 *
 * In order to get ANSI colors showing in the CLion Run Console,
 * we need to do the following routine:
 *
 * 1. Choose Help -> Edit Custom Properties from CLion menu
 * 2. Add the following line to the idea.properties file:
 *      run.processes.with.pty=false
 * 3. Restart CLion.
 *
 * Reference:
 * https://youtrack.jetbrains.com/issue/CPP-8395/Registry-setting-runprocesseswithpty-not-saved#focus=Comments-27-2499735.0-0
 *
 */

//source https://www.theurbanpenguin.com/4184-2/

int main(int argc, char *argv[]) {
    setbuf(stdout,0);
    char **gameBoard;//two d array need two pointer symbol?
    //2d array
//    char** wordslist = calloc (MAX_NUM_OF_WORDS,sizeof (char*));
    bool winFlag = false;
    char inputFile[20],outputFile[20];
    char writeMessage[MAX_NUM_OF_WORDS];

    //VALIDATE IF CORRECT ARGUMENT NUMBER
    if(argc==5){//If the argument number is right
        if((strcmp(argv[1],"-i")==0&&strcmp(argv[3],"-o")==0)||(strcmp(argv[1],"-o")==0&&strcmp(argv[3],"-i")==0)){

        }

        else{//if the second and fouth argument is not valid output error message
            fprintf(stderr,"Invalid command line argument usage.");
            return 1;
        }
        //Finish the first validation, proceed the game.
        // argv[2] inputfile or output file argv[4] input file or output file

        if((strcmp(argv[1],"-i")==0&&strcmp(argv[3],"-o")==0)){

            strcpy(inputFile,argv[2]);
            strcpy(outputFile,argv[4]);
        }

        else {
            strcpy(inputFile,argv[4]);
            strcpy(outputFile,argv[2]);
        }

        //READ FILE HANDLER
        FILE *wordsFile = fopen(inputFile,"r");
        FILE *writeFile = fopen(outputFile,"w");

        //READ FILE HANDLER GET THREE CHARACTER ARRAY
        char numOfLetter[3],maxGuesses[3],word[20];

        if(wordsFile==NULL){
            fprintf(stderr,"Cannot open %s for reading.",inputFile);
            return 1;
        }

        if(writeFile==NULL){
            fprintf(stderr,"Cannot open %s for writing.",outputFile);
            return 1;
        }
        printf("Welcome to C-Wordle!!\n");

        fscanf(wordsFile,"%s %s %s", numOfLetter,maxGuesses,word);

        //TODO CONVERT THE MAXGUESS AND NUMOFLETTER INTO DIGIT.
        int numOfGuess = atoi(maxGuesses);
        int wordLength = atoi(numOfLetter);

        //TODO DYNAMICALLY ALLOCATE AN ARRAY
        gameBoard = (char **)malloc(sizeof(char *)*numOfGuess);

        for (int count = 0; count < numOfGuess; count++)
        {
            gameBoard[count] = (char *)malloc(sizeof(char)*wordLength);
        }

        //TODO LOAD THE ELEMENTS IN THE GAMEBOARD IN THE FUNCTION.THE GAMEBOARD HAS TO BE PRINTED IN THE FUNCTION

        wordleGame(gameBoard,numOfGuess,wordLength,word,&winFlag);
        //TODO WHY NEED & HERE?


        if(winFlag){
            printf("You WIN!!!\n");
            strcpy(writeMessage, "The solution was found.");
            }
        else{
            strcpy(writeMessage, "The solution was not found.");
            printf("You LOSE!!!\n");
        }


        int count=0;
        while(writeMessage[count] != '\0') {
           // fprintf(writeFile, "test\n");
           putc(writeMessage[count], writeFile);
           count++;
        }

//        writeFile = fopen(outputFile,"a");
        for (int i = 0; i < numOfGuess; ++i) {
            fprintf(writeFile, "\n");
            for (int j = 0; j < wordLength; ++j) {
                putc(toupper(gameBoard[i][j]),writeFile);
                putc(' ', writeFile);
            }
        }

        printf("The game result was written to the %s\n",outputFile);


        //TODO FREE MALLOC MEMORY

        fclose(wordsFile);
        fclose(writeFile);

        for (int row = 0; row < numOfGuess; row++)
        {
            free(gameBoard[row]);
        }

        free(gameBoard);

    }

    else{//TODO WHY THIS LINE CANNOT REACH
        fprintf(stderr,"Invalid number of command line arguments.");
        return 1;
    }

    return 0;

}
