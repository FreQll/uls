#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *a, void *b)) {
	if (lst == NULL || cmp == NULL)
        return lst;

    t_list* node = lst;
    while (node) {
        t_list* temp_node = lst;
        while (temp_node->next) {
			mx_printstr(temp_node->data);
            if (cmp(temp_node->data, temp_node->next->data)) {
                void* temp = temp_node->data;
                temp_node->data = temp_node->next->data;
                temp_node->next->data = temp;
            }
            temp_node = temp_node->next;
        }
        node = node->next;
    }
    return lst;
}
