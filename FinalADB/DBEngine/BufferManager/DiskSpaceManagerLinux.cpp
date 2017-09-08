#include<fcntl.h>
#include "VSBufferManager.h"
#include <sys/types.h> // for disk space manager i.e.., lseek ,off_t and size_t
#include <unistd.h>
#include "standards.h"

DiskSpaceManagerLinux* DiskSpaceManagerLinux :: singleInstance_C=0;

DiskSpaceManagerLinux* DiskSpaceManagerLinux :: getInstance(char *fileName_P)
	{
	if(singleInstance_C==0)
		singleInstance_C=new DiskSpaceManagerLinux(fileName_P);
	return singleInstance_C;
	}	

DiskSpaceManagerLinux :: DiskSpaceManagerLinux(char * fileName_P)
	{
#ifdef DEBUG
	printf("\nDiskSpaceManagerLinux: Constructed");
#endif		
	fileName_C=(char*)MSF::myMalloc(strlen(fileName_P+1));
	strcpy(fileName_C,fileName_P);	
	}	

DiskSpaceManagerLinux :: ~DiskSpaceManagerLinux()
	{
#ifdef DEBUG
	printf("\nDiskSpaceManagerLinux: Desturcted");
#endif		
	MSF::myFree(fileName_C);
	}
	
int DiskSpaceManagerLinux :: readPageFromHDD(int pageNumber,void *data)
	{
	int fileDescriptor=-1;
	int returnFlag=0;
	fileDescriptor=open(fileName_C,O_RDONLY);
	size_t size=0;
#ifdef DEBUG
	printf("\n\t\tDiskSpaceManagerLinux: readPageFromHDD()");
#endif		
	if(fileDescriptor==-1)
		{
#ifdef DEBUG
	printf("\n\t\t\tError Reading File %s",fileName_C);
#endif		
		returnFlag=1;
		goto RPFHEND;
		}
	else
		{
		off_t offset;
		offset=lseek(fileDescriptor,off_t(pageNumber * PAGESIZE),SEEK_SET);
		if(offset==off_t(-1))
			{
#ifdef DEBUG
	printf("\n\t\t\tError Reading File %s",fileName_C);
#endif			
			returnFlag=1;
			goto RPFHEND;
			}
		size=read(fileDescriptor,data,PAGESIZE);
		if(size==size_t(-1))
			{
#ifdef DEBUG
	printf("\n\t\t\tError Reading File %s",fileName_C);
#endif
			returnFlag=1;
			goto RPFHEND;
			}
#ifdef DEBUG
	printf("\n\t\t\tSuccessfully Read %d Page of %s File \n",pageNumber,fileName_C);
#endif			
		goto RPFHEND;
		}	
RPFHEND:
	if(fileDescriptor!=-1)
		close(fileDescriptor);
	if(returnFlag==1) 
		return FAILED;
	else
	  	return int(size);
	}

int DiskSpaceManagerLinux :: writePageToHDD(int pageNumber,void *data)
	{
	int fileDescriptor=-1;
	int returnFlag=0;
	fileDescriptor=open(fileName_C,O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);
	size_t size=0;
#ifdef DEBUG
	printf("\n\t\tDiskSpaceManagerLinux: writePageToHDD()");
#endif		
	if(fileDescriptor==-1)
		{
#ifdef DEBUG
	printf("\n\t\t\tError Writing to File %s",fileName_C);
#endif		
		returnFlag=1;
		goto RPFHEND;
		}
	else
		{
		off_t offset;
		offset=lseek(fileDescriptor,off_t(pageNumber * PAGESIZE),SEEK_SET);
		if(offset==off_t(-1))
			{
#ifdef DEBUG
	printf("\n\t\t\tError Writing to File %s",fileName_C);
#endif			
			returnFlag=1;
			goto RPFHEND;
			}
		size=write(fileDescriptor,data,PAGESIZE);
		if(size==size_t(-1))
			{
#ifdef DEBUG
	printf("\n\t\t\tError Writing to File %s",fileName_C);
#endif
			returnFlag=1;
			goto RPFHEND;
			}
#ifdef DEBUG
	printf("\n\t\t\tSuccessfully Written to %d Page of %s File \n",pageNumber,fileName_C);
#endif			
		goto RPFHEND;
		}	
RPFHEND:
	if(fileDescriptor!=-1)
		close(fileDescriptor);
	if(returnFlag==1) 
		return FAILED;
	else
	  	return int(size);	
	}	

  C rea