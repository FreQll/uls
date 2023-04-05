#include "../inc/libmx.h"

void mx_print_list(t_list *list) {
    if (!list) return;

    bool cat_e = false;

    if (isatty(1)) cat_e = false;
	else cat_e = true;

    t_list *temp = list;
    while (temp) {
        mx_printstr(temp->data);
        if (temp->next != NULL && !cat_e) {
            mx_printstr("  ");
        }
        else if (temp->next != NULL && cat_e) {
            mx_printchar('\n');
        }
        temp = temp->next;
    }
    //mx_printchar('\n');
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

void sort_list_by_alphabet(t_list *lst)
{
	if (lst) {
        for (t_list *temp1 = lst; temp1; temp1 = temp1->next){
			for (t_list *temp2 = lst; temp2->next; temp2 = temp2->next) {
				if (mx_strcmp(temp2->data, temp2->next->data) > 0) {
					void *temp = temp2->data;
					temp2->data = temp2->next->data;
					temp2->next->data = temp;
				} 
			}
		}
    }
}

