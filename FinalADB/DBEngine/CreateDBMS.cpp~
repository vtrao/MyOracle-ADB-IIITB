#include "BufferManager/standards.h"
#include "VSDBEngine.h"

CreateDBMS* CreateDBMS :: singleInstance_C=0;

CreateDBMS* CreateDBMS :: getInstance()
	{
	if(singleInstance_C==0)
		{
#ifdef DBCONDES		
		printf("\n\tIn Static Invoker of CreateDBMS");
#endif				
		singleInstance_C=new CreateDBMS();
		}
	return singleInstance_C;	
	}

CreateDBMS :: CreateDBMS()
	{
#ifdef DBCONDES
	printf("\n\t  In Constructor of CreateDBMS");
#endif	
	dBH_C=0;//data Base Header 
	vSB_C=VSBufferManager :: getInstance();
	cTQH_C=CTQH::getInstance();
	iQH_C=IQH::getInstance();
	dPH_C=DPH::getInstance();
	tS_C=TableScan::getInstance();
	}

CreateDBMS :: ~CreateDBMS()		
	{
#ifdef DBCONDES
	printf("\n\t  In Destructor of CreateDBMS");
#endif	
	}	
	
			
int CreateDBMS :: printDBHeaderStructure()
	{
	printf("\n\tCreateDBMS: DISPLAY DB HEADER");
	int tp=0,ap=0,dp=0,ip=0,ia=0;
	DBHeader *dBH;
	void *displayDBHData=0, *displayData=0;
	long *l;
	displayDBHData=MSF::myMalloc(PAGESIZE);
	displayData=MSF::myMalloc(PAGESIZE);
	//reading the DBHeader from page 0
		vSB_C->readFromBufferPool(0,displayDBHData);
		dBH=(DBHeader*)displayDBHData;
	printf("\n\tFree List  PageNumber = %ld",dBH->fpListPointer);
	printf("\n\tdbCatalog  PageNumber = %ld",dBH->dbCatPointer); dp=dBH->dbCatPointer;
	printf("\n\ttCatalog   PageNumber = %ld",dBH->tCatPointer);  tp=dBH->tCatPointer;
	printf("\n\taCatalog   PageNumber = %ld",dBH->aCatPointer);  ap=dBH->aCatPointer;
	printf("\n\tiCatalog   PageNumber = %ld",dBH->iCatPointer);  ip=dBH->iCatPointer;
	printf("\n\tiaCatalog  PageNumber = %ld",dBH->iaCatPointer); ia=dBH->iaCatPointer;
	printf("\n\tAssigned Page Number = %ld",dBH->assignedPN);
	//testing the contents of respective header pages of the catalogs upon retrevial
		printf("\n*******************Contents of the DB HEADER************************ ");
		vSB_C->readFromBufferPool(dBH->fpListPointer,displayData);
		l=(long*)displayData;
		printf("\n\tfreeListPointer%ld",l[0]);
	
	printf("\nContents of the database Catalog Header Page ");
   	dPH_C->checkDPandDE(dp);	
   
	printf("\nContents of the table Catalog Header Page ");
   	dPH_C->checkDPandDE(tp);
   
	printf("\nContents of the attribute Catalog Header Page ");
   	dPH_C->checkDPandDE(ap);
   
	printf("\nContents of the index Catalog Header Page ");
   	dPH_C->checkDPandDE(ip);
	
	printf("\nContents of the index Fields Catalog Header Page ");
   	dPH_C->checkDPandDE(ia);
	
	printf("\n******************************END OF DBHEADER DETAILS***************************");	
	MSF::myFree(displayData);
	MSF::myFree(displayDBHData);
	}		

