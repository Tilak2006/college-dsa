#include <stdio.h>
#include <stdbool.h>

#define MAX 10

bool isSafe(int v, int graph[MAX][MAX], int color[], int c, int V){
    for(int i = 0; i < V; ++i){
        if(graph[v][i] && color[i] == c)
            return false;
    }
    return true;
}

bool graphColoringUtil(int graph[MAX][MAX], int m, int color[], int v, int V){
    if(v == V)
        return true;

    for(int c = 1; c <= m; ++c){
        if(isSafe(v, graph, color, c, V)){
            color[v] = c;

            if(graphColoringUtil(graph, m, color, v + 1, V))
                return true;

            color[v] = 0;
        }
    }
    return false;
}

bool graphColoring(int graph[MAX][MAX], int m, int V){
    int color[MAX] = {0};

    if(!graphColoringUtil(graph, m, color, 0, V)){
        printf("No solution exists\n");
        return false;
    }

    printf("Solution Exists: Following are the assigned colors:\n");
    for(int i = 0; i < V; ++i)
        printf("%d ", color[i]);
    printf("\n");

    return true;
}

int main(){
    int V;
    printf("enter number of vertices: ");
    scanf("%d", &V);

    int graph[MAX][MAX];
    printf("enter adjacency matrix (%d x %d):\n", V, V);
    for(int i = 0; i < V; ++i){
        for(int j = 0; j < V; ++j){
            scanf("%d", &graph[i][j]);
        }
    }

    int m;
    printf("enter number of colors: ");
    scanf("%d", &m);

    /*
    int V = 4;
    int graph[MAX][MAX] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    int m = 3;
    */

    graphColoring(graph, m, V);
    return 0;
}
