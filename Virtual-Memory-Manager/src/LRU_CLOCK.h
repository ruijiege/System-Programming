#ifndef _LRU_CLOCK_H_
#define _LRU_CLOCK_H_
#include"main.h"

extern struct timeval tpstart,tpend;
extern float timeuse;



extern int Search(int frames[],int frameNumber,int singlepage);
int LRUClockAlg(int pageSequence[],int pageNumber,int frameNumber);

#endif
