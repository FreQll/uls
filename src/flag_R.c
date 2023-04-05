#include "../inc/uls.h"

void uls_flag_R(const char *dir, int op_a, int op_R) {
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
	sort_list_by_alphabet(list);

	if (op_R) {
		flag_R(".", list);
		closedir(dh);
		mx_clear_list(&list, false);
		exit(0);
	}

	mx_print_list(list);
	mx_clear_list(&list, false);
	if(!op_R)
		mx_printchar('\n');
	closedir(dh);
}

void flag_R(char *dir_name, t_list *list) {

    mx_print_list(list);
    mx_printstr("\n");

    for (t_list *i = list; i; i = i->next) {
        if (mx_count_substr(i->data, ".a") > 0) continue;
        struct stat filestat;
        stat(i->data, &filestat);
        if (S_ISDIR(filestat.st_mode)) {
            traverse_directory(dir_name, i->data);
        }
    } 

}

