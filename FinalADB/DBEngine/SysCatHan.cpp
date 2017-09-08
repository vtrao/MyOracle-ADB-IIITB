#include "BufferManager/standards.h"
#include "VSDBEngine.h"
//#define SYSDEBUG 12
/*********************************CreateTable Query Handler***********************************/
SysCatHan* SysCatHan :: singleInstance_C=0;

SysCatHan* SysCatHan :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES		
		printf("\n\tIn Static Invoker of SysCatHan");
#endif			
		singleInstance_C= new SysCatHan();	
		}
	return singleInstance_C;
        }

SysCatHan :: SysCatHan()
        {
#ifdef DBCONDES
	printf("\n\t  In Constructor of SysCatHan");
#endif
	vSB_C=VSBufferManager::getInstance();
	SdBHDataC=MSF::myMalloc(PAGESIZE);
	ShPDataC=MSF::myMalloc(PAGESIZE);	
	SdPDataC=MSF::myMalloc(PAGESIZE);
	SdBDataC=MSF::myMalloc(PAGESIZE);
        }

SysCatHan :: ~SysCatHan()
	{
#ifdef DBCONDES
	printf("\n\t  In Destructor of SysCatHan");
#endif
	if(SdPDataC!=0)		MSF::myFree(SdPDataC);
	if(SdBDataC!=0)		MSF::myFree(SdBDataC);
	if(SdBHDataC!=0)	MSF::myFree(SdBHDataC);	
	if(ShPDataC!=0)		MSF::myFree(ShPDataC);
	}	

void SysCatHan :: getDetailsOfFields(char *tableName_P,char *databaseName_P,createColumns **columns_P)
	{
#ifdef VERBOSEMODE		
	printf("\n\t\t\tIN getDetailsOfFields method of SysCatHan Class :%s table and %s dbname ",tableName_P,databaseName_P);
#endif	
	DirectoryPage *dP;
	DirectoryEntry *dE;
	DataBasePage *dBP;
	SlotMap *sM;
	int dPNum=9,loopCounter=0,iLoopCounter=0;  // 9 is the First dp of attribute Catalog
	do
		{
		vSB_C->readFromBufferPool(dPNum,SdPDataC);
		dP=(DirectoryPage*)SdPDataC;
		dE=(DirectoryEntry*)((char*)SdPDataC + 3 * sizeof(long));;
		for(loopCounter=0;loopCounter<dP->nDE;loopCounter++)
			{
			vSB_C->readFromBufferPool(dE->pageNumber,SdBDataC);
			dBP=(DataBasePage*)((char*)SdBDataC + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));
			sM=(SlotMap*)((char*)SdBDataC + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(2)*(1*sizeof(long)+1*sizeof(short)));
			for(iLoopCounter=0;iLoopCounter<dBP->totalNumberOfSlots;iLoopCounter++)
				{				
				void *tempData=(void*)((char*)SdBDataC + sM->offset);
				short *offset1,tempOffset=0;
				int loopCounter1=0;
				offset1=(short*)tempData;
				char *attlen,*preci,*nnull,*unique,*pkey,*pos;
				char *temp1,*cname,*dtype,*defval;								
				if(loopCounter==0)
					{
					temp1=(char*)tempData+*offset1;
					if(!strcmp(temp1,databaseName_P))
						{
						offset1++;
						temp1=(char*)tempData+*offset1;
						if(!strcmp(temp1,tableName_P))
							{
							//printf("\n %10s",temp1);
							offset1++;
							cname=(char*)tempData+*offset1; //	printf("\t%s",cname);
							offset1++;
							dtype=(char*)tempData+*offset1; //      printf("\t%s",dtype);
							offset1++;
							attlen=(char*)tempData+*offset1; //printf("\t%d",*attlen);
							offset1++;
							preci=(char*)tempData+*offset1;  //printf("\t%d",*preci);
							tempOffset=*offset1;	
							offset1++;	
							if(tempOffset==*offset1)
								{
								defval=NULL;//printf("\t NULL");
								}
							else
								{	
								defval=(char*)tempData+*offset1;
								}	
							offset1++;
							pos=(char*)tempData+*offset1; //	printf("\t%d",*pos);
							offset1++;
							pkey=(char*)tempData+*offset1;//	printf("\t%d",*pkey);
							offset1++;
							nnull=(char*)tempData+*offset1;//	printf("\t%d",*nnull);
							offset1++;
							unique=(char*)tempData+*offset1;//	printf("\t%d",*unique);
							TLQH :: InsertToList(columns_P,cname,atoi(dtype),atoi(attlen),atoi(preci),defval,
							                                     atoi(nnull),atoi(unique),atoi(pkey),atoi(pos));
							}
						}	
					}					
				sM=(SlotMap*)((char*)SdBDataC + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(iLoopCounter+2+1)*(1*sizeof(long)+1*sizeof(short)));
				}
			dE=(DirectoryEntry*)((char*)SdPDataC + 3 * sizeof(long) + (loopCounter+1)*(sizeof(long)+sizeof(short)));			  
			}
		dPNum=dP->addressToNextDP;
		} while(dPNum!=-1);
	}
	
