#include "../inc/uls.h"

int check_dir(char *name, char* uls, DIR* dir) {
	//FILE *f = acl_get_file();

	if (errno != 0) {
		if (errno == ENOTDIR) { 
			errno = 0;
			return 0;
		}
		else {
			mx_printerr(uls);
			mx_printerr(": ");
			mx_printerr(name);
			mx_printerr(": No such file or directory\n");
			closedir(dir);
			errno = 0;
			return -1;
		}
	}
	return 1;
}

void uls(const char *dir,int op_a,int op_l)
{
	int count = 0;
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
		//mx_printstr(d->d_name);
		count++;
		//mx_printstr("\t");
		//if(op_l) mx_printstr("\n");
	}
	char **array = malloc(sizeof(char*));
	for (int i = 0; i < count; i++) {
		array[i] = mx_strnew(sizeof(char*));
	}
	DIR *dtemp = opendir(dir);
	int temp = 0;
	while ((d = readdir(dtemp)) != NULL)
	{
		//If hidden files are found we continue
		if (!op_a && d->d_name[0] == '.')
			continue;
		array[temp] = d->d_name;
		temp++;
	}
	mx_bubble_sort(array, count);
	for (int i = 0; i < count; i++) {
		mx_printstr(array[i]);
		mx_printstr("  ");
	}

	mx_printint(count);

	if(!op_l)
	mx_printstr("\n");
}
