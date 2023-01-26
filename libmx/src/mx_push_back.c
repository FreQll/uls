#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (!data) return;

    if (*list == NULL) {
        *list = mx_create_node(data); 
        return;
    }

    t_list* temp = *list;
    for (; temp->next != NULL; temp = temp -> next);

    temp->next = mx_create_node(data);
}

