#include <stdio.h>

#define max 10
#define inf 9999

int n, cost[max][max], visited[max], minCost = inf;

void tsp(int curr, int count, int sum, int start){
    if(count == n && cost[curr][start]){
        int total = sum + cost[curr][start];
        if(total < minCost) minCost = total;
        return;
    }
    for(int i = 0; i < n; ++i){
        if(!visited[i] && cost[curr][i]){
            visited[i] = 1;
            tsp(i, count + 1, sum + cost[curr][i], start);
            visited[i] = 0;
        }
    }
}

int main(){
    printf("enter number of cities: ");
    scanf("%d", &n);

    printf("enter cost matrix:\n");
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", &cost[i][j]);

    for(int i = 0; i < n; ++i)
        visited[i] = 0;

    visited[0] = 1;
    tsp(0, 1, 0, 0);

    printf("minimum cost: %d\n", minCost);
    return 0;
}
