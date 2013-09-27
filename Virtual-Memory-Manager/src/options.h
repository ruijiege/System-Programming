#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "main.h"

extern int frameNumber,replaceAlg;//frame number and replace policy
extern int pageNumber;//the number of page in the page sequence
extern char inputFile[MAX_FILE_NAME_LEN];//To store the file-name (including the address)
extern int pageSequence[MAX_PAGE_NUM];//To store the page sequence(not include " ")
extern int replacePageNum,optReplacePageNum;
extern float penalty;

int flen;//the length of the file not the page sequence
int i;
char s[9]; //To store the string of replace-policy. FIFO as a default
char *d;
char buf[10000];//To store the page sequence

struct stat attri;

int options(int argc, char* argv[]);
int GetPage(int n[],char* buf);
void init_opt();
void storebuf(char* buf);

#endif
