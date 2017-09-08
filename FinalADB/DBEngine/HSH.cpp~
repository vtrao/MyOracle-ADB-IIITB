#include "BufferManager/standards.h"
#include "VSDBEngine.h"

/*******************************************************Heap Structure Handlers**************************************/
//********************************************************Record Handler RH******************************************
// Given a set of Rids handles the records or returns them after calling the Buffer manager for respective PageNumbers
RH* RH :: singleInstance_C=0;
RH* RH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES
		printf("\n\t\tIn Static Invoker of RecordHandler RH");	
#endif		
	        singleInstance_C = new RH();
		}
	return singleInstance_C;	
	}
	
RH :: RH()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Constructor of RecordHandler RH");
#endif	
	vSB_C=VSBufferManager :: getInstance();		
	}
	
void RH :: insertToRIDList(RID **rID,long pgno,short slotID)
	{
	if(*rID==NULL)
		{
		*rID=(RID*)MSF::myMalloc(sizeof(RID));
		(*rID)->pageNumber=pgno; (*rID)->slotID=slotID;
		(*rID)->next=NULL;
		}
	else
		{
		RID *t=*rID;
		while(t->next!=NULL)
			t=t->next;
		RID *temp=(RID*)MSF::myMalloc(sizeof(RID));
		temp->pageNumber=pgno; temp->slotID=slotID;
		t->next=temp;
		temp->next=NULL;	
		}
	}

void RH :: displayRIDList(RID *rID)
	{
	while(rID!=NULL)
		{
		printf("\n\tPGNO %ld \t SlotID %d",rID->pageNumber,rID->slotID);
		rID=rID->next;
		}
	}

void RH :: freeRIDList(RID *rID)
	{
	RID *temp=rID;
	while(rID!=NULL)
		{
		temp=rID;
		rID=rID->next;
		MSF::myFree(temp);
		}	
	}

int RH :: deleteRecord(RID *rID)
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside Delete Record method of RH class");	
#endif	
	//printf("\n\tDeletion of Record PGNO %ld \t SlotID %d",rID->pageNumber,rID->slotID);
	//RH::displayRIDList(rID);
	void *dBPData=0;
	dBPData=MSF::myMalloc(PAGESIZE);
	vSB_C->readFromBufferPool(rID->pageNumber,dBPData);
	SlotMap *sM;
	sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(rID->slotID+1)*(1*sizeof(long)+1*sizeof(short)));
	//printf("\n %d is offset and %d is size",sM->offset,sM->recordLength);
	sM->offset*=-1;sM->recordLength*=-1;
	vSB_C->writeToBufferPool(rID->pageNumber,dBPData);
	if(dBPData!=0)	MSF::myFree(dBPData);
	}
	
int RH :: returnRecord(RID *rID,createColumns *columns,AttributeValues **avalues)
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside return Record method of RH class");	
#endif		
	//use knowledge from the above function and below funtion to deliver this functionality
	void *dBPData=0,*tempData=0;
	char *string;
	short *offset=0;
	char *integer;
	dBPData=MSF::myMalloc(PAGESIZE);
	vSB_C->readFromBufferPool(rID->pageNumber,dBPData);
	SlotMap *sM;
	sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(rID->slotID+1)*(1*sizeof(long)+1*sizeof(short)));
	tempData=(void*)((char*)dBPData + sM->offset);
	while(columns!=NULL)
		{
		offset=(short*)((char*)tempData+ (columns->position-1)*sizeof(short));
		if(columns->dataType==DBCHARTYPE)
			{
			string=(char*)tempData+*offset;
			//printf("%10s",string);
			RLQH::insertToAttList(avalues,string);
			}
		else if(columns->dataType==DBINTTYPE)
			{
			integer=((char*)tempData+*offset);
			//printf("%10d",atoi(integer));
			RLQH::insertToAttList(avalues,integer);
			}	
		columns=columns->next;
		}	
	if(dBPData!=0)	MSF::myFree(dBPData);
	}
				 			
int RH :: handleRecord(void* dBPData,SlotMap* sM,createColumns *columns,int type,char *columnName,char *value,short operation)//for do table scan
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside handleRecord method of RH class");	
#endif		
	void *tempData=0;
	char *string;
	short processFlag=FAILED;
	char *integer;
	short *offset=0,*tempoffset=0;
	createColumns *tempColumns=columns;
	if(sM->offset<0 || sM->recordLength<0)	
		{
		processFlag=FAILED;		
		goto HREND;
		}
	if(columnName==NULL) 
		{
		processFlag=SUCCESS;
		tempData=(void*)((char*)dBPData + sM->offset);
		goto NEXT;
		}
	
	tempData=(void*)((char*)dBPData + sM->offset);	
	while(tempColumns!=NULL)
		{
		offset=(short*)((char*)tempData+ (tempColumns->position-1)*sizeof(short));
		if(!strcmp(tempColumns->columnName,columnName))
			{
			switch(operation)
				{
				case LE:
					if(tempColumns->dataType==DBCHARTYPE)
						{
						string=(char*)tempData+*offset;
						if(strcmp(string,value)<=0)
							processFlag=SUCCESS;
						}
					else if(tempColumns->dataType==DBINTTYPE)
						{
						integer=((char*)tempData+*offset);
						if(atoi(integer)<=atoi(value))
							processFlag=SUCCESS;
						}	
					break;	
				case LT:
					if(tempColumns->dataType==DBCHARTYPE)
						{
						string=(char*)tempData+*offset;
						if(strcmp(string,value)<0)
							processFlag=SUCCESS;
						}
					else if(tempColumns->dataType==DBINTTYPE)
						{
						integer=((char*)tempData+*offset);
						if(atoi(integer)<atoi(value))
							processFlag=SUCCESS;
						}					
					break;					
				case GE:
					if(tempColumns->dataType==DBCHARTYPE)
						{
						string=(char*)tempData+*offset;
						if(strcmp(string,value)>=0)
							processFlag=SUCCESS;
						}
					else if(tempColumns->dataType==DBINTTYPE)
						{
						integer=((char*)tempData+*offset);
						if(atoi(integer)>=atoi(value))
							processFlag=SUCCESS;
						}	
					break;
				case GT:
					if(tempColumns->dataType==DBCHARTYPE)
						{
						string=(char*)tempData+*offset;
						if(strcmp(string,value)>0)
							processFlag=SUCCESS;
						}
					else if(tempColumns->dataType==DBINTTYPE)
						{
						integer=((char*)tempData+*offset);
						if(atoi(integer)>atoi(value))
							processFlag=SUCCESS;
						}	
					break;
				case EQ:
					if(tempColumns->dataType==DBCHARTYPE)
						{
						string=(char*)tempData+*offset;
						if(strcmp(string,value)==0)
							processFlag=SUCCESS;
						}
					else if(tempColumns->dataType==DBINTTYPE)
						{
						integer=((char*)tempData+*offset);
						if(atoi(integer)==atoi(value))
							processFlag=SUCCESS;
						}	
					break;
				case NE:
					if(tempColumns->dataType==DBCHARTYPE)
						{
						string=(char*)tempData+*offset;
						if(strcmp(string,value)!=0)
							processFlag=SUCCESS;
						}
					else if(tempColumns->dataType==DBINTTYPE)
						{
						integer=((char*)tempData+*offset);
						if(atoi(integer)!=atoi(value))
							processFlag=SUCCESS;
						}	
					break;		
				}
			goto NEXT;	
			}	
		tempColumns=tempColumns->next;
		}
