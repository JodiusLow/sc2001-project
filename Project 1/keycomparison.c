#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define constants
#define  MIN_ARRSIZE  10000
#define  MAX_ARRSIZE  1000000
#define  X_VALUE 1000000 //x value can change

void InsertionSort(int arr[], int n);
void MergeSort(int arr[], int l, int r);
void Merge(int arr[], int l, int m, int r);
void HybridMergeSort(int arr[], int l, int r, int S);
void HybridInsertionSort(int arr[], int l, int r);

int key_comparisons = 0;

// Algorithm Implementation
int main()
{
    srand(time(NULL));

    int S;

    for(int i = MIN_ARRSIZE; i<=MAX_ARRSIZE; i *=10)
    {
        int *arr = (int *)malloc(i * sizeof(int));
        int arrsize = i;

        if(arr == NULL)
        {
            printf("Memory Allocation Fail");
            exit(1);
        }

        //Filling the array with random integers in the range [1, x]
        for(int j = 0; j < i; j++)
        {
            arr[j] = (rand() % X_VALUE) + 1;
        }

        printf("Enter S value: ");
        scanf("%d",&S);
        HybridMergeSort(arr, 0, arrsize-1, S);
        printf("key comparisons = %d\n", key_comparisons);
        key_comparisons = 0;

        // Create a filename based on the array size
        char filename[20];
        snprintf(filename, sizeof(filename), "array_%d.txt", i);

        // Open a new text file for writing
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            exit(1);
        }

        // Write array data to the file
        for (int k = 0; k < i; k++) {
            fprintf(file, "%d ", arr[k]);
        }

        // Close the file
        fclose(file);

        free(arr);

    }
    return 0;
}

void InsertionSort(int arr[], int n)
{
    int i, j, key;
    for(i = 1 ;i < n ;i++)
    {
        key = arr[i];
        j = i - 1;

        while(j>=0 && arr[j] > key) //previous element larger than current element
        {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j+1] = key;
    }
}

void MergeSort(int arr[], int l, int r)
{
    if(r-l <= 0) return;
    int m = l + (r-l)/2; //finding the middle element

    MergeSort(arr, l, m); // sort left
    MergeSort(arr, m+1, r); // sort right
    Merge(arr, l, m, r); // merging

}

void Merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1; //size of first array [l,....,m]
    int n2 = r - m; //size of second array [m,....,r]

    int L[n1]; //temp left array
    int R[n2]; //temp right array

    for(int i = 0; i < n1; i++) //copy into left temp array
    {
        L[i] = arr[l+i];
    }

    for(int j = 0; j < n2; j++)//copy into right temp array
    {
        R[j] = arr[m + 1 + j];
    }

    int i = 0; // reset the index of left temp array
    int j = 0; // reset the index of right temp array
    int k = l; // index of the merge array

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j]) //1st elm of left temp array <= 1st elm of right temp array
        {
            key_comparisons++;
            arr[k] = L[i];
            i++;
        }
        else // 1st elm of left temp array > 1st elm of right temp array
        {
            key_comparisons++;
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1)//copy remaining of elements in left temp array
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2) //copy remaining of elements in right temp array
    {
        arr[k] = R[j];
        j++;
        k++;
    }

}

void HybridMergeSort(int arr[],int l, int r, int S)
{
    if(r-l <= 0) return;
    else if(r - l <= S)// value of threshold = S
    {
        HybridInsertionSort(arr, l, r);
        return;
    }
    int m = l + (r-l)/2; //finding the middle element
    HybridMergeSort(arr, l, m, S); // sort left
    HybridMergeSort(arr, m + 1, r, S); // sort right
    Merge(arr, l, m, r); // merging
    return;
}

void HybridInsertionSort(int arr[], int l, int r)
{
    int i, j, key;
    for (i = l + 1; i <= r; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= l && arr[j] > key)
        {
            key_comparisons++;
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
    return;
}
