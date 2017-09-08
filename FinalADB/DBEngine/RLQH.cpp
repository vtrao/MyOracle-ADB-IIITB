#include "BufferManager/standards.h"
#include "VSDBEngine.h"
//#define RLQDEBUG
/****************************Select Query Handler*********************************************/
SQH* SQH :: singleInstance_C=0;

SQH* SQH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES		
		printf("\n\t\tIn Static Invoker of SQH of RLQH");
#endif			
                singleInstance_C = new SQH();
		}
        return singleInstance_C;
	}	
	
SQH :: SQH() //constructor
        {
#ifdef DBCONDES
	printf("\n\t\t  In Constructor of SQH of RLQH");
#endif		
        sCH_C=SysCatHan::getInstance();	
        }

SQH :: ~SQH()
	{
#ifdef DBCONDES
	printf("\n\t\t  In Destructor of SQH of RLQH");
#endif	
	}

int SQH::displayRIDListOnRetreival(char *tableName_P,char *databaseName_P,FieldNames *fNames_P,RID *rID_P)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside displayRIDListOnRetrieval method of SQH class %s dbname and %s tableName",databaseName_P,tableName_P);	
#endif		
	createColumns *columns=NULL,*tempColumns=NULL;
	//RID *oi=NULL;
	Fetch *fetch=Fetch::getInstance();
	sCH_C->getDetailsOfFields(tableName_P,databaseName_P,&columns);
	if(fNames_P==NULL) //requested for a select * operation
		{} 
	else  		   //requested for some specific columns in frames_P  
		{			
		tempColumns=columns;
		columns=NULL;
		if(TLQH :: testAndUpdateList(&columns,tempColumns,fNames_P)==FAILED) goto DREND;
		}
	//RH::displayRIDList(rID_P);	
	fetch->fetchRIDs(rID_P,NULL,DISPLAY,NULL,EQ,NULL,columns);	
DREND:	
	RLQH :: freeFdList(fNames_P);
	TLQH :: freeCColumns(columns);
	TLQH :: freeCColumns(tempColumns);
	RH::freeRIDList(rID_P);
	printf("\n\n");
	}		

int SQH::getRIDs(char *tableName,char *dbName,char *columnName,int operation,char *value,RID **rID)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside getRIDs method of SQH class %s dbname and %s tableName,(%s op %s)",dbName,tableName,columnName,value);	
#endif		
	//printf("\n In retrieve RIDS %s is the column and %s is value",columnName,value);
	createColumns *columns=NULL,*tempColumns;
	short matchedFlag=0;
	long indexPN=0;
	if(sCH_C->returnDataBaseExistence(dbName,CHECK)==SUCCESS)
		{
		if(sCH_C->returnTableExistence(tableName,dbName,CHECK)!=FAILED) 
			{
			sCH_C->getDetailsOfFields(tableName,dbName,&columns);
			//if index exists on the attribute do that else, b4 this do the table check and db check 
			//do table scan and get the RIDS
			tempColumns=columns;
			while(tempColumns!=NULL)
				{
				if(!strcmp(tempColumns->columnName,columnName))
					{
					if(IQH::tellType(value)==tempColumns->dataType)		matchedFlag=1;
					else							matchedFlag=2;	
					}	
				tempColumns=tempColumns->next;
				}
			if(matchedFlag==1)
				{
				//printf("\n SUCCESS VENKI CARRY ON");
				short flag=0;
				indexPN=sCH_C->returnIndexExistence(dbName,tableName,columnName);
				//printf("\n %s is value %d is index",value,indexPN);
				if(IQH::tellType(value)==DBCHARTYPE)
					{
					int i=0,j=0;
					char *tempp=0;
					j=strlen(value);
					tempp=(char*)MSF::myMalloc(j);
					
					for(i=1;i<j-1;i++)	tempp[i-1]=value[i];
					tempp[i-1]='\0';
#ifdef RLQDEBUG						
					printf("\n&&&&&&& %s %d",tempp,strlen(tempp));
#endif				
					MSF::myFree(value);
					value=(char*)MSF::myMalloc(strlen(tempp));
					strcpy(value,tempp);
					MSF::myFree(tempp);
					flag=1;
					}
				if(indexPN==FAILED)
					{
					TableScan *tsc=TableScan::getInstance();
					*rID=NULL;
					//printf("\n%s %s %s %s",tableName,dbName,columnName,value);
					tsc->doTableScan(tableName,dbName,rID,NULL,CHECK,columnName,value,operation);
					//RH::displayRIDList(*rID);
					}
				else
					{
					VIndexManager *vim=new VIndexManager();
#ifdef RLQDEBUG						
					printf("\n Index Found at %d",indexPN);
#endif					
					KeyList *khead=NULL;
					if(flag==0)	VIndexManager::addToKeyList(&khead,IQH::tellType(value),value);
					else		VIndexManager::addToKeyList(&khead,DBCHARTYPE,value);
					
					vim->find(indexPN,khead,operation,rID);
					VIndexManager::freeKeyList(khead);
					delete vim;
					}	
				}
			else if(matchedFlag==2)
				{
				printf("\n\tColumn \"%s\" does not support \"%s\" value!",columnName,value);
				*rID=NULL;
				TLQH::freeCColumns(columns);
				return FAILED;
				}
			else
				{
				printf("\n\tColumn \"%s\" does not exists!",columnName,value);			
				*rID=NULL;
				TLQH::freeCColumns(columns);
				return FAILED;
				}
			TLQH::freeCColumns(columns);	
			}
		else
			{
			printf("\n\tRequested Table \"%s\" Doesnot Exist in \"%s\" database!",tableName,dbName);
			*rID=NULL;
			return FAILED;
			}	
		}
	else
		{
		printf("\n\tRequested \"%s\" database does not exist!",dbName);
		*rID=NULL;
		return FAILED;
		}	 
	}	
		
