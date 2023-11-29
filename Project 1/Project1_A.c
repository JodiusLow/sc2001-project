#include <stdio.h>

void InsertionSort(int arr[], int n);
void MergeSort(int arr[], int l, int r);
void Merge(int arr[], int l, int m, int r);
void HybridMergeSort(int arr[], int l, int r);
void HybridInsertionSort(int arr[], int l, int r);


// Algorithm Implementation
int main()
{
    int arr[] = {12, 14, 6, 5, 3, 7};
    int arrsize = sizeof(arr) / sizeof(arr[0]);

    InsertionSort(arr, arrsize);
    for(int i=0;i<arrsize;i++)
    {
        printf("%d ", arr[i]);
    }

    int arr2[] = {12, 14, 6, 5, 3, 7};
    int arrsize2 = sizeof(arr2) / sizeof(arr2[0]); 

    MergeSort(arr2, 0, arrsize2-1);

    printf("\n"); 

    for(int j=0;j<arrsize2;j++)
    {
        printf("%d ", arr2[j]);
    }

    int arr3[] = {12, 16, 3, 9, 3, 7};
    int arrsize3 = sizeof(arr3)/sizeof(arr3[0]); 

    printf("\n"); 

    HybridMergeSort(arr3, 0, arrsize3-1);

    for(int k=0;k<arrsize3;k++)
    {
        printf("%d ", arr3[k]);
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
    
    while( i < n1 && j < n2)
    {
        if(L[i] <= R[j]) //1st elm of left temp array <= 1st elm of right temp array
        {
            arr[k] = L[i];
            i++;
        }
        else // 1st elm of left temp array > 1st elm of right temp array
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while( i < n1)//copy remaining of elements in left temp array
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while( j < n2) //copy remaining of elements in right temp array
    {
        arr[k] = R[j];
        j++;
        k++;
    }

}

void HybridMergeSort(int arr[],int l, int r)
{
    if(r-l <= 0) return;
    else if(r - l <= 3)// value of threshold = 3
    { 
        HybridInsertionSort(arr, l, r);
        return;
    }
    int m = l + (r-l)/2; //finding the middle element
    HybridMergeSort(arr, l, m); // sort left 
    HybridMergeSort(arr, m + 1, r); // sort right
    Merge(arr, l, m, r); // merging
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
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}




