#include "../inc/uls.h"

int main(int argc, char **argv) {
    if (argc == 1) {
		uls(".", 0, 0);
		return 0;
	}

	int flag = 0;

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 'l') {
			flag = i;
		}
		if (argv[i][0] == '-' && argv[i][1] == 'l' && argc == 2) {
			uls(".", 0, 1);
			return 0;
		}
		else if (argv[i][0] == '-' && argv[i][1] != 'l') {
			mx_printerr("uls: illegal option -- ");
			mx_printerr(&argv[i][1]);
			mx_printerr("\nusage: uls [-l] [file ...]\n");
			return -1;
		}
	}

	t_list *incorrect_values = NULL;
	t_list *list_files = NULL;
	t_dir list_dir[argc - 1];

	for (int i = 0; i < argc - 1; i++)
	{
		list_dir[i].list = NULL;
	}

	int temp = 0;
	int incorrect_count = 0;
	int file_count = 0;
	int dir_count = 0;

	for (int i = 1; argv[i] != NULL; i++) {	
			
		char *name = argv[i];
		errno = 0;
		DIR *dir = opendir(argv[i]);
		int check = check_dir(argv[i]);
		if (check == -1) {
			if (i != flag) {
				mx_push_back(&incorrect_values, argv[i]);
				incorrect_count++;
			}
		}
		else if (check == 0) { //files
			mx_push_back(&list_files, name);
			file_count++;
		}
		else { //for dirs
			struct dirent *entry;
			list_dir[temp].data = name;

			while ((entry = readdir(dir)) != NULL) {
				if (entry->d_name[0] == '.')
					continue;

				char *t = mx_strdup(entry->d_name);
				mx_push_back(&list_dir[temp].list, t);
			}

			closedir(dir);
			temp++;
			dir_count++;
		}
	}

	if (incorrect_count > 0) {
		mx_print_incorrect(incorrect_values);
	}

	if (flag != 0) {
		flag_l(list_files, NULL);
	}

	if (file_count > 0 && flag == 0) {
		sort_list_by_alphabet(list_files);
		mx_print_list(list_files);
		mx_printstr("\n\n");
	}

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

	//for l flag
	if (flag == 0) {
		for (int i = 0; i < dir_count; i++) {
			if (i != 0) mx_printstr("\n");
			mx_printstr(list_dir[i].data);
			mx_printstr(":\n");
			sort_list_by_alphabet(list_dir[i].list);
			mx_print_list(list_dir[i].list);
			if (list_dir[i].list != NULL) mx_printchar('\n');
		}
	}
	else {
		if (file_count > 0) mx_printchar('\n');
		for (int i = 0; i < dir_count; i++) {
			mx_printstr(list_dir[i].data);
			mx_printstr(":\n");
			sort_list_by_alphabet(list_dir[i].list);
			flag_l(list_dir[i].list, list_dir[i].data);
			if (i + 1 != dir_count) mx_printchar('\n');
		}
	}

	//////очистка
	mx_clear_list(&incorrect_values, false);
	mx_clear_list(&list_files, false);
	for (int i = 0; i < argc - 1; i++)
		mx_clear_list(&list_dir[i].list, true);
	
	return 0;
}
