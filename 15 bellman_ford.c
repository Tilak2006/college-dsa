#include <stdio.h>
#include <limits.h>

void bellmanFord(int V, int E, int edge[E][3], int src){
    int dist[V];
    for(int i = 0; i < V; ++i)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for(int i = 1; i <= V - 1; ++i){
        for(int j = 0; j < E; ++j){
            int u = edge[j][0];
            int v = edge[j][1];
            int w = edge[j][2];

            if(dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for(int j = 0; j < E; ++j){
        int u = edge[j][0];
        int v = edge[j][1];
        int w = edge[j][2];

        if(dist[u] != INT_MAX && dist[u] + w < dist[v]){
            printf("graph contains negative weight cycle\n");
            return;
        }
    }

    printf("vertex\tdistance from source\n");
    for(int i = 0; i < V; ++i)
        printf("%d\t%d\n", i, dist[i]);
}

int main(){
    int V, E;
    printf("enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    int edge[E][3];
    printf("enter edges (src dest weight):\n");
    for(int i = 0; i < E; ++i)
        scanf("%d %d %d", &edge[i][0], &edge[i][1], &edge[i][2]);

    int src;
    printf("enter source vertex: ");
    scanf("%d", &src);

    /*
    int V = 5, E = 8;
    int edge[8][3] = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };
    int src = 0;
    */

    bellmanFord(V, E, edge, src);
    return 0;
}