int SQH :: executeSelect(RLQds *r,void *getResult)
	{
#ifdef EPATH	
	printf("\n\t\t Inside executeSelect method of SQH class");	
#endif	
#ifdef VERBOSEMODE	
	printf("\n\t\tInside executeSelect method of SQH class %s dbname and %s tableName",r->dbname,r->objectName);	
#endif	
	//printf("\n IN Select query handler %s is tablename and %s is database name\n",r->objectName,r->dbname);
	//RLQH::displayList(r->values,r->names);
	TableScan *tSC=TableScan::getInstance();
	RID *ri=NULL;
	tSC->doTableScan(r->objectName,r->dbname,&ri,r->names,DISPLAY,NULL,NULL,EQ);
#ifdef VERBOSEMODE	
	RH::displayRIDList(ri);
#endif	
	RH::freeRIDList(ri);
	//delete tSC;
	}
		
/****************************Delete Query Handler*********************************************/
DQH* DQH :: singleInstance_C=0;

DQH* DQH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES		
		printf("\n\t\tIn Static Invoker of DQH of RLQH");
#endif			
                singleInstance_C = new DQH();
		}
        return singleInstance_C;
	}	

DQH :: DQH() //constructor
        {
#ifdef DBCONDES
	printf("\n\t\t  In Constructor of DQH of RLQH");
#endif		
	sCH_C=SysCatHan::getInstance();
        }

DQH :: ~DQH()
	{
#ifdef DBCONDES
	printf("\n\t\t  In Destructor of DQH of RLQH");
#endif	
	}

int DQH :: executeDelete(RID *rID,char *tableName,char *dbName)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside executeDelete method of DQH class %s dbname and %s tableName",dbName,tableName);	
#endif		
	//printf("\n venki in here");
	//RH::displayRIDList(rID);
	doDeletion(rID,tableName,dbName);
	RH::freeRIDList(rID);	
	}
	
int DQH :: doDeletion(RID *rID,char *tableName,char *dbName)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside doDeletion method of DQH class %s dbname and %s tableName",dbName,tableName);	
#endif		
	createColumns *columns=NULL;
	IndexOnTable *iOT=NULL;		
	RH  *rH_C=RH::getInstance();
	sCH_C->getDetailsOfFields(tableName,dbName,&columns);	
	sCH_C->returnIndexExistence(dbName,tableName,&iOT);
	RID *temp;
	temp=rID;
	while(temp!=NULL)
		{
		AttributeValues *avalues=NULL,*aTemp=NULL;
		rH_C->returnRecord(temp,columns,&avalues); //fetch the record to delete the indexex on it
		aTemp=avalues;
		IndexOnTable *headIOT=iOT;
		FieldNames *tempF;
		KeyList* khead=NULL;
		createColumns *tempColumns=NULL;
				
		while(headIOT!=NULL) //for each index
			{
			tempF=headIOT->fieldNames;
			while(tempF!=NULL)  //for each field of index
				{
				tempColumns=columns;
				aTemp=avalues;
				while(tempColumns!=NULL)
					{
					if(!strcmp((tempF)->name,tempColumns->columnName))
							VIndexManager::addToKeyList(&khead,tempColumns->dataType,aTemp->value);
					aTemp=aTemp->next;
					tempColumns=tempColumns->next;
					}	
				tempF=tempF->next;
				}
			//VIndexManager :: displayKeyList(khead);
			VIndexManager *vIM1=new VIndexManager();
			vIM1->deleteEntry(headIOT->pageNumber,khead,NULL);
			delete vIM1;	
			VIndexManager :: freeKeyList(khead);		
			khead=NULL;	
			headIOT=headIOT->next;
			}
		rH_C->deleteRecord(temp);
		RLQH::freeAttList(avalues);
		temp=temp->next;
		}
	SysCatHan :: freeIOT(iOT);		
	TLQH::freeCColumns(columns);	
	}			
	
int DQH :: executeDelete(RLQds *r,void *getResult)
	{
#ifdef EPATH	
	printf("\n\t\t Inside executeDelete method of DQH class");	
#endif	
	//printf("\n IN Delete query handler %s is tablename and %s is database name\n",r->objectName,r->dbname);
	RID *rID=NULL;
	TableScan *tS_C=TableScan::getInstance();
	tS_C->doTableScan(r->objectName,r->dbname,&rID,NULL,CHECK,NULL,NULL,EQ);
	
	doDeletion(rID,r->objectName,r->dbname);
	
	RH::freeRIDList(rID);	
	}
/****************************Update Query Handler*********************************************/
UQH* UQH :: singleInstance_C=0;

UQH* UQH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES		
		printf("\n\t\tIn Static Invoker of UQH of RLQH");
#endif			
                singleInstance_C = new UQH();
		}
        return singleInstance_C;
	}	

