#include"main.h"
#include"LRU_REF8.h"

int LRUREF8Alg(int pageSequence[],int pageNumber,int frameNumber)
{
    gettimeofday(&tpstart,NULL); // begin time
    int i=1,k=1,j=1;
    int min,mint,add2,m;
	int count=0,r=0,add=0,mark=0,cnt=0;
	int frames[frameNumber+1];
	unsigned int ref[pageNumber+1];
    
    int pageshowtime[frameNumber+1];
    for(i=1;i<=frameNumber;i++) pageshowtime[i]=0;//init pageshowtime
	for(i=1;i<=frameNumber;i++) ref[i]=0;
	for(i=1;i<=frameNumber;i++) frames[i]=0;
	for(i=1;i<=pageNumber;i++)
    {
	    if(!Search(frames,frameNumber,pageSequence[i]))//find whether pageSequence[i] in frames
        {
//            printf("*pageSequence[%d]=%d\n",i,pageSequence[i]);
	        if(count<frameNumber)
            {
		        frames[k]=pageSequence[i];
		    	count++;
                for (j=1; j<=frameNumber; j++)//value of the each page number must smaller than 100
                {
                    ref[j]=ref[j]>>1;
                }
                ref[k]=ref[k]|0x0080;k++;
                pageshowtime[cnt]=cnt;cnt++;
            }
			else
            {
			    r++;
                
                mint=ref[1];
                mark=1;
                for (j=1; j<=frameNumber; j++)
                {
                    if(ref[j]<mint)
                    {
                        mint=ref[j];
                        add2=j;
                        min=pageshowtime[add2];
                        mark=j;
                    }
                }
                
                for (m=1; m<=frameNumber; m++)
                {
                    if (mint==ref[m])
                    {
                        if (pageshowtime[m]<min)
                        {
                            min=pageshowtime[m];
                            mark=m;
                        }
                    }
                    //printf("mint=%d\n",mint);
                }
                
                frames[mark]=pageSequence[i];
                for (j=1; j<=frameNumber; j++)//value of the each page number must smaller than 100
                {
                    ref[j]=ref[j]>>1;
                }
                ref[mark]=ref[mark]|0x0080;
             				//	printf("%d frame: %d,%d,%d,%d,%d\n",r,frames[1],frames[2],frames[3],frames[4],frames[5]);
            }
        }
		else
        {
            add=Search(frames,frameNumber,pageSequence[i]);
            for (j=1; j<=frameNumber; j++)//value of the each page number must smaller than 100
            {
                ref[j]=ref[j]>>1;
            }
            ref[add]=ref[add]|0x0080;
            
            pageshowtime[add]=cnt;
            //        printf("cnt: %d,%d,%d,%d,%d\n",pageshowtime[1],pageshowtime[2],pageshowtime[3],pageshowtime[4],pageshowtime[5]);
            cnt++;
        }
//        printf("%d frame: %d,%d,%d,%d,%d\n",r,frames[1],frames[2],frames[3],frames[4],frames[5]);
  //      printf("ref:      %d,%d,%d,%d,%d\n\n",ref[1],ref[2],ref[3],ref[4],ref[5]);
    }
    gettimeofday(&tpend,NULL);   // end time
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    return r;
}