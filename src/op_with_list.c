#include "../inc/uls.h"

void mx_print_list(t_list *list) {
    if (!list) return;

    t_list *temp = list;
    while (temp) {
        mx_printstr(temp->data);
        mx_printchar('\t');
        temp = temp->next;
    }
    mx_printchar('\n');
}

void mx_print_incorrect(t_list *list) {
    if (!list) return;

    t_list *temp = list;
    while (temp) {
        mx_printerr("uls: ");
        mx_printerr(temp->data);
        mx_printerr(": No such file or directory\n");
        temp = temp->next;
    }
}

void mx_clear_list(t_list** list, bool is_clear) {
    if (!(*list)) return;

	while (*list){
		t_list *node = (*list)->next;
		if (is_clear) free((*list)->data);
		free(*list);
		*list = node;
	}
}

