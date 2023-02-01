#ifndef ULS_H
#define ULS_H

#include "libmx.h"

#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include <sys/types.h>
//include <sys/acl.h>

#include <stdio.h>

void check_no_dir(char **argv);
void uls(const char *dir, int op_a, int op_l);
void add_cat(char **argv);
int check_dir();
void mx_print_list(t_list *list);
void mx_clear_list(t_list** list, bool is_clear);
void mx_print_incorrect(t_list *list);

void sort_list_by_alphabet(t_list *lst);
void flag_l(t_list *list, char *dir);
//void _l_func_dir(t_list *list, char *dir);
void print_blocks(char *name);
int get_blocks(char *name);

void print_permission(char *name);
void print_linked_links(char *name);
void print_owners(char *name);
void print_file_size(char *name, int spaces);
void print_file_time(char *name);

int get_num_digits(int n);
char *mx_strcat_directory(char *dir, char *file);

int get_file_size(char *name);

char *convert_time(time_t t);

typedef struct s_dir {
    void *data;
    struct s_list *list;
}              t_dir;


#endif