UQH :: UQH() //constructor
        {
#ifdef DBCONDES
	printf("\n\t\t  In Constructor of UQH of RLQH");
#endif
	sCH_C=SysCatHan::getInstance();
        }

UQH :: ~UQH()
	{
#ifdef DBCONDES
	printf("\n\t\t  In Destructor of UQH of RLQH");
#endif	
	}

int UQH :: updateQueryHandler(RLQds *r,RID *rID)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside updateQueryHandler method of UQH class %s dbname and %s tableName",r->dbname,r->objectName);	
#endif		
	//printf("\n IN Update rquery handler %s is tablename and %s is database name\n",r->objectName,r->dbname);
	//RLQH::displayList(r->values,r->names);
	//RH::displayRIDList(rID);
	RH  *rH_C=RH::getInstance();
	DQH *dQH=DQH::getInstance();
	IQH *iQH=IQH::getInstance();
	AttributeValues *avalues;
	RID *tempRID,*rid;
	createColumns *columns=NULL,*tempColumns;
	sCH_C->getDetailsOfFields(r->objectName,r->dbname,&columns);
	FieldNames *fNames,*sourceNames;
	AttributeValues *aTemp,*aaTemp,*sourceValues;
	short okFlag=0;
	fNames=r->names;
	sourceNames=r->names;
	aTemp=r->values;
	sourceValues=r->values;
	while(fNames!=NULL)
		{
		okFlag=0;
		tempColumns=columns;
		while(tempColumns!=NULL)
			{
			if(!strcmp(fNames->name,tempColumns->columnName))
				{
				okFlag=1;
				if(IQH::tellType(aTemp->value)!=tempColumns->dataType)
					{
					printf("\n\t %s value doesnot match the %s column Datatype",aTemp->value,fNames->name);
					goto UEND;
					}
				}
			tempColumns=tempColumns->next;
			}
		if(okFlag==0)
			{
			printf("\n\t \"%s\" column doesnot Exist in table \"%s\" table of \"%s\" database",fNames->name,r->objectName,r->dbname);
			goto UEND;
			}		
		fNames=fNames->next;
		aTemp=aTemp->next;
		}
	tempRID=(RID*)MSF::myMalloc(sizeof(RID));
	rid=rID;
	while(rid!=NULL)
		{
		avalues=NULL;
		aaTemp=NULL;
		rH_C->returnRecord(rid,columns,&avalues);
	//reached this stage means data is ok	
		tempRID->pageNumber=rid->pageNumber;
		tempRID->slotID=rid->slotID;
		tempRID->next=NULL;
		dQH->doDeletion(tempRID,r->objectName,r->dbname); //because doDeletion expects a list of RIDs to delete
		
		fNames=sourceNames;
		aTemp=sourceValues;//stores the data that is supposed to use to update
		while(fNames!=NULL)
			{
			tempColumns=columns;
			aaTemp=avalues;//stores the retrieved data
			while(tempColumns!=NULL)
				{
				if(!strcmp(tempColumns->columnName,fNames->name))
					{
					MSF::myFree(aaTemp->value);
					aaTemp->value=(char*)MSF::myMalloc(strlen(aTemp->value));
					strcpy(aaTemp->value,aTemp->value);
					}
				tempColumns=tempColumns->next;
				aaTemp=aaTemp->next;
				}			
			fNames=fNames->next;
			aTemp=aTemp->next;
			}
		r->names=NULL;
		r->values=NULL;
		while(aaTemp!=NULL)
			{
			RLQH :: insertToAttList(&r->values,aaTemp->value);
			aaTemp=aaTemp->next;
			}	
		iQH->executeInsert(r);	
		RLQH :: freeAttList(r->values);
		r->values=NULL;		
		rid=rid->next;
		RLQH::freeAttList(avalues);
		}
UEND:		
	RLQH :: freeAttList(sourceValues);
	RLQH :: freeFdList(sourceNames);
	MSF::myFree(tempRID);
	TLQH::freeCColumns(columns);
	RH::freeRIDList(rID);
	}	
			
int UQH :: executeUpdate(RLQds *r,void *getResult)
	{
#ifdef EPATH	
	printf("\n\t\t Inside executeUpdate method of UQH class");	
#endif
	}	
/****************************Insert Query Handler*********************************************/
IQH* IQH :: singleInstance_C=0;

IQH* IQH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES		
		printf("\n\t\tIn Static Invoker of IQH of RLQH");
#endif			
                singleInstance_C = new IQH();
		}
        return singleInstance_C;
	}

IQH :: IQH() //constructor
        {
#ifdef DBCONDES
	printf("\n\t\t  In Constructor of IQH of RLQH");
#endif	
	sCH_C=SysCatHan::getInstance();
	dPH_C=DPH :: getInstance();
	tS_C=TableScan::getInstance();
	vSB_C=VSBufferManager :: getInstance();
	headerPageNumber_C=0;
	IhPDataC=MSF::myMalloc(PAGESIZE);			
	IdBDataC=MSF::myMalloc(PAGESIZE);
	}

IQH :: ~IQH()
	{
#ifdef DBCONDES
	printf("\n\t\t  In Destructor of IQH of RLQH");
#endif	
	if(IhPDataC!=0)	MSF::myFree(IhPDataC);
	if(IdBDataC!=0)	MSF::myFree(IdBDataC);
	}		

