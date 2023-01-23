#include "../inc/uls.h"

void check_no_dir(char **argv) {
	int dir_index = 1;
	for (; argv[dir_index] != NULL; dir_index++) {	
		char* dir = argv[dir_index];
		DIR *dh = opendir(dir);
		//FILE *f = acl_get_file();
		if (!dh) {
			mx_printerr(argv[0]);
			mx_printerr(": ");
			mx_printerr(argv[dir_index]);
			mx_printerr(": No such file or directory\n");
			exit(-1);
		}
	}
}

void check_dir(char **argv) {
	int dir_index = 1;
	for (; argv[dir_index] != NULL; dir_index++) {	
		char* dir = argv[dir_index];
		DIR *dh = opendir(dir);
		
		struct dirent *entry;
		while (entry = readdir(dh))
		{
			mx_printstr(entry->d_name);
			mx_printstr(" ");
		}
		
	}
}

/*void add_cat(char **argv) {
		mx_printstr(argv[1]);
	if (argv[1] != NULL && mx_strcmp(argv[1], "| cat -e")) {

		//mx_printstr("fhsd");
		int dir_index = 1;
		for (; argv[dir_index] != NULL; dir_index++) {	
			char* dir = argv[dir_index];
			mx_printstr(dir);
			mx_printstr("\n");
		}
	}

}*/

void uls(const char *dir,int op_a,int op_l)
{
	//Here we will list the directory
	struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh)
	{
		if (errno == ENOENT)
		{
			//If the directory is not found
			perror("Directory doesn't exist");
		}
		else
		{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
	//While the next entry is not readable we will print directory files
	while ((d = readdir(dh)) != NULL)
	{
		//If hidden files are found we continue
		if (!op_a && d->d_name[0] == '.')
			continue;
		printf("%s  ", d->d_name);
		if(op_l) printf("\n");
	}
	if(!op_l)
	printf("\n");
}