NEXT:	
	if(type==DISPLAY && processFlag==SUCCESS)	printf("\n");	
	if(processFlag==SUCCESS)
		{
		if(type==DISPLAY)
			{printf("\t");
			while(columns!=NULL)
				{
				offset=(short*)((char*)tempData+ (columns->position-1)*sizeof(short));
				//printf("\n %d %d",tempoffset,offset);
				//if(tempoffset==offset)
				//	printf("%10c",'-');
				//else
					{	
					if(!strcmp(columns->columnName,"pkey") || !strcmp(columns->columnName,"notnull") || !strcmp(columns->columnName,"unique"))
						{
						string=(char*)tempData+*offset;
						printf("%-10c",atoi(string));
						}
					else if(!strcmp(columns->columnName,"atype"))
						{
						string=(char*)tempData+*offset;
						if(!strcmp(string,"1240"))      printf("%-10s","int");
						else if(!strcmp(string,"1241")) printf("%-10s","float");
						else if(!strcmp(string,"1242")) printf("%-10s","char");
						else				printf("%-10s","date");
						}	
					else if(columns->dataType==DBCHARTYPE || columns->dataType==DBDATETYPE)
						{
						string=(char*)tempData+*offset;
						printf("%-10s",string);
						}
					else if(columns->dataType==DBINTTYPE)
						{
						integer=((char*)tempData+*offset);
						printf("%-10d",atoi(integer));
						}	
					columns=columns->next;
					}
				tempoffset=offset;	
				}	
			}
		}
HREND:		
	return processFlag;		
	}
	
void RH :: printRecord(RID *rID)
	{
	
	}
	
RH :: ~RH()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Destructor of RecordHandler RH");
#endif			
	}
	
//************************************************DataBasePageHandler DBPH*******************************************
// Calls Buffer Manager's Read From Buffer Pool method to read the corresponding database page into buffer
// And this calls the Record handler to handle the records in slots
DBPH* DBPH :: singleInstance_C=0;
DBPH* DBPH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES
		printf("\n\t\tIn Static Invoker of DataBasePageHandler DBPH");	
#endif		
	        singleInstance_C = new DBPH();
		}
	return singleInstance_C;	
	}

	
DBPH :: DBPH()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Constructor of DataBasePageHandler DBPH");
#endif	
	vSB_C=VSBufferManager::getInstance();
	rH_C =RH :: getInstance();	
		
	}

void DBPH :: scanDBPHForColumns(long dBPageNumber,createColumns *columns,RID **rID,int type,char *columnName,char *value,short operation)// for do Table Scan
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside ScanDBPHForColumns  method of DBPH class");	
#endif		
	#ifdef TSDEBUG
	printf("\n IN SDBFC,dBPgn  %d",dBPageNumber);
	#endif
	void *dBPData=0;
	dBPData=MSF::myMalloc(PAGESIZE);
	DataBasePage *dBP;
	SlotMap *sM;
	int iLoopCounter=0;
	vSB_C->readFromBufferPool(dBPageNumber,dBPData);
	dBP=(DataBasePage*)((char*)dBPData + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));
	int noc=0;
	if(type==DISPLAY)
		{
		printf("\n ");
		createColumns *temp=columns;
		while(temp!=NULL)
			{
			printf("%10s",temp->columnName);
			noc++;
			temp=temp->next;
			}
		printf("\n   ");	
		while(noc--)		
			printf("----------");
		}
	for(iLoopCounter=0;iLoopCounter< dBP->totalNumberOfSlots;iLoopCounter++)
		{
		sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(iLoopCounter+2)*(1*sizeof(long)+1*sizeof(short)));
		if(rH_C->handleRecord(dBPData,sM,columns,type,columnName,value,operation)==SUCCESS)
			RH::insertToRIDList(rID,dBPageNumber,iLoopCounter+1);	
		//printf("\n In Loop of DBPH offset=%d\tlength=%d",sM->offset,sM->recordLength);
		}
	if(dBPData!=0)		MSF::myFree(dBPData);
	}
	