int CreateDBMS :: createTableStructure(DBHeader *dBH)
	{
	FLHH *flh=0;
	int tp=0,ap=0,dp=0,ip=0,ia=0;	
	void *datum;
	HeaderPage *hd;
	datum=MSF::myMalloc(PAGESIZE); // Free List pointer page i.e..,page 1 is initialized with a value of -1
	flh=(FLHH*)datum;
	flh->flag  =FLEMPTY;
	flh->prevPN=FLEMPTY;
	flh->nextPN=FLEMPTY;
	flh->index=0;
	
	vSB_C->writeToBufferPool(dBH->fpListPointer,datum);
	FLH *ffLH=FLH::getInstance();
	
	ffLH->printFLH();
	
	//initializing the header page contents
		hd=(HeaderPage*)datum;
		hd->totNumRec=0;
		hd->totNumDP=1;
		hd->maxDEInDP=MAXDE;

//Writing the corresponding header structures to respective pages
	//initializing dbCatPointer i.e.., database Catalog
		dp=dBH->assignedPN;
		hd->pNFirstDP=dBH->assignedPN++;
		vSB_C->writeToBufferPool(dBH->dbCatPointer,datum);
	//initializing tCatPointer i.e.., table catalog
		tp=dBH->assignedPN;
        	hd->pNFirstDP=dBH->assignedPN++;
		vSB_C->writeToBufferPool(dBH->tCatPointer,datum);
	//initializing aCatPointer i.e.., attribute Catalog	
		ap=dBH->assignedPN;
		hd->pNFirstDP=dBH->assignedPN++;
		vSB_C->writeToBufferPool(dBH->aCatPointer,datum);
	//initializing iCatPointer i.e.., index Catalog
		ip=dBH->assignedPN;
		hd->pNFirstDP=dBH->assignedPN++;
        	vSB_C->writeToBufferPool(dBH->iCatPointer,datum);
	//initializing iacatPointer i.e.., index fields catalog	
		ia=dBH->assignedPN;
		hd->pNFirstDP=dBH->assignedPN++;
		vSB_C->writeToBufferPool(dBH->iaCatPointer,datum);
			
#ifdef INSTALLDEBUG			
	printf("\nThe values of Directory page Numbers dp=%d,tp=%d,ap=%d,ip=%d,ia=%d,assignedPN=%d respectively\n",dp,tp,ap,ip,ia,
			dBH->assignedPN);
#endif			
	//initialize the Directory Pages as well as Directory Entries	
	dPH_C->initializeDPandDE(datum);
        vSB_C->writeToBufferPool(dp,datum);
	vSB_C->writeToBufferPool(tp,datum);
	vSB_C->writeToBufferPool(ap,datum);
	vSB_C->writeToBufferPool(ip,datum);
	vSB_C->writeToBufferPool(ia,datum);
	
	MSF::myFree(datum);
	//update sys catalog about it
	}	
	
