#include <stdio.h>
#include <limits.h>

#define INF 99999
#define MAX 100

void floydWarshall(int n, int graph[MAX][MAX]){
    int dist[MAX][MAX];

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            dist[i][j] = graph[i][j];

    for(int k = 0; k < n; ++k){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    printf("shortest distances between every pair of vertices:\n");
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(dist[i][j] == INF)
                printf("inf ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int n;
    printf("enter number of vertices: ");
    scanf("%d", &n);

    int graph[MAX][MAX];
    printf("enter adjacency matrix (use %d for inf):\n", INF);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &graph[i][j]);

    /*
    int n = 4;
    int graph[4][4] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };
    */

    floydWarshall(n, graph);
    return 0;
}
