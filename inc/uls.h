#ifndef ULS_H
#define ULS_H

#include "libmx.h"

#include <dirent.h>
#include <errno.h>
#include <string.h>
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

void sort_alpha(t_list *lst);

typedef struct s_dir {
    void *data;
    struct s_list *list;
}              t_dir;


#endif
