#ifndef _SIMDISK_H_
#define _SIMDISK_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CYLINDERNUM 200
#define FCFS 0
#define SSTF 1
#define CSCAN 2
#define LOOK 3
#define FILELEN 500
#define REQLEN 500

int userCylinderNum,userPolicy;
int reqNum;
int totalTrvld;

char userInput[FILELEN];
int reqSeq[REQLEN];
int schedSeq[REQLEN];

int FCFSSched(int n[REQLEN], int m[REQLEN], int num);
int SSTFSched(int n[REQLEN], int m[REQLEN], int num);
int CSCANSched(int n[REQLEN], int m[REQLEN], int num, int cylinders);
int LOOKSched(int n[REQLEN], int m[REQLEN], int num);
int FileToInt(int n[REQLEN],char* buf,int num);
int StdToInt(int n[REQLEN],char* buf,int num);


#endif
