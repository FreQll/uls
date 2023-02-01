#include "../inc/uls.h"

char *mx_strcat_directory(char *dir, char *file) {
    char *temp_path = mx_strnew(mx_strlen(dir) + mx_strlen(file) + 1);

    mx_strcat(temp_path, dir);    
    mx_strcat(temp_path, "/");   
    mx_strcat(temp_path, file);

    return temp_path;
}

int get_num_digits(int n) {
    int count = 0;
    if (n == 0) return 1;
    while(n != 0) {  
        n = n/10;  
        count++;  
    }  
    return count;
}
