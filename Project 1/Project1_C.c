#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void Merge(int arr[], int l, int m, int r);
void InsertionSort(int arr[], int n);
void HybridMergeSort(int arr[], int l, int r, int S);
void HybridInsertionSort(int arr[], int l, int r);
void writeArrayToFile(int arr[], int size, const char *filename);


//define constants
#define  MIN_ARRSIZE  1000
#define  MAX_ARRSIZE  10000000
#define  X_VALUE 10000000 //x value can change

int key_comparisons = 0;
int L[MAX_ARRSIZE];
int R[MAX_ARRSIZE];
 
int main() {

    // Varying N with fixed S value
    /*int S;
    srand(time(NULL));
    //inputing datas into the array
    for(int i = MIN_ARRSIZE; i<=MAX_ARRSIZE; i *=10)
    {
        int *arr = (int *)malloc(i * sizeof(int));

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

    // Open the CSV file for writing
    FILE *csvFile = fopen("output.csv", "a");

     // Check if the file was opened successfully
    if (csvFile == NULL) {
        perror("Error opening CSV file");
        return 1;
    }

    // Write the CSV header row
    fprintf(csvFile, "Array Size,S Value,Key Comparisons,Time Taken (milliseconds)\n");
    
    for(int i = MIN_ARRSIZE; i<=MAX_ARRSIZE; i *=10)
    {
        char filename[20];
        sprintf(filename, "array_%d.txt", i);
        printf("%s\n", filename);


        //read file & append into arr
        int *arr = (int *)malloc(i * sizeof(int));
        FILE *file = fopen(filename, "r");
    
        int index =0;
        int num;
        while (fscanf(file, "%d", &num) == 1)
        {
            arr[index] = num;
            index++;
        }
        fclose(file);

        int arrsize = index;
        
        //calculate time taken
        clock_t start_time = clock();
        //sort the array
        // printf("Enter S value: ");
        // scanf("%d",&S);
        S = 25;
        HybridMergeSort(arr, 0, arrsize-1, S);
        printf("key comparisons = %d\n", key_comparisons);
        clock_t end_time = clock();
        double time_taken = ((double)(end_time - start_time))/CLOCKS_PER_SEC * 1000; // in milliseconds

        // Create a new filename for the sorted array
        char sortedFilename[20];
        sprintf(sortedFilename, "sorted_array_%d.txt", i);

        // Write the sorted array to the new text file
        writeArrayToFile(arr, arrsize, sortedFilename);
      
        printf("time taken to execute: %.5f milliseconds \n", time_taken);
        printf("number of element: %d \n", arrsize);

        time_t current_time;
        time(&current_time);
        char* time_string = ctime(&current_time);

        //write output log file
        FILE *file1 = fopen("output.txt", "a");
        if (file1 == NULL) {
            // If the file doesn't exist, create a new one
            file = fopen("output.txt", "w");
            if (file == NULL) 
            {
                perror("Error opening file");
                exit(1);
            }
        }
        fprintf(file1, "%s output: \n", filename);
        fprintf(file1, "Data Size: %d elements \n", arrsize);
        fprintf(file1, "Key Comparisons: %d\n", key_comparisons);
        fprintf(file1, "Time taken to execute: %.5f milliseconds \n", time_taken);
        fprintf(file1, "Date and time: %s \n\n", time_string);
        fprintf(csvFile, "%d,%d,%d,%.5f\n", arrsize, S, key_comparisons, time_taken); // CSV fiile

        time_taken = 0;
        key_comparisons = 0;

        // Close the file
        fclose(file1);
        free(arr);
    }
    
    //Close CSV file
    fclose(csvFile);
    */
    


    //Varying S with fixed N value
    srand(time(NULL));

    // Input array size (n)
    int n;
    //printf("Enter the fixed array size (n): ");
    //scanf("%d", &n);
    n = 10000000;

    // Open the CSV file for writing
    FILE *csvFile = fopen("output.csv", "a");
    if (csvFile == NULL) {
        perror("Error opening CSV file");
        return 1;
    }
    // Write the CSV header row
    fprintf(csvFile, "Array Size,S Value,Key Comparisons,Time Taken (milliseconds)\n");

    // Iterate over different values of S
    for (int S = 5; S <= 100; S += 5) {
        // Allocate memory for the array
        int *arr = (int *)malloc(n * sizeof(int));

        if (arr == NULL) {
            printf("Memory Allocation Fail");
            exit(1);
        }

        // Fill the array with random integers in the range [1, x]
        for (int j = 0; j < n; j++) {
            arr[j] = (rand() % X_VALUE) + 1;
        }

        // Calculate time taken
        clock_t start_time = clock();
        HybridMergeSort(arr, 0, n - 1, S);
        clock_t end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000; // in milliseconds

        printf("Array Size: %d, S Value: %d\n", n, S);
        printf("Key comparisons = %d\n", key_comparisons);
        printf("Time taken to execute: %.5f milliseconds\n", time_taken);

        // Write results to CSV file
        fprintf(csvFile, "%d,%d,%d,%.5f\n", n, S, key_comparisons, time_taken);

        // Reset key comparisons
        key_comparisons = 0;

        // Free memory
        free(arr);
    }
    // Close the CSV file
    fclose(csvFile);
    
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

    // int L[n1]; //temp left array
    // int R[n2]; //temp right array

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


void writeArrayToFile(int arr[], int size, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}
