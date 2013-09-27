#ifndef _FIFO_H_
#define _FIFO_H_
#include"main.h"

extern struct timeval tpstart,tpend;
extern float timeuse;

extern int Search(int frames[],int frameNumber,int singlepage);
int FifoAlg(int n[],int m,int u);

#endif
