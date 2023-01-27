#include "../inc/uls.h"

int check_dir() {
	if (errno != 0) {
		if (errno == ENOTDIR) { 
			return 0;
		}
		else {
			return -1;
		}
	}
	errno = 0;
	return 1;
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
	struct dirent *d;
	DIR *dh = opendir(dir);
	if (!dh)
	{
		if (errno == ENOENT)
		{
			perror("Directory doesn't exist");
		}
		else
		{
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE);
	}
	t_list *list = NULL;
	while ((d = readdir(dh)) != NULL)
	{
		if (!op_a && d->d_name[0] == '.')
			continue;
		mx_push_front(&list, d->d_name);
	}
	sort_alpha(list);
	mx_print_list(list);
	if(!op_l)
		mx_printchar('\n');
	closedir(dh);
}

void sort_alpha(t_list *lst)
{
	if (lst) {
        for (t_list *temp1 = lst; temp1; temp1 = temp1->next){
			for (t_list *temp2 = lst; temp2->next; temp2 = temp2->next) {
				if (mx_strcasecmp(temp2->data, temp2->next->data) > 0) {
					void *temp = temp2->data;
					temp2->data = temp2->next->data;
					temp2->next->data = temp;
				} 
			}
		}
    }
}
