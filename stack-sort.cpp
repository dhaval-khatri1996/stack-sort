#include<stdio.h>
#include <ctime>
#include<algorithm>
#include <cstdlib> 
#include<iostream>
using namespace std;
int count=0;
void actualSort(int *,int *,int *,int *);
void stackSort(int *start,int *end){
	int size=(end-start);
	int *arr2=(int *)calloc((size),sizeof(int));
	actualSort(start,arr2,end,arr2+size);
	free(arr2);
}
int *divide(int *start1,int *start2,int *end1,int *end2){
	int *top1=start2,*top2=end2,flag=0,*i=start1;
	*start2 = *i++;

    /*code to devide the array
      Working
      Assume two stacks are made from each end of the array.
      We start from inserting elements from orignal array to one of the stacks
      Note: (start from anyone stack of your choice, the code below starts from stack one)
      Keep adding elements in the current stack from the orignal array until the element on the top
      is smaller or equal to the element being inserted.(condition 1)
      If the current element is bigger then the element to be added we add the new element in the other stack, 
      consider this(stack 2) as our current stack and keep adding elements from the orignal array as long as condition 1 is followed
      We switch stacks everytime condition 1 is false
      NOTE : (While switching the stack when ignore condition 1 for that element)
      the process is done when all elements are pushed into the two stack (or one of them)*/

	while(i<end1){
        /*Flag indictes the number of times the stack was changed 
        and helps us keep record of the stack being used*/
	
		if(flag%2){
			if(*i<*top2){
				*(++top1)=*i;
				flag++;
			}else{
				*(--top2)=*i;
			}
		}
		else{
			if(*i<*top1){
				*(--top2)=*i;
				flag++;
			}else{
				*(++top1)=*i;
			}
		}
		i++;
	}
	i=start1;
    /*If flag value is 0/1 this indicates the values in both stack are sorted.*/
    if(flag<2){             
		end2--;
		while(top1>=start2&&top2<=end2){
			if(*start2<*end2){
				*i=*start2++;
			}else{
				*i=*end2--;
			}
			i++;
		}
		while(top1>=start2){
			*i=*start2++;
			i++;
		}
		while(top2<end2){
			*i=*end2--;
			i++;
		}
		return NULL;
	}
	return top1;
}
void actualSort(int *start1,int *start2,int *end1,int *end2){
	if(start1>=end1){                   //1 or 0 elements in the array
		return;
	}
	if((end1-start1)==2){               //2 elements in the array
		 end1--;
		if(*end1<*start1){              //Swap only if the first element is bigger the the other
			int temp = *start1;
			*start1=*end1;
			*end1=temp;
		}
		return;
	}

	int *top1=divide(start1,start2,end1,end2);          //return NULL if the array is not sorted
    
    if(top1!=NULL){                                     //Sort the array if it is not already sorted
		int *top2=top1+1,*temp=start1+(top1-start2)+1,*i=start1;
        /* sorting the smaller sub array first to keep the stack trace small*/

		if((top2-start2)<(end2-top2)){
			actualSort(start2,start1,top2,temp);
			actualSort(top2,temp,end2,end1);
		}else{
			actualSort(top2,temp,end2,end1);
			actualSort(start2,start1,top2,temp);
		}

        //Merging both the sorted array.
		while(top1>=start2&&top2<end2){
			if(*start2<*top2){
					*i=*start2++;
				}else{
					*i=*top2++;
				}
			i++;
		}
		while(top1>=start2){
			*i=*start2++;
			i++;
		}
		while(top2<end2){
			*i=*top2++;
			i++;
		}
	}
}

int main(){
	int i,*arr,size= 1;
	printf("Enter the size of array : ");
	scanf("%d",&size);
	arr=(int *)calloc(size,sizeof(int));
	for(i=0;i<size;i++){
		arr[i]=rand();
	}
	clock_t now1,now2;
	now1=clock();
	stackSort(arr,arr+size);
	now2=clock();
	printf("Time taken by stack-sort to %d sort elemts is %llf seconds.",size,(float)(now2-now1)/(float)CLOCKS_PER_SEC);
	return 0;
}

