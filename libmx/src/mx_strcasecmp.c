#include "../inc/libmx.h"

int mx_strcasecmp(const char *s1, const char *s2) { 
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
