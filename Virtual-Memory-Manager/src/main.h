#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <getopt.h>

#define FRAMENUM 5
#define FIFO 0
#define LRU_CLOCK 1
#define LFU 2
#define LRU_STACK 3
#define LRU_REF8 4
#define MAX_FILE_NAME_LEN 10000
#define MAX_PAGE_NUM 1000000

int frameNumber,replaceAlg;
int pageNumber;
char inputFile[MAX_FILE_NAME_LEN];
int pageSequence[MAX_PAGE_NUM];
int replacePageNum,optReplacePageNum;
float penalty,algTime;
struct timeval tpstart,tpend;
float timeuse,rui,jie;
extern float opttimeuse;
extern char s[9];
int Search(int f[],int frameNumber,int singlepage);

#endif
