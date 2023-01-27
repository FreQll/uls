#include "../inc/uls.h"

int main(int argc, char **argv) {
    if (argc == 1) {
		uls(".", 0, 0);
		return 0;
	}

	t_list *incorrect_values = NULL;
	t_list *list_files = NULL;
	t_dir list_dir[argc - 1];

	for (int i = 0; i < argc - 1; i++)
	{
		list_dir[i].list = NULL;
	}
	
	
	int temp = 0;

	for (int i = 1; argv[i] != NULL; i++) {	
		
		char *name = argv[i];
		errno = 0;
		DIR *dir = opendir(name);
		int check = check_dir(name);
		if (check == -1) {
			mx_push_back(&incorrect_values, name);
		}
		else if (check == 0) {
			mx_push_back(&list_files, name);
		}
		else {
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
		}
	}
	
	//////вывод
	mx_print_incorrect(incorrect_values);
	mx_printstr("\n");
	mx_print_list(list_files);
	mx_printstr("\n");

	for (int i = 0; i < argc - 1; i++) {
		if (list_dir[i].list != NULL) {
			if (i != 0) mx_printstr("\n");
			mx_printstr(list_dir[i].data);
			mx_printstr(":\n");
			mx_print_list(list_dir[i].list);
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
