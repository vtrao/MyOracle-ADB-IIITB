#include "pdstandards.h"
//#include "BufferManager/FLH.h"
#include "VIndexManager.h"
#define MAXDE 1363     
//((PAGESIZE - 3*sizeof(long)) / sizeof(DirectoryEntry) )
#define MAXFS 8164    
 // PAGESIZE - (3*sizeof(long) + 2*sizeof(short)) -2(1*sizeof(long) + 1*sizeof(short))  
#define DBCAT "dbcat"
#define TCAT  "tcat"
#define ICAT  "icat" 
#define IACAT "iacat"

//DBHeader moved to FLH.h

typedef struct HeaderPage
	{
	long totNumRec;
	long totNumDP;
	long maxDEInDP;
	long pNFirstDP;
	};

typedef struct DirectoryEntry
        {
        long pageNumber;
	short totalFreeSpace;
	}DE;

		
typedef struct DirectoryPage
	{
	long nDE;
	long maxFS;
	long addressToNextDP;
	}DP;	

typedef struct DataBasePage
	{
	long timeStamp;
	long recordsInSlots;
	long totalNumberOfSlots;
	short totalFreeSpace;
	short conFreeSpace;
	}DBP;	

typedef struct SlotMap
	{
	long offset;
	short recordLength;
	}SM;

typedef struct IndexOnTable
	{
	char *indexName;
	FieldNames *fieldNames;
	long pageNumber;
	IndexOnTable *next;
	};

/*********************************************************System Catalog Handler Par**********/
class SysCatHan // Loads the initial DBMSystemCatalog Handler i.e., Sys(tem)Cat(alog)Han(dler)  of VSDBEngine
        {
        private:
                static SysCatHan *singleInstance_C;
		VSBufferManager *vSB_C;
                SysCatHan();
		void *SdBHDataC;
		void *ShPDataC;
		void *SdPDataC;
		void *SdBDataC;
        public:
                static SysCatHan *getInstance();
                int returnTableExistence(char *tableName,char *dbname,int type);       //returns the headerpage of table if exists else FAILED
                int returnDataBaseExistence(char *databaseName,int type);    //sets the static DATABASENAME_C to database if exists
                                                                    //Returns SUCCESS or FAILED accordingly
                int returnIndexExistence(char *databaseName,char *tableName,FieldNames *fNames);//Returns the Pageno of Index  if exists else FAILED
		int returnIndexExistence(char *databaseName,char *tableName,IndexOnTable **iOT);
		int returnIndexExistence(char *databaseName,char *tableName,char *columnNames);
		void getDetailsOfFields(char *tableName_P,char *databaseName_P, createColumns **columns_P);
		static void insertToIOT(IndexOnTable **head,char *indexName,FieldNames *fd,long pageNumber);
		static void displayIOT(IndexOnTable *head);					      
		static void freeIOT(IndexOnTable *head);
		virtual ~SysCatHan();							      
        };
                                                                                                      
/*******************************************************Heap Structure Handlers**************************************/
class RH          // Record Handler
	{
	// Given a set of Rids handles the records or returns them after calling the Buffer manager for respective 
	// PageNumbers
	private:
		static RH *singleInstance_C;
		VSBufferManager *vSB_C;
		RH();
	public:
		static RH *getInstance();
		static void insertToRIDList(RID **rID,long pgno,short slotID);
		static void displayRIDList(RID *rID);
		static void freeRIDList(RID *rID);
		int deleteRecord(RID *rID);
		int returnRecord(RID *rID,createColumns *columns,AttributeValues **avalues);
		int handleRecord(void* dBPData,SlotMap* sM,createColumns *columns,int type,char *columnName,char *value,short operation);
		void printRecord(RID *rID);
		virtual ~RH();
	};

