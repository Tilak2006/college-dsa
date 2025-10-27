#include <stdio.h>

int a[100], b[100];

void merge(int lo, int m, int hi);

void mergesort(int lo, int hi) {
    if (lo < hi) {
        int m = (lo + hi) / 2;
        mergesort(lo, m);
        mergesort(m + 1, hi);
        merge(lo, m, hi);
    }
}

void merge(int lo, int m, int hi) {
    int i, j, k;
    for (i = lo; i <= hi; i++) {
        b[i] = a[i]; 
    }
    i = lo;        
    j = m + 1;     
    k = lo;        

    while (i <= m && j <= hi) { 
        if (b[i] <= b[j]) a[k++] = b[i++]; 
        else a[k++] = b[j++]; 
    }

    while (i <= m) { 
        a[k++] = b[i++]; 
    }
    while (j <= hi) { 
        a[k++] = b[j++]; 
    }
}


int main() {
    int n, i;

    printf("enter size of the array: ");
    scanf("%d", &n);
    
    printf("enter %d elements:\n", n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]); 
    }

    mergesort(0, n - 1); 

    printf("sorted array: ");
    for (i = 0; i < n; ++i) { 
        printf("%d ", a[i]); 
    }
    printf("\n");

    // Complexity Output
    printf("merge sort tc: o(nlogn) all cases\n");
    printf("merge sort sc: o(n) auxiliary space\n");

    return 0; 
}