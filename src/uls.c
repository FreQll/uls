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
	sort_list_by_alphabet(list);
	if (op_l) {
		flag_l(list, NULL);
		exit(0);
	}

	mx_print_list(list);
	if(!op_l)
		mx_printchar('\n');
	closedir(dh);
}

void flag_l(t_list *list, char *dir) {
	if (list) {
		t_list *temp = list;

		if (dir) {
			t_list *temp_blocks = list;

			while (temp_blocks) {
				if (temp_blocks->next == NULL) {
					break;
				}
				temp_blocks = temp_blocks->next;
			}

			mx_printstr("total ");
			print_blocks(temp_blocks->data);
		}

		t_list *size = list;
		int max = 0;
		while (size) {
			if (get_file_size(size->data) > max) {
				max = get_file_size(size->data);
			}
			size = size->next;
		}

		mx_clear_list(&size, false);
		int count = get_num_digits(max); 

		char *temp_path;

		while (temp) {
			if (dir) temp_path = mx_strcat_directory(dir, temp->data);
			else temp_path = temp->data;

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

// void flag_l_dir(t_list *list, char *dir) {
// 	if (list) {
// 		t_list *temp = list;

// 		t_list *temp_blocks = list;

// 		while (temp_blocks) {
// 			if (temp_blocks->next == NULL) {
// 				break;
// 			}
// 			temp_blocks = temp_blocks->next;
// 		}

// 		t_list *size = list;
// 		int max = 0;
// 		while (size) {
// 			char *temp_path = mx_strcat_directory(dir, size->data);
// 			if (get_file_size(temp_path) > max) {
// 				max = get_file_size(temp_path);
// 			}
// 			size = size->next;
// 		}
// 		mx_clear_list(&size, false);
// 		int count = get_num_digits(max); 

// 		mx_printstr("total ");
// 		print_blocks(temp_blocks->data);

// 		while (temp) {
// 			char *temp_path = mx_strcat_directory(dir, temp->data);

// 			print_permission(temp_path);
// 			mx_printstr(" ");
// 			print_linked_links(temp_path);
// 			mx_printstr(" ");
// 			print_owners(temp_path);
// 			mx_printstr(" ");
// 			print_file_size(temp_path, count);
// 			mx_printstr(" ");
// 			print_file_time(temp_path);
// 			mx_printstr(" ");
// 			mx_printstr(temp->data);
// 			mx_printchar('\n');
//         	temp = temp->next;
// 		}
// 	}
// }
