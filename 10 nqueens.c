#include <stdio.h>
#include <stdlib.h>

#define max_size 10

void printBoard(int n, int board[max_size][max_size]) {
    printf("\nsolution:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}

int isSafe(int n, int board[max_size][max_size], int row, int col) {
    int i, j;

    for (i = 0; i < col; i++) {
        if (board[row][i])
            return 0;
    }
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return 0;
    }
    for (i = row, j = col; j >= 0 && i < n; i++, j--) {
        if (board[i][j])
            return 0;
    }
    return 1;
}

int solveQueen(int n, int board[max_size][max_size], int col) {
    if (col >= n) {
        printBoard(n, board);
        return 1;
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (isSafe(n, board, i, col)) {
            board[i][col] = 1;

            res = solveQueen(n, board, col + 1) || res;

            board[i][col] = 0;
        }
    }
    return res;
}

int main() {
    int n;
    int board[max_size][max_size];

    printf("enter the size of the board (n, max %d): ", max_size);
    scanf("%d", &n);

    if (n <= 0 || n > max_size) {
        printf("invalid size. exiting.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }

    printf("\nsearching for solutions for n=%d...\n", n);
    
    if (solveQueen(n, board, 0) == 0) {
        printf("\nno solution exists for a %dx%d board.\n", n, n);
    }
    
    return 0;
}