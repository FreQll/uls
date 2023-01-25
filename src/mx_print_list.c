#include "../inc/libmx.h"

void mx_print_list(t_list *list) {
    if (!list) return;

    t_list *temp = list;
    while (temp) {
        mx_printstr(temp->data);
        mx_printchar('\n');
        temp = temp->next;
    }
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

