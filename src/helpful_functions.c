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

void sort_directories(int dir_count, t_dir *list_dir) {
    t_dir dir_temp;
	for (int i = 0; i < dir_count; i++) {
		for (int j = 0; j < dir_count - 1; j++) {
			if (mx_strcasecmp(list_dir[j].data, list_dir[j + 1].data) == 0 
				&& mx_strcmp(list_dir[j].data, list_dir[j + 1].data) < 0) {
					dir_temp.data = list_dir[j].data;
					dir_temp.list = list_dir[j].list;
					list_dir[j] = list_dir[j + 1];
					list_dir[j + 1] = dir_temp;
					continue;
			}
            if(mx_strcasecmp(list_dir[j].data, list_dir[j + 1].data) > 0) {
                dir_temp.data = list_dir[j].data;
				dir_temp.list = list_dir[j].list;
                list_dir[j] = list_dir[j + 1];
                list_dir[j + 1] = dir_temp;
            }
        }
	}
}