int SysCatHan :: returnTableExistence(char *tableName,char *dbname_P,int type)           //returns the headerpage of table if exists else FAILED
	{
#ifdef VERBOSEMODE		
	printf("\n\t\t\tIN returnTableExistence method of SysCatHan Class: %s table and %s database ",tableName,dbname_P);
#endif	
	int returnFlag=0,dPNum=0,loopCounter=0,iLoopCounter=0;               		                         //Returns SUCCESS or FAILED accordingly
	DBHeader *dBH;
	HeaderPage *hP;
	DirectoryPage *dP;
	DirectoryEntry *dE;
	DataBasePage *dBP;
	SlotMap *sM;
	void *tempData=0;
	vSB_C->readFromBufferPool(0,SdBHDataC);
	dBH=(DBHeader*)SdBHDataC;
	vSB_C->readFromBufferPool(dBH->tCatPointer,ShPDataC);
	hP=(HeaderPage*)ShPDataC;
	char *temp1,*temp2,*temp3;
	dPNum=hP->pNFirstDP;
	if(type==DISPLAY) printf("\n\tContents of \"%s\" DataBase",dbname_P);
	do
		{
#ifdef SYSDEBUG				
		printf("\n here in do while");
#endif		
		vSB_C->readFromBufferPool(dPNum,SdPDataC);
#ifdef SYSDEBUG			
		printf("\n dpNum %d",dPNum);
#endif			
		dP=(DirectoryPage*)SdPDataC;
		dE=(DirectoryEntry*)((char*)SdPDataC + 3 * sizeof(long));
#ifdef SYSDEBUG			
		printf("\n dP->nDE=%d,",dP->nDE);	
#endif			
		for(loopCounter=0;loopCounter<dP->nDE;loopCounter++)
			{
#ifdef SYSDEBUG				
			printf("\n%s table Name dE->pageNumber=%d,",tableName,dE->pageNumber);
#endif				
			vSB_C->readFromBufferPool(dE->pageNumber,SdBDataC);
			dBP=(DataBasePage*)((char*)SdBDataC + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));			
			sM=(SlotMap*)((char*)SdBDataC + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(2)*(1*sizeof(long)+1*sizeof(short)));
#ifdef SYSDEBUG				
			printf("\nNOSlots %d",dBP->totalNumberOfSlots);
#endif				
			for(iLoopCounter=0;iLoopCounter < dBP->totalNumberOfSlots;iLoopCounter++)
				{
#ifdef SYSDEBUG					
				printf("\n%d is offset,%d is length",sM->offset,sM->recordLength);
#endif					
				if(sM->offset<0) 
					{
#ifdef SYSDEBUG						
					printf("\n Escaped this value");
#endif						
					goto ESCAPEDD;
					}
				tempData=(void*)((char*)SdBDataC + sM->offset);
				short *offset;
				offset=(short*)tempData;
				temp1=(char*)tempData+*offset;	
				if(!strcmp(dbname_P,temp1))//if database name matches			
					{
					offset++;
					temp2=(char*)tempData+*offset;
					if(type==CHECK)
						{	
						if(!strcmp(tableName,temp2)) 
							{
#ifdef SYSDEBUG								
							printf("\n RIght Here");
#endif								
							offset++;
							temp3=(char*)tempData+*offset;//babu jagratha nana
							returnFlag=1;
							goto RDBEND;
							}
						}
					else if(type==DISPLAY)
						{
						returnFlag=2;
						printf("\n\t\t%s",temp2);
						}
					}
				ESCAPEDD:	
				sM=(SlotMap*)((char*)SdBDataC + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(iLoopCounter+2+1)*(1*sizeof(long)+1*sizeof(short)));	
				} 
			dE=(DirectoryEntry*)((char*)SdPDataC + 3 * sizeof(long) + (loopCounter+1)*(sizeof(long)+sizeof(short)));	 			
			}					
		dPNum=dP->addressToNextDP;
		}while(dPNum!=-1);
