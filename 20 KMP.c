#include <stdio.h>
#include <string.h>

void calculateLps(const char* pattern, int* lps, int m){
    int len = 0, i = 1;
    lps[0] = 0;
    while(i < m){
        if(pattern[i] == pattern[len]){
            ++len;
            lps[i] = len;
            ++i;
        } else{
            if(len != 0)
                len = lps[len - 1];
            else{
                lps[i] = 0;
                ++i;
            }
        }
    }
}

void KMP(const char* pattern, const char* text){
    int m = strlen(pattern);
    int n = strlen(text);
    int i = 0, j = 0;
    int lps[m];

    calculateLps(pattern, lps, m);

    while(i < n){
        if(pattern[j] == text[i]){
            ++i;
            ++j;
        }
        if(j == m){
            printf("pattern found at index %d\n", i - j);
            j = lps[j - 1];
        } else if(i < n && pattern[j] != text[i]){
            if(j != 0)
                j = lps[j - 1];
            else
                ++i;
        }
    }
}

int main(){
    const char text[] = "aaababe";
    const char pattern[] = "abab";
    KMP(pattern, text);

    return 0;
}
