#include <stdio.h>
#define MAX_SIZE 100

void swap_elements(int arr[], int idx1, int idx2) {
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j <= high; ++j){
        if(arr[j] < pivot){
            i++;
            swap_elements(arr, i, j);
        }
    }
    swap_elements(arr, i + 1, high);
    return (i + 1);
}

void quickSort(int arr[], int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArr(int a[], int size, const char* label){
    printf("%s ", label);
    for(int i = 0; i < size; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

int main(){
    int n;
    printf("enter the size of arr: ");
    scanf("%d", &n);

    if(n < 0 || n > MAX_SIZE){
        printf("Invalid size. \n");
        return 1;
    }

    int quick_arr[MAX_SIZE];
    printf("enter the elements for quick sort: \n");
    for(int i = 0; i < n; ++i){
        printf("Element %d: ", i + 1);
        scanf("%d", &quick_arr[i]);
    }

    printf("Array before qs -> ");
    printArr(quick_arr, n, "Initial");

    quickSort(quick_arr, 0, n-1);
    printf("Sorted arr -> ");
    printArr(quick_arr, n, "Final");

    printf("Quicksort TC: avg O(nlogn), O(n^2) worst");
    printf("Quicksort SC: avg O(logn), O(n) worst");
}