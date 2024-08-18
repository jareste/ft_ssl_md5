#ifndef FT_LIST_H
#define FT_LIST_H

typedef struct t_list
{
    char *data;
    struct t_list *next;
} list_t;

list_t* list_get_next(list_t *node);
void list_add_last(list_t **head, char *data);
void list_remove_single(list_t **head, list_t *node_to_remove);
void list_clear(list_t **head);
void list_print(list_t *head);

#endif