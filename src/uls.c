#include "../inc/uls.h"

int check_dir(void) {
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

void uls(const char *dir, int op_a, int op_l)
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
		flag_l(list, NULL, FOR_ALL_DIRECTORIES);
		closedir(dh);
		mx_clear_list(&list, false);
		exit(0);
	}
	mx_print_list(list);
	mx_clear_list(&list, false);
	if(!op_l)
		mx_printchar('\n');
	closedir(dh);
}

void flag_l(t_list *list, char *dir, enum checkArgs chTotal) {
	if (list) {
		t_list *temp = list;

		if (chTotal == FOR_SPEC_DIRECTORIES) {
			t_list *files_from_dir = NULL;
			DIR *Dir = opendir(dir);
			if (Dir) {
				files_from_dir = get_files_from_dir(dir);
			}
			print_total(files_from_dir);
			mx_clear_list(&files_from_dir, true);
			closedir(Dir);

		}
		else if (chTotal == FOR_ALL_DIRECTORIES) print_total(temp);

		char *temp_path;
		
		temp = list;
		int spaces1 = get_spaces_count_1(temp, dir);
		int spaces2 = get_spaces_count_2(temp, dir);

		while (temp) {
			if (dir) temp_path = mx_strcat_directory(dir, temp->data);
			else temp_path = temp->data;


			print_permission(temp_path);
			mx_printstr("  ");
			print_linked_links(temp_path, spaces1);
			mx_printstr(" ");
			print_owners(temp_path);
			mx_printstr("  ");
			print_file_size(temp_path, spaces2);
			mx_printstr(" ");
			print_file_time(temp_path);
			mx_printstr(" ");
			mx_printstr(temp->data);
			mx_printchar('\n');
        	temp = temp->next;

			if (dir) mx_strdel(&temp_path);
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