int DBPH :: scanAndInsertIntoDBPage(long dBPNum,void *record,int lengthOfRecord,int newOrNot,RID **rID_P) //for insertion
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside scanAndInsertIntoDBPage method of DBPH class");	
#endif		
	void * dBPData=0,*tempData=0;
	DataBasePage *dBPH;
	SlotMap *sM,*cSM;
	int loopCounter=0;
	short tFS=0,tempLength=0;
	dBPData=MSF::myMalloc(PAGESIZE);
	if(newOrNot==0)      //DBPage already exists, so insert and update the neccessary fields
		{				
		vSB_C->readFromBufferPool(dBPNum,dBPData);
		dBPH=(DataBasePage*)((char*)dBPData + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));                
		sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-1*sizeof(long)-1*sizeof(short));
		cSM=sM;     //to store CFS slot pointer
#ifdef INSTALLDEBUG		
		printf("\n\tB4 Insertion CFS slot<size=%d,offset=%ld>",cSM->recordLength,cSM->offset);
#endif		
		dBPH->timeStamp +=1;
		dBPH->recordsInSlots +=1;
#ifdef INSTALLDEBUG		
		printf("\n\tFor Deleted Slots\n");
#endif		
		sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(2)*(1*sizeof(long)+1*sizeof(short)));
		for(;loopCounter < (dBPH->totalNumberOfSlots);loopCounter++)
			{
#ifdef INSTALLDEBUG			
			printf("\n***TotSlots %d,cSM at %u sM at %u Checking %d slot, offset %d and recordLength %d",dBPH->totalNumberOfSlots,cSM,sM,loopCounter+1,sM->offset,sM->recordLength);
#endif			
			//printf("\n Venki is here in while");
			if(sM->offset < 0 || sM->recordLength < 0)
				{
				//printf("\n\t Venki is here outer if");
				tempLength=sM->recordLength;
				tempLength*=-1;
				if( tempLength >= lengthOfRecord)
					{
					//printf("\n\t Venki is here inner if");
					sM->recordLength*= -1;
					sM->offset*= -1;
					dBPH->totalFreeSpace +=sM->recordLength - lengthOfRecord;
					
					tFS=dBPH->totalFreeSpace;							
					sM->recordLength=lengthOfRecord;
					tempData= (void*)((char*)dBPData + sM->offset);
					
					memcpy(tempData,record,lengthOfRecord);
					if(rID_P!=NULL) RH::insertToRIDList(rID_P,dBPNum,loopCounter+1);
					goto SAIIDBPEND;
					}	
				}
			sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(loopCounter+2+1)*(1*sizeof(long)+1*sizeof(short)));		
			}
		//this number of slots is increased only when a new slot is created but in the above for loop for reallocation, no need to ++	
		dBPH->totalNumberOfSlots +=1;	
		sM->offset=cSM->offset;
		sM->recordLength=lengthOfRecord;
		tempData= (void*)((char*)dBPData + sM->offset);
		
                memcpy(tempData,record,lengthOfRecord);
		
		cSM->offset=cSM->offset+lengthOfRecord;
		cSM->recordLength -= ( lengthOfRecord + 1* ( sizeof(long) + sizeof(short) ) );
#ifdef INSTALLDEBUG		
		printf("\n\tAfter Insertion CFS slot<size=%d,offset=%ld>",cSM->recordLength,cSM->offset);
		printf("\n\tIN DBPAGE RID <pageNum=%ld,slot=%d>;sM<size=%d,offset=%ld>",dBPNum,dBPH->totalNumberOfSlots,sM->recordLength,sM->offset);
#endif		
		if(rID_P!=NULL) RH::insertToRIDList(rID_P,dBPNum,dBPH->totalNumberOfSlots);
		dBPH->totalFreeSpace -= ( lengthOfRecord + 1* ( sizeof(long) + sizeof(short) ) );
		tFS=dBPH->totalFreeSpace;
		goto SAIIDBPEND;		
		//if(lengthOfRecord < cSM->recordLength) ;//defrag algo
		}
	else if(newOrNot==1) //DBPage doesnot exists, so create a new one and insert into that	
		{
#ifdef INSTALLDEBUG				
		printf("\n Entered into creation of new slot\n");
#endif		
		dBPH=(DataBasePage*)((char*)dBPData+ PAGESIZE - 3*sizeof(long) - 2* sizeof(short));
		dBPH->timeStamp=1;
		dBPH->recordsInSlots=1;
		dBPH->totalNumberOfSlots=1;
		dBPH->totalFreeSpace=MAXFS-lengthOfRecord - 1*( sizeof(long) + sizeof(short));
		// reducing it for 2 times size of slotmap, 1 for current slotmap and the other for future slotmap		                            
		tFS=dBPH->totalFreeSpace;
		sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-1*sizeof(long)-1*sizeof(short));
		cSM=sM;
		cSM->offset=lengthOfRecord;             //CFS Slot
		cSM->recordLength=dBPH->totalFreeSpace; //CFS Slot
#ifdef INSTALLDEBUG		
		printf("\n\tCFS slot<size=%d,offset=%ld>",cSM->recordLength,cSM->offset);
#endif		
		sM=(SlotMap*)((char*)dBPData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-2*(1*sizeof(long)+1*sizeof(short)));
#ifdef INSTALLDEBUG		
		printf("\n***dBPH %u,CSM %u,SM is at %u",dBPH,cSM,sM);
#endif			
		sM->offset=0;                    //Assigned Slot
		sM->recordLength=lengthOfRecord; //Assigned Slot
		memcpy(dBPData,record,lengthOfRecord);
#ifdef INSTALLDEBUG		
		printf("\n\tIN DBPAGE RID <pageNum=%ld,slot=%d>;sM<size=%d,offset=%ld>",dBPNum,dBPH->totalNumberOfSlots,sM->recordLength,sM->offset);
#endif		
		if(rID_P!=NULL) RH::insertToRIDList(rID_P,dBPNum,dBPH->totalNumberOfSlots);
		goto SAIIDBPEND;		
		}	