RDBEND:		
	if(returnFlag==1)
		{
#ifdef SYSDEBUG			
		printf("\nreturning value %d",atoi(temp3));
#endif			
		return atoi(temp3);
		}
	else if(returnFlag==2)
		return SUCCESS;
	else
		return FAILED;		
	}
	
int SysCatHan :: returnDataBaseExistence(char *databaseName,int type)     //sets the static DATABASENAME_C to database if exists
	{ 
#ifdef VERBOSEMODE		
	printf("\n\t\t\tIN returnDataBaseExistence method of SysCatHan Class: %s databasename",databaseName);
#endif	
	int returnFlag=0,dPNum=0,loopCounter=0,iLoopCounter=0;               		                         //Returns SUCCESS or FAILED accordingly
	DBHeader *dBH;
	HeaderPage *hP;
	DirectoryPage *dP;
	DirectoryEntry *dE;
	DataBasePage *dBP;
	SlotMap *sM;
	void *tempData=0;
	
	vSB_C->readFromBufferPool(0,SdBHDataC);
	dBH=(DBHeader*)SdBHDataC;
	vSB_C->readFromBufferPool(dBH->dbCatPointer,ShPDataC);
	hP=(HeaderPage*)ShPDataC;
	char *temp1;
	dPNum=hP->pNFirstDP;
	if(type==DISPLAY) printf("\n\tContents of Relational DataBase Management System");
	do
		{		
		vSB_C->readFromBufferPool(dPNum,SdPDataC);
		dP=(DirectoryPage*)SdPDataC;
		dE=(DirectoryEntry*)((char*)SdPDataC + 3 * sizeof(long));
		for(loopCounter=0;loopCounter<dP->nDE;loopCounter++)
			{
			vSB_C->readFromBufferPool(dE->pageNumber,SdBDataC);
			dBP=(DataBasePage*)((char*)SdBDataC + PAGESIZE - 3*sizeof(long) - 2* sizeof(short));			
			sM=(SlotMap*)((char*)SdBDataC + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(2)*(1*sizeof(long)+1*sizeof(short)));
			for(iLoopCounter=0;iLoopCounter < dBP->totalNumberOfSlots;iLoopCounter++)
				{
				if(sM->offset<0) goto ESCAPED;
				tempData=(void*)((char*)SdBDataC + sM->offset);
				short *offset;
				offset=(short*)tempData;
				temp1=(char*)tempData+*offset;
				if(type==CHECK)
					{	
					if(!strcmp(databaseName,temp1)) 
						{
						returnFlag=1;
						goto RDBEND;
						}
					}
				else if(type==DISPLAY)
					{
					printf("\n\t\t%s",temp1);
					returnFlag=1;
					}
				ESCAPED:	
				sM=(SlotMap*)((char*)SdBDataC + PAGESIZE-3*sizeof(long)-2*sizeof(short)-(iLoopCounter+2+1)*(1*sizeof(long)+1*sizeof(short)));
				}
			dE=(DirectoryEntry*)((char*)SdPDataC + 3 * sizeof(long) + (loopCounter+1)*(sizeof(long)+sizeof(short)));	  			
			}					
		dPNum=dP->addressToNextDP;
		}while(dPNum!=-1);
RDBEND:	
	if(returnFlag==1)		return SUCCESS;
	else 				return FAILED;		
	}

