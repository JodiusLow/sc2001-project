#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generate input data

//define constants
#define  MIN_ARRSIZE  1000
#define  MAX_ARRSIZE  10000000
#define  X_VALUE 10000000 //x value can change


int main ()
{
    srand(time(NULL));

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
    return 0;
}