SAIIDBPEND:
	vSB_C->writeToBufferPool(dBPNum,dBPData);
	//return totalfreespace
	if(dBPData!=0)		MSF::myFree(dBPData);
	return(tFS);		
	}	

DBPH :: ~DBPH()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Destructor of DataBasePageHandler DBPH");
#endif		
	}
	
//*********************************************DirectoryPageHandler DPH**********************************************	
//Calls Buffer Manager's Read From Buffer Pool method to read the Directory Page i.e.., pageno, filename, data
//For each DE structure in the Directory page call the DBPH i.e.., Data Base Page handler	

DPH* DPH :: singleInstance_C=0;

DPH* DPH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES
		printf("\n\t\tIn Static Invoker of DirectoryPageHandler DPH");	
#endif		
	        singleInstance_C = new DPH();
		}
	return singleInstance_C;	
	}
	
void DPH :: printDBHeaderPager()
	{
	
	}
	
DPH :: DPH()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Constructor of DirectoryPageHandler DPH");
#endif	
	vSB_C=VSBufferManager :: getInstance();		
	dBPH_C=DBPH :: getInstance();
	}

void DPH :: scanDPHForColumns(long dPageNumber,createColumns *columns,RID **rID,int type,char *columnName,char *value,short operation) //for do Table Scan
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside scanDPHForColumns method of DPH class");	
#endif		
	#ifdef TSDEBUG
	printf("\n In SDFC , DPgn  %d",dPageNumber);
	#endif
	DirectoryPage *dP;
	DirectoryEntry *dE;
	void *dPData=0;
	long dPNum=dPageNumber;
	int loopCounter=0;
	dPData=MSF::myMalloc(PAGESIZE);
	do
		{
		vSB_C->readFromBufferPool(dPNum,dPData);
		dP=(DirectoryPage*)dPData;
		//dE=(DirectoryEntry*)((char*)dPData + 3 * sizeof(long));
		for(loopCounter=0;loopCounter<dP->nDE;loopCounter++)
			{
			dE=(DirectoryEntry*)((char*)dPData + 3 * sizeof(long)+loopCounter *(sizeof(short)+sizeof(long)));
			dBPH_C->scanDBPHForColumns(dE->pageNumber,columns,rID,type,columnName,value,operation);
			}
		dPNum=dP->addressToNextDP;
		}while(dPNum!=-1);
	if(dPData!=0)		MSF::myFree(dPData);
	}		

void DPH :: initializeDPandDE(void *datum) //for creation of table structure
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside initializeDPandDE method of DPH class");	
#endif			
	DirectoryPage *dP;
        dP=(DirectoryPage*)datum;
        dP->maxFS=MAXFS;
        dP->nDE=0;
        dP->addressToNextDP=-1;
        DirectoryEntry *dE;
        dE=(DirectoryEntry*)((char*)datum+3*sizeof(long));
#ifdef INSTALLDEBUG	
        printf("\nDP is %u and DE is %u\n",dP,dE);
#endif	
        int loopCounter=0;
        for(;loopCounter<MAXDE;loopCounter++)
                {
                dE->totalFreeSpace=0;
                dE->pageNumber=-1;
#ifdef INSTALLDEBUG		
		printf("Assign %u %d %ld %4d\t",dE,dE->totalFreeSpace,dE->pageNumber,loopCounter);
		if(loopCounter%3==0) printf("\n");
#endif				
              	dE=(DirectoryEntry*)((char*)datum+3*sizeof(long)+loopCounter*(sizeof(long)+sizeof(short)));
                }
	}
	
void DPH :: checkDPandDE(long dPPageNum) //for checking the created database mydb structure initially
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside checkDPandDE method of DPH class");	
#endif			
	printf("\n\n****************PRINT HeaderPage, DP and DE******************************\n");	
	int i=0;
	void *aHPData=0,*aDPData=0;
	VSBufferManager *vSB_C=VSBufferManager::getInstance();
	DBHeader *dBH;
	HeaderPage *hP;
	DirectoryPage *dP;
	DirectoryEntry *dE;
	aHPData=MSF::myMalloc(PAGESIZE);
	printf("\n%ld",dPPageNum);
	
	vSB_C->readFromBufferPool(dPPageNum,aHPData);	
	
	hP=(HeaderPage*)aHPData;
	printf("\n\tHeader Page  Contents");
        printf("\n\t\tTotalNumberRecords=%ld;\n\t\tTotalNumberDirectoryPages=%ld;\n\t\tMaximumDEsInDPs=%ld;\n\t\tPNFirstDP=%ld"
			                        ,hP->totNumRec,hP->totNumDP,hP->maxDEInDP,hP->pNFirstDP);
	    
    	aDPData=MSF::myMalloc(PAGESIZE);
	vSB_C->readFromBufferPool(hP->pNFirstDP,aDPData);
	
	
	dP=(DirectoryPage*)aDPData;
	printf("\n\tDirectory Page Contents--->");
	printf("\n\t\t\tNumOfDEs=%ld;\n\t\t\tMaxFreeSpace=%ld;\n\t\t\tAddressToNextDP=%ld\n"
			                        ,dP->nDE,dP->maxFS,dP->addressToNextDP);
	
	dE=(DirectoryEntry*)((char*)aDPData +3 * sizeof(long));
	for(i=0;i<MAXDE;i++)
		{
		printf("C####DEIndex=%4d; TFS=%2d; DBPN=%2ld at DE=%10u\t",i,dE->totalFreeSpace,dE->pageNumber,dE);
		dE=(DirectoryEntry*)((char*)aDPData +3 * sizeof(long) +i*(sizeof(long)+sizeof(short)));
		if(i%2==0) printf("\n");
		}	
	MSF::myFree(aHPData);
	MSF::myFree(aDPData);
	}		