int IQH::tellType(char *string)
	{
	if(strchr(string,'\"')!=NULL)		
		{
		return DBCHARTYPE;
		}	
	else if(strchr(string,'-')!=NULL)	
		{
		return DBDATETYPE;
		}
	else if(strchr(string,'.')!=NULL)	
		{
		return DBFLOATTYPE;
		}
	else if(!strcmp("null",string))
		return 143;
	else if(!strcmp("default",string))
		return 431;		
	else	
		{
		return DBINTTYPE;
		}
	}
		
int IQH :: executeInsert(RLQds *r)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside executeInsert method of IQH class %s dbname and %s tableName",r->dbname,r->objectName);	
#endif		
#ifdef RLQDEBUG	
	printf("\n IN Insert query handler %s is tablename and %s is database name\n",r->objectName,r->dbname);
	RLQH::displayList(r->values,r->names);
#endif	
	//check whether the values sent match the datatypes of the table if not error, if yes ok , if default is sent, replace default value with the
	//actual default value... and then calllb
	void *record=0;
	HeaderPage *hP;
	short *displacement=0;
	char *cpdata=0,*temp=0;
	long tableHPN=0;
	RID *rID=0;
	createColumns *columns=NULL,*tempColumns;
	AttributeValues *aTemp=r->values;
	char *tempp;
	int i=0,j=0,recLength=0,nof=0,offset=0;
	IndexOnTable *iOT=NULL;
	if(sCH_C->returnDataBaseExistence(r->dbname,CHECK)==SUCCESS)
		{
		tableHPN=sCH_C->returnTableExistence(r->objectName,r->dbname,CHECK);
		if(tableHPN!=FAILED)
			{
			sCH_C->getDetailsOfFields(r->objectName,r->dbname,&columns);
			tempColumns=columns;
#ifdef RLQDEBUG				
			TLQH :: displayList(columns);
#endif			
			if(r->names==NULL)
				{
				while(tempColumns!=NULL || aTemp!=NULL)
					{
#ifdef RLQDEBUG					
					printf("\n%s %d %d %d %s %d %d %d %d",tempColumns->columnName,tempColumns->dataType,tempColumns->attLen,
									      tempColumns->precision,tempColumns->defaultValue,tempColumns->position,
									      tempColumns->primaryKey,tempColumns->notNull,tempColumns->unique);
#endif									      
					if(tempColumns->dataType==IQH::tellType(aTemp->value))
						{
#ifdef RLQDEBUG						
						printf("\nSUCCESSFULLY MATCHED \n");
#endif						
						if(tempColumns->dataType==DBCHARTYPE)
							{
							j=strlen(aTemp->value);
							tempp=(char*)MSF::myMalloc(j);
							for(i=1;i<j-1;i++)	tempp[i-1]=aTemp->value[i];
							tempp[i-1]='\0';
#ifdef RLQDEBUG							
							printf("\n&&&&&&& %s %d",tempp,strlen(tempp));
#endif							
							MSF::myFree(aTemp->value);
							aTemp->value=(char*)MSF::myMalloc(strlen(tempp));
							strcpy(aTemp->value,tempp);
							MSF::myFree(tempp);
							}
						}	
					else if(IQH::tellType(aTemp->value)==143)//for null value sent as arguement	
						{
						if(tempColumns->notNull=='y' || tempColumns->unique=='y' || tempColumns->primaryKey=='y')
							{
							printf("\n!! NULL value not supported for %s column\n",tempColumns->columnName);
							goto IQHEND;
							}
						else
							{
							MSF::myFree(aTemp->value);
							aTemp->value=(char*)MSF::myMalloc(5);
							strcpy(aTemp->value,"null");
							}	
						}
					else if(IQH::tellType(aTemp->value)==431)//for null value sent as arguement	
						{
						if(tempColumns->defaultValue==0)
							{
							printf("\n!! Default value not set for %s column\n",tempColumns->columnName);
							goto IQHEND;							
							}
						else
							{
							MSF::myFree(aTemp->value);
							aTemp->value=(char*)MSF::myMalloc(strlen(tempColumns->defaultValue));
							strcpy(aTemp->value,tempColumns->defaultValue);
							}	
						}
					else
						{
						printf("\n\t!! Datatype MisMatch %s is the value and %s is the columnname\n",aTemp->value,tempColumns->columnName);
						goto IQHEND;
						}	
					tempColumns=tempColumns->next;
					aTemp=aTemp->next;
					if(aTemp==NULL && tempColumns!=NULL)
						{
						printf("\n\t!! Insufficent Input Supplied (Correct the input)\n");
						goto IQHEND;
						}
					else if(aTemp!=NULL && tempColumns==NULL)	
						{
						printf("\n\t!! Surplus Input Supplied (Correct the input)\n");
						goto IQHEND;
						}
					}
				}
			//read from index tables the indexes defined on the table 	
			sCH_C->returnIndexExistence(r->dbname,r->objectName,&iOT);
#ifdef RLQDEBUG				
			SysCatHan :: displayIOT(iOT);					
#endif			
			
			//test finding the corresponding values into each of the indexes defined on the table
			//if any one fails then goto IQHEND and display Failure message
			IndexOnTable *headIOT=iOT;
			FieldNames *tempF;
			KeyList* khead=NULL;	
			while(headIOT!=NULL)
				{
#ifdef RLQDEBUG				
				printf("\nIndex Name %s at %d",headIOT->indexName,headIOT->pageNumber);
#endif				
				tempF=headIOT->fieldNames;
				while(tempF!=NULL)
					{
					tempColumns=columns;
					aTemp=r->values;
					while(tempColumns!=NULL)
						{
						if(!strcmp((tempF)->name,tempColumns->columnName))
							VIndexManager::addToKeyList(&khead,tempColumns->dataType,aTemp->value);
						aTemp=aTemp->next;
						tempColumns=tempColumns->next;
						}
#ifdef RLQDEBUG						
					printf("\n\t%s is Field",(tempF)->name);
#endif					
					tempF=tempF->next;
					}
#ifdef RLQDEBUG						
				VIndexManager :: displayKeyList(khead);
#endif				
				VIndexManager *vIM1=new VIndexManager();
				if(vIM1->find(headIOT->pageNumber,khead,EQ,NULL)==FAILED)
					{
#ifdef RLQDEBUG					
					printf("\nNOT EXISTS");
#endif					
					}
				else
					{
					printf("\n\t!!Trying to insert duplicate values into key field\n");
					VIndexManager :: freeKeyList(khead);		
					khead=NULL;
					goto IQHEND;
					}	
				delete vIM1;	
				VIndexManager :: freeKeyList(khead);		
				khead=NULL;
				headIOT=headIOT->next;
				}
			//inserting into the actual table structure
			//tableHPN holds the pagenumber
			
			vSB_C->readFromBufferPool(tableHPN,IhPDataC);
			hP=(HeaderPage*)IhPDataC;
			aTemp=r->values;
			while(aTemp!=NULL) 
				{
				nof++;
				recLength+=strlen(aTemp->value)+1;		
				recLength+=sizeof(short);
#ifdef RLQDEBUG
				printf("\n\t%s %d",aTemp->value,recLength);
#endif				
				aTemp=aTemp->next;
				}
			//printf("\n************************ Venki look out this malloc\n");	
			record=MSF::myMalloc(recLength); 
			aTemp=r->values;
			displacement=(short*)record;
			cpdata=(char*)((char*)record+ nof * sizeof(short));
			while(aTemp!=NULL)
				{
				temp=aTemp->value;	
				offset=cpdata-(char*)record;
				*displacement=offset; 
#ifdef RLQDEBUG				
				printf("\ndisplacement=%d,offset=%d\t",*displacement,offset);
#endif				
				displacement++;
				while(*temp!= '\0')
					{
#ifdef RLQDEBUG					
					printf("%c",*temp);
#endif					
					*cpdata=*temp;	
					cpdata++; 
					temp++;
					}
				*cpdata='\0';
				cpdata++;
				aTemp=aTemp->next;
				}	
			dPH_C->findAndInsertToDEinDP(record,recLength,hP->pNFirstDP,&rID);
			//if all are successful then insert into index structure
			//insert all the columns into table structure upon converting into record	
#ifdef RLQDEBUG			
			printf("\n\t\t\t\t******Displaying");RH::displayRIDList(DBPH::rID);		
#endif			

			//rID=(RID*)MSF::myMalloc(sizeof(RID));
			//rID->pageNumber=(DBPH::rID)->pageNumber;
			//rID->slotID    =(DBPH::rID)->slotID;
			
			headIOT=iOT;
			khead=NULL;	
			while(headIOT!=NULL)
				{
#ifdef RLQDEBUG				
				printf("\nIndex Name %s at %d",headIOT->indexName,headIOT->pageNumber);
#endif				
				tempF=headIOT->fieldNames;
				while(tempF!=NULL)
					{
					tempColumns=columns;
					aTemp=r->values;
					while(tempColumns!=NULL)
						{
						if(!strcmp((tempF)->name,tempColumns->columnName))
							VIndexManager::addToKeyList(&khead,tempColumns->dataType,aTemp->value);
						aTemp=aTemp->next;
						tempColumns=tempColumns->next;
						}
#ifdef RLQDEBUG						
					printf("\n\t%s is Field",(tempF)->name);
#endif					
					tempF=tempF->next;
					}
#ifdef RLQDEBUG						
				VIndexManager :: displayKeyList(khead);
#endif				
				VIndexManager *vIM=new VIndexManager();
				vIM->insert(headIOT->pageNumber,khead,rID);
				delete vIM;
				VIndexManager :: freeKeyList(khead);		
				khead=NULL;
				headIOT=headIOT->next;
				}			
			}
		else
			printf("\n\t!! Table \"%s\" doesnot exist in \"%s\" database..Insertion Not Possible",r->objectName,r->dbname);	
		}	
	else
		printf("\n\t!! Database \"%s\" does not exist....Insertion Not Possible\n",r->dbname);	