class DBPH        // Data Base Page Handler
	{
	// Calls Buffer Manager's Read From Buffer Pool method to read the corresponding database page into buffer
	// And this calls the Record handler to handle the records in slots
	private:
                static DBPH *singleInstance_C;
		VSBufferManager *vSB_C;
		RH *rH_C;
                DBPH();
        public:
                static DBPH *getInstance();
		void scanDBPHForColumns(long dBPageNumber,createColumns *columns,RID **rID,int type,char *columnName,char *value,short operation);
		int scanAndInsertIntoDBPage(long dBPNum,void *record,int lengthOfRecord,int newOrNot,RID **rID_P);
		virtual ~DBPH();
									
	};	

class DPH         // Directory Page Handler
	{
	// Calls Buffer Manager's Read From Buffer Pool method to read the Directory Page i.e.., pageno, filename, data
	// For each DE structure in the Directory page call the DBPH i.e.., Data Base Page handler
	private:
                static DPH *singleInstance_C;
		VSBufferManager *vSB_C;
		DBPH* dBPH_C;
                DPH();
        public:
                static DPH *getInstance();
		void freeTableStructure(long indexPN);
		void initializeDPandDE(void *datum);
		void scanDPHForColumns(long hPageNumber,createColumns *columns,RID **rID,int type,char *columnName,char *value,short operation);
		void checkDPandDE(long dPPageNum);
		void findAndInsertToDEinDP(void *record,int lengthOfRecord,long DirPageNum,RID **rID_P);							
		void printDBHeaderPager();
		virtual ~DPH();
	};

class TableScan   // Header Page Handler to satisify queries with no where clause directly
	{
	// Calls BufferManager's Read From Buffer Pool method  to read the headerpage, filename and void *data
	// then calls Directory Page Handler DPH to handle the directory page as specified in the header page
	private:
                static TableScan *singleInstance_C;
		VSBufferManager *vSB_C;
		SysCatHan *sCH_C;
		DPH *dPH_C;
                TableScan();
        public:
                static TableScan *getInstance();
		void readAndPrint(int, int);
		int doTableScan(char *tableName_P, char *databaseName_P,RID **r,FieldNames *fNames_P,int type,char *columnName,char *value,short operation);
		virtual ~TableScan();
	};	

class Fetch       // In case of where condition this class serves the purpose
	{
	// 
	//
	private:
                static Fetch *singleInstance_C;
		VSBufferManager *vSB_C;
		RH *rH_C;
                Fetch();
        public:
                static Fetch *getInstance();
		void   fetchRIDs(RID *sourceRIDList,RID **qualifiedRIDList,int type,char *columnName,short operation,char * value, createColumns *columns);
		void   fetchColumnValues(RID *sourceRIDList,AttributeValues **values,char *columnName,createColumns *columns);
		void   fetchColumnValues(RID *sourceRIDList,AttributeValues **values1,AttributeValues **values2,
                                                            char *columnName1        ,char *columnName2        ,createColumns *columns);
		virtual ~Fetch();				
		//(RID[] rIDs,
	};

/************************************Record Level Query Handler*******************************/
class SQH  //Select Query Handler of Record Level Query Handler
	{
	private:
		int headerPageNumber_C;
		SysCatHan *sCH_C;
		static SQH *singleInstance_C;
		SQH();
	public:	
		int getRIDs(char *tableName,char *dbName,char *columnName,int operation,char *value,RID **rID);
		int displayRIDListOnRetreival(char *tableName_P,char *dbName_P,FieldNames *fNames_P,RID *rID_P);
		static SQH *getInstance();
		int executeSelect(RLQds *r,void *getResult);		
		virtual ~SQH();
	};	

class DQH //Delete Query Handler of Record Level Query Handler 
	{
	private:
		int headerPageNumber_C;
		SysCatHan *sCH_C;
		static DQH *singleInstance_C;
		DQH();
	public:	
		static DQH *getInstance();
		int doDeletion(RID *rID,char *tableName,char *dbName);
		int executeDelete(RID *rID,char *tableName,char *dbName);//internally calls doDeletion
		int executeDelete(RLQds *r,void *getResult);             //internally calls doDeletion  
		virtual ~DQH();
	};	

