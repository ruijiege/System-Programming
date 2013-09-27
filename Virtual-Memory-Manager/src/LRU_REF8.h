#ifndef _LRU_REF8_H_
#define _LRU_REF8_H_
#include"main.h"

extern struct timeval tpstart,tpend;
extern float timeuse;

extern int Search(int frames[],int frameNumber,int singlepage);
int LRUREF8Alg(int pageSequence[],int pageNumber,int frameNumber);

#endif