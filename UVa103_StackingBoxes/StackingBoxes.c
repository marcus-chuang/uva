
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> /*malloc*/
#include <time.h>

int TraceBoxeDimension(unsigned long *inBox,unsigned long *outBox,int dimension);
void FindNestsBox(unsigned long **BoxPtr,int SelectBox,unsigned short *answer,int numofbox,int index,int dimension);
int ReadAndSortData (unsigned long *NowColumn,unsigned long **BoxPtr,unsigned int dimension,unsigned int boxnum);

#define MAXBOX 31
#define MAXDIM 12  /* 0th: volume 11th: box number*/

int main(int argv,char *argc[])
{
#ifndef ONLINE_JUDGE
	clock_t start,end;
	start = clock();
#endif

	unsigned short answer [2][MAXBOX];
	unsigned long *BoxPtr[MAXBOX],NumOfBoxList[MAXBOX][MAXDIM],*ColumnPtr;
    unsigned int numofbox ,dimension,loopi;

	while (scanf("%d %d",&numofbox,&dimension) != EOF)
	{
		for (loopi =0;loopi<numofbox;loopi++)
		{
			/* 1. Read data from input file and sort dimension data of the box */
			ColumnPtr = *(NumOfBoxList+loopi);
			memset(ColumnPtr,0,sizeof(unsigned long) * MAXDIM);
			if (!ReadAndSortData (ColumnPtr,(unsigned long**)BoxPtr,dimension,loopi)) return 0;
		}

		/* 2. Computer maximum length of nest box. */
		answer[0][0] = 0;
		answer[1][0] = 0;
		for (loopi=0;loopi < (numofbox-answer[1][0]);loopi++)
		{
			answer[0][0] = 1;
			answer[0][1] = *(*(BoxPtr+loopi)+dimension+1);
			FindNestsBox(BoxPtr,loopi,(unsigned short*)answer,numofbox,2,dimension);
		}

		/* 3. Print Answer*/
		printf ("%d\n",answer[1][0]);
		printf ("%d",answer[1][1]);
		for (loopi=2;loopi<=answer[1][0];loopi++)
			printf (" %d",answer[1][loopi]);
		printf ("\n");
	}

#ifndef ONLINE_JUDGE
        end = clock();
        printf ("run time:%f\n",((double)(end-start)/CLOCKS_PER_SEC));
#endif
	return 0;
}

int ReadAndSortData (unsigned long *NowColumn,unsigned long **BoxPtr,unsigned int dimension,unsigned int boxnum)
{
    int loopi,loopj;
	unsigned long *dimpos,*pos,tmpvalue;
	unsigned long tmpsum,*tmpptr;

	*(NowColumn+dimension+1) = boxnum+1; /* set each box number*/

	for (loopi=1;loopi<=dimension;loopi++)
	{
		/* 1. read data from input data */
		dimpos = NowColumn+loopi;
		if (scanf("%ld",dimpos) == EOF) return 0;
		*NowColumn = *NowColumn + *dimpos;

		/* 2. sort dimension data of read data */
		for (loopj=1;loopj < loopi;loopj++)
		{
			pos = NowColumn+loopj;
			if (*dimpos < *pos)
			{
				tmpvalue = *dimpos;
				*dimpos = *pos;
				*pos = tmpvalue;
			}
		}
	}

	/* 3. Sort BoxPtr array by sum length of the box edge */
	tmpsum = *NowColumn; 		/* volume */
	for (loopi = 0;loopi<boxnum;loopi++)
	{
		if (tmpsum < **(BoxPtr+loopi))
		{
			tmpptr = *(BoxPtr+loopi);
			tmpsum = *tmpptr;
			*(BoxPtr+loopi) = NowColumn;
			NowColumn = tmpptr;
		}
	}
	*(BoxPtr+loopi)= NowColumn;
	return 1;
}

void FindNestsBox(unsigned long **BoxPtr,int SelectBox,unsigned short *answer,int numofbox,int index,int dimension)
{
	int loopi;
	unsigned short remaning_box;
	unsigned long tmpVolume,*outptr,*inptr;

	if (SelectBox != numofbox)
	{
		inptr = *(BoxPtr+SelectBox);
		tmpVolume = **(BoxPtr+SelectBox)+dimension;
		for (loopi=SelectBox+1;loopi<numofbox;loopi++)
		{
			outptr = *(BoxPtr+loopi);
			remaning_box = (numofbox - loopi) + index ;
			if ((remaning_box > *(answer+MAXBOX))  && (tmpVolume <= *outptr))
			{
				if( TraceBoxeDimension(inptr,outptr,dimension) == 1)
				{
					*answer = index;
					*(answer+index) = *(outptr+dimension+1);
					FindNestsBox(BoxPtr,loopi,(unsigned short*)answer,numofbox,index+1,dimension);
					if (*(answer+MAXBOX) == numofbox){return;}
				}
			}
		}
		if ( *answer > *(answer+MAXBOX))
				memcpy((answer+MAXBOX),answer,sizeof(unsigned short)* index);
	}
}

int TraceBoxeDimension(unsigned long *inBox,unsigned long *outBox,int dimension)
{
	int loopi;
	for (loopi=1;loopi<=dimension;loopi++)
		if (*(inBox+loopi) >= *(outBox+loopi)) return 0;
	return 1;
}
