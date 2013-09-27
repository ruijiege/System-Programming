#include"main.h"
#include"optimal.h"

int Search2(int record[],int frameNumber,int singlepage)
{
    int i=0;
	while(i<frameNumber-1)
    {
	    if(record[i]==singlepage)
        {
           return 0;
        }
        i++;
    }
    return singlepage;
}

int OptAlg(int pageSequence[],int pageNumber,int frameNumber)
{
    gettimeofday(&opttpstart,NULL); // begin time
    int count=0;
    int cnt=0;
    int flag=0;
    int r=0;
    int k=1;
    int m,n,rp,from,i,j;
    int record[frameNumber-1];
    for (m=0; m<frameNumber-1; m++) {record[m]=0;}
    
    int forsearch[frameNumber+1];
    for (n=0; n<frameNumber; n++) {forsearch[n]=n+1;}
    
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
                from=i+1;
                j=0;
                while ((cnt<frameNumber-1)&&(from<=pageNumber))
                {

                    flag=0;
                    
                    if (Search(frames,frameNumber,pageSequence[from]))
                    {
                       
                        for (m=0; m<frameNumber-1; m++)
                        {
                            if (record[m]==Search(frames,frameNumber,pageSequence[from]))
                            {
                                flag=1;
                            }
       //                    printf("***record[%d]=%d\n",m,record[m]);

                        }
                        
                        if (flag==0)
                        {
                            record[j]=Search(frames,frameNumber,pageSequence[from]);
                            //                      printf("record[%d]=%d\n",j,record[j]);
                            j++;
                            cnt++;
 //                           printf("cnt=%d\n",cnt);
                        }
                        from++;
                    }
                    else
                    {
                        from++;
                    }
                }
 //               printf("cnt=%d\n",cnt);
 //               for (m=0; m<5; m++)
   //             {
     //               printf("record[%d]:%d forsearch[%d]:%d\n",m,record[m],m,forsearch[m]);
       //         }
                
                if (cnt==(frameNumber-1))
                {
                    cnt=0;
                    for (m=0; m<frameNumber; m++)
                    {
                        
                        rp=Search2(record,frameNumber,forsearch[m]);
           //             printf("rp=%d\n",rp);
                        if (rp)
                        {
                            frames[rp]=pageSequence[i];
                        }
                    }
                    for (m=0; m<frameNumber-1; m++) {record[m]=0;}

                }
                else
                {
                    cnt=0;
                    for (m=0; m<frameNumber; m++)
                    {
                        
                        rp=Search2(record,frameNumber,forsearch[m]);
                        //             printf("rp=%d\n",rp);
                        if (rp)
                        {
                            frames[rp]=pageSequence[i];
                        }
                    }
                    for (m=0; m<frameNumber-1; m++) {record[m]=0;}
                }
            }
        }
//       printf("frame: %d,%d,%d,%d,%d\n",frames[1],frames[2],frames[3],frames[4],frames[5]);
	}
    gettimeofday(&opttpend,NULL);   // end time
    opttimeuse=1000000*(opttpend.tv_sec-opttpstart.tv_sec)+opttpend.tv_usec-opttpstart.tv_usec;
    
    return r;
}