void DPH :: findAndInsertToDEinDP(void *record,int lengthOfRecord,long DirPageNum,RID **rID_P)//for insertion	
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside findAndInsertToDEinDP method of DPH class");	
#endif			
#ifdef INSTALLDEBUG	
	printf("\nIn findAndInsertToDEinDP\n");
#endif	
	FLH *fL=FLH::getInstance();
	void *aDPData=0,*datum=0;
	long tempPN=DirPageNum;
	DirectoryPage* dP;
	DirectoryEntry* dE;
	aDPData=MSF::myMalloc(PAGESIZE);
	int i=0;
	do
		{
		vSB_C->readFromBufferPool(DirPageNum,aDPData);
		dP=(DirectoryPage*)aDPData;
#ifdef INSTALLDEBUG			
		printf("\n\tDirectory Page Contents--->");
		printf(" ;NumOfDEs=%ld; MaxFreeSpace=%ld; AddressToNextDP=%ld"
			                        ,dP->nDE,dP->maxFS,dP->addressToNextDP);
#endif						
		dE=(DirectoryEntry*)((char*)aDPData +3 * sizeof(long));
//Case 1*******************************Initial Condition to check whether the page is a new one or not	
		if(dE->pageNumber==-1) // case is the DPage is a new one
			{
			dE->pageNumber=fL->getFreePage();
			dE->totalFreeSpace=MAXFS;
#ifdef INSTALLDEBUG			
			printf("\n\tB4 Insertion Directory Entry: new Case(-1) TFS=%2d; DBPN=%2ld at DE=%10u\t",
					  dE->totalFreeSpace,dE->pageNumber,dE);
#endif					  
		//insert the record and update the free space value of dirEntry of DirPage	1 as last argument means create a new one(DBPage)		
			dE->totalFreeSpace=dBPH_C->scanAndInsertIntoDBPage(dE->pageNumber,record,lengthOfRecord,1,rID_P); 			
			dP->nDE+=1;
#ifdef INSTALLDEBUG			
			printf("\n\tAfter Insertion Directory Entry: new Case(-1) TFS=%2d; DBPN=%2ld at DE=%10u\t",
					  dE->totalFreeSpace,dE->pageNumber,dE);
#endif					  
			goto IIDBPEND;
			}
//Case 2******************************Check all the available DE's to accomodate the Record
		for(i=0;i<dP->nDE;i++)
			{
			if(dE->totalFreeSpace>=lengthOfRecord )
				{	
#ifdef INSTALLDEBUG				
				printf("\n\tB4 Insertion DirectoryEntry:Already Exists Case DEIndex=%4d;TFS=%2d;DBPN=%2ld at DE=%10u\t" ,i+1,dE->totalFreeSpace,dE->pageNumber,dE);
#endif				
				//scan and insert into that DBPAGE, update the free space value of dirEntry of DirPage
				dE->totalFreeSpace=dBPH_C->scanAndInsertIntoDBPage(dE->pageNumber,record,lengthOfRecord,0,rID_P); 
#ifdef INSTALLDEBUG				
				printf("\n\tAfter Insertion DirectoryEntry:Already Exists Case DEIndex=%4d;TFS=%2d;DBPN=%2ld at DE=%10u\t" ,i+1,dE->totalFreeSpace,dE->pageNumber,dE);                                                     // 0 means already exists
#endif				
				goto IIDBPEND;
				}
			dE=(DirectoryEntry*)((char*)aDPData +3 * sizeof(long)+(i+1)*(sizeof(long)+sizeof(short)));	
			}	// tested with dP->nDE=1360;

//Case 3*****************************Go for a next new DE if possible i.e.., only upon checking the upper bound of nDE in a DP
		if(dP->nDE < MAXDE)  // if dp->nDE == MAXDE, means that the DE entries are full so new DP page is required
			{
			dE->pageNumber=fL->getFreePage();
			dE->totalFreeSpace=MAXFS;
#ifdef INSTALLDEBUG			
			printf("\n\tB4 Insertion Directory Entry Full: New DE Case DEIndex=%4d; TFS=%2d; DBPN=%2ld at DE=%10u\t",
				  	i,dE->totalFreeSpace,dE->pageNumber,dE);
#endif					
		//insert the record and update the free space value of dirEntry of DirPage	1 as last argument means create a new one(DBPage)		
			dE->totalFreeSpace=dBPH_C->scanAndInsertIntoDBPage(dE->pageNumber,record,lengthOfRecord,1,rID_P); 				
			dP->nDE+=1;
#ifdef INSTALLDEBUG			
			printf("\n\tAfter Insertion Directory Entry Full: New DE Case DEIndex=%4d; TFS=%2d; DBPN=%2ld at DE=%10u\t",
				  	i,dE->totalFreeSpace,dE->pageNumber,dE);
#endif					
			goto IIDBPEND;
			}
		printf("\n NO MORE SPACE SO GO TO NEXT DP %d\n",dP->addressToNextDP);
		if(dP->addressToNextDP!=-1)
				tempPN=dP->addressToNextDP;	
		DirPageNum=dP->addressToNextDP;	
		} while(DirPageNum!=-1);									
	
//case 4*****************************Go for a new DirectoryPage as the current DP is full
	
	datum=MSF::myMalloc(PAGESIZE);	
	initializeDPandDE(datum);
	dP->addressToNextDP=fL->getFreePage();
	DirPageNum=tempPN;
	vSB_C->writeToBufferPool(dP->addressToNextDP,datum); 	
//	printf("\n-----------------CREATE A NEW DP DEAR aat %d",dP->addressToNextDP);
	findAndInsertToDEinDP(record,lengthOfRecord,dP->addressToNextDP,rID_P); //recursion

IIDBPEND:
#ifdef INSTALLDEBUG
	printf("\n\tAfter updation ????tfs=%d and pn=%ld and dP's nDE= %d",dE->totalFreeSpace,dP->addressToNextDP,dP->nDE);
