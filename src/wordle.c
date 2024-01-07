//
// Created by Xiaoxia.Ding 2023-3-30.
//
#include <stdio.h>
#include <stdbool.h>
#include "../inc/wordle.h"
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>

void green () {
    printf("\033[1;32m");
}

void yellow () {
    printf("\033[1;33m");
}

void reset () {
    printf("\033[0m");
}

char stringResponse[4096]="";

static size_t
WriteMemoryCallback1(void *contents, size_t size, size_t nmemb, void *userp){
    sprintf(stringResponse,"%s",contents);
}
//STRUCT TO STORE THE VALUE FROM WEBSITE
struct MemoryStruct {
    char *memory;
    size_t size;
};

//FUNCTION TO PASS VALUE TO MEMORY?
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
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

        bool letterFlag,numInput;
        char tempWord[20];
        //PROMPT USER INPUT AND VALIDATE IF LETTERS
        do{
            letterFlag=true;numInput=true; //INITIALIZE TWO BOOL VARIABLES
            printf("Please enter a %i-letter word:\n",numOfLetter);
            scanf("%s", tempWord);
            //CHECK IF CORRECT NUMBER OF LETTER
            if(strlen(tempWord)!=numOfLetter) {
                numInput=false;}
            else {//CHECK IF ALL LETTER
                for (int j = 0; j < numOfLetter; ++j) {
                    if (!isalpha(tempWord[j])){
                        letterFlag = false;
                    }
                }
            }
            //DO THE MATCHES HERE
            //IF CORRECT NUMBER OF LETTER AND REAL WORD, GAMEBOARD REPLACE.
            if(numInput&&letterFlag&& checkRealWord(tempWord)) {
                    printf("Current game state:\n");
                    strcpy(gameBoard[i], tempWord);
                    for (int row = 0; row < maxGuesses; ++row) {
                        for (int j = 0; j < numOfLetter; ++j) {
                            if (toupper(gameBoard[row][j]) == toupper(word[j])) {
                                matchFlags[row][j] = true;
                            } else {//check if exist but wrong place
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

                            //CHECK IF IT SHOULD BE IN THIS POSITION
                        }
                        printf("\n");
                    } //FINISH COMPARISON

                    // CHECK IF WIN
                    int countCorrect = 0;
                    for (int j = 0; j < numOfLetter; ++j) {
                        if (toupper(gameBoard[i][j]) != toupper(word[j])) {
                            break;
                        }
                        if (j == numOfLetter - 1) {
                            *winFlag = true;
                        }
                    }
                    if (*winFlag) {
                        break;
                    }
            }

            //IF NOT CORRECT NUMBER AND ALL LETTER, OUTPUT AND DO WHILE LOOP.
            else{
                if(!letterFlag)printf("Sorry, but you can only enter letter\n");
                else if(!numInput)printf("Sorry, but you can only enter %i-letter\n", numOfLetter);
                else if(!checkRealWord(tempWord))printf("Sorry, please enter a real word\n");
//                printf("Sorry, but you can only enter %i-letter real words.\n",numOfLetter);

            }

        }while(!letterFlag||!numInput|| !checkRealWord(tempWord));

        if(*winFlag){
            break;}
    }
    return (char *) gameBoard;
}
//OUTPUT FILE IN MAIN

//FUNCTION TO CHECK IF A REAL WORD
bool checkRealWord(char inputWord[]) {
    CURL *curl;
    CURLcode response;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */
    
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();//INITIALIZE
    char checkWord[150];

    strcpy(checkWord,"https://api.dictionaryapi.dev/api/v2/entries/en/");
    strcat(checkWord,inputWord);
    char stringHeader[256];
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, checkWord);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);//make an HTTPS request with SSL/TLS certificate verification disabled
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);//SEND ALL DATA TO THE FUNCTION
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);//PASS CHUNK STRUCT TO THE CALLBACK FUNCTION
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");//Use a user agent

        response = curl_easy_perform(curl);

        if (response != CURLE_OK) {
            fprintf(stderr, "Not a real word\n", curl_easy_strerror(response));
//            return false;
        } else {
            char notExist[30];
            char *ret;
            strcpy(notExist, "No Definitions Found");
            char toBeScanned[4096];
            strcpy(toBeScanned, chunk.memory);
            ret = strstr(toBeScanned, notExist); //p==null, a real word, return true

            if (ret != NULL) {
                return false;
            }
        }
        curl_easy_cleanup(curl);
    }

    free(chunk.memory);
    curl_global_cleanup();

    return true;
}