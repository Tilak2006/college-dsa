#include <stdio.h>

#define SIZE 10
int hashTable[SIZE];

int hash(int key) {
    return key % SIZE;
}

void initialize() {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = -1;
    }
}

void insert(int key) {
    int initial_indx = hash(key);

    for (int i = 0; i < SIZE; ++i) {
        int idx = (initial_indx + i) % SIZE;

        if (hashTable[idx] == -1) {
            hashTable[idx] = key;
            return;
        }
    }

    printf("No space available for key %d\n", key);
}

void display() {
    printf("\n--- Hash Table Contents ---\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Slot %2d -> %d\n", i, hashTable[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("enter the number of keys to insert (max %d): ", SIZE);
    scanf("%d", &n);

    if (n <= 0 || n > SIZE) {
        printf("invalid number of keys. setting n to %d.\n", SIZE);
        n = SIZE;
    }

    int keys[SIZE];

    printf("\nenter %d keys:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("key %d: ", i + 1);
        scanf("%d", &keys[i]);
    }

    initialize();

    for (int i = 0; i < n; ++i) {
        insert(keys[i]);
    }

    display();

    return 0;
}
