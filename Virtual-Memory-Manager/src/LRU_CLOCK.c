#include"main.h"
#include"LRU_CLOCK.h"



int LRUClockAlg(int pageSequence[],int pageNumber,int frameNumber)
{
    gettimeofday(&tpstart,NULL); // begin time
    int frames[frameNumber+1];
    int clock[frameNumber+1];
    int i=1,k=1,l=1;
	int count=0,r=0,temp;

	int flag=0;
	for(i=1;i<=frameNumber;i++) clock[i]=0;
	for(i=1;i<=frameNumber;i++) frames[i]=0;
	for(i=1;i<=pageNumber;i++)
    {
	    if(!Search(frames,frameNumber,pageSequence[i]))//find whether pageSequence[i] in frames
        {
	        if(count<frameNumber)
            {
                clock[k]=0;
		        frames[k]=pageSequence[i];
                k++;
		    	count++;                
            }
			else
            {
                
			    r++;
				flag=0;
			    while(!flag)
                {
			        if(clock[1]==0)
                    {
						for(l=1;l<frameNumber;l++)
                        {
                            frames[l]=frames[l+1];
                            clock[l]=clock[l+1];
                        }
  					    frames[frameNumber]=pageSequence[i];
                        clock[frameNumber]=0;
						flag=1;
                    }
					else
                    {
					    clock[1]=0;
						temp=frames[1];
						for(l=1;l<frameNumber;l++)
                        {
                            frames[l]=frames[l+1];
                            clock[l]=clock[l+1];
                        }
						frames[frameNumber]=temp;
                        clock[frameNumber]=0;
                    }
                }
            }
        }
		else
        {
            clock[Search(frames,frameNumber,pageSequence[i])]=1;
        }
      //         printf("frame: %d,%d,%d,%d,%d\n",frames[1],frames[2],frames[3],frames[4],frames[5]);

    }
    gettimeofday(&tpend,NULL);   // end time
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    return r;
}
