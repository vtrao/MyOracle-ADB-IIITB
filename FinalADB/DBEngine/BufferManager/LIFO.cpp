#include "VSBufferManager.h"
#include "standards.h"

LIFO* LIFO :: singleInstance_C = 0;

LIFO* LIFO :: getInstance()
	{
	if(singleInstance_C==0)
		singleInstance_C=new LIFO();
	return singleInstance_C;
	}

LIFO :: LIFO()
	{
#ifdef DEBUG
	printf("\n\tLIFO Constructed");
#endif		
        }


int LIFO :: getRecentTimeStampFrame(FrameClass *frames,int numberOfFrames)
        {
        int i=0,recentTimeStampFrameNumber=0,recentTimeStamp;
        recentTimeStamp=(frames + i)->getTimeStamp();
#ifdef DEBUG
	printf("\n\tLIFO : getRecentTimeStampFrame()");
#endif		
        for(i=1;i<numberOfFrames;i++)
                {
                if(recentTimeStamp < (frames + i)->getTimeStamp())
                        {
                        recentTimeStamp= (frames + i)->getTimeStamp();
                        recentTimeStampFrameNumber=i;
                        }
                }	
#ifdef DEBUG
        printf("\n\t\tThe Recent timestamp Frame Number is %d\n",recentTimeStampFrameNumber);
#endif
        return recentTimeStampFrameNumber; //
        }


int LIFO :: replaceFrame(FrameClass *frames,int pageNumber,int numberOfFrames,DiskSpaceManagerLinux *dsml)
       {
       int recentTimeStampFrameNumber,size=0;
       recentTimeStampFrameNumber=getRecentTimeStampFrame(frames,numberOfFrames);
#ifdef DEBUG
	printf("\n\tLIFO : replaceFrame()");
#endif       
       if((frames + recentTimeStampFrameNumber)->getDirtyBit()==1)
                {
                size=dsml->writePageToHDD((frames + recentTimeStampFrameNumber)->getPageNumber(),(frames + recentTimeStampFrameNumber)->getData());
#ifdef DEBUG
        printf("\n\t\tFrame Replaced is %d and Number of bytes successfully writtem is %d\n", 
                                         recentTimeStampFrameNumber,size);
#endif
                }
        return recentTimeStampFrameNumber;
       }
  li