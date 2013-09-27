#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "simdisk.h"

int main(int argc, char* argv[]){
//  data initialization
    userCylinderNum=CYLINDERNUM;
	userPolicy=FCFS;
    int flen;
	int i=1;
	char s[4];
	bzero(s,sizeof(s));
	strcpy(s,"FCFS");
	char buf[FILELEN];
	bzero(buf,sizeof(buf));
//  get options
	for(i=1;i<argc;i++){
	    if(!strcmp(argv[i],"-h")){
		    puts("This is summary of all options!\n");
   	        puts("-n number-of-cylinders : Set the total number cylinders on the disk."
      			 "By default it should be 200.(disk cylinder indexes would be between 0-199)\n");
    	    puts("-d disk-shed-policy : Set the disk scheduling policy."
 			     "It can be either FCFS (First-come-firstserved), SSTF (Shortest-seek-time-first)," 
				 "C-SCAN, or LOOK. The default will be FCFS. Assume at the t=t0, the disk head was moving"
                 "from 0 towards other end of the disk.\n");
    	    puts("-i input file : Read the I/O request sequence from a specified file. If not given,"
                 "the sequence should be read from STDIN (ended with ENTER).\n");
			return 0;}
		else if(!strcmp(argv[i],"-n")){
		    i++;
			userCylinderNum=atoi(argv[i]);}
		else if(!strcmp(argv[i],"-d")){
		    i++;
			bzero(s,sizeof(s));
			if(!strcmp(argv[i],"FCFS")){ userPolicy=FCFS;strcpy(s,"FCFS");}
			else if(!strcmp(argv[i],"SSTF")){ userPolicy=SSTF;strcpy(s,"SSTF");}
			else if(!strcmp(argv[i],"C-SCAN")){ userPolicy=CSCAN;strcpy(s,"C-SCAN");}
			else if(!strcmp(argv[i],"LOOK")){ userPolicy=LOOK;strcpy(s,"LOOK");}
			}
		else if(!strcmp(argv[i],"-i")){
		    i++;
			bzero(userInput,sizeof(userInput));
			strcpy(userInput,argv[i]);
			struct stat attri;
		    lstat(userInput,&attri);
		    if(S_ISREG(attri.st_mode)){//get I/O request sequence from specified file
		        FILE* inpt;
		        inpt=fopen(userInput,"r");
		        fseek(inpt,0,SEEK_END);
		        flen=ftell(inpt);
		        fseek(inpt,0,SEEK_SET);
                fread(buf,sizeof(char),flen,inpt);
		        fclose(inpt);
				strcat(buf," ");
				reqNum=FileToInt(reqSeq,buf,userCylinderNum);//get number of I/O requests, convert input to integers and
				                             //store them in array "reqSeq"
				
		        }
		    else{ //get I/O request sequence from input
		        strcpy(buf,argv[i]);
		    	i++;
			    while(i<argc){
				    strcat(buf," ");
			        strcat(buf,argv[i]);
			    	i++;}
			    strcat(buf," ");
				reqNum=StdToInt(reqSeq,buf,userCylinderNum);
			}}
		}

	if(userPolicy==FCFS)
	    totalTrvld=FCFSSched(schedSeq,reqSeq,reqNum);
    else if(userPolicy==SSTF)
	    totalTrvld=SSTFSched(schedSeq,reqSeq,reqNum);
	else if(userPolicy==CSCAN)
        totalTrvld=CSCANSched(schedSeq,reqSeq,reqNum,userCylinderNum);
	else if(userPolicy==LOOK)
        totalTrvld=LOOKSched(schedSeq,reqSeq,reqNum);	
    printf("\n%s processing order : ",s);
	if(userPolicy==CSCAN) reqNum=reqNum+2;
    for(i=0;i<reqNum;i++) printf("%d ",schedSeq[i]);	
    printf("\n# of cylinders traveled : %d\n",totalTrvld);
}

int FileToInt(int n[REQLEN],char* buf,int num){
    char* index;
	char* temp;
	temp=(char*) malloc(REQLEN);
	strcpy(temp,buf);
	int i=0,j=0,a;
	int tag=0;
	char invalid[REQLEN];
	bzero(invalid,sizeof(invalid));
	strcpy(invalid,"Illegal I/O request: ");
	while(*temp!='\0' && *temp!=' '){
	    index=strchr(temp,' ');
	    *index='\0';
		if(*temp<48||*temp>57){
		        tag=1;strcat(invalid,temp);strcat(invalid," ");}
		else{
		    a=atoi(temp);
	        if(a<0||a>num){
			        tag=1;strcat(invalid,temp);}
			else {n[i]=a;i++;}
			}
	    *index=' ';
	    index+=2;
	    temp=index;
	    }
    if(tag==1) printf("%s",invalid);
	return i;
}	

