#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void main()
{
	int randomValue;
	FILE *fptr1,*fptr2;
	fptr1=fopen("input.bin","wb");
	if (fptr1==0)
	{
		printf("..Error in opening the file\n");
		exit(0);
	}
	for (long i = 0; i < (long)pow(5,5) ;i++)
	{
		//randomValue=14-i;
		randomValue=rand();
		fwrite(&randomValue,sizeof(int),1,fptr1);
	}
	fclose(fptr1);

	fptr1=fopen("input.bin","rb");
	if (fptr1==0)
	{
		printf("..Error in opening the file\n");
		exit(0);
	}

	fptr2=fopen("input.txt","w");
	while(fread(&randomValue,sizeof(int),1,fptr1)==1)
    	{
    		fprintf(fptr2,"%d ",randomValue);
    	}
    	fclose(fptr1);
    	fclose(fptr2);
}

