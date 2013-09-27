#include"main.h"
#include"FIFO.h"

int FifoAlg(int pageSequence[],int pageNumber,int frameNumber)
{
    gettimeofday(&tpstart,NULL); // begin time
    int i=1,j=1,k=1;
	int count=0,r=0;
	int frames[frameNumber+1];
	for(i=1;i<=frameNumber;i++) frames[i]=0;
	for(i=1;i<=pageNumber;i++)
    {
	    if(!Search(frames,frameNumber,pageSequence[i]))
        {
	        if(count<frameNumber)
            {
		        frames[k]=pageSequence[i];k++;
		    	count++;
            }
			else
            {
			    r++;
			    for(j=1;j<frameNumber;j++)
				    frames[j]=frames[j+1];
				frames[frameNumber]=pageSequence[i];
            }
		}
    }
    //	printf("%d,%d,%d,%d,%d",frames[1],frames[2],frames[3],frames[4],frames[5]);
    gettimeofday(&tpend,NULL);   // end time
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    return r;
}
