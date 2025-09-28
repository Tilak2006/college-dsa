#include <stdio.h>
#define MAX_ITEMS 100 

int main(){
    int n, W;
    
    printf("enter the number of items (max %d): ", MAX_ITEMS);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_ITEMS) {
        printf("invalid item count. exiting.\n");
        return 1;
    }

    int w[MAX_ITEMS], v[MAX_ITEMS], index[MAX_ITEMS];
    float b[MAX_ITEMS];
    float x[MAX_ITEMS]; 
    float result[MAX_ITEMS]; 

    printf("enter the weight of knapsack: ");
    scanf("%d", &W);

    printf("enter the weight & value of each item respectively:\n");
    for (int i = 0; i < n; i++) {
        printf("item %d - ", i + 1);
        scanf("%d %d", &w[i], &v[i]);
        index[i] = i; 
    }

    for (int i = 0; i < n; i++) {
        b[i] = (float)v[i] / w[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int max_index = i;
        
        for (int j = i + 1; j < n; j++) {
            if (b[j] > b[max_index]) {
                max_index = j;
            }
        }
        
        if (max_index != i) {
            float temp_b = b[i];
            b[i] = b[max_index];
            b[max_index] = temp_b;

            int temp_w = w[i];
            w[i] = w[max_index];
            w[max_index] = temp_w;

            int temp_v = v[i];
            v[i] = v[max_index];
            v[max_index] = temp_v;

            int temp_idx = index[i];
            index[i] = index[max_index];
            index[max_index] = temp_idx;
        }
    }

    printf("\nitems sorted by benefit ratio (value/weight):\n");
    printf("weight\tvalue\tbenefit\n");
    
    float profit = 0.0;
    int weight = 0;
    
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%.2f\n", w[i], v[i], b[i]);
        x[i] = 0.0; 
    }

    int i = 0;
    while (i < n && weight < W) {
        if (weight + w[i] <= W) {
            //whole item
            x[i] = 1.0;
            weight += w[i];
        } else {
            //fraction
            x[i] = (float)(W - weight) / w[i];
            weight = W; 
        }
        
        profit += x[i] * v[i];
        i++;
    }

    for (int j = 0; j < n; j++)
        result[index[j]] = x[j]; 
    
    printf("\nfraction of each item taken:\n");
    for (int j = 0; j < n; j++) {
        printf("item %d: %.2f\n", j + 1, result[j]);
    }

    printf("\ntotal profit = %.2f\n", profit);
    
    return 0;
}