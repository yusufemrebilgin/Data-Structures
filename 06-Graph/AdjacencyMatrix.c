#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

typedef struct {
    size_t numOfVertices;
    bool **matrix;
} Graph;

Graph *createGraph(size_t numOfVertices);
Graph *addVertex(Graph *graph, size_t newSize);
void addEdge(Graph *graph, size_t source, size_t destination);
void removeEdge(Graph *graph, size_t source, size_t destination);
bool areConnected(const Graph *graph, size_t source, size_t destination);
void printGraph(const Graph *graph, const char *info);
void freeGraph(Graph **graph);

#define GRAPH_SIZE 8

int main(void) {

    Graph *graph = createGraph(GRAPH_SIZE);

    if (graph == NULL) {
        fprintf(stderr, "Memory allocation failed for the graph");
        exit(EXIT_FAILURE);
    }

    
    /* ------------------ Rastgele kenar ekleme işlemi ------------------*/
    srand(time(NULL));
    int i, times = GRAPH_SIZE;
    for (i = 0; i < times; i++) {
        int randSourceIndex = rand() % GRAPH_SIZE;
        int randDestinationIndex = rand() % GRAPH_SIZE;
        printf("Adding edge %d to %d\n", randSourceIndex, randDestinationIndex);
        addEdge(graph, randSourceIndex, randDestinationIndex);
        assert(areConnected(graph, randSourceIndex, randDestinationIndex) == true);
    }

    printGraph(graph, "\nGraph after adding random edges");

    graph = addVertex(graph, GRAPH_SIZE * 2);
    if (graph == NULL) {
        fprintf(stderr, "Memory reallocation failed for the graph");
        exit(EXIT_FAILURE);
    }

    printGraph(graph, "Graph after adding vertices");

    freeGraph(&graph);

    return 0;
}

Graph *createGraph(size_t numOfVertices) {
    Graph *graph = malloc(sizeof(Graph));
    bool isAllocationFailed = false; // Bellek ayırma işlemini kontrol etmek için 'flag' değişkeni
    if (graph != NULL && (graph->matrix = malloc(sizeof(bool *) * numOfVertices)) != NULL) {
        graph->numOfVertices = numOfVertices;
        size_t i, j;
        for (i = 0; i < numOfVertices; i++) {
            graph->matrix[i] = malloc(sizeof(bool) * numOfVertices);
            if (graph->matrix[i] != NULL) {
                for (j = 0; j < numOfVertices; j++) {
                    graph->matrix[i][j] = false;
                }
            } else {
                isAllocationFailed = true;
                break;
            }
        }
    } else {
        isAllocationFailed = true;
    }

    if (isAllocationFailed) {
        freeGraph(&graph);
    }

    return graph;
}

Graph *addVertex(Graph *graph, size_t newSize) {
    if (graph != NULL && graph->numOfVertices < newSize) {

        bool isReallocationFailed = false; // Belleği yeniden ayırma işleminin kontrolü için 'flag' değişkeni
        if ((graph->matrix = realloc(graph->matrix, sizeof(bool *) * newSize)) != NULL) {
            size_t i, j;
            for (i = 0; i < newSize; i++) {

                if (i < graph->numOfVertices) {
                    // Var olan satırlar için belleği yeniden ayırır
                    graph->matrix[i] = realloc(graph->matrix[i], sizeof(bool) * newSize);
                } else {
                    // Yeni satırlar için bellek ayırır
                    graph->matrix[i] = malloc(sizeof(bool) * newSize);
                }

                if (graph->matrix[i] != NULL) {
                    /* Yeni satırların tamamı için, var olan satırlar için ise 
                    eklenen sütun sayısı kadar 'false' atması yapılır */
                    j = (i < graph->numOfVertices) ? graph->numOfVertices : 0;
                    while (j < newSize) {
                        graph->matrix[i][j] = false;
                        j++;
                    }

                } else {
                    isReallocationFailed = true;
                }
            }
            graph->numOfVertices = newSize;

        } else {
            isReallocationFailed = true;
        }

        if (isReallocationFailed) 
            freeGraph(&graph);
    }

    return graph;
}

void addEdge(Graph *graph, size_t source, size_t destination) {
    if (graph != NULL && source < graph->numOfVertices && destination < graph->numOfVertices) {
        graph->matrix[source][destination] = true;
        graph->matrix[destination][source] = true; // 'Undirected graph' olduğu için simetrik olarak ayarlanır  
    } 
}

void removeEdge(Graph *graph, size_t source, size_t destination) {
    if (graph != NULL && source < graph->numOfVertices && destination < graph->numOfVertices) {
        graph->matrix[source][destination] = false;
        graph->matrix[destination][source] = false;
    }
}

bool areConnected(const Graph *graph, size_t source, size_t destination) {
    if (graph != NULL && source < graph->numOfVertices && destination < graph->numOfVertices) {
        return (graph->matrix[source][destination] == 1 && graph->matrix[destination][source] == 1);
    }
    return false;
}

void printGraph(const Graph *graph, const char *info) {
    if (graph == NULL) {
        return;
    }

    printf("%s\n", info);
    size_t i, j;
    for (i = 0; i < graph->numOfVertices; i++) {
        printf("[");
        for (j = 0; j < graph->numOfVertices; j++) {
            printf("%d", graph->matrix[i][j]);
            if (j != graph->numOfVertices - 1)
                printf("  ");
        }
        printf("]\n");
    }
    printf("\n\n");
}

void freeGraph(Graph **graph) {
    if (*graph != NULL) {
        size_t i;
        for (i = 0; i < (*graph)->numOfVertices; i++) {
            if ((*graph)->matrix[i] == NULL) {
                break;
            }
            free((*graph)->matrix[i]);
        }
        free(*graph);

        /* Belleği iade etme işlemi gerçekleştikten sonra, 'graph'ın serbest bırakıldığını ifade etmek için 
        parametre olarak gelen adres NULL olarak işaretlenir */
        *graph = NULL;
    }
}