IQHEND:		
	TLQH::freeCColumns(columns); 	
	SysCatHan :: freeIOT(iOT);
	if(record!=0)	MSF::myFree(record);
	
	if(rID!=0)	RH::freeRIDList(rID);
	}

void IQH ::insertToCatTables(RLQds *r)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside insertToCatTable method of IQH class %s dbname and %s tableName",r->dbname,r->objectName);	
#endif	
	void *record=0;
	HeaderPage *hP;
	DBHeader *dBH;

	vSB_C->readFromBufferPool(0,IdBDataC);
	dBH=(DBHeader*)IdBDataC;
	AttributeValues *tAttVal;
	int recLength=0,offset=0,nof=0,nor=0;
	short *displacement=0;
	char *cpdata=0,*temp=0;
	//RLQH::displayList(r->values,NULL);
	if(r!=NULL)
		{
		tAttVal=r->values;
		while(tAttVal!=NULL) //to get the number of fields to insert
			{
			nof++;
			recLength+=strlen(tAttVal->value)+1;		
			recLength+=sizeof(short);
#ifdef INSTALLDEBUG			
			printf("\n{{{ %s , %d",tAttVal->value,recLength);
#endif			
			tAttVal=tAttVal->next;
			}
		record=MSF::myMalloc(recLength); 
		tAttVal=r->values;
		displacement=(short*)record;
		cpdata=(char*)((char*)record+ nof * sizeof(short));
		while(tAttVal!=NULL)
			{
			temp=tAttVal->value;	
			offset=cpdata-(char*)record;
			*displacement=offset; 
#ifdef INSTALLDEBUG			
			printf("\ndisplacement=%d,offset=%d\t",*displacement,offset);
#endif			
			displacement++;
			while(*temp!= '\0')
				{
#ifdef INSTALLDEBUG				
				printf("%c",*temp);
#endif				
				*cpdata=*temp;	
				cpdata++; 
				temp++;
				}
			*cpdata='\0';
			cpdata++;
			tAttVal=tAttVal->next;
			}
#ifdef INSTALLDEBUG			
		printf("\n");
#endif		
		nor++; //number of records counter
		tAttVal=r->values;	
		}
	if(!strcmp(DBCAT,r->objectName))
		{
#ifdef INSTALLDEBUG		
		printf("\n\t\tInserting into dbcat");
#endif		
		vSB_C->readFromBufferPool(dBH->dbCatPointer,IhPDataC);
		hP=(HeaderPage*)IhPDataC;
		dPH_C->findAndInsertToDEinDP(record,recLength,hP->pNFirstDP,NULL);
		hP->totNumRec+=nor;
		vSB_C->writeToBufferPool(dBH->dbCatPointer,IhPDataC);
		}
	else if(!strcmp(TCAT,r->objectName))
		{
#ifdef INSTALLDEBUG		
		printf("\n\t\tInserting into tcat");
#endif		
		vSB_C->readFromBufferPool(dBH->tCatPointer,IhPDataC);
		hP=(HeaderPage*)IhPDataC;
		dPH_C->findAndInsertToDEinDP(record,recLength,hP->pNFirstDP,NULL);
		hP->totNumRec+=nor;
		vSB_C->writeToBufferPool(dBH->tCatPointer,IhPDataC);
		}
	else if(!strcmp(ICAT,r->objectName))
		{
		//printf("\n Here is the position %d is icat pointer",dBH->iCatPointer);
		vSB_C->readFromBufferPool(dBH->iCatPointer,IhPDataC);
		hP=(HeaderPage*)IhPDataC;
		//printf("\ntotNumRec %d,totNumDP %d,maxDEInDP %d,pNFirstDP %d",hP->totNumRec,hP->totNumDP,hP->maxDEInDP,hP->pNFirstDP);
		dPH_C->findAndInsertToDEinDP(record,recLength,hP->pNFirstDP,NULL);	
		hP->totNumRec+=nor;
		vSB_C->writeToBufferPool(dBH->iCatPointer,IhPDataC);
		}
	else if(!strcmp(IACAT,r->objectName))
		{
		vSB_C->readFromBufferPool(dBH->iaCatPointer,IhPDataC);
		hP=(HeaderPage*)IhPDataC;
		//printf("\ntotNumRec %d,totNumDP %d,maxDEInDP %d,pNFirstDP %d",hP->totNumRec,hP->totNumDP,hP->maxDEInDP,hP->pNFirstDP);
		dPH_C->findAndInsertToDEinDP(record,recLength,hP->pNFirstDP,NULL);	
		hP->totNumRec+=nor;
		vSB_C->writeToBufferPool(dBH->iaCatPointer,IhPDataC);
		}	
	
	
	if( record!=0)		MSF::myFree(record);
	}

