//Argumnets both optional size if not passedd 10,000,000 is default and -c or -compare to run inbuilt std.
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include<string.h>
int THRESSHOLD = 14;
void merge(int *,int *, int *, int *);
int *partition(int *, int *, int *, int *);
void stackSort(int *, int *, int *, int *);
void reverseArray(int *, int *);
void insertionSort(int *arrayStart,int *arrayEnd)
{
    int n = arrayEnd-arrayStart, i, j, temp = 0;
    for(i = 1 ; i<n ; i++)
    {
        temp = *(arrayStart + i);
        for(j = i-1; j>=0; j--)
        {
            if(temp<(*(arrayStart+j)))
            {
                *(arrayStart + j + 1) = *(arrayStart + j);
            }
            else
            {
                break;
            }
        }
        *(arrayStart + j+ 1) = temp;
    }
}
void stackSort(int *arrayStart,int *arrayEnd)
{
    if(arrayStart>=arrayEnd)
    {
        return;
    }
    int arraySize=(arrayEnd-arrayStart);
    //auxilary array is used to divide the data to be sorted
    int *auxilaryArray=(int *)calloc((arraySize),sizeof(int));
    stackSort(arrayStart, arrayEnd, auxilaryArray, auxilaryArray+arraySize);
    free(auxilaryArray);
}

void stackSort(int * arrayStart, int * arrayEnd, int *auxilaryArrayStart, int *auxilaryArrayEnd)
{
    if(arrayStart>=arrayEnd)
        return;

    if((arrayEnd-arrayStart) < THRESSHOLD)
        return insertionSort(arrayStart,arrayEnd);

    int *auxilaryArrayMid = partition(arrayStart,arrayEnd,auxilaryArrayStart,auxilaryArrayEnd);

    if(auxilaryArrayMid!=NULL)
    {

        int *arrayMid = arrayStart + (auxilaryArrayMid - auxilaryArrayStart);

        //auxillary array and origanl array have been swapped now.
        stackSort(auxilaryArrayStart, auxilaryArrayMid+1, arrayStart, arrayMid+1);
        stackSort(auxilaryArrayMid+1, auxilaryArrayEnd, arrayMid+1, arrayEnd);

        merge(arrayStart,auxilaryArrayStart,auxilaryArrayMid,auxilaryArrayEnd);
    }
}

int * partition(int * arrayStart,int * arrayEnd, int *auxilaryArrayStart, int *auxilaryArrayEnd )
{
    if(arrayStart>=arrayEnd)
        return NULL;
    int *leftStackTop = auxilaryArrayStart, *rightStackTop = auxilaryArrayEnd, stackChangeCount=0;
    int *i = arrayStart ;                             //to traverse the array

    *leftStackTop = *i++;  //First element is copied on left stack as we start from left stack

    while(i < arrayEnd)
    {

        /*if element *i is not in order( greater as in our case) then we change the stack,
          and put the element on top of the current stack*/

        if(stackChangeCount % 2)
        {
            if(*i<*rightStackTop)
            {
                *(++leftStackTop)=*i;
                stackChangeCount++;
            }
            else
            {
                *(--rightStackTop)=*i;
            }
        }
        else
        {
            if(*i<*leftStackTop)
            {
                *(--rightStackTop)=*i;
                stackChangeCount++;
            }
            else
            {
                *(++leftStackTop)=*i;
            }
        }
        i++;
    }

    if(stackChangeCount <3)
    {
        if(stackChangeCount != 0)  //right stack is sorted but in reverse
            reverseArray(rightStackTop,auxilaryArrayEnd);
        else                      // array is already sorted
            return NULL;
    }
    return leftStackTop;
}

void reverseArray(int *arrayStart, int *arrayEnd)
{
    arrayEnd--;
    int temp;
    while(arrayStart<arrayEnd)
    {
        temp = *arrayStart;
        *arrayStart = *arrayEnd;
        *arrayEnd = temp;
        --arrayEnd;
        ++arrayStart;
    }
    return;
}
void merge(int *arrayStart, int *auxilaryArrayStart, int *auxilaryMid,int *auxilaryArrayEnd)
{
    int *i = arrayStart,*leftArrayTop = auxilaryArrayStart, *rightArrayStart = auxilaryMid+1;
    while(auxilaryMid>=leftArrayTop&&rightArrayStart<auxilaryArrayEnd)
    {
        if(*leftArrayTop<*rightArrayStart)
        {
            *i=*leftArrayTop++;
        }
        else
        {
            *i=*rightArrayStart++;
        }
        i++;
    }
    while(auxilaryMid>=leftArrayTop)
    {
        *i=*leftArrayTop++;
        i++;
    }
    while(rightArrayStart<auxilaryArrayEnd)
    {
        *i=*rightArrayStart++;
        i++;
    }
}

int main(int argc, char** argv)
{
    int i,*arr1,*arr2,arraySize= 50000000;//100000000;
    time_t timer1,timer2,timer3,timer4;

if(argc>1){	
try{
	arraySize = atoi(argv[1]);
}catch(...){
	arraySize = 50000000;
}
}
    printf("Enter the size of array : %d",arraySize);
    arr1=(int *)calloc(arraySize,sizeof(int));
    arr2=(int *)calloc(arraySize,sizeof(int));
    for(i=0; i<arraySize; i++)
    {
        *(arr1+i)=rand();
        *(arr2 + i) = *(arr1+i);
    }
    time(&timer1);
    stackSort(arr1,arr1+arraySize);
    time(&timer2);
    printf("\nTime taken to sort data: %lld\n",(long long)(timer2 -timer1));
if(argc>2 && (strcmp(argv[2],"-compare")==0 || strcmp(argv[2],"-c")==0)){
	time(&timer3);
	std::sort(arr2,arr2+arraySize);	
	time(&timer4);
	printf("\nTime taken Inbuilt sort: %lld\n",(long long)(timer4 -timer3));
}
    for(i = 1 ; i< arraySize; i++)
    {
        if(arr1[i]<arr1[i-1])
            printf("stack sort did not sort the array!!!!");
	    break;
    }
    return 0;
}