#endif	
	vSB_C->writeToBufferPool(DirPageNum,aDPData);
	if(aDPData!=0)		MSF::myFree(aDPData);
	if(datum!=0)		MSF::myFree(datum);
	return;	
	}

void DPH :: freeTableStructure(long indexPN)//for freeing the table structure index pn	
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside freeTableStructure method of DPH class");	
#endif		
#ifdef INSTALLDEBUG	
	printf("\nIn freeTableStructure\n");
#endif	
	FLH *fL=FLH::getInstance();
	
	void * hPData=0;
	hPData=MSF::myMalloc(PAGESIZE);
	vSB_C->readFromBufferPool(indexPN,hPData);
	HeaderPage *hP=0;
	hP=(HeaderPage*)hPData;
	
	DirectoryPage *dP;
	DirectoryEntry *dE;
	void *dPData=0;
	long dPNum=hP->pNFirstDP;
	long tempPN=0;
	int loopCounter=0;
	dPData=MSF::myMalloc(PAGESIZE);
	do
		{
		vSB_C->readFromBufferPool(dPNum,dPData);
		dP=(DirectoryPage*)dPData;
		//dE=(DirectoryEntry*)((char*)dPData + 3 * sizeof(long));
		for(loopCounter=0;loopCounter<dP->nDE;loopCounter++)
			{
			dE=(DirectoryEntry*)((char*)dPData + 3 * sizeof(long)+loopCounter *(sizeof(short)+sizeof(long)));
			fL->addToFL(dE->pageNumber);
			}
		tempPN=dPNum;	
		dPNum=dP->addressToNextDP;
		fL->addToFL(tempPN);
		}while(dPNum!=-1);
	fL->addToFL(indexPN);	
	if(dPData!=0)		MSF::myFree(dPData);
	if(hPData!=0)		MSF::myFree(hPData);
	return;	
	}	
			
DPH :: ~DPH()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Destructor of DirectoryPageHandler DPH");
#endif			
	}	

//*********************************************TableScan*************************************************************
// Calls BufferManager's Read From Buffer Pool method  to read the headerpage, filename and void *data
// then calls Directory Page Handler DPH to handle the directory page as specified in the header page
// Header Page Handler to satisify queries with no where clause directly
TableScan* TableScan :: singleInstance_C=0;
TableScan* TableScan :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES
		printf("\n\t\tIn Static Invoker of TableScan");	
#endif		
	        singleInstance_C = new TableScan();
		}
	return singleInstance_C;	
	}
	
TableScan :: TableScan()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Constructor of TableScan");
#endif			
	vSB_C=VSBufferManager :: getInstance();
	sCH_C=SysCatHan :: getInstance();
	dPH_C=DPH :: getInstance();
	}
	
int TableScan :: doTableScan(char *tableName_P, char *databaseName_P,RID **rID,FieldNames *fNames_P,int type,char *columnName,char *value,short operation) 
	{	//make use of database, if fNames is NULL means all the columns are to be displayed and rID is populated accordingly, type specifies the 
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside doTableScan method of TableScan class");	
#endif			
	int returnFlag=0;
	void *hPData=0;
	HeaderPage *hP;
	createColumns *tempColumns;
	createColumns *columns=NULL;
	long hPageNumber=sCH_C->returnTableExistence(tableName_P,databaseName_P,CHECK);
	#ifdef TSDEBUG
	printf("\n\tIN TABLE SCAN's doTableScan Table Name=%s  Database Name=%s , hPN=%d",tableName_P,databaseName_P,hPageNumber);
	#endif
	if( hPageNumber!=FAILED)
		{
		hPData=MSF::myMalloc(PAGESIZE);
		vSB_C->readFromBufferPool(hPageNumber,hPData);
		hP=(HeaderPage*)hPData;
		#ifdef TSDEBUG
		printf("\n\tIn Header Page \tPageNumber = %ld\tTotNumRec=%d\tTotNumDP=%d\tMaxDEInDP=%d\tPNFirstDP=%d",
							hPageNumber,hP->totNumRec,hP->totNumDP,hP->maxDEInDP,hP->pNFirstDP);  
		#endif					
		if(hP->pNFirstDP==-1) // this should be replaced with totNumRec
			{
			printf("\n\tTable \"%s\" is EMPTY",tableName_P);
			goto DTSEND;
			}	
		else
			{
			sCH_C->getDetailsOfFields(tableName_P,databaseName_P,&columns);
			if(fNames_P==NULL) //requested for a select * operation
				{} 
			else  		   //requested for some specific columns in frames_P  
				{			
				tempColumns=columns;
				columns=NULL;
				if(TLQH :: testAndUpdateList(&columns,tempColumns,fNames_P)==FAILED)
					returnFlag=1;	
				TLQds *ds=(TLQds*)MSF::myMalloc(sizeof(TLQds));
				ds->dbname=NULL;
				ds->pKeyFields=NULL;
				ds->uniqueFields=NULL;
				ds->objectName=NULL;
				ds->columns=tempColumns;
				TLQH :: freeList(ds);
				if(returnFlag==1)	goto DTSEND;
				}
			#ifdef TSDEBUG	
			TLQH :: displayList(columns);	
			#endif
			dPH_C->scanDPHForColumns(hP->pNFirstDP,columns,rID,type,columnName,value,operation);	
			}								
		}
	else
		{
		printf("\n\tRequested Table \"%s\" Doesnot Exist in \"%s\" database!",tableName_P,databaseName_P);
		goto DTSEND;
		}	
DTSEND:	
	TLQds *dst=(TLQds*)MSF::myMalloc(sizeof(TLQds));
	dst->dbname=NULL;
	dst->objectName=NULL;
	dst->columns=columns;
	dst->pKeyFields=NULL;
	dst->uniqueFields=NULL;
	TLQH :: freeList(dst);		
	if(hPData!=0)	MSF::myFree(hPData);
	if(returnFlag==1)	return FAILED;
	else			return SUCCESS;
	}
			
