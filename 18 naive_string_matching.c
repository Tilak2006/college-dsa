#include <stdio.h>
#include <string.h>

void naiveStringMatch(const char* text, const char* pattern){
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;

    for(i = 0; i <= n - m; ++i){
        for(j = 0; j < m; ++j)
            if(text[i + j] != pattern[j])
                break;

        if(j == m)
            printf("pattern found at index %d\n", i);
    }
}

int main(){
    const char text[] = "aaababe";
    const char pattern[] = "abab";
    naiveStringMatch(text, pattern);
    return 0;
}