void IQH :: insertToSysCat(TLQds *r)
	{
#ifdef VERBOSEMODE	
	printf("\n\t\tInside insertToSysCat method of IQH class %s dbname and %s tableName",r->dbname,r->objectName);	
#endif	
	int recordLength=0,numberOfFields=11;  //for offset directory
	short *displacement,offset=0;
	HeaderPage *hP;
	createColumns *c;
	void *record=0;
	char *cpdata,*temp;
	
	
	DBHeader *dBH;	
	
	
	
	vSB_C->readFromBufferPool(0,IdBDataC);
	
	dBH=(DBHeader*)IdBDataC;

#ifdef INSTALLDEBUG
	printf("\t***************IN IQH :Convert To Records()\n\t\tDatabase Name: %s\n",r->dbname);	
	printf("\n\tFree List  PageNumber = %ld",dBH->fpListPointer);
	printf("\n\tdbCatalog  PageNumber = %ld",dBH->dbCatPointer); 
	printf("\n\ttCatalog   PageNumber = %ld",dBH->tCatPointer);  
	printf("\n\taCatalog   PageNumber = %ld",dBH->aCatPointer); 
	printf("\n\tiCatalog   PageNumber = %ld",dBH->iCatPointer); 
	printf("\n\tiaCatalog  PageNumber = %ld",dBH->iaCatPointer); 
	printf("\n\tAssigned   PageNumber = %ld",dBH->assignedPN);
#endif	
	
	vSB_C->readFromBufferPool(dBH->aCatPointer,IhPDataC);	
	
	hP=(HeaderPage*)IhPDataC;
#ifdef INSTALLDEBUG	
	printf("\n\tHeader Page  Contents-->");
        printf("\n\t\tTotalNumberRecords=%ld;\n\t\tTotalNumberDirectoryPages=%ld;\n\t\tMaximumDEsInDPs=%ld;\n\t\tPNFirstDP=%ld"
			                        ,hP->totNumRec,hP->totNumDP,hP->maxDEInDP,hP->pNFirstDP);
#endif							
	c=r->columns;
	int nor=0;//number of records
	char *df=(char*)MSF::myMalloc(10);
	while(c!=NULL)//until all the rows are done
		{			
		recordLength=0;	
		offset=0;
		recordLength+=strlen(r->dbname)+1;
		recordLength+=strlen(r->objectName)+1; 
		recordLength+=strlen(c->columnName)+1;
		if(c->defaultValue!=0)	recordLength+=strlen(c->defaultValue)+1;
		recordLength+=7*sizeof(int);
		recordLength+=numberOfFields*sizeof(short);
		
		record=MSF::myMalloc(recordLength);	
		
		displacement=(short*)record;
		cpdata=(char*)((char*)record+numberOfFields*sizeof(short));
		
// inserting database name into record datastructure
		temp=r->dbname;	
		offset=cpdata-(char*)record;
		*displacement=offset; displacement++;
		while(*temp!= '\0')
			{
			*cpdata=*temp;	
			cpdata++; 
			temp++;
			}
		*cpdata='\0';
		cpdata++; 
	
// inserting Table name into record datastructure
		offset=cpdata-(char*)record;
	        *displacement=offset; displacement++;
		temp=r->objectName; 
		while(*temp!='\0') 
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
                cpdata++;

// inserting attribute name into record datastructure
		offset=cpdata-(char*)record;
	        *displacement=offset; displacement++;				
		temp=c->columnName;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++; 
	
// inserting data type into record datastructure
		offset=cpdata-(char*)record;
	        *displacement=offset; displacement++;		
		df=MSF::itoa(c->dataType,df);
		temp=df;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++; 

// inserting attribute length into record data structure		
		offset=cpdata-(char*)record;
        	*displacement=offset; displacement++;
		df=MSF::itoa(c->attLen,df);
		temp=df;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++; 	

//inserting attribute precision into record datastructure		
		offset=cpdata-(char*)record;
        	*displacement=offset; displacement++;
		df=MSF::itoa(c->precision,df);
		temp=df;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++; 	

//inserting attribute default Value into record datastructure
		offset=cpdata-(char*)record;
		*displacement=offset; displacement++;
		if(c->defaultValue==0)
			{ // if default value is NULL offset value is remain unchanged
			}
		else
			{
			temp=c->defaultValue;
			while(*temp!='\0')
				{
	        		*cpdata=*temp;
		        	cpdata++;
                        	temp++;
                        	}
                	*cpdata='\0';
			cpdata++; 
			offset=cpdata-(char*)record;	
			}

//inserting attribute position value(in the table) into record datastructure	
		*displacement=offset; displacement++;
		df=MSF::itoa(c->position,df);
		temp=df;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++;
		
//inserting attribute primary key Value into record datastructure
		offset=cpdata-(char*)record;
        	*displacement=offset; displacement++;
		df=MSF::itoa(c->primaryKey,df);
		temp=df;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++;
		
//inserting attribute notNull Value into record datastructure
		offset=cpdata-(char*)record;
        	*displacement=offset; displacement++;
		df=MSF::itoa(c->notNull,df);
		temp=df;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++;
		
//inserting attribute unique Value into record datastructure
		offset=cpdata-(char*)record;
        	*displacement=offset; displacement++;
		df=MSF::itoa(c->unique,df);
		temp=df;
		while(*temp!='\0')
			{
			*cpdata=*temp;
			cpdata++;
			temp++;
			}
		*cpdata='\0';
		cpdata++;
		
//inserting the record constructed into DBPAGE through DPHandler			
		dPH_C->findAndInsertToDEinDP(record,recordLength,hP->pNFirstDP,NULL);
#ifdef INSTALLDEBUG		
		//tS_C->printRecord(record,numberOfFields);
		printf("\nBack to Convert to records");		
#endif		
		MSF::myFree(record);
		c=c->next;		
		nor++;
		}
	hP->totNumRec+=nor;
	vSB_C->writeToBufferPool(dBH->aCatPointer,IhPDataC);			
	MSF::myFree(df);	
	}	
	
