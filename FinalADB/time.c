#include<stdio.h>
#include<time.h>
int main()
	{
	time_t start,end,result;
	double dif;
	int i=0;
	time(&start);
	for(i=0;i<32700;i++) printf("\n venki is here");;
	time(&end);
	result=end-start;
	printf("\n%d %d %ld",start,end,result);
	}

 