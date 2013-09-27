#ifndef _LFU_H_
#define _LFU_H_
#include"main.h"

extern struct timeval tpstart,tpend;
extern float timeuse;

extern int Search(int frames[],int frameNumber,int singlepage);
int LFUAlg(int pageSequence[],int pageNumber,int frameNumber);

#endif
