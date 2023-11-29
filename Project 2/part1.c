#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

struct GraphInfo {
    int **graph;
    int edges;
};

int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int **graph, int src, int V) {
    int dist[V];
    int sptSet[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

struct GraphInfo generateRandomGraph(int V) {
    int **graph = malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = malloc(V * sizeof(int));
    }

    int E = 0;

    srand(time(NULL));
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) {
                graph[i][j] = 0; // No self-loops
            } else {
                // Generate random weights between 1 and 100 for the edges
                graph[i][j] = rand() % 100 + 1;
                E++;
            }
        }
    }
    struct GraphInfo info;
    info.graph = graph;
    info.edges = E;
    return info;
}

void freeGraph(int **graph, int V) {
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);
}

int main() {
    // int V;
    // printf("Enter the number of vertices: ");
    // scanf("%d", &V);
    int V = 1000;
    for(int V; V<=20000; V+=1000){

    struct GraphInfo graphInfo = generateRandomGraph(V);
    int **graph = graphInfo.graph;
    int E = graphInfo.edges;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    dijkstra(graph, 0, V);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
	 printf("Number of Vertices: %d ", V);
    printf("Number of Edges: %d ", E);
    printf("Time taken by function: %f seconds\n", cpu_time_used);

	// Write V and time taken to a CSV file
    // FILE *fp;
    // fp = fopen("output.csv", "a"); // Open file in append mode
    // if (fp != NULL) {
    //     fprintf(fp, "%d,%f\n", V, cpu_time_used); // Write V and time to the file
    //     fclose(fp); // Close the file
    // } else {
    //     printf("Error: Could not open the file for writing.\n");
    // }

    freeGraph(graph, V);
    }

    return 0;
}