int SysCatHan :: returnIndexExistence(char *databaseName,char *tableName,FieldNames *fNames) //Returns the Pageno of Index
	{                                
	TableScan *tbScan=TableScan::getInstance();
	Fetch *fetch     =    Fetch::getInstance();
	RID *s1RID=NULL;
	RID *s2RID=NULL;
	createColumns *columns=NULL;
	AttributeValues *avalues=NULL;
	AttributeValues *indvalues=NULL;
	AttributeValues *cvalues=NULL;
	AttributeValues *pvalues=NULL;
	short indexFound=0;
	tbScan->doTableScan("icat","sys",&s1RID,NULL,CHECK,"dbname",databaseName,EQ);		//step 1  Filtering the dbname
	
	getDetailsOfFields("icat","sys",&columns);						//step 2a Getting the column structure of icat
	
	fetch->fetchRIDs(s1RID,&s2RID,CHECK,"tname",EQ,tableName,columns);			//step 2b Filtering the tablename
		
	fetch->fetchColumnValues(s2RID,&avalues,&indvalues,"iname","indpn",columns);		//step 3  populating the avalues with inames
	
	RH::freeRIDList(s1RID);	s1RID=NULL;			//
	RH::freeRIDList(s2RID);	s2RID=NULL;			//Used during the scan of icat...and will be reused to scan iacat
	TLQH::freeCColumns(columns); columns=NULL;		//
	
#ifdef SYSDEBUG		
	printf("\n\n IN return Index Existence\n");
#endif	
	AttributeValues *temp=avalues,*temp1=indvalues,*temp2,*temp3;
	FieldNames *fTemp;
	int sequence=0;
#ifdef SYSDEBUG		
	while(temp!=NULL)
		{
		printf("\n %s in inamae and %s is indpn",temp->value,temp1->value);
		temp=temp->next;
		temp1=temp1->next;
		}
	printf("\nStart getting data from iacat\n");
#endif	
	getDetailsOfFields("iacat","sys",&columns);
	temp=avalues;
	temp1=indvalues;
	while(temp!=NULL)
		{
#ifdef SYSDEBUG			
		printf("\n********CHECK:%s is iname %s is indpn",temp->value,temp1->value);
#endif
		tbScan->doTableScan("iacat","sys",&s1RID,NULL,CHECK,"iname",temp->value,EQ);
		RH::displayRIDList(s1RID);
			
		fetch->fetchColumnValues(s1RID,&cvalues,&pvalues,"fname","position",columns);
		fTemp=fNames;
		sequence=0;
		while(fTemp!=NULL) //user input array
			{
			++sequence;
			temp2=cvalues;
			temp3=pvalues;
			while(temp2!=NULL)
				{
				if(sequence==atoi(temp3->value) && !strcmp(fTemp->name,temp2->value))
					{
#ifdef SYSDEBUG						
					printf("\nSUCCESS %s in fname and %s is position",temp2->value,temp3->value);
#endif					
					indexFound=atoi(temp1->value);
					break;
					}
				else
					{
					indexFound=FAILED;
					}
				temp2=temp2->next;
				temp3=temp3->next;
				}
			fTemp=fTemp->next;	
			if(fTemp==NULL && indexFound!=FAILED)
				{
				RLQH::freeAttList(cvalues);cvalues=NULL;
				RLQH::freeAttList(pvalues);pvalues=NULL; 	
				RH::freeRIDList(s1RID);	s1RID=NULL;
				goto RIEEND;
				}
			}	
		RLQH::freeAttList(cvalues);cvalues=NULL;
		RLQH::freeAttList(pvalues);pvalues=NULL; 	
		RH::freeRIDList(s1RID);	s1RID=NULL;
	;	temp=temp->next;
		temp1=temp1->next;
		}
RIEEND:		
	TLQH::freeCColumns(columns); columns=NULL;		
	RH::freeRIDList(s1RID);
	RLQH::freeAttList(avalues);
	RLQH::freeAttList(indvalues); 
	return indexFound;
	}	

int SysCatHan :: returnIndexExistence(char *databaseName,char *tableName,IndexOnTable **iOT) //Returns the structure of indexes on table
	{
#ifdef VERBOSEMODE		
	printf("\n\t\t\tIN returnIndexExistence method of SysCatHan Class: %s database and %s table",databaseName,tableName);
#endif		   		   
	TableScan *tbScan=TableScan::getInstance();
	Fetch *fetch     =    Fetch::getInstance();
	RID *s1RID=NULL;
	RID *s2RID=NULL;
	createColumns *columns=NULL;
	AttributeValues *avalues=NULL;
	AttributeValues *indvalues=NULL;
	AttributeValues *cvalues=NULL;
	AttributeValues *pvalues=NULL;
	
	tbScan->doTableScan("icat","sys",&s1RID,NULL,CHECK,"dbname",databaseName,EQ);		//step 1  Filtering the dbname	
	getDetailsOfFields("icat","sys",&columns);						//step 2a Getting the column structure of icat	
	fetch->fetchRIDs(s1RID,&s2RID,CHECK,"tname",EQ,tableName,columns);			//step 2b Filtering the tablename		
	fetch->fetchColumnValues(s2RID,&avalues,&indvalues,"iname","indpn",columns);		//step 3  populating the avalues with inames	
	RH::freeRIDList(s1RID);	s1RID=NULL;			//
	RH::freeRIDList(s2RID);	s2RID=NULL;			//Used during the scan of icat...and will be reused to scan iacat
	TLQH::freeCColumns(columns); columns=NULL;		//
	//avalues holds the indexes Name defined on the table and indvalues holds the corresponding page numbers 
	getDetailsOfFields("iacat","sys",&columns);
	AttributeValues *temp=avalues,*temp1=indvalues,*temp2,*temp3;
	FieldNames *fn=NULL;
	int nof=0,i;
	while(temp!=NULL)
		{
		nof=0;
		tbScan->doTableScan("iacat","sys",&s1RID,NULL,CHECK,"iname",temp->value,EQ);
		//RH::displayRIDList(s1RID);
		fetch->fetchColumnValues(s1RID,&cvalues,&pvalues,"fname","position",columns);
		temp2=cvalues;
		while(temp2!=NULL)
			{
			++nof;
			temp2=temp2->next;
			}	
		for(i=1;i<=nof;i++)
			{
			temp2=cvalues;temp3=pvalues;
			while(temp2!=NULL)
				{
				if(atoi(temp3->value)==i)
					{
#ifdef SYSDEBUG						
					printf("\n\t\t\tInserting %s column %d is position",temp2->value,atoi(temp3->value));
#endif					
					RLQH::insertToFdList(&fn,temp2->value);
					RLQH::deleteFromAttList(&cvalues,temp2->value);//deleting the values used 
					RLQH::deleteFromAttList(&pvalues,temp3->value);//deleting the values used
					break;
					}					
				temp3=temp3->next;
				temp2=temp2->next;
				}
			}
		RH::freeRIDList(s1RID);	s1RID=NULL;	
#ifdef SYSDEBUG			
		printf("\n\t\t%s is indexname and %d is pageNumber",temp->value,atoi(temp1->value));
#endif		
		SysCatHan::insertToIOT(iOT,temp->value,fn,atoi(temp1->value));
		fn=NULL;	
		temp1=temp1->next;//this holds the pagenumbers		
		temp=temp->next;  //this holds the index names
		}
	TLQH::freeCColumns(columns); columns=NULL;
	RLQH::freeAttList(avalues);
	RLQH::freeAttList(indvalues);
	}

