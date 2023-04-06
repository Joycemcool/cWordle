//
// Created by joyce on 2023-03-30.
//
#include <stdio.h>
#include <stdbool.h>
#include "../inc/wordle.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//TODO

void green () {
    printf("\033[1;32m");
}

void yellow () {
    printf("\033[1;33m");
}

void reset () {
    printf("\033[0m");
}

//TAKE PARAMETERS FROM MAIN, ASSIGN VALUE AND DO THE MATCH IN THE FUNCTION.
char *wordleGame( char **gameBoard, int maxGuesses, int numOfLetter, char word[],bool *winFlag){

    //DECLARE MATCH FLAGS BOOL ARRAY
    bool matchFlags[maxGuesses][numOfLetter],existFlags[maxGuesses][numOfLetter];

    printf("Current game state:\n");

    //CREATE THE INITIAL GAMEBOARD.
    for (int i = 0; i < maxGuesses; i++) {
        for (int j = 0; j < numOfLetter; j++) {
            gameBoard[i][j] = '_';
        }
    }

    //OUTPUT ORIGINAL GAMEBOARD
    for (int i = 0; i < maxGuesses; ++i) {
        for (int j = 0; j < numOfLetter; ++j) {
            printf("%c ",gameBoard[i][j]);
        }
        printf("\n");
    }

    //INITIAL THE 2D MATCHFLAGS *2
    for (int i = 0; i < maxGuesses; i++) {
        for (int j = 0; j < numOfLetter; j++) {
            matchFlags[i][j] = false;
        }
    }

    for (int i = 0; i < maxGuesses; i++) {
        for (int j = 0; j < numOfLetter; j++) {
            existFlags[i][j] = false;
        }
    }




    //COMPARE AND SEE IF WIN
    for (int i = 0; i < maxGuesses; ++i) {//loop max guesses

        bool letterFlag;
        //PROMPT USER INPUT
        do{
            letterFlag=true;
        printf("Please enter a 5-letter word:\n");
        scanf("%s", gameBoard[i]);//TODO NEED VALIDATION?
            for (int j = 0; j < numOfLetter; ++j) {
                if(!isalpha(gameBoard[i][j])){
                    letterFlag=false;
                }
            }
            printf("Sorry, but you can only enter 5-letter words.\n");
        }while(!letterFlag);

        //DO THE MATCHES HERE
        for (int row = 0; row < maxGuesses; ++row) {

            for (int j = 0; j < numOfLetter; ++j) {


                if (toupper(gameBoard[row][j]) == toupper(word[j])) {
                    matchFlags[row][j] = true;
                }
                else {//check if exist but wrong place
                    for (int k = 0; k < numOfLetter; k++) {
                        if (toupper(gameBoard[row][j]) == toupper(word[k]) &&
                            !matchFlags[row][j]) {//position not match, yellow output USE ANOTHER 2D BOOL ARRAY FOR THIS
                            existFlags[row][j] = true;
                            break;
                        }
                    }

                }
                //FINISH COMPARE OUTPUT GAMEBOARD
                if (matchFlags[row][j]) {
                    green();
                } else if (existFlags[row][j]) {
                    yellow();
                } else { reset(); }
                printf("%c ", toupper(gameBoard[row][j]));

                //TODO CHECK IF IT SHOULD BE IN THIS POSITION
            }
//            word[numOfLetter] = '\0';
            printf("\n");

        }


//        gameBoard[i][numOfLetter] = '\0';
        int countCorrect=0;
        for (int j = 0; j <numOfLetter ; ++j) {
            if (toupper(gameBoard[i][j])!= toupper(word[j])){
                break;
            }
            if(j==4){
                *winFlag = true;
            }

        }
        if(*winFlag){//TODO WHY HAS TO USE POINTER ASTRICK HERE?
        break;}

    }
    return gameBoard;
}
    //OUTPUT FILE IN MAIN