class UQH //Update Query Handler of Record Level Query Handler
	{
	private:
		int headerPageNumber_C;
                SysCatHan *sCH_C;				
		static UQH *singleInstance_C;
		UQH();
	public:	
		static UQH *getInstance();
		int updateQueryHandler(RLQds *r,RID *rID);
		int executeUpdate(RLQds *r,void *getResult);
		virtual ~UQH();
	};	

class IQH //Insert Query Handler of Record Level Query Handler
	{
	private:
		int headerPageNumber_C;
                SysCatHan *sCH_C;
		DPH* dPH_C;
		TableScan* tS_C;
		VSBufferManager *vSB_C;	
		void *IhPDataC;			
		void *IdBDataC;
		static IQH *singleInstance_C;
		IQH();
	public:	
		static IQH *getInstance();
		static int tellType(char *string);
		int executeInsert(RLQds *r);
		void insertToSysCat(TLQds *r);
		void insertToCatTables(RLQds *r);
		virtual ~IQH();
	};	

class RLQH // Record Level Query Handler of VSDBEngine
	{
	private:	
		SQH* sQH_C;
		DQH* dQH_C;
		UQH* uQH_C;
		IQH* iQH_C;
		static RLQH *singleInstance_C;
		RLQH();
	public:	
		static RLQH *getInstance();
		int executeRLQ(RLQds *r);
		static void insertToAttList(AttributeValues **head,char* valuep);
		static void insertToFdList(FieldNames **head,char* namep);
		static void deleteFromAttList(AttributeValues **head,char *fieldName);
		static void freeList(RLQds *r);
		static void freeAttList(AttributeValues *head);
		static void freeFdList(FieldNames *head);
		static void displayList(AttributeValues *head,FieldNames *head);
		virtual ~RLQH();
	};	

/******************************************Table Level Query Handler**************************/
class CTQH //Create Table Query Handler of Table Level Query Handler
	{
	private:
		int headerPageNumber_C;
                SysCatHan *sCH_C;
		IQH* iQH_C;
		FLH *fLH_C;
		VSBufferManager* vSB_C;
		DPH* dPH_C;
		static CTQH *singleInstance_C;
		CTQH();
	public:	
		static CTQH *getInstance();
		int executeCreateT(TLQds *t);
		virtual ~CTQH();
	};	

class DTQH //Drop Table Query Handler of Table Level Query Handler
	{
	private:
		int headerPageNumber_C;
                SysCatHan *sCH_C;
		TableScan *tS_C;	
		RH *rH_C;		
		static DTQH *singleInstance_C;
		DTQH();
	public:	
		static DTQH *getInstance();
		int executeDropT(TLQds *t);
		virtual ~DTQH();
	};	

class ATQH //Alter Table Query Handler of Table Level Query Handler
	{
	private:
		int headerPageNumber_C;
		SysCatHan *sCH_C;
		static ATQH *singleInstance_C;
		ATQH();
	public:	
		static ATQH *getInstance();		
		int executeAlterT(TLQds *t);
		virtual ~ATQH();
	};	

class STQH //Show Table Query Handler of Table Level Query Handler
	{
	private:
                SysCatHan *sCH_C;
		VSBufferManager *vSB_C;
		TableScan *tS_C;
		static STQH *singleInstance_C;
		STQH();
	public:	
		static STQH *getInstance();
		int executeShowT(TLQds *t);
		virtual ~STQH();
	};
	
class TLQH // Table Level Query Handler of VSDBEngine
	{
	private:
		CTQH* cTQH_C;
		DTQH* dTQH_C;
		ATQH* aTQH_C;
		STQH* sTQH_C;
		static TLQH *singleInstance_C;
		TLQH();
	public:
		static TLQH *getInstance();
	        int executeTLQ(TLQds *t);
					
		static int testAndUpdateList(createColumns** destColumns,createColumns *sourceColumns,FieldNames* fNames_P);
		static void InsertToList(createColumns **head,char *cname,int dtype,int attlen,int preci,
		                       char *defValue,int nNull,int uniq,int pKey,int pos);
		static void displayList(createColumns *head);
		static void freeList(TLQds *r);
		static void freeCColumns(createColumns *c);
		virtual ~TLQH();
	};	