TableScan :: ~TableScan()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Destructor of TableScan");
#endif			
	}	
	
void TableScan :: readAndPrint(int hPN, int numberOfFields) // directory PageNumber
	{
	printf("\n In Table Scan\n");
	void *hPData=0;
	void *dPData=0;
	void *dBData=0;
	void *record=0;
	void *tempData=0;
	HeaderPage *hP;
	DirectoryPage *dP;
	DirectoryEntry *dE;
	DataBasePage *dBP;
	SlotMap *sM;
	long dPNum;
	int loopCounter=0,iLoopCounter=0;
	hPData=MSF::myMalloc(PAGESIZE);
	dBData=MSF::myMalloc(PAGESIZE);
	dPData=MSF::myMalloc(PAGESIZE);
	vSB_C->readFromBufferPool(hPN,hPData);
	hP=(HeaderPage *)hPData;
#ifdef INSTALLDEBUG	
	printf("\n\tIn Header Page \tPageNumber = %ld\tTotNumRec=%d\tTotNumDP=%d\tMaxDEInDP=%d\tPNFirstDP=%d",
							hPN,hP->totNumRec,hP->totNumDP,hP->maxDEInDP,hP->pNFirstDP);  
#endif							
	dPNum=hP->pNFirstDP;						
	do
		{
		vSB_C->readFromBufferPool(dPNum,dPData);
		dP=(DirectoryPage*)dPData;
		dE=(DirectoryEntry*)((char*)dPData + 3 * sizeof(long));
#ifdef INSTALLDEBUG		
		printf("\n\t\tIn Directory Page \n\t\tPageNumber = %ld\n\t\tnDE=%d\n\t\tmaxFS=%d\n\t\taddressToNextDP=%d",
							dPNum,dP->nDE,dP->maxFS,dP->addressToNextDP);
#endif							
		for(loopCounter=0;loopCounter<dP->nDE;loopCounter++)
			{
#ifdef INSTALLDEBUG			
			printf("\n\t\t\tIn Directory Entry %d\n\ttotalFreeSpace=%d\n\tpageNumber=%ld",loopCounter,dE->totalFreeSpace,dE->pageNumber);
#endif			
			vSB_C->readFromBufferPool(dE->pageNumber,dBData);
			dBP=(DataBasePage*)((char*)dBData + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));
#ifdef INSTALLDEBUG			
			printf("\n\t\t\tIn DataBasePage PageNumber %ld  ;timeStamp=%ld;  \n\t\t\t\trecordsInSlots=%ld; totalNumberOfSlots=%ld;  totalFreeSpace=%d ;  ConFreeSpace=%d",
			          dE->pageNumber,dBP->timeStamp,dBP->recordsInSlots,dBP->totalNumberOfSlots,dBP->totalFreeSpace,dBP->conFreeSpace);
#endif				  
			sM=(SlotMap*)((char*)dBData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-1*(1*sizeof(long)+1*sizeof(short)));
#ifdef INSTALLDEBUG			
			printf("\n\t\t\t\tCFS SLOT\toffset=%d\tlength=%d",sM->offset,sM->recordLength);
#endif			
			sM=(SlotMap*)((char*)dBData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-2*(1*sizeof(long)+1*sizeof(short)));
			for(iLoopCounter=0;iLoopCounter<dBP->totalNumberOfSlots;iLoopCounter++)
				{
				tempData=(void*)((char*)dBData + sM->offset);
				short *offset1=0,*tempoffset=0;
				int loopCounter1=0;
				offset1=(short*)((char*)tempData);
				char *utemp1;
				char *temp1=0;				
				printf("\nIn Print Record ");				
				for(;loopCounter1<numberOfFields;loopCounter1++)
					{
					if(loopCounter1== 1 || loopCounter1== 0 || loopCounter1 == 2)	
						{
						temp1=(char*)tempData+*offset1;
						printf(" %10s",temp1);
						offset1++;
						}
					else if(loopCounter1==6)
						{
						tempoffset=offset1;
						temp1=(char*)tempData+*offset1;
                        			offset1++;		
						if(*tempoffset!=*offset1)	
							printf("%5s",temp1);
						else
							printf("NULL ");				
						}	
					else 
						{
		     			   	utemp1=(char*)tempData+*offset1;
						printf(" %5s",(utemp1));
						offset1++;
						}
					}
#ifdef INSTALLDEBUG					
				printf(" offset=%d length=%d",sM->offset,sM->recordLength);			
#endif				
				sM=(SlotMap*)((char*)dBData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(iLoopCounter+2+1)*(1*sizeof(long)+1*sizeof(short)));
				}
#ifdef INSTALLDEBUG				  
			printf("\n\t\tIn Directory Entry %d\ttotalFreeSpace=%d\tpageNumber=%ld",loopCounter,dE->totalFreeSpace,dE->pageNumber);	
			printf("\n\t\t\tIn DataBasePage PageNumber %ld  ;timeStamp=%ld;  \n\t\t\t\trecordsInSlots=%ld; totalNumberOfSlots=%ld;  totalFreeSpace=%d ;  ConFreeSpace=%d",
			          dE->pageNumber,dBP->timeStamp,dBP->recordsInSlots,dBP->totalNumberOfSlots,dBP->totalFreeSpace,dBP->conFreeSpace);	
#endif			
			dE=(DirectoryEntry*)((char*)dPData + 3 * sizeof(long) + (loopCounter+1)*(sizeof(long)+sizeof(short)));	  
			}					
		dPNum=dP->addressToNextDP;
		} while(dPNum!=-1);
	
	if(hPData!=0) MSF::myFree(hPData);
	if(dPData!=0) MSF::myFree(dPData);
	if(dBData!=0) MSF::myFree(dBData);
	if(record!=0) MSF::myFree(record);
	}
	
		
