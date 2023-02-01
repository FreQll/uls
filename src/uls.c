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
	///////////////
	if (op_l) {
		_l_func(list);
		exit(0);
	}

	mx_print_list(list);
	if(!op_l)
		mx_printchar('\n');
	closedir(dh);
}

void _l_func(t_list *list) {
	if (list) {
		t_list *temp = list;

		t_list *size = list;
		int max = 0;
		while (size) {
			if (get_file_size(size->data) > max) {
				max = get_file_size(size->data);
			}
			size = size->next;
		}

		//mx_printint(max);
		mx_clear_list(&size, false);
		int count = get_num_digits(max); 

		while (temp) {
			print_permission(temp->data);
			mx_printstr(" ");
			print_linked_links(temp->data);
			mx_printstr(" ");
			print_owners(temp->data);
			mx_printstr(" ");
			print_file_size(temp->data, count);
			mx_printstr(" ");
			print_file_time(temp->data);
			mx_printstr(" ");
			mx_printstr(temp->data);
			mx_printchar('\n');
        	temp = temp->next;
		}
	}
}

void _l_func_dir(t_list *list, char *dir) {
	if (list) {
		t_list *temp = list;

		t_list *temp_blocks = list;

		while (temp_blocks) {
			if (temp_blocks->next == NULL) {
				break;
			}
			temp_blocks = temp_blocks->next;
		}

		t_list *size = list;
		int max = 0;
		while (size) {
			char *temp_path = mx_strcat_directory(dir, size->data);
			if (get_file_size(temp_path) > max) {
				max = get_file_size(temp_path);
			}
			size = size->next;
		}
		mx_clear_list(&size, false);
		int count = get_num_digits(max); 

		mx_printstr("total ");
		print_blocks(temp_blocks->data);

		while (temp) {
			char *temp_path = mx_strcat_directory(dir, temp->data);

			print_permission(temp_path);
			mx_printstr(" ");
			print_linked_links(temp_path);
			mx_printstr(" ");
			print_owners(temp_path);
			mx_printstr(" ");
			print_file_size(temp_path, count);
			mx_printstr(" ");
			print_file_time(temp_path);
			mx_printstr(" ");
			mx_printstr(temp->data);
			mx_printchar('\n');
        	temp = temp->next;
		}
	}
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
