#include <stdio.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve unbounded Knapsack problem using dynamic programming
int unboundedKnapsack(int C, int n, int weights[], int profits[]) {
    int i, w;
    int dp[n + 1][C + 1];

    // Build the dp table bottom-up
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= C; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(profits[i - 1] + dp[i][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // The final result is stored in dp[n][C]
    return dp[n][C];
}

// Example usage
int main() {
    int n = 3; // Number of objects
    int C = 14; // Knapsack capacity

    int weights[] = {4, 6, 8};
    int profits[] = {7, 6, 9};

    printf("Capacity\tMaximum Profit\n");

    for (int i = 0; i <= C; i++) {
        int result = unboundedKnapsack(i, n, weights, profits);
        printf("%d\t\t%d\n", i, result);
    }

    int result = unboundedKnapsack(C, n, weights, profits);

    printf("\n");

    printf("Maximum profit: %d\n", result);

    return 0;
}