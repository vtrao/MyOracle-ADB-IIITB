#include<stdio.h>
int main()
	{
	FILE *fp;
	fp=fopen("insert","w");
	char vv[10];
	int i=0;
	fprintf(fp,"create table indian (i int,j char,k char,x int,y int);\n");
	for(i=0;i<100000;i++)
		{
		vv[0]='\0';
		sprintf(vv,"vv%d",i);
		fprintf(fp,"insert into indian values(%d,\"%s\",\"%s\",%d,%d)\n",i+1,vv,vv,i/2+1,i%2+1);
		//fprintf(fp,"insert into venki values(%d,\"%s\",%d,\"%s\")\n",i+700,"tempVenki",i+701,vv); 
		//fprintf(fp,"insert into venki values(%d,\"%s\",%d,\"%s\")\n",i+500,"tempVenki",i+501,vv); 
		}
	fprintf(fp,"quit");	
	fclose(fp);	
		
	} 
 