int StdToInt(int n[REQLEN],char* buf,int num){
    char* index;
	char* temp;
	temp=(char*) malloc(REQLEN);
	strcpy(temp,buf);
	int i=0,j=0,a;
	int tag=0;
	char invalid[REQLEN];
	bzero(invalid,sizeof(invalid));
	strcpy(invalid,"Illegal I/O request: ");
	while(*temp!='\0'){
	        index=strchr(temp,' ');
	        *index='\0';
			if(*temp<48||*temp>57){
		        tag=1;strcat(invalid,temp);strcat(invalid," ");}
	        else{
				a=atoi(temp);
	            if(a<0||a>num){
			        tag=1;strcat(invalid,temp);}
		    	else{n[i]=a;i++;}
				}
	        *index=' ';
	        index++;
	        temp=index;
			}
	if(tag==1) printf("%s",invalid);
	return i;
}

int FCFSSched(int n[REQLEN], int m[REQLEN], int num){
    int total=0;
	int i;
    for(i=0;i<num;i++) n[i]=m[i];
	for(i=0;i<num-1;i++)
	    total+=abs(m[i]-m[i+1]);
	return total;
	}

int SSTFSched(int n[REQLEN], int m[REQLEN], int num){
    int total=0,min=10000;
	int i=0,k=1,j,next;
	int tag[num];
	for(j=0;j<num;j++){ tag[j]=0;}
	n[0]=m[0];tag[0]=1;
//	printf("num:%d\n",num);
	while(k<num){
	    min=1000;
	    for(j=0;j<num;j++){
		    if(tag[j]!=1){
		        if(abs(m[i]-m[j])<min){
					min=abs(m[i]-m[j]);
			    	next=j;}
				}
			}
//		printf("%d %d\n",next,min);
		n[k]=m[next];
		total+=min;
		tag[next]=1;
		i=next;
		k++;}
	return total;
	}

int CSCANSched(int n[REQLEN], int m[REQLEN], int num, int cylinders){
    int total=0;
	int i,j,l,k=1,h=1,now;
	int tag[num];
	for(i=0;i<num;i++) tag[i]=0;
	n[0]=m[0];tag[0]=1;now=0;
	m[num]=0;
	int z[num];
	for(i=0;i<num;i++){
	    if(m[i]>m[now]&&tag[i]!=1){
            for(j=0;j<k;j++){
			    if(m[i]<n[j]){
				    for(l=k;l>j;l--) n[l]=n[l-1];
					n[j]=m[i];k++;
					tag[i]=1;
					break;}}
            if(tag[i]!=1) {
			    n[k]=m[i];
			    k++;tag[i]=1;}
        }}
	if(k<num){
		n[k]=cylinders-1;k++;
		now=num;z[0]=0;
		for(i=0;i<num;i++){
	    	if(m[i]>m[now]&&tag[i]!=1){
            	for(j=0;j<h;j++){
			    	if(m[i]<z[j]){
				    	for(l=h;l>j;l--) z[l]=z[l-1];
						z[j]=m[i];h++;
						tag[i]=1;
						break;}}
                if(tag[i]!=1) {
				    z[h]=m[i];h++;tag[i]=1;}
            }}
        for(i=0;i<h;i++){ n[k]=z[i];k++;}			
	}
	for(i=0;i<k-1;i++) total+=abs(n[i]-n[i+1]);
	return total;
}

int LOOKSched(int n[REQLEN], int m[REQLEN], int num){
    int total=0;
	int i,j,l,k=1,h=0,now;
	int tag[num];
	for(i=0;i<num;i++) tag[i]=0;
	n[0]=m[0];tag[0]=1;now=0;
	int z[num];
	for(i=0;i<num;i++){
	    if(m[i]>m[now]&&tag[i]!=1){
            for(j=0;j<k;j++){
			    if(m[i]<n[j]){
				    for(l=k;l>j;l--) n[l]=n[l-1];
					n[j]=m[i];k++;
					tag[i]=1;
					break;}}
            if(tag[i]!=1) {
			    n[k]=m[i];
			    k++;tag[i]=1;}
        }}
	if(k<num){
		for(i=0;i<num;i++){
	    	if(tag[i]!=1){
            	for(j=0;j<h;j++){
			    	if(m[i]<z[j]){
				    	for(l=h;l>j;l--) z[l]=z[l-1];
						z[j]=m[i];h++;
						tag[i]=1;
						break;}}
                if(tag[i]!=1) {
				    z[h]=m[i];h++;tag[i]=1;}
            }}
        for(i=h-1;i>=0;i--){ n[k]=z[i];k++;}			
	}
	for(i=0;i<k-1;i++){total+=abs(n[i]-n[i+1]);}
	return total;    
}
