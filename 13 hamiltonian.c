#include <stdio.h>

#define v 10

int n, graph[v][v], path[v];

int isSafe(int pos, int vertex){
    if(!graph[path[pos - 1]][vertex]) return 0;
    for(int i = 0; i < pos; ++i)
        if(path[i] == vertex)
            return 0;
    return 1;
}

int hamiltonianUtil(int pos){
    if(pos == n){
        if(graph[path[pos - 1]][path[0]])
            return 1;
        return 0;
    }
    for(int vertex = 1; vertex < n; ++vertex){
        if(isSafe(pos, vertex)){
            path[pos] = vertex;
            if(hamiltonianUtil(pos + 1))
                return 1;
            path[pos] = -1;
        }
    }
    return 0;
}

void hamiltonianCycle(){
    for(int i = 0; i < n; ++i)
        path[i] = -1;
    path[0] = 0;
    if(hamiltonianUtil(1)){
        printf("hamiltonian cycle found: ");
        for(int i = 0; i < n; ++i)
            printf("%d ", path[i]);
        printf("%d\n", path[0]);
    } else
        printf("no hamiltonian cycle exists\n");
}

int main(){
    printf("enter number of vertices: ");
    scanf("%d", &n);

    printf("enter adjacency matrix:\n");
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &graph[i][j]);

    hamiltonianCycle();
    return 0;
}
