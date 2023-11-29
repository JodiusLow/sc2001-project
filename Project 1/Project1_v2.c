#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 15000000

void mergeInsertionSort(int*,int,int,int);
void merge(int*,int,int);
void swap(int,int,int*);
void InsertionSort(int*,int,int);

long int comparisons;
int*tmp;

int main(void) 
{
    int i,j;
    int S;
    int*array = malloc(MAX_ARRAY_SIZE * sizeof(int));
    tmp = malloc(sizeof(int)*MAX_ARRAY_SIZE);
    
    printf("What is the threshold? ");
    scanf("%d",&S);
    
    srand(time(NULL));
    //srand() is a function that initializes the random number generator with a seed value. It expects an integer argument as the seed.
    //time(NULL) retrieves the current time in seconds since January 1, 1970 (UNIX timestamp) and returns it as a value of type time_t. This value changes every second.
    //By using srand(time(NULL));, you are setting the seed of the random number generator to the current time, which ensures that each time you run your program, the random numbers generated will be different (or at least appear to be different) because the seed is constantly changing.
    
    //Altering problem size with respect to S
    for(i=1000;i<=MAX_ARRAY_SIZE;i+=500000)
    {
        if (i==501000)
            i = 500000;

        for(j=0;j<i;j++)
            array[j]=(rand()%i+1);
        
        comparisons=0;
        clock_t begin=clock();
        mergeInsertionSort(array,0,i-1,S);
        clock_t end=clock();

        printf("Array Size: %d, Time Taken: %lf seconds, Key Comparisons: %ld\n",i,(double)(end-begin)/CLOCKS_PER_SEC,comparisons);
    }

    //Altering S with respect to problem size
    /*for(i=0;i<1000000;i++)
    {
        array[i]=(rand()%MAX_ARRAY_SIZE+1);
    }
        
    printf("Array Size: MAX_ARRAY_SIZE\n");

    for(S=1;S<=50;S++)
    {
        for(i=0;i<MAX_ARRAY_SIZE;i++)
        {
            array[i]=(rand()%MAX_ARRAY_SIZE+1);
        }

        comparisons=0;
        clock_t begin=clock();
        mergeInsertionSort(array,0,9999999,S);
        clock_t end=clock();
        
        printf("Threshold: %d Runtime: %lf seconds, Key Comparisons: %ld\n",S,(double)(end-begin)/CLOCKS_PER_SEC,comparisons);
    }
    return 0;*/

    free(array);
    free(tmp);
}

void mergeInsertionSort(int* array, int start, int end, int S)
{

    if(start >= end) return;

    if(end - start > S) //merge sort
    {
        int mid=(start + end)/2;
        mergeInsertionSort(array,start,mid,S);
        mergeInsertionSort(array,mid+1,end,S);
        merge(array,start,end);
    }
    else //insert sort
        InsertionSort(array,start,end);
}

//merge settled
void merge(int*array,int start,int end)
{

    int mid=(start+end)/2;

    int i = start, j = mid+1, k=0;

    if(end<=start) return;

    while(i <= mid && j <= end) //while both subarrays are not empty
    {
        comparisons++;
        if(array[i] <= array[j]) //left smaller than right
        {
            tmp[k] = array[i];//put into tmp array
            k++;
            i++; 
        }
        else 
        {
            tmp[k] = array[j];
            k++;
            j++;
        }
    }

    while(i <= mid) //fill the array with remaining elements from the non-empty sorted list
    {
        tmp[k] = array[i];
        k++;
        i++;
    } 
    
    while(j <= end)
    {
        tmp[k] = array[j];
        k++;
        j++;
    }
    
    i=start;

    for(k=0; k < end-start+1; k++) //i put tmp back into the first array
    {
        array[i] = tmp[k];
        i++;
        k++;
    } 

}


//insertion sort settled
void InsertionSort(int*array, int start, int end)
{

    int i, j;
    
    for(i = start+1; i <= end; i++) //Traverse entries from left to right
    {
        for(j = i; j > start; j--) //Insert entry into sorted array from right to left
        { 
            comparisons++;

            if(array[j] < array[j-1]) swap(j, j-1, array);
            else break;
        }
    }
}


void swap(int index1,int index2,int *array)
{
    int tmp = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp;
}