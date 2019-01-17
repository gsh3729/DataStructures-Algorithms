/*
	PROGRAMMER'S NAME : G SRIHARSHA
	ROLLNO:111601005
	PROGRAM NAME : mergeFile.c
	DATE : 9/1/18
	*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	char filename[30];
	FILE *fptr1a,*fptr1b,*fptr2,*fptr3;

	printf("..Enter the input file:");
	scanf("%s",filename);

	int value1,value2,flag=0;
	int size=1,size1,size2;
	int count1,count2,filesize;
	
	fptr3=fopen(filename,"rb");
	fseek(fptr3,0,SEEK_END);
	filesize=(ftell(fptr3))/sizeof(int); //To get the file size
	//printf("N value:%d\n", n);
	while(1)
 	{
 		if(flag==0) //fptr1a and fptr1b are for reading the files
 		{			//fptr2 is for writing data to the file
 			fptr1a=fopen(filename,"rb");
 			fptr1b=fopen(filename,"rb");

 			fptr2=fopen("outputFile.bin","wb");
 			flag=1;
 		}
 		else 		//using the same initial files but swapped
 		{
 			fptr1a=fopen("outputFile.bin","rb");
 			fptr1b=fopen("outputFile.bin","rb");
 			
 			fptr2=fopen(filename,"wb");
 			flag=0;
 		}
 		
 		while(fread(&value1,sizeof(int),1,fptr1a)==1)
 		{
 			if( ( (ftell(fptr1a)/sizeof(int)) -1 + size) > filesize ) 
 			{	//(position of fptr1 before scanning value1 + size > filesize)
 				size1=filesize-((ftell(fptr1a)/sizeof(int))-1);
 				size2=0;
 			}
 			else if( filesize - ( (ftell(fptr1a)/sizeof(int)) -1 + size) < size)
 			{	//(filesize - position of fptr1 before scanning value1 < size)
 				size1=size;
 				size2=filesize - ( (ftell(fptr1a)/sizeof(int)) -1 + size);

 			}
 			else
 			{
 				size1=size;
 				size2=size;
 			}
 			
 			fseek(fptr1b,size*sizeof(int),SEEK_CUR);
 			fread(&value2,sizeof(int),1,fptr1b);

			count1=0;
			count2=0;
			while(count1<size1 && count2<size2) 
			{
				if(value1 <= value2)
				{
					fwrite(&value1,sizeof(int),1,fptr2);
					if(count1!=size1-1)
					{
						fread(&value1,sizeof(int),1,fptr1a);
					}
					count1++;
				}
				else
				{
					fwrite(&value2,sizeof(int),1,fptr2);
					if(count2!=size2-1)
					{
						fread(&value2,sizeof(int),1,fptr1b);
					}
					count2++;
				}
			}
			while(count1<size1) 
			{
				fwrite(&value1,sizeof(int),1,fptr2);
				if (count1!=size1-1)
				{
					fread(&value1,sizeof(int),1,fptr1a);
				}
				count1++;
			}
			while(count2<size2) 
			{			
				fwrite(&value2,sizeof(int),1,fptr2);
				if(count2!=size2-1)
				{
					fread(&value2,sizeof(int),1,fptr1b);
				}
				count2++;
			}
			fseek(fptr1a,size*sizeof(int),SEEK_CUR);
			
 		}
 		fclose(fptr1a);
 		fclose(fptr1b);
 		fclose(fptr2);
 		size=2*size;
 		if (size>=filesize) //terminating condition for outer loop
 		{
 			break;
 		}
 	}

 	 if (flag==0)
 	 {
 	 	fptr1a=fopen(filename,"rb");
 	 }
 	 else
 	 {
 		fptr1a=fopen("outputFile.bin","rb");
 	 }
 	
 	fptr2=fopen("finalOutput.txt","w");
	while(fread(&value1,sizeof(int),1,fptr1a)==1)
    {
    	fprintf(fptr2,"%d ",value1);
    }
    fclose(fptr1a);
    fclose(fptr2);

}


// if (fptr1a==0)
	// {
	// 	printf("..Error in opening the file\n");
	// 	exit(0);
	// }

	// if (fptr2==0)
	// {
	// 	printf("..Error in writing(creating) the file\n");
	// 	exit(0);
	// }


