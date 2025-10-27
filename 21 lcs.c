#include <stdio.h>
#include <string.h>
#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs(char X[], char Y[], int m, int n) {
    int dp[MAX][MAX];
    
    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

int main() {
    char X[MAX], Y[MAX];
    
    printf("enter first string\n");
    scanf("%s", X);
    
    printf("enter second string\n");
    scanf("%s", Y);
    
    int m = strlen(X);
    int n = strlen(Y);
    
    int length = lcs(X, Y, m, n);
    
    printf("length of lcs is %d\n", length);
    
    return 0;
}