#include <stdio.h>
#include <limits.h>

#define max 100

void prims(int n, int graph[max][max]) {
    int selected[max] = {0}; 
    int no_edge = 0;
    
    selected[0] = 1; 
    
    printf("\nprims mst edges:\n");
    
    while (no_edge < n - 1) { 
        int min = INT_MAX, u = -1, v = -1;
        
        for (int i = 0; i < n; i++) {
            if (selected[i]) {
                for (int j = 0; j < n; j++) {
                    if (!selected[j] && graph[i][j] && graph[i][j] < min) {
                        min = graph[i][j];
                        u = i; 
                        v = j; 
                    }
                }
            }
        }
        
        printf("edge %d - %d weight %d\n", u, v, graph[u][v]);
        selected[v] = 1;
        no_edge++;
    }
}

int parent[max];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSets(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

void kruskals(int n, int graph[max][max]) {
    int edges = 0;
    
    for (int i = 0; i < n; i++)
        parent[i] = i;
    
    printf("\nkruskals mst edges:\n");
    
    while (edges < n - 1) {
        int min = INT_MAX, u = -1, v = -1;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][j] && find(i) != find(j) && graph[i][j] < min) {
                    min = graph[i][j];
                    u = i;
                    v = j;
                }
            }
        }
        
        if (u != -1 && v != -1) { 
            unionSets(u, v);
            printf("edge %d - %d weight %d\n", u, v, min);
            edges++;
        }
    }
}

int main() {
    int n;
    int graph[max][max];
    
    printf("enter number of vertices (max %d)\n", max);
    scanf("%d", &n);
    
    if (n <= 0 || n > max) {
        printf("invalid number of vertices. exiting.\n");
        return 1;
    }
    
    printf("enter adjacency matrix (0 if no edge, positive weight otherwise)\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    prims(n, graph);
    kruskals(n, graph);
    
    return 0;
}