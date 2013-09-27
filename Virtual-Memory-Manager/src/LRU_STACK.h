#ifndef _LRU_STACK_H_
#define _LRU_STACK_H_
#include"main.h"

extern struct timeval tpstart,tpend;
extern float timeuse;

extern int Search(int frames[],int frameNumber,int singlepage);
int LRUStackAlg(int pageSequence[],int pageNumber,int frameNumber);

#endif