/**********************************************Database Level Query Handler*******************/
class CDQH // Create Database Query Handler of Database Level Query Handler
	{
	private:
		int dataBaseExistsOrNot_C;
		SysCatHan *sCH_C;
		IQH *iQH_C;
		static CDQH *singleInstance_C;
		CDQH();
	public:	
		static CDQH *getInstance();
		int executeCreateDB(DLQds *d);
		virtual ~CDQH();
	};		

class UDQH // Use Database Query Handler of Database Level Query Handler
	{
	private:
		int dataBaseExistsOrNot_C;
                SysCatHan *sCH_C;
		static UDQH *singleInstance_C;
		UDQH();
	public:	
		static UDQH *getInstance();
		int executeUseDB(DLQds *d);		
		virtual ~UDQH();
	};	

class SDQH // Show Database Query Handler of Database Level Query Handler
	{
	private:
		int dataBaseExistsOrNot_C;
		SysCatHan *sCH_C;				
		static SDQH *singleInstance_C;
		SDQH();
	public:
		static SDQH *getInstance();		
		int executeShowDB(DLQds *d);
		virtual ~SDQH();
	};	

class DDQH // Drop Database Query Handler of Database Level Query Handler
	{
	private:
		int dataBaseExistsOrNot_C;
                SysCatHan *sCH_C;
		TableScan *tS_C;
		RH *rH_C;
		static DDQH *singleInstance_C;
		DDQH();
	public:	
		static DDQH *getInstance();
		int executeDropDB(DLQds *d);
		virtual ~DDQH();
	};

class DLQH //Database Level Query Handler of VSDBEngine
	{
	private:
		CDQH* cDQH_C;
		UDQH* uDQH_C;
		SDQH* sDQH_C;
		DDQH* dDQH_C;
		static DLQH *singleInstance_C;
		DLQH();
	public:
		static char* dBName;
		static DLQH *getInstance();
		int executeDLQ(DLQds *d);
		virtual ~DLQH();
		
	};

	
/*********************************************************DBINITILIZER************************/
class CreateDBMS
	{
	private:
		static CreateDBMS* singleInstance_C;
		VSBufferManager* vSB_C;
		DBHeader* dBH_C;
		CTQH* cTQH_C;
		IQH* iQH_C;
		DPH* dPH_C;
		TableScan* tS_C;
		CreateDBMS();
	public:
		static CreateDBMS *getInstance();
		int createTableStructure(DBHeader *dBH);
		int printDBHeaderStructure();
		int initializeDBH(int fileNotExists);            //Required 
		virtual ~CreateDBMS();
	};		

/*********************************************************VDBEngeine Class********************/
class VSDBEngine
	{
		private:
			SysCatHan* sysCatHan_C;
			VSBufferManager* vSB_C;
			DiskSpaceManagerLinux* dSML_C;
			ReplacementPolicy* rP_C;
			RLQH*         rLQH_C;
			TLQH*         tLQH_C;
			DLQH*         dLQH_C;
			CreateDBMS*   cDBMS_C; 
			FLH*	      fLH_C;         //Free List Handler
			static VSDBEngine *singleInstance_C;
			VSDBEngine(char *fileName,int BufferSize); // constructor is private to make singleton object
			
			
		public:
			//DBHeader *dBH_C;
			static VSDBEngine *getInstance(char *fileName,int bufferSize);
			void installDB(char *fileName);
			int temp(char *value);
			int executeQuery(RLQds *r,void *getResult);
			int executeQuery(TLQds *t);
			int executeQuery(DLQds *d);
			virtual ~VSDBEngine();			
	};

  