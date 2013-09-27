#include"main.h"
#include"LRU_STACK.h"



int LRUStackAlg(int pageSequence[],int pageNumber,int frameNumber)
{
    gettimeofday(&tpstart,NULL); // begin time
    int i=1,k=frameNumber,l=1;
	int count=0,r=0,temp,add=0;
	int frames[frameNumber+1];
	for(i=1;i<=frameNumber;i++) frames[i]=0;

	for(i=1;i<=pageNumber;i++)
    {
	    if(!Search(frames,frameNumber,pageSequence[i]))//find whether pageSequence[i] in frames
        {
	        if(count<frameNumber)
            {
		        frames[k]=pageSequence[i];k--;
		    	count++;
            }
			else
            {
			    r++;
                for(l=frameNumber;l>0;l--)
                {
                    temp=frames[l-1];
                    frames[l]=temp;
                }
                frames[1]=pageSequence[i];
            }
        }
		else
        {
            add=Search(frames,frameNumber,pageSequence[i]);
            temp=frames[add];
            for(l=add;l>0;l--)
            {
                temp=frames[l-1];
                frames[l]=temp;
            }
            frames[1]=pageSequence[i];
        }
 //       printf("frame: %d,%d,%d,%d,%d\n\n",frames[1],frames[2],frames[3],frames[4],frames[5]);

    }

    gettimeofday(&tpend,NULL);   // end time
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    return r;
}