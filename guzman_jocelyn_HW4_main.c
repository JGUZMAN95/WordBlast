/**************************************************************
* Class:  CSC-415-0# Summer 2021
* Name: Jocelyn Guzman
* Student ID: 915040482
* GitHub ID:JGUZMAN95
* Project: Assignment 4 – Word Blast
*
* File: guzman_jocelyn_HW4_main.c
*
* Description:
*
**************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>




// You may find this Useful
//char * delim = "\"\'.“”‘’?:;-,—*($%)! \t\n\x0A\r";


#define MAXWORDS 10
#define MINCHARS 6

char *fileName;

struct wordCount{
    char *word;
    int wordApperance;
    int count;
} *wordEntry;

struct BlockInfo{
    long startOfBlock;
    long sizeOfBlock;
} *blockInfo;

struct topTen{
    char word;
    int wordCount;
} *topTen;

//1. count tally each word that is 6 or more characters long
void *runThread(void *ptr){
    long i;
    i = (long) ptr;
    printf("\ni vaule %ld\n", i);

    printf("blockprint%ld\n",blockInfo[i].sizeOfBlock);
    char buffer[blockInfo[i].sizeOfBlock];
    char temp[1];
    char word[] = {'\0'};
    int fd = open(fileName,O_RDONLY);

    wordEntry->count = 0;
    int count = wordEntry->count;

    //int re =
   // printf("read %d\n",re);
    int start = blockInfo[i].startOfBlock;
    int end = blockInfo[i].startOfBlock +blockInfo[i].sizeOfBlock;
    int copy =0;
    int n;
    lseek(fd,start, SEEK_SET);
    while ((n = read(fd,buffer,1)) > 0) {
        strcpy(temp, buffer);
        char *delim = " ";

        if (isalpha(*temp) != 0) {
            strcpy(&word[copy], temp);
            copy++;
            //printf("%s\n",word);
            //printf("%s\n",temp);
        } else {
            if (copy >= MINCHARS) {
                //printf("%s\n", word);
                int found = 0;
                int j = 0;
                while (found != 1) {
                    if (count == 0) {
                        wordEntry[j].word = word;
                        wordEntry[j].wordApperance = 1;
                        wordEntry->count++;
                        found = 1;
                    } else {
                        int value = strcmp(wordEntry[j].word, word);

                        if (value == 0) {
                            wordEntry[j].wordApperance++;
                            found = 1;

                        } else if (j == wordEntry->count - 1) {
                            wordEntry[j].word = word;
                            wordEntry[j].wordApperance = 1;
                            wordEntry->count++;
                            found = 1;
                        } else if (j < wordEntry->count) {
                            j++;
                        }

                    }

                }

            }
            copy =0;
            memset(word,0, sizeof word);
            }

    }
   close(fd);
}

int main (int argc, char *argv[]) {
    //***TO DO***  Look at arguments, open file, divide by threads
    //             Allocate and Initialize and storage structures
    if (argc != 3) {
        printf("Proper usage is: filename threadCount\n");
        return -1;
    }

    int fd;

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("File Does Not Exist.\n");
        return -1;
    }else{
        fileName = argv[1];
        printf("%s\n",fileName);
    }

    int threadCount = atoi(argv[2]);

    if (threadCount <= 0) {
        perror("Need number larger than 0\n");
        return -1;
    }
    printf("count %d\n", threadCount);

    //allocating
    blockInfo = (struct BlockInfo *) malloc(sizeof(struct BlockInfo) * threadCount);
    wordEntry = malloc(sizeof (struct wordCount));
    topTen = (struct topTen *) malloc(sizeof(struct topTen) * MAXWORDS);


    //first we need size of file
    long fileSize = lseek(fd, 0, SEEK_END);
    printf("%ld\n",fileSize);
    close(fd);

    for (int i = 0; i < threadCount; i++) {

        //then we divede by the number of threads
        blockInfo[i].startOfBlock = fileSize / threadCount * i;
        printf("start %ld\n ",blockInfo[i].startOfBlock);

        //then we assign every thread to a section
        if (i == threadCount - 1) {
            blockInfo[i].sizeOfBlock = fileSize - blockInfo[i].startOfBlock;
            printf("sizeofblock %ld\n",blockInfo[i].sizeOfBlock);

        } else {
            blockInfo[i].sizeOfBlock = fileSize / threadCount;
            printf("sizeofblock else %ld\n",blockInfo[i].sizeOfBlock);

        }
    }

    //**************************************************************
    // DO NOT CHANGE THIS BLOCK
    //Time stamp start
    struct timespec startTime;
    struct timespec endTime;

    clock_gettime(CLOCK_REALTIME, &startTime);
    //**************************************************************


    // *** TO DO ***  start your thread processing
    //                wait for the threads to finish
    pthread_t threads[threadCount];

    int i = 0;

    for(i = 0; i < threadCount; i++) {
        pthread_create(&threads[i], NULL, &runThread, (void*)i);

    }

    for (i = 0; i < threadCount; i++) {
        pthread_join(threads[i], NULL);
    }

    //for (i = 0; i < wordEntry->count ; i++) {
        //printf("Total: %s words, %d wordAppearance\n",
          //     wordEntry[3].word, wordEntry[3].wordApperance);
    //}

    // ***TO DO *** Process TOP 10 and display

//in main 10 words with 6 characters or more will be printed
//word must have the highest tallies
//must be in order from highest to lowest
//must also contain count of the word

    for (i = 0; i < MAXWORDS; i++) {
        topTen[i].wordCount = 0;
    }

    for (i = 0; i < wordEntry.count; i++) {

        if (wordEntry[i].wordApperance > topTen[MAXWORDS - 1].count) { //goes into top 10
            top10[TOP - 1].word = wordList[j].word;
            top10[TOP - 1].count = wordList[j].count;

            for (int k = TOP - 2; k >= 0; k--) {
                if (wordList[j].count > top10[k].count) {
                    top10[k + 1].word = top10[k].word;
                    top10[k + 1].count = top10[k].count;
                    top10[k].word = wordList[j].word;
                    top10[k].count = wordList[j].count;
                }
            }
        }
    }


            //**************************************************************
            // DO NOT CHANGE THIS BLOCK
            //Clock output
            clock_gettime(CLOCK_REALTIME, &endTime);
            time_t sec = endTime.tv_sec - startTime.tv_sec;
            long n_sec = endTime.tv_nsec - startTime.tv_nsec;
            if (endTime.tv_nsec < startTime.tv_nsec) {
                --sec;
                n_sec = n_sec + 1000000000L;
            }

            printf("Total Time was %ld.%09ld seconds\n", sec, n_sec);
            //**************************************************************


            // ***TO DO *** cleanup

            free(blockInfo);
            free(wordEntry);
            free(topTen);

            blockInfo = NULL;
            wordEntry = NULL;
            topTen = NULL;

    }