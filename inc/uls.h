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
int check_dir(char *name, char* uls, DIR* dir);

bool compare_names(void *a, void *b);

#endif