/****************************Record Level Query Handler***************************************/
RLQH* RLQH :: singleInstance_C=0;

RLQH* RLQH :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES		
		printf("\n\tIn Static Invoker of RLQH");
#endif			
		singleInstance_C = new RLQH();
		}
	return singleInstance_C;
	}

RLQH :: RLQH() //constructor
	{
#ifdef DBCONDES
	printf("\n\t  In Constructor of RLQH");
#endif	
	sQH_C= SQH::getInstance();
	dQH_C= DQH::getInstance();
	uQH_C= UQH::getInstance();
	iQH_C= IQH::getInstance();	
	}	

RLQH :: ~RLQH()
	{
#ifdef DBCONDES
	printf("\n\t  In Destructor of RLQH");
#endif
	sQH_C->~SQH();
	dQH_C->~DQH();
	uQH_C->~UQH();	
	iQH_C->~IQH();
	}		

void RLQH :: insertToAttList(AttributeValues **head,char *valuep) // these are static instances
	{
	if(*head==NULL)
		{
#ifdef INSTALLDEBUG		
		printf("\n\t In Head is NULL");	
#endif
		*head=(AttributeValues*)MSF::myMalloc(sizeof(AttributeValues));			
		(*head)->value=(char*)MSF::myMalloc(strlen(valuep)+1);
		strcpy((*head)->value,valuep);
		strcat((*head)->value,"\0");
		(*head)->next=NULL;
		}
	else
		{
		AttributeValues *t=(*head);	
		while(t->next!=NULL)
			{
			t=t->next;
			}
		AttributeValues *temp;	
		temp=(AttributeValues*)MSF::myMalloc(sizeof(AttributeValues));
        	temp->value=(char*)MSF::myMalloc(strlen(valuep)+1);
		strcpy(temp->value,valuep);
		strcat(temp->value,"\0");
		t->next=temp;
		temp->next=NULL;
		}
	}

