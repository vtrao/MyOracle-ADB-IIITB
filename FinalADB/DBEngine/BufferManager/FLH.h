#include "VSBufferManager.h"
#define FLEMPTY -1
#define FLCHAINED -2
#define FLGROUNDED -3


#define DBINTTYPE   1240
#define DBFLOATTYPE 1241
#define DBCHARTYPE  1242
#define DBDATETYPE  1243

#define LE	1020	//Less Than or Equal To
#define LT	1021	//Less Than
#define GE	1022	//Greater Than or Equal To
#define GT	1023	//Greater Than
#define EQ	1024	//Equal To
#define NE	1025	//Not Equal To


typedef struct DBHeader
	{
	long fpListPointer; // freePage List Pointer
	long dbCatPointer;  // database Catalog Pointer
	long tCatPointer;   // table Catalog Pointer
	long aCatPointer;   // attribute Catalog Pointer
	long iCatPointer;   // index Catalog Pointer
	long assignedPN;    // Highest Assigned PageNumber in the file so far
	long iaCatPointer;
	};
		
typedef struct FLHH //FreeListHandler header
	{
	short flag;
	short index;
	long prevPN;
	long nextPN;
	};	

typedef struct RID
	{
	long pageNumber;
	long slotID;
	RID *next;
	};	
	
/*********************************************************Data Structure Classes**************/
class FLH //Free List handler, maintains the free list
	{
	private:
		static FLH *singleInstance_C;
		int INDEX;
		VSBufferManager *VSB;
		long *FL;
		void* fLData;
		long PNO;
		FLHH *fLHH;
		FLH();
	public:
		static FLH *getInstance();
		int MAXIND;
		void cleanit(long pn);
		long getFreePage(); // returns pageNumber if freepage exists else -1
		void displayFL();
		void addToFL(long pageNumber);
		void printFLH();
		virtual ~FLH();
	};
  ʠ!0