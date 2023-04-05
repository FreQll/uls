#include "../inc/uls.h"

int main(int argc, char **argv) {
    
	if (argc == 1) {
		uls(".", 0, 0);
		return 0;
	}

	bool isDir = true;
	int flagL = 0;
	int flagR = 0;
	int checkInvalid = 0;

	for (int i = 1; i < argc; i++) {
		if (argv[1][0] == '-') isDir = false;

		if (isDir && i > 1 && argv[i][0] == '-') break;

		if (argv[i][0] == '-') {
			if (argv[i][1] == 'l' && argc == 2) {
				uls(".", 0, 1);
				return 0;
			}
			else if (argv[i][1] == 'R' && argc == 2) {
				uls_flag_R(".", 0, 1);
				return 0;
			}
			else if (argv[i][1] == 'l') flagL = i;
			else if (argv[i][1] == 'R') flagR = i;
			else if (argv[i][1] != 'l' && argv[i][1] != 'R') {
				mx_printerr("uls: illegal option -- ");
				mx_printerr(&argv[i][1]);
				mx_printerr("\nusage: uls [-l] [file ...]\n");
				return 1;
			}
		} 
	}

	t_list *incorrect_values = NULL;
	t_list *list_files = NULL;
	t_dir list_dir[argc - 1];
	int temp = 0;
	int incorrect_count = 0;
	int file_count = 0;
	int dir_count = 0;

	for (int i = 0; i < argc - 1; i++) {
		list_dir[i].list = NULL;
	}

	for (int i = 1; argv[i] != NULL; i++) {	
		char *name = argv[i];
		errno = 0;
		DIR *dir = opendir(argv[i]);
		int check = check_dir();
		if (check == -1) {
			if (i != flagL && i != flagR) {
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
		checkInvalid = 1;
		mx_print_incorrect(incorrect_values);
	}

	if (file_count > 0 && flagL == 0 && flagR == 0) {
		sort_list_by_alphabet(list_files);
		mx_print_list(list_files);
		if (dir_count > 0) mx_printstr("\n\n");
		else mx_printchar('\n');
	}

	sort_directories(dir_count, list_dir);
	//for l flag
	if (flagR == 0) {
		if (flagL == 0) {
			for (int i = 0; i < dir_count; i++) {
				//mx_printint(dir_count);
				if (i != 0 && dir_count != 1) mx_printstr("\n");
				if (argc > 2) {
					mx_printstr(list_dir[i].data);
					mx_printstr(":");
				}
				sort_list_by_alphabet(list_dir[i].list);
				
				//mx_print_list(list_dir[i].list);
				//if (list_dir[i].list != NULL) mx_printchar('\n');

				if (list_dir[i].list != NULL) {
					if (dir_count != 1) mx_printstr("\n");
					mx_print_list(list_dir[i].list);
				}
				//else mx_printstr("\t# empty directory");
				mx_printchar('\n');
			}
		}
		else if (flagL != 0){
			if (list_files) flag_l(list_files, NULL, FOR_FILES);
			if (file_count > 0 && dir_count > 0) mx_printchar('\n');
			for (int i = 0; i < dir_count; i++) {
				if (argc > 3){
					mx_printstr(list_dir[i].data);
					mx_printstr(":\n");
				}
				sort_list_by_alphabet(list_dir[i].list);
				flag_l(list_dir[i].list, list_dir[i].data, FOR_SPEC_DIRECTORIES);
				if (i + 1 != dir_count) mx_printchar('\n');
			}
		}
	}

	if (flagR != 0) {
		mx_print_list(list_files);
		if (file_count > 0 && dir_count > 0) mx_printstr("\n\n");
		for (int i = 0; i < dir_count; i++) {
			sort_list_by_alphabet(list_dir[i].list);
				if (argc > 3){
					mx_printstr(list_dir[i].data);
					mx_printstr(":\n");
				}
			
			flag_R(list_dir[i].data, list_dir[i].list);
			if (i + 1 != dir_count) mx_printchar('\n');
		}
	}
	

	//////очистка
	mx_clear_list(&incorrect_values, false);
	mx_clear_list(&list_files, false);
	for (int i = 0; i < argc - 1; i++)
		mx_clear_list(&list_dir[i].list, true);
	
	if (checkInvalid == 1) return 1;

	return 0;
}
