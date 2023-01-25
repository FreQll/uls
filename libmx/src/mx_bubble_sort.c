#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int swap = 0;
    char *temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if(mx_low_strcmp(arr[j], arr[j + 1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swap++;
            }
        }
    }
    return swap;
}

int mx_low_strcmp(const char *s1, const char *s2) { 
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (mx_tolower(s1[i]) != mx_tolower(s2[i])) {
            return mx_tolower(s1[i]) - mx_tolower(s2[i]);
        }
        i++;
    }
    return mx_tolower(s1[i]) - mx_tolower(s2[i]);
}

int mx_tolower(int c){
    if (c > 64
        && c < 91){
        return c + 32;
    }else{
        return c;
    }
}
