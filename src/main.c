#include "../inc/uls.h"

int main(int argc, char **argv) {
    if (argc == 1) {
		uls(".", 0, 0);
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == 'l') {
			//_l_func(argv);
		}
		else if (argv[i][0] == '-' && argv[i][1] != 'l') {
			mx_printerr("uls: illegal option -- ");
			mx_printerr(&argv[i][1]);
			mx_printerr("\nusage: uls [-l] [file ...]\n");
			exit(0);
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
			mx_push_back(&incorrect_values, argv[i]);
			incorrect_count++;
		}
		else if (check == 0) { //files
			mx_push_back(&list_files, name);
			file_count++;
		}
		else { //for dirs
			struct dirent *entry;
			list_dir[temp].data = name;
			//
			//if (i != 1) mx_printstr("\n");

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

	if (file_count > 0) {
		sort_alpha(list_files);
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
			// mx_printstr(list_dir[j].data);
			// 	mx_printstr(" -> ");
			// 	mx_printstr(list_dir[j + 1].data);
			// 	mx_printchar('\t');
			// 	mx_printint(mx_strcasecmp(list_dir[j].data, list_dir[j + 1].data));
			// 	mx_printstr("\n\n");
            if(mx_strcasecmp(list_dir[j].data, list_dir[j + 1].data) > 0) {
				//mx_printstr("\t swap\n\n");
                dir_temp.data = list_dir[j].data;
				dir_temp.list = list_dir[j].list;
                list_dir[j] = list_dir[j + 1];
                list_dir[j + 1] = dir_temp;
            }
        }
	}
	
	for (int i = 0; i < argc - 1; i++) {
		if (list_dir[i].list != NULL) {
			if (i != 0) mx_printstr("\n");
			mx_printstr(list_dir[i].data);
			mx_printstr(":\n");
			sort_alpha(list_dir[i].list);
			mx_print_list(list_dir[i].list);
			mx_printchar('\n');
		}
	}

	//////очистка
	mx_clear_list(&incorrect_values, false);
	mx_clear_list(&list_files, false);
	for (int i = 0; i < argc - 1; i++)
		mx_clear_list(&list_dir[i].list, true);

		//add_cat(argv);
		
		


		//CREATIVE
		/*
		if (argv[1][0] == '-')
		{

			//Checking if option is passed
			//Options supporting: a, l
			int op_a = 0, op_l = 0;
			char *p = (char*)(argv[1] + 1);
			while(*p){
				if(*p == 'a') op_a = 1;
				else if(*p == 'l') op_l = 1;
				else{
					perror("Option not available");
					exit(EXIT_FAILURE);
				}
				p++;
			}
			uls(".",op_a,op_l);
			
		}*/
	
	//}
	return 0;
}
