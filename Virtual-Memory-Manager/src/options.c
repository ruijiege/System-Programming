#include "options.h"
#include "main.h"
/****************************************************/
//init the data
void init_opt()
{
    bzero(s,sizeof(s));
    strcpy(s,"FIFO");//default replace-policy=FIFO
    bzero(buf,sizeof(buf));
    frameNumber=FRAMENUM;//default frame naumber=5
	replaceAlg=FIFO;
    
    
}
/****************************************************/

int options(int argc,char **argv)
{
    init_opt();
    int c,i;
    char ch;
    int stdin_flag=1,bufcnt=0;
    i=1;
    opterr=0;
    bzero(buf,sizeof(buf));
    while ((c = getopt(argc, argv, "hr:f:i:")) != -1)
    {
            switch(c)
            {
                case 'h':
                    printf("\nOptions you can choose:\n");
                    printf("-h : Print a usage summary with all options and exit.\n");
                    printf("-f You can set your own frame number,the default value of frame number is 5.\n");
                    printf("-r You can set your own replacement-policy from here.You have the options of FIFO LRU_CLOCK  LRU_STACK, LRU_REF8, and LFU. The default replacement-policy is FIFO.\n");
                    printf("-i You can set your own input file frome here.If you don't use the option, then please input the page sequrenc from keyboard.\n\n");
                    exit(0);
                    break;
                case 'f':
                    d= (char *) malloc(sizeof optarg);
                    strcpy(d,optarg);
 //                   printf("frameNumber:%s\n",d);
                    frameNumber=atoi(d);
 //                   printf("frameNumber:%d\n",frameNumber);

                    i=i+2;
                    break;
                case 'r':
                  //  s = (char *) malloc(sizeof optarg);
                    strcpy(s,optarg);
                    if(!strcmp(s,"FIFO"))
                    {
                        replaceAlg=FIFO;
                    }
                    else if(!strcmp(s,"LRU_REF8"))
                    {
                        replaceAlg=LRU_REF8;
                    }
                    else if(!strcmp(s,"LFU"))
                    {
                        replaceAlg=LFU;
                    }
                    else if(!strcmp(s,"LRU_CLOCK"))
                    {
                        replaceAlg=LRU_CLOCK;
                    }
                    else if(!strcmp(s,"LRU_STACK"))
                    {
                        replaceAlg=LRU_STACK;
                    }
                    else
                    {
                        printf("Wrong replace-policy settings, please set again!\n");
                        exit(0);
                    }
 //                   printf("replacepolicy:%d\n",replaceAlg);
                    i=i+2;
                    break;
                case 'i':
                    stdin_flag=0;
                    i++;
                    bzero(inputFile,sizeof(inputFile));
                    strcpy(inputFile,optarg);
                    lstat(inputFile,&attri);
                    if(S_ISREG(attri.st_mode))// if this is a file
                    {//get page reference from specified file
                        storebuf(buf);
                        pageNumber=GetPage(pageSequence,buf);//get length of page reference
                        //   printf("pageSequence[1]=%d\n",pageSequence[13]);
                    }
                    else
                    { //get page reference from input
      //                  strcpy(buf,optarg);
    //                    printf("buf=%s\n",buf);
      //                  i++;
                        /*int aa;
                        for(aa=i;aa<argc;aa++)
                        {   
                            strcat(buf,argv[aa]);
                            strcat(buf," ");
//                            printf("buf=%s\n",buf);
                        }
                        flen=2*(argc-i);
//                        printf("flen=%d\n",flen);
                        pageNumber=GetPage(pageSequence,buf);//get length of page reference*/
                        
                    }
 
                    break;
                default:
                    printf("Other Options");
            }
    }
    if (stdin_flag)
    {
        printf("Please input the page sequence:\n ");
        //flen=sizeof(buf);
       /* while ((ch=getchar())!='\n')
        {
            buf[bufcnt]=ch;
            bufcnt++;
        }*/
        //fgets(buf,flen,stdin);
        gets(buf);
        strcat(buf," ");
        flen=sizeof(buf);
        pageNumber=GetPage(pageSequence,buf);//get length of page reference
    }
    return 1;
}

void storebuf(char* buf)
{
    FILE* myfile;
    myfile=fopen(inputFile,"r");
    fseek(myfile,0,SEEK_END);//move the cur to the end of the file
    flen=ftell(myfile);//get the file length
    fseek(myfile,0,SEEK_SET);//moce the cur to the begin of the file
    //	printf("%d",flen);
    fread(buf,sizeof(char),flen,myfile);// read flen's content to the buf
    fclose(myfile);
    strcat(buf," ");//add the " " to the end of buf
 //   strcat(buf," ");
//    printf("buf=%s\n",buf);

}
/*********************************************/
////get length of page reference from the file
int GetPage(int pageSequence[MAX_PAGE_NUM],char* buf)
{
    char* refplace;
	char* reffile;
	reffile=(char*) malloc(MAX_PAGE_NUM);
	strcpy(reffile,buf);
    refplace=reffile;
	int i=1;
    int j=0;
    for (j=0; j<flen; j++)
    {
        if((*refplace!='\0') && (*refplace!=' ') && (!(isdigit(*refplace)))&&(*refplace!='\n')&&(*refplace!='\t'))
        {
            printf("The input page sequence has illegale character!\n");
            exit(0);
        }
        else if ((*refplace==' '))
        {
            refplace++;
        }
        else if ((*refplace=='\n'))
        {
            refplace++;
        }
        else if ((*refplace=='\t'))
        {
            refplace++;
        }
        else if((*refplace=='\0'))
        {
            goto X;
        }
        else
        {
            reffile=refplace;
            refplace=strchr(reffile,' ');//find the pointer of the first time the " " occrued in reffile
            *refplace='\0';//turn " " to "\0"
            pageSequence[i]=atoi(reffile);
            *refplace=' ';
           // refplace++;
            //printf("2********pageSequence[%d]=%d\n",i,pageSequence[i]);
            i++;
        }
    }
X:{};
//    printf("%d",i);
	return i-1;
}
/********************************************/

