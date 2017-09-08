#include "VSBufferManager.h"
#include "standards.h"

ACP* ACP :: singleInstance_C = 0;

ACP* ACP :: getInstance()
	{
        if(singleInstance_C==0)
                singleInstance_C=new ACP();
        return singleInstance_C;
        }

ACP :: ACP()
	{
#ifdef DEBUG
	printf("\n\tACP Constructed");
#endif	
	}

int ACP :: getLowPriorityFrame(FrameClass *frames,int numberOfFrames)
	{
	int i=0,lowestPriorityFrameNumber=0;
	unsigned int ts=0,temp[numberOfFrames],lowPriority;
         
         	lowPriority=(frames + i)->getPriority();
		ts = (frames + i)->getTimeStamp();
		ts= ts/100000;
		temp[i]= lowPriority * 1000000 +ts;
		//printf("ts = %u, temp = %u\n",ts,temp[i]);


	for(i=1;i<numberOfFrames;i++)
		{

		lowPriority= (frames + i)->getPriority();
		ts = (frames + i)->getTimeStamp();
		ts= ts/100000;
		temp[i]= lowPriority * 1000000 +ts;
		if(temp[i-1] > temp[i])
			{
			temp[i-1]=temp[i];	
			lowestPriorityFrameNumber=i;
			}
        	
		}	
#ifdef DEBUG
	printf("\nIn getLowPriorityFrameNumber %d is the Lowest Priority Frame Number\n",lowestPriorityFrameNumber);
#endif	
	return lowestPriorityFrameNumber; //
	}	



int ACP :: replaceFrame(FrameClass *frames,int pageNumber,int numberOfFrames,DiskSpaceManagerLinux *dsml)
       {
       int lowestPriorityFrameNumber,size=0;
       lowestPriorityFrameNumber=getLowPriorityFrame(frames,numberOfFrames);
       if((frames + lowestPriorityFrameNumber)->getDirtyBit()==1)
       		{
		size=dsml->writePageToHDD((frames + lowestPriorityFrameNumber)->getPageNumber(),(frames + lowestPriorityFrameNumber)->getData());
#ifdef DEBUG
	printf("\nIn ReplaceFrame of ACP frame Replaced is %d and Number of bytes successfully writtem %d\n",
			                 lowestPriorityFrameNumber,size);		
#endif		
		}
	return lowestPriorityFrameNumber;
       }



/*int main()
       {
       ReplacementPolicy *l=new ACP();
       FrameClass *f;
       DiskSpaceManagerLinux *dsml;
       printf("\n%d ---\n",l->replaceFrame(f,"venki",1,1,dsml));
       }*/