//************************************************Fetch**************************************************************
// In case of where condition this class serves the purpose	
Fetch* Fetch :: singleInstance_C=0;
Fetch* Fetch :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES
		printf("\n\t\tIn Static Invoker of Fetch");	
#endif		
	        singleInstance_C = new Fetch();
		}
	return singleInstance_C;	
	}
	
Fetch :: Fetch()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Constructor of Fetch");
#endif			
	vSB_C=VSBufferManager :: getInstance();
	rH_C =RH :: getInstance();
	}
	
Fetch :: ~Fetch()
	{
#ifdef DBCONDES	
	printf("\n\t\t  In Destructor of Fetch");
#endif			
	}

void Fetch::fetchRIDs(RID *sourceRIDList,RID **qualifiedRIDList,int type,char *columnName,short operation,char * value, createColumns *columns)
	{//if type ==DISPLAY then qualifiedRIDList,columnName,operation,value can be NULL
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside fetchRIDs method of Fetch class");	
#endif		
	void *tempData=0;
	DataBasePage *dBP;
	SlotMap *sM;
	tempData=MSF::myMalloc(PAGESIZE);
	dBP=(DataBasePage*)((char*)tempData + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));
	int noc=0;
	if(type==DISPLAY)
		{
		printf("\n ");
		createColumns *temp=columns;
		while(temp!=NULL)
			{
			printf("%10s",temp->columnName);
			noc++;
			temp=temp->next;
			}
		printf("\n   ");	
		while(noc--)		
			printf("----------");
		}
	while(sourceRIDList!=NULL)
		{
		vSB_C->readFromBufferPool(sourceRIDList->pageNumber,tempData);
		sM=(SlotMap*)((char*)tempData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(sourceRIDList->slotID+1)*(1*sizeof(long)+1*sizeof(short)));
		if(rH_C->handleRecord(tempData,sM,columns,type,columnName,value,operation)==SUCCESS)
			if(qualifiedRIDList!=NULL)
				RH::insertToRIDList(qualifiedRIDList,sourceRIDList->pageNumber,sourceRIDList->slotID);
		sourceRIDList=sourceRIDList->next;
		}
	if(tempData!=0)	MSF::myFree(tempData);
	}	

void Fetch::fetchColumnValues(RID *sourceRIDList,AttributeValues **values,char *columnName,createColumns *columns)	
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside fetchColumnValues method of Fetch class");	
#endif			
	void *tempData=0;
	DataBasePage *dBP;
	SlotMap *sM;
	short *offset=0;
	short dataType,position;
	char *string=0;
	tempData=MSF::myMalloc(PAGESIZE);
	dBP=(DataBasePage*)((char*)tempData + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));
	while(columns!=NULL)
		{
		if(!strcmp(columns->columnName,columnName))
			{
			dataType=columns->dataType;
			position=columns->position;
			break;
			}	
		columns=columns->next;
		}
	while(sourceRIDList!=NULL)
		{
		sM=0;
#ifdef FETDEBUG		
		printf("\n %d %d RID %d %d",sourceRIDList->pageNumber,sourceRIDList->slotID,dataType,position);
#endif		
		vSB_C->readFromBufferPool(sourceRIDList->pageNumber,tempData);
		sM=(SlotMap*)((char*)tempData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(sourceRIDList->slotID+1)*(1*sizeof(long)+1*sizeof(short)));
		
		offset=(short*)((char*)tempData+sM->offset+(position-1)*sizeof(short));
		string=(char*)tempData+sM->offset+*offset;
#ifdef FETDEBUG
		printf("\t %s is String %ld %ld",string,sM,*offset);
#endif
		RLQH::insertToAttList(values,string);
		sourceRIDList=sourceRIDList->next;
		}
	if(tempData!=0)	MSF::myFree(tempData);
	}

void Fetch::fetchColumnValues(RID *sourceRIDList,AttributeValues **values1,AttributeValues **values2,
                                                 char *columnName1        ,char *columnName2        ,createColumns *columns)	
	{
#ifdef VERBOSEMODE
	printf("\n\t\t\t\tInside fetchColumnValues method of Fetch class");	
#endif			
	void *tempData=0;
	DataBasePage *dBP;
	SlotMap *sM;
	short *offset1=0,*offset2=0;
	short position1,position2;
	char *string1=0;
	char *string2=0;
	tempData=MSF::myMalloc(PAGESIZE);
	dBP=(DataBasePage*)((char*)tempData + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));
	while(columns!=NULL)
		{
		if(!strcmp(columns->columnName,columnName1))
			position1=columns->position;
		if(!strcmp(columns->columnName,columnName2))
			position2=columns->position;	
		columns=columns->next;
		}
	while(sourceRIDList!=NULL)
		{
		sM=0;
#ifdef FETDEBUG		
		printf("\n %d %d RID %d %d",sourceRIDList->pageNumber,sourceRIDList->slotID,position1,position2);
#endif		
		vSB_C->readFromBufferPool(sourceRIDList->pageNumber,tempData);
		sM=(SlotMap*)((char*)tempData + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(sourceRIDList->slotID+1)*(1*sizeof(long)+1*sizeof(short)));
		
		offset1=(short*)((char*)tempData+sM->offset+(position1-1)*sizeof(short));
		offset2=(short*)((char*)tempData+sM->offset+(position2-1)*sizeof(short));
		string1=(char*)tempData+sM->offset+*offset1;
		string2=(char*)tempData+sM->offset+*offset2;
#ifdef FETDEBUG		
		printf("\t %s is String1 %ld %ld and %s is String2 %ld %ld",string1,sM,*offset1,string2,sM,*offset2);
#endif		
		RLQH::insertToAttList(values1,string1);
		RLQH::insertToAttList(values2,string2);
		sourceRIDList=sourceRIDList->next;
		}
	if(tempData!=0)	MSF::myFree(tempData);
	}	
 