int SysCatHan :: returnIndexExistence(char *databaseName,char *tableName,char *columnName)	
	{
#ifdef VERBOSEMODE		
	printf("\n\t\t\tIN returnIndexExistence method of SysCatHan Class: %s database, %s table, %s Column",databaseName,tableName,columnName);
#endif		   		   	
	IndexOnTable *iOT=NULL;
	returnIndexExistence(databaseName,tableName,&iOT);
	if(iOT==NULL)
		return FAILED;
	else
		{
		IndexOnTable *headIOT=iOT;	
		while(headIOT!=NULL)
			{
#ifdef RLQDEBUG	
			printf("\nIndex Name %s at %d",headIOT->indexName,headIOT->pageNumber);
#endif				
			if(!strcmp((headIOT->fieldNames)->name,columnName))
				{
				SysCatHan :: freeIOT(iOT);		
				return headIOT->pageNumber;
				}
			
			headIOT=headIOT->next;
			}
		}
	SysCatHan :: freeIOT(iOT);		
	return FAILED;
	}

void SysCatHan :: insertToIOT(IndexOnTable **head,char *indexName,FieldNames *fd,long pageNumber)
	{
	if(*head==NULL)
		{
		*head=(IndexOnTable*)MSF::myMalloc(sizeof(IndexOnTable));
		
		(*head)->indexName=(char*)MSF::myMalloc(strlen(indexName));
		strcpy((*head)->indexName,indexName);
		(*head)->pageNumber=pageNumber;
		(*head)->fieldNames=fd;
		(*head)->next=NULL;
		}	
	else
		{
		IndexOnTable *t=(*head);	
		while(t->next!=NULL)
			t=t->next;
		IndexOnTable *temp;	
		temp=(IndexOnTable*)MSF::myMalloc(sizeof(IndexOnTable));
		
		temp->indexName=(char*)MSF::myMalloc(strlen(indexName));
		strcpy(temp->indexName,indexName);
		temp->pageNumber=pageNumber;
		temp->fieldNames=fd; 
		temp->next=NULL;
		t->next=temp;
		}
	}
	
void SysCatHan :: displayIOT(IndexOnTable *head)
	{
	FieldNames *tempF;
	while(head!=NULL)
		{
		printf("\n\tIndex Name \"%s\" defined at %d",head->indexName,head->pageNumber);
		tempF=head->fieldNames;
		while(tempF!=NULL)
			{
			printf("\n\t\t%s is Field",(tempF)->name);
			tempF=tempF->next;
			}
		head=head->next;
		}
	printf("\n");	
	}
	
void SysCatHan :: freeIOT(IndexOnTable *head)
	{
	IndexOnTable *temp;
	while(head!=NULL)
		{
		temp=head;
		RLQH :: freeFdList(head->fieldNames);
		head=head->next;
		MSF::myFree(temp->indexName);
		MSF::myFree(temp);
		}
	head=NULL;	
	}
  !€sJ