void RLQH :: insertToFdList(FieldNames **head,char *namep)
	{
	//printf("\n%ld %s is namep",*head,namep);
	if(*head==NULL)
		{
#ifdef INSTALLDEBUG		
		printf("\n\t In Head is NULL");	
#endif		
		*head=(FieldNames*)MSF::myMalloc(sizeof(FieldNames));			
		(*head)->name=(char*)MSF::myMalloc(strlen(namep)+1);
		strcpy((*head)->name,namep);
		strcat((*head)->name,"\0");
		(*head)->next=NULL;
		}
	else
		{
		FieldNames *t=(*head);	
		while(t->next!=NULL)
			{
			t=t->next;
			}
		FieldNames *temp;	
		temp=(FieldNames*)MSF::myMalloc(sizeof(FieldNames));
        	temp->name=(char*)MSF::myMalloc(strlen(namep)+1);
		strcpy(temp->name,namep);
		strcat(temp->name,"\0");
		t->next=temp;
		temp->next=NULL;
		}
		
	}	

void RLQH :: deleteFromAttList(AttributeValues **head,char *fieldName)
	{
	AttributeValues *temp=*head;
	AttributeValues *node=*head;
	AttributeValues *swap;
	if(!strcmp((*head)->value,fieldName))
		{
		(*head)=(*head)->next;
		MSF::myFree(temp->value);
		MSF::myFree(temp);
		}
	else
		{
		temp=(*head)->next;
		node=(*head);
		while(temp!=NULL)
			{
			if(!strcmp(temp->value,fieldName))
				{
				swap=temp;
				temp=temp->next;
				node->next=temp;
				MSF::myFree(swap->value);
				MSF::myFree(swap);
				break;
				}
			node=temp;	
			temp=temp->next;
			}
		}	
	}
		
void RLQH ::displayList(AttributeValues *headA,FieldNames *headF)
	{
	while(headA!=NULL)
		{
		printf("\t%s",headA->value);
		headA=headA->next;
		}
	while(headF!=NULL)
		{
		printf("\t%s",headF->name);
		headF=headF->next;
		}
	}

void RLQH :: freeAttList(AttributeValues *head)
	{
	AttributeValues *tempA;
	while(head!=NULL)
		{
		tempA=head;
		head=head->next;
		MSF::myFree(tempA->value);
		MSF::myFree(tempA);
		}
	}
	
void RLQH :: freeFdList(FieldNames *head)
	{
	FieldNames *tempF;
	while(head!=NULL)
		{
		tempF=head;
		head=head->next;
		MSF::myFree(tempF->name);
		MSF::myFree(tempF);
		}
	}
			
void RLQH :: freeList(RLQds *r)
	{
	if(r!=0)
		{
		AttributeValues *tempA;
		FieldNames *tempF;
		while(r->values!=NULL)
			{
			tempA=r->values;
			r->values=(r->values)->next;
			MSF::myFree(tempA->value);
			MSF::myFree(tempA);
			}	
		while(r->names!=NULL)
			{
			tempF=r->names;
			r->names=(r->names)->next;
			MSF::myFree(tempF->name);
			MSF::myFree(tempF);
			}
		MSF::myFree(r->objectName);
		MSF::myFree(r->dbname);
		MSF::myFree(r);			
		}
	r=0;	
	}
	 				 		
int RLQH :: executeRLQ(RLQds *r)
	{
#ifdef VERBOSEMODE		
	printf("\n\tInside executeRLQ method of RLQH class");
#endif	
        if(r->queryType==SELECTQUERY || r->queryType==SELECTWHERE)
                sQH_C->executeSelect(r,NULL);
        else if(r->queryType==INSERTQUERY)
                iQH_C->executeInsert(r);
        else if(r->queryType==DELETEQUERY)
                dQH_C->executeDelete(r,NULL);
        else if(r->queryType==UPDATEQUERY)
                uQH_C->executeUpdate(r,NULL);
	}	

  Ä