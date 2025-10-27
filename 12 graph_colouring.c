#include <stdio.h>

#define MAX 10

int graph[MAX][MAX], color[MAX], n;

int isSafe(int v, int c){
    for(int i = 0; i < n; ++i)
        if(graph[v][i] && color[i] == c)
            return 0;
    return 1;
}

int colorGraph(int v, int m){
    if(v == n)
        return 1;
    for(int c = 1; c <= m; ++c){
        if(isSafe(v, c)){
            color[v] = c;
            if(colorGraph(v + 1, m))
                return 1;
            color[v] = 0;
        }
    }
    return 0;
}

int main(){
    int m;
    printf("enter number of vertices: ");
    scanf("%d", &n);

    printf("enter adjacency matrix:\n");
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &graph[i][j]);

    printf("enter number of colors: ");
    scanf("%d", &m);

    for(int i = 0; i < n; ++i)
        color[i] = 0;

    if(colorGraph(0, m)){
        printf("solution exists, colors are:\n");
        for(int i = 0; i < n; ++i)
            printf("%d ", color[i]);
        printf("\n");
    } else
        printf("no solution exists\n");

    return 0;
}
