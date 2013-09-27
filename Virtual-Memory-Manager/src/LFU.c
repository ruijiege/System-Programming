#include"main.h"
#include"LFU.h"

int LFUAlg(int pageSequence[],int pageNumber,int frameNumber)
{//use the code on the internet as a reference.
    gettimeofday(&tpstart,NULL); // begin time
    int i=1,j=1,k=1;
	int cnt=0,r=0,p=0,mark=0,addinfo=0;
	int f[frameNumber+1];
	int showtime[frameNumber+1];//reprsent the kth page in pagesequence, the later show page the bigger of showtime
	int same[frameNumber+1];
	int countr[1000000];
	int min;
	int min2;
	for(i=1;i<=pageNumber;i++) countr[i]=0;
	for(i=1;i<=frameNumber;i++) f[i]=0;//init frames
	for(i=1;i<=pageNumber;i++)
    {
	    if(!Search(f,frameNumber,pageSequence[i]))//find whether pageSequence[i] in f
        {
	        if(cnt<frameNumber)
            {
		        f[k]=pageSequence[i];
				showtime[k]=k;k++;//showtime[1]=1,showtime[2]=2,showtime[3]=3,showtime[4]=4,showtime[5]=5,
		    	cnt++;
            }
			else
            {
			    r++;
			    min=countr[f[1]];
			    for(j=1;j<=frameNumber;j++)
                {
                    addinfo=0;
				    if(countr[f[j]]<min)//to find the page in the frame with the smallest countr mumber
                    {
					    min=countr[f[j]]; p=j;
                    }
                }
                if (addinfo)
                {
                    printf("show star *");
                }
				for(j=1;j<=frameNumber;j++)
                {
                    addinfo=0;
				    if(countr[f[j]]==min)//if there are more than 1 same  min countr number
                    {
					    same[mark]=j;// mark which frame has the same countr number to same
						mark++;
                    }
                }
                if (addinfo)
                {
                    printf("show star *");
                }
				if(mark>1)//if there only one min countr, replace it directly
                {
                    min2=showtime[same[0]];
				    for(j=0;j<mark;j++)// among the number of lables same countr page in the farme ,
                    {
					    if(showtime[same[j]]<min2)//find the smallest showtime, which means that this page in the frame show earliest
                        {
						    min2=showtime[same[j]];
							p=same[j];//replace the page with min showtime
                        }
                    }
                }
                mark=0;
				f[p]=pageSequence[i];
				showtime[p]=k;
				k++;
            }
        }
		countr[pageSequence[i]]++;
	}
    gettimeofday(&tpend,NULL);   // end time
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    
    return r;
}