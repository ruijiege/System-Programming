#include "main.h"
#include "options.h"
#include "optimal.h"
#include "FIFO.h"
#include "LFU.h"
#include "LRU_CLOCK.h"
#include "LRU_STACK.h"
#include "LRU_REF8.h"

int main(int argc, char* argv[])
{

    if(!(options(argc,argv)))
    {
        printf("Can't get your input command!\n");
        return 0;
    }
    
	if(replaceAlg==FIFO)
	    replacePageNum=FifoAlg(pageSequence,pageNumber,frameNumber);
    else if(replaceAlg==LRU_REF8)
        replacePageNum=LRUREF8Alg(pageSequence,pageNumber,frameNumber);
    else if(replaceAlg==LRU_STACK)
        replacePageNum=LRUStackAlg(pageSequence,pageNumber,frameNumber);
    else if(replaceAlg==LRU_CLOCK)
	    replacePageNum=LRUClockAlg(pageSequence,pageNumber,frameNumber);
	else if(replaceAlg==LFU)
        replacePageNum=LFUAlg(pageSequence,pageNumber,frameNumber);
    optReplacePageNum=OptAlg(pageSequence,pageNumber,frameNumber);

    algTime=100*(opttimeuse-timeuse)/opttimeuse;
	printf("\n# of page replacements with %s : %d",s,replacePageNum);
	printf("\n# of page replacements with Optimal : %d",optReplacePageNum);
    rui=(float)replacePageNum;
	jie=(float)optReplacePageNum;
	penalty=((rui-jie)/jie)*100;
	printf("\n%% page replacement penalty using %s : %.1f%%\n",s,penalty);
    printf("\nTotal time to run %s algorithm :%.f msec",s,timeuse);
    printf("\nTotal time to run Optimal algorithm :%.f msec",opttimeuse);
    printf("\n%s is %.1f%% faster than Optimal algorithm.\n\n",s,algTime);
    
    return 0;
}


int Search(int f[],int frameNumber,int singlepage)
{
    int i=1;
	while(i<=frameNumber)
    {
	    if(f[i]==singlepage) return i;
        i++;
    }
	return 0;
}
