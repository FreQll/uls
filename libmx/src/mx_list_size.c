#include "../inc/libmx.h"

int mx_list_size(t_list *list) {
    t_list* node = list;
    int count = 0;

    for (; node != NULL; count++)
        node = node->next;

    return count;
}

