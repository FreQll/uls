#include "../inc/uls.h"

int main(int argc, char **argv) {
    if (argc == 1) {
		uls(".", 0, 0);
	}
	for (int i = 1; argv[i] != NULL; i++) {	
		
		DIR *dir = opendir(argv[i]);
		int check = check_dir(argv[i], argv[0], dir);
		if (check == -1) continue;
		if (check == 0) {
			mx_printstr(argv[i]);
			mx_printstr("\n");
		}
		else {
			struct dirent *entry;

			mx_printstr("\n");
			mx_printstr(argv[i]);
			mx_printstr(":\n");
			while ((entry = readdir(dir)) != NULL)
			{
				mx_printstr(entry->d_name);
				mx_printstr(" ");
			}
			mx_printstr("\n");
		}
			errno = 0;
		closedir(dir);
	}

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
