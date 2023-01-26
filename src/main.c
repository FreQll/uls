#include "../inc/uls.h"

int main(int argc, char **argv) {
    if (argc == 1) {
		uls(".", 0, 0);
	}

	t_list *incorrect_values = NULL;

	t_list *files = NULL;
	//t_list *dir_names = NULL;
	//t_list *file_names = NULL;
	//t_list **directories = NULL;

	for (int i = 1; argv[i] != NULL; i++) {	
		
		errno = 0;
		DIR *dir = opendir(argv[i]);
		int check = check_dir(argv[i]);
		if (check == -1) {
			mx_push_back(&incorrect_values, argv[i]);
		}
		else if (check == 0) { //files
			mx_push_front(&files, argv[i]);
			//mx_printstr(argv[i]);
			//mx_printstr("\n");
		}
		else { //for dirs
			struct dirent *entry;
			//
			if (i != 1) mx_printstr("\n");

			//mx_push_front(&dir_names, argv[i]);

			mx_printstr(argv[i]);
			mx_printstr(":\n");
			while ((entry = readdir(dir)) != NULL)
			{
				if (entry->d_name[0] == '.')
					continue;
				//mx_push_front(&file_names, entry->d_name);
				mx_printstr(entry->d_name);
				mx_printstr("  ");
			}
			mx_printstr("\n");
		}
		closedir(dir);
	}

	sort_alpha(files);
	mx_print_list(files);
	
	mx_printstr("\n");
	mx_print_incorrect(incorrect_values);

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