int CreateDBMS :: initializeDBH(int flag_P)
	{ 	
	if(flag_P==1) //filenot exists
		{
		char *temp=(char*)MSF::myMalloc(strlen("touch ")+strlen(DBFILENAME)+1);
		strncpy(temp,"touch ",6);
		strcat(temp,DBFILENAME);
		system(temp); //making a request to create a new file
		MSF::myFree(temp);
		}
	else if(flag_P==2) //reinstall
		{
		}			
	void *iniData=0;
	iniData=MSF::myMalloc(PAGESIZE);               // initial setup of dbheader at 0 page of dbfile
	dBH_C=(DBHeader*)MSF::myMalloc(7*sizeof(long));
        dBH_C->fpListPointer=1;
       	dBH_C->dbCatPointer=2;
        dBH_C->tCatPointer=3;
       	dBH_C->aCatPointer=4;
        dBH_C->iCatPointer=5;
       	dBH_C->assignedPN=7;
	dBH_C->iaCatPointer=6;
	memcpy(iniData,dBH_C,7*sizeof(long));	
	vSB_C->writeToBufferPool(0,iniData);
		
	createTableStructure(dBH_C);   //calling to create the initial table structure
	
	memcpy(iniData,dBH_C,7*sizeof(long));	
	vSB_C->writeToBufferPool(0,iniData);
	vSB_C->commitBufferPool();
	if(iniData!=0)		MSF::myFree(iniData);
	if(dBH_C!=0)		
		{
		dBH_C=0;
		MSF::myFree(dBH_C);
		}
		
#ifdef INSTALLDEBUG		
	printDBHeaderStructure();	
#endif	

// To update SysCatlog i.e.., attribute catalog table
// For Table Creation means inserting it into System catalog, use TLQds for RLQH (a special case)
	TLQds *r=0; 
        r=(TLQds*)MSF::myMalloc(sizeof(TLQds));
	r->dbname=(char*)MSF::myMalloc(strlen("sys"));
	r->uniqueFields=NULL;
	r->pKeyFields=NULL;
	strcpy(r->dbname,"sys");
        r->objectName=(char *)MSF::myMalloc(strlen("acat"));
	strcpy(r->objectName,"acat");
        r->columns=NULL; //make every list entry null before adding items to list
	TLQH :: InsertToList(&r->columns,"dbname"   ,DBCHARTYPE,30,0,"Default",NO,NO,YES,1 );
	TLQH :: InsertToList(&r->columns,"tname"    ,DBCHARTYPE,30,0,0,NO,NO,YES,2 );
	TLQH :: InsertToList(&r->columns,"aname"    ,DBCHARTYPE,30,0,0,NO,NO,YES,3 );
	TLQH :: InsertToList(&r->columns,"atype"    ,DBINTTYPE ,5 ,0,0,NO,NO,NO ,4 );
	TLQH :: InsertToList(&r->columns,"alength"  ,DBINTTYPE ,5 ,0,0,NO,NO,NO ,5 );
	TLQH :: InsertToList(&r->columns,"precision",DBINTTYPE ,5 ,0,0,NO,NO,NO ,6 );
	TLQH :: InsertToList(&r->columns,"defval"   ,DBCHARTYPE,30,0,0,NO,NO,NO ,7 );
	TLQH :: InsertToList(&r->columns,"position" ,DBINTTYPE ,5 ,0,0,NO,NO,NO ,8 );
	TLQH :: InsertToList(&r->columns,"pkey"     ,DBINTTYPE ,5 ,0,0,NO,NO,NO ,9 );
	TLQH :: InsertToList(&r->columns,"notnull"  ,DBINTTYPE ,5 ,0,0,NO,NO,NO ,10);
	TLQH :: InsertToList(&r->columns,"unique"   ,DBINTTYPE ,5 ,0,0,NO,NO,NO ,11);
	TLQH :: displayList(r->columns);
	
//int x;
//for(x=0;x<100;x++)		
	iQH_C->insertToSysCat(r);

	TLQH :: freeList(r);
	
	//FLH *fh=FLH::getInstance();
	//printf("\n Venki Free page %d",fh->getFreePage());

//Inserting into acat contents attributes of dbcat	
	r=(TLQds*)MSF::myMalloc(sizeof(TLQds));
	r->dbname=(char*)MSF::myMalloc(strlen("sys"));
	strcpy(r->dbname,"sys");
	r->uniqueFields=NULL;
	r->pKeyFields=NULL;
	r->objectName=(char*)MSF::myMalloc(strlen("dbcat"));
	strcpy(r->objectName,"dbcat");
	r->columns=NULL;
	TLQH :: InsertToList(&r->columns,"dbname",DBCHARTYPE,30,0,0,NO,NO,YES,1 );
	//TLQH :: displayList(r->columns);
	
	iQH_C->insertToSysCat(r);
	
	TLQH :: freeList(r);
	
//Inserting into acat contents attributes of tcat	
	r=(TLQds*)MSF::myMalloc(sizeof(TLQds));
	r->dbname=(char*)MSF::myMalloc(strlen("sys"));
	r->uniqueFields=NULL;
	r->pKeyFields=NULL;
	strcpy(r->dbname,"sys");
	r->objectName=(char*)MSF::myMalloc(strlen("tcat"));
	strcpy(r->objectName,"tcat");
	r->columns=NULL;
	TLQH :: InsertToList(&r->columns,"dbname",DBCHARTYPE,30,0,0,NO,NO,YES,1 );
	TLQH :: InsertToList(&r->columns,"tname" ,DBCHARTYPE,30,0,0,NO,NO,YES,2 );
	TLQH :: InsertToList(&r->columns,"hpn"   ,DBINTTYPE, 5 ,0,0,NO,NO,YES,3 );	
	//TLQH :: displayList(r->columns);
	
	iQH_C->insertToSysCat(r);
	
	TLQH :: freeList(r);
	
//Inserting into acat contents attributes of icat
	r=(TLQds*)MSF::myMalloc(sizeof(TLQds));
	r->dbname=(char*)MSF::myMalloc(strlen("sys"));
	strcpy(r->dbname,"sys");
	r->uniqueFields=NULL;
	r->pKeyFields=NULL;
	r->objectName=(char*)MSF::myMalloc(strlen("icat"));
	strcpy(r->objectName,"icat");
	r->columns=NULL;
	TLQH :: InsertToList(&r->columns,"dbname",DBCHARTYPE,30,0,0,NO,NO,YES,1 );
	TLQH :: InsertToList(&r->columns,"tname" ,DBCHARTYPE,30,0,0,NO,NO,YES,2 );
	TLQH :: InsertToList(&r->columns,"iname" ,DBCHARTYPE,30,0,0,NO,NO,YES,3 );
	TLQH :: InsertToList(&r->columns,"indpn" ,DBINTTYPE, 5 ,0,0,NO,NO,YES,4 );
	//TLQH :: displayList(r->columns);
	
	iQH_C->insertToSysCat(r);
	
	TLQH :: freeList(r);
	
//Inserting into acat contents attributes of iacat, i.e.., index field catalog
	r=(TLQds*)MSF::myMalloc(sizeof(TLQds));
	r->dbname=(char*)MSF::myMalloc(strlen("sys"));
	strcpy(r->dbname,"sys");
	r->uniqueFields=NULL;
	r->pKeyFields=NULL;
	r->objectName=(char*)MSF::myMalloc(strlen("iacat"));
	strcpy(r->objectName,"iacat");
	r->columns=NULL;
	TLQH :: InsertToList(&r->columns,"iname" ,DBCHARTYPE,30,0,0,NO,NO,YES,1 );
	TLQH :: InsertToList(&r->columns,"fname" ,DBCHARTYPE,30,0,0,NO,NO,YES,2 );
	TLQH :: InsertToList(&r->columns,"position" ,DBINTTYPE, 5 ,0,0,NO,NO,YES,3 );
	//TLQH :: displayList(r->columns);
	
	iQH_C->insertToSysCat(r);
	
	TLQH :: freeList(r);	

	TableScan *ts=TableScan :: getInstance();
	ts->readAndPrint(4,11);		


//inserting into dbcat the default database and sys database names DBCATALOG	
	RLQds *rDS=0;
	rDS=(RLQds*)MSF::myMalloc(sizeof(RLQds)); // inserting sys value
	rDS->objectName=(char*)MSF::myMalloc(strlen("dbcat"));
	strcpy(rDS->objectName,"dbcat");
	rDS->values=NULL;
	rDS->names=NULL;	
	RLQH :: insertToAttList(&rDS->values,"sys");
	iQH_C->insertToCatTables(rDS);
	RLQH :: freeList(rDS);
	
	rDS=(RLQds*)MSF::myMalloc(sizeof(RLQds)); //inserting default value
	rDS->objectName=(char*)MSF::myMalloc(strlen("dbcat"));
	strcpy(rDS->objectName,"dbcat");
	rDS->values=NULL;
	rDS->names=NULL;	
	RLQH :: insertToAttList(&rDS->values,"Default");
	iQH_C->insertToCatTables(rDS);
	RLQH :: freeList(rDS);
	
//inserting into tcat the tables available so far NOTE  TCATALOG       :: ADD the icat table contents, once done with B+trees(index manager);
	rDS=(RLQds*)MSF::myMalloc(sizeof(RLQds)); // inserting  dbcat value
	rDS->objectName=(char*)MSF::myMalloc(strlen("tcat"));
	strcpy(rDS->objectName,"tcat");
	rDS->values=NULL;
	rDS->names=NULL;	
	RLQH :: insertToAttList(&rDS->values,"sys");
	RLQH :: insertToAttList(&rDS->values,"dbcat");
	RLQH :: insertToAttList(&rDS->values,"2");
	iQH_C->insertToCatTables(rDS);
	RLQH :: freeList(rDS);
	
	rDS=(RLQds*)MSF::myMalloc(sizeof(RLQds)); // inserting tcat value
	rDS->objectName=(char*)MSF::myMalloc(strlen("tcat"));
	strcpy(rDS->objectName,"tcat");
	rDS->values=NULL;
	rDS->names=NULL;	
	RLQH :: insertToAttList(&rDS->values,"sys");
	RLQH :: insertToAttList(&rDS->values,"tcat");
	RLQH :: insertToAttList(&rDS->values,"3");
	iQH_C->insertToCatTables(rDS);
	RLQH :: freeList(rDS);
	
	rDS=(RLQds*)MSF::myMalloc(sizeof(RLQds)); // inserting acat value
	rDS->objectName=(char*)MSF::myMalloc(strlen("tcat"));
	strcpy(rDS->objectName,"tcat");
	rDS->values=NULL;
	rDS->names=NULL;	
	RLQH :: insertToAttList(&rDS->values,"sys");
	RLQH :: insertToAttList(&rDS->values,"acat");
	RLQH :: insertToAttList(&rDS->values,"4");
	iQH_C->insertToCatTables(rDS);
	RLQH :: freeList(rDS);
	
	rDS=(RLQds*)MSF::myMalloc(sizeof(RLQds)); // inserting icat value
	rDS->objectName=(char*)MSF::myMalloc(strlen("tcat"));
	strcpy(rDS->objectName,"tcat");
	rDS->values=NULL;
	rDS->names=NULL;	
	RLQH :: insertToAttList(&rDS->values,"sys");
	RLQH :: insertToAttList(&rDS->values,"icat");
	RLQH :: insertToAttList(&rDS->values,"5");
	iQH_C->insertToCatTables(rDS);
	RLQH :: freeList(rDS);
	
	rDS=(RLQds*)MSF::myMalloc(sizeof(RLQds)); // inserting icat value
	rDS->objectName=(char*)MSF::myMalloc(strlen("tcat"));
	strcpy(rDS->objectName,"tcat");
	rDS->values=NULL;
	rDS->names=NULL;	
	RLQH :: insertToAttList(&rDS->values,"sys");
	RLQH :: insertToAttList(&rDS->values,"iacat");
	RLQH :: insertToAttList(&rDS->values,"6");
	iQH_C->insertToCatTables(rDS);
	RLQH :: freeList(rDS);
	
//----------------------------	
	vSB_C->displayBufferStatisitics();	

	}	
		
