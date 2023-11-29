#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

// Define a structure to represent a node in the adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Define a structure to represent the adjacency list
struct Graph {
    int V; // Number of vertices
    struct Node** adjList;
};

// Define a structure to represent a heap node
struct HeapNode {
    int vertex;
    int distance;
};

// Create a new node
struct Node* createNode(int vertex, int weight) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with V vertices
struct Graph* createGraph(int V) 
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) 
    {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Add an edge to the graph (bidirectional)
void addEdge(struct Graph* graph, int source, int destination, int weight) 
{
    //source is the INDEX of the vertex source
    struct Node* cur = graph->adjList[source];//cur pointer to traverse the adjList
    struct Node* newNode = createNode(destination, weight);
    graph->adjList[source] = newNode;
    newNode->next = cur;
    //  struct Node* newNode = createNode(destination, weight);
    //  newNode->next = graph->adjList[source];
    //  graph->adjList[source] = newNode;
}

// Min-heap functions
struct HeapNode* createHeapNode(int vertex, int distance) 
{
    struct HeapNode* node = (struct HeapNode*)malloc(sizeof(struct HeapNode));
    node->vertex = vertex;
    node->distance = distance;
    return node;
}

void swap(struct HeapNode** a, struct HeapNode** b) 
{
    struct HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct HeapNode* arr[], int n, int i) //fixHeap minHeap
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && (arr[left]->distance < arr[smallest]->distance))
        smallest = left;

    if (right < n && (arr[right]->distance < arr[smallest]->distance))
        smallest = right;

    if (smallest != i) 
    {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

// void buildHeap(struct HeapNode* arr[], int n) 
// {
//     int i = (n - 1) / 2;
//     while (i >= 0) {
//         heapify(arr, n, i);
//         i--;
//     }
// }

struct HeapNode* extractMin(struct HeapNode* arr[], int* n) 
{
    if (*n <= 0) return NULL;
    struct HeapNode* root = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return root;
}

void decreaseKey(struct HeapNode* arr[], int heapSize, int source, int dist) //check if need to update shortest distance of other vertices
{
    int i;
    for (i = 0; i < heapSize; i++)  
    {
        if (arr[i]->vertex == source)//search for the specific 'source' vertex
            break;
    }

    if (i < heapSize) 
    {
        arr[i]->distance = dist;//update the distance value
        while (i != 0 && (arr[i]->distance < arr[(i - 1) / 2]->distance))//compare distance of current node with its parents node and swap if necessary
        {
            swap(&arr[i], &arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

// Dijkstra's algorithm using min-heap
void dijkstra(struct Graph* graph, int source) 
{
    int V = graph->V;//no. of vertices
    int *dist = (int *)malloc(V*sizeof(int));

    // Initialize the min-heap
    struct HeapNode* heap[V];
    int heapSize = 0;

    for (int i = 0; i < V; i++) 
    {
        dist[i] = INT_MAX;
        heap[i] = createHeapNode(i, dist[i]);
        heapSize++;
    }

    dist[source] = 0;
    decreaseKey(heap, heapSize, source, dist[source]);//check if need to update shortest distance of other vertices

    while (heapSize > 0) 
    {
        struct HeapNode* minNode = extractMin(heap, &heapSize);
        int u = minNode->vertex; //get the vertex that is being removed

        struct Node* current = graph->adjList[u];
        while (current != NULL) 
        {
            int v = current->vertex;
            int weight = current->weight;

            if (dist[u] != INT_MAX && (dist[u] + weight < dist[v])) //finding shortest distance from source to vertex
            {
                dist[v] = dist[u] + weight; //update the shortest distance in the dist array
                decreaseKey(heap, heapSize, v, dist[v]);//check if need to update shortest distance of other vertices
            }
            current = current->next;
        }
        free(minNode);
    }

    free(dist);
    //for checking if dijkstra algo is working
    /*printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; ++i) 
        printf("%d \t %d\n", i, dist[i]);
    */
}

int main() 
{
    int maxVertices = 20000; // Maximum number of vertices
    srand(time(NULL)); // Seed the random number generator with the current time

    //increasing number of V in a complete graph
    for (int V = 1000; V<=maxVertices; V+=500)
    {
        struct Graph* graph = createGraph(V);
        int E = 0;
        // Generate complete (fully connected) graph, BIDIRECTIONAL
        for (int i = 0; i < V; i++) 
        {
            for (int j = 0; j< V; j++)
            {   
                if (i!=j)
                {
                    int weight = 1 + rand() % (INT_MAX);
                    addEdge(graph, i, j, weight);
                    E ++;
                }
                
            }
        }
        
        int source = 0;
        clock_t start = clock();
        dijkstra(graph, source);
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d, %d, %f\n", V, E/2, cpu_time_used);//for excel
        //printf("Graph with %d vertices and %d edges: Time taken: %f seconds\n", V, E/2, cpu_time_used);
        // Free the memory used by the graph for each iteration
        for (int i = 0; i < V; i++) 
        {
            struct Node* current = graph->adjList[i];
            while (current != NULL) 
            {
                struct Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->adjList);
        free(graph);
    }

    //increasing number of E with fixed V
    /*for (int V = 10000; V<=maxVertices; V+=500)
    {
        struct Graph* graph = createGraph(V);
        int E = 0;
        // Generate complete (fully connected) graph, BIDIRECTIONAL
        for (int i = 0; i < V; i++) 
        {
            for (int j = 0; j< V; j++)
            {   
                if (i!=j)
                {
                    int weight = 1 + rand() % (INT_MAX);
                    addEdge(graph, i, j, weight);
                    // if (E>5000000)//for excel, cap it if not too many data
                    // break;
                    E ++;
                }
            }
            // if (E>5000000)//for excel, cap it if not too many data
            // break;
            int source = 0;
            clock_t start = clock();
            dijkstra(graph, source);
            clock_t end = clock();
            double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            //printf("%d, %d, %f\n", V, E/2, cpu_time_used);//for excel
            printf("Graph with %d vertices and %d edges: Time taken: %f seconds\n", V, E/2, cpu_time_used);
        }
        
        // Free the memory used by the graph for each iteration
        for (int i = 0; i < V; i++) 
        {
            struct Node* current = graph->adjList[i];
            while (current != NULL) 
            {
                struct Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->adjList);
        free(graph);
    }*/

    //increasing number of V in a SPARSE graph
    /*for (int V = 1000; V<=maxVertices; V+=500)
    {
        struct Graph* graph = createGraph(V);
        int E = 0;
        // Generate sparse graph
        for (int i = 0; i < V; i++) 
        {
            int j = i+1;
            if (j<V) //can do (j==V)
            {
                int weight = 1 + rand() % (INT_MAX);
                addEdge(graph, i, j, weight);
                E ++; //E should be |V|-1 for sparse graph
            }
        }
        
        int source = 0;
        clock_t start = clock();
        dijkstra(graph, source);
        clock_t end = clock();
        double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d, %d, %f\n", V, E, cpu_time_used);//for excel
        //printf("Graph with %d vertices and %d edges: Time taken: %f seconds\n", V, E/2, cpu_time_used);
        // Free the memory used by the graph for each iteration
        for (int i = 0; i < V; i++) 
        {
            struct Node* current = graph->adjList[i];
            while (current != NULL) 
            {
                struct Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->adjList);
        free(graph);
    }*/

    



    return 0;
}
