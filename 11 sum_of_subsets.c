#include <stdio.h>

int n, target, count = 0;
int set[20], subset[20];

void sumOfSubsets(int i, int sum){
    if(sum == target){
        printf("subset %d: ", ++count);
        for(int j = 0; j < i; ++j)
            if(subset[j]) printf("%d ", set[j]);
        printf("\n");
        return;
    }
    if(i >= n || sum > target) return;

    subset[i] = 1;
    sumOfSubsets(i + 1, sum + set[i]);
    subset[i] = 0;
    sumOfSubsets(i + 1, sum);
}

int main(){
    printf("enter number of elements: ");
    scanf("%d", &n);

    printf("enter elements: ");
    for(int i = 0; i < n; ++i)
        scanf("%d", &set[i]);

    printf("enter target sum: ");
    scanf("%d", &target);

    printf("subsets with sum %d:\n", target);
    sumOfSubsets(0, 0);
    return 0;
}
