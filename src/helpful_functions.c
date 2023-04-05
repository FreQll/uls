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

int get_spaces_count_1(t_list *temp, char* dir) {

    t_list *size = temp;
    int max = 0;
    char *name;
    while (size) {
		if (dir) name = mx_strcat_directory(dir, size->data);
		else name = size->data;
        struct stat fileStat;
        stat(name, &fileStat);
        if (fileStat.st_nlink > max) {
            max = fileStat.st_nlink;
        }
        size = size->next;
        if (dir) mx_strdel(&name);
    }

    mx_clear_list(&size, false);
    return get_num_digits(max); 
}

int get_spaces_count_2(t_list *temp, char* dir) {
    t_list *size = temp;
    int max = 0;
    char *name;
    while (size) {
		if (dir) name = mx_strcat_directory(dir, size->data);
		else name = size->data;
        if (get_file_size(name) > max) {
            max = get_file_size(name);
        }
        size = size->next;
        if (dir) mx_strdel(&name);
    }

    mx_clear_list(&size, false);
    return get_num_digits(max); 
}

bool isDirectory(char *name) {
    if (mx_count_substr(name, ".a") > 0) return false;
    struct stat filestat;
    stat(name, &filestat);
    if (S_ISDIR(filestat.st_mode)) return true;
    return false;
}

void count_fold_in_dir(char *name, int *count) {
    DIR *dir = opendir(name);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' || entry->d_type != DT_DIR) continue;
        if (entry->d_type == DT_DIR) {
            *count = *count + 1;
            char *new_name = mx_strcat_directory(name, entry->d_name);
            count_fold_in_dir(new_name, count);
            mx_strdel(&new_name);
        }
    }
    closedir(dir);
}

void func1(DIR *dir, t_list **list, char *name) {

        char * tName = mx_strdup(name);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            
            if (entry->d_name[0] == '.')
                continue;
			
			if (entry->d_type == DT_DIR) {
				tName = mx_strcat(tName, "/");
				tName = mx_strcat(tName, entry->d_name);

				DIR* tDir = opendir(tName);
                char *temp_name = mx_strdup(entry->d_name);
            	mx_push_back(list, temp_name);

				func1(tDir, list, tName);
                closedir(tDir);
                mx_strdel(&tName);
                return;
			}
            if (entry->d_type != DT_DIR) {
                char *temp_name = mx_strdup(entry->d_name);
            	mx_push_back(list, temp_name);

			}
        }
        mx_strdel(&tName);

}


void print_traverse_dir(char *dir_name, char *name) {
    char * name_dir = mx_strcat_directory(dir_name, name);
    if (!isDirectory(name_dir)) {
        mx_strdel(&name_dir);
        return;
    }
    mx_printstr("\n");
    t_list *files = get_name_files_from_dir(name_dir);
    

    mx_printstr(dir_name);
    mx_printstr("/");
    mx_printstr(name);
    mx_printstr(":");
    if(files != NULL) mx_printstr("\n");
    
	sort_list_by_alphabet(files);
    mx_print_list(files);
    mx_printstr("\n");
    
	for (t_list *t_files = files; t_files; t_files = t_files->next) {
        //if (!isDirectory(t_files->data)) continue;

        t_list *list = NULL;
        char *new_name = mx_strcat_directory(name_dir, t_files->data);

        if (!isDirectory(new_name)) {
            mx_strdel(&new_name);
            continue;
        }

        DIR *dir = opendir(new_name);
        func1(dir, &list, new_name);
        sort_list_by_alphabet(list);
        closedir(dir);

        mx_printstr("\n");
        mx_printstr(new_name);
        mx_printstr(":\n");
        //mx_print_list(list);
        t_list *files_from_dir = get_name_files_from_dir(new_name);
        mx_print_list(files_from_dir);
        if (files_from_dir != NULL) mx_printstr("\n");
        mx_clear_list(&files_from_dir, false);

        for (t_list *i = list; i; i = i->next) {
            char *tName = mx_strcat_directory(new_name, i->data);
            if (isDirectory(tName)) {
                print_traverse_dir(new_name, i->data);
            }
            mx_strdel(&tName);
        }
        mx_strdel(&new_name);
        mx_clear_list(&list, true);
        
	}
    mx_clear_list(&files, false);
    mx_strdel(&name_dir);
}

void func(DIR *dir, t_list **list, char *name, int *total) {

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            char * tName = mx_strdup(name);
            if (entry->d_name[0] == '.')
                continue;
			
			if (entry->d_type == DT_DIR) {

				tName = mx_strcat(tName, "/");
				tName = mx_strcat(tName, entry->d_name);

                mx_printstr("\n");
                mx_printstr(tName);
                mx_printstr(":");
                t_list *files = get_name_files_from_dir(tName);
                if (files != NULL) mx_printstr("\n");
                mx_print_list(files);
                mx_printstr("\n");
                mx_clear_list(&files, false);

				DIR* tDir = opendir(tName);
				func(tDir, list, tName, total);
                closedir(tDir);
			}
            if (entry->d_type != DT_DIR) {
                char *temp_name = mx_strcat_directory(tName, entry->d_name);
                /*char *temp_name =  mx_strndup(tName, mx_strlen(tName) + 1 + mx_strlen(entry->d_name));
				temp_name = mx_strcat(temp_name, "/");
                temp_name = mx_strcat(temp_name, entry->d_name);*/

            	mx_push_back(list, temp_name);

                //if (stats != -1) *total += st.st_blocks;
                //mx_strdel(&temp_name);
			}
            mx_strdel(&tName);
        }

}

void traverse_directory(char *dir_name, char *name) {

    print_traverse_dir(dir_name, name);
    
}

t_list *get_files_from_dir(char *name) {
    t_list *list = NULL;
    char * tName = mx_strdup(name);
    DIR *dir = opendir(tName);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        if (entry->d_type == DT_DIR) continue;

        char *temp_name = mx_strcat_directory(tName, entry->d_name);
        /*char *temp_name = mx_strndup(tName, mx_strlen(tName) + 1 + mx_strlen(entry->d_name));
        temp_name = mx_strcat(temp_name, "/");
        temp_name = mx_strcat(temp_name, entry->d_name);*/
        mx_push_back(&list, temp_name);
			
    }

	sort_list_by_alphabet(list);
    closedir(dir);
    mx_strdel(&tName);
    
    return list;
}

t_list *get_name_files_from_dir(char *name) {
    t_list *list = NULL;
    char * tName = mx_strdup(name);
    DIR *dir = opendir(tName);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        mx_push_back(&list, entry->d_name);
			
    }

	sort_list_by_alphabet(list);
    closedir(dir);
    mx_strdel(&tName);
    
    return list;
}
