#ifndef _OPTIMAL_H_
#define _OPTIMAL_H_
#include"main.h"

struct timeval opttpstart,opttpend;
float opttimeuse;


extern int Search(int frames[],int frameNumber,int singlepage);
int Search2(int record[],int frameNumber,int singlepage);
int OptAlg(int n[],int m,int u);

#endif
