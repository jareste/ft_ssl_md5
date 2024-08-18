#ifndef FT_LIST_H
#define FT_LIST_H

typedef struct t_node
{
    char *data;
    char *procedence;
} node_t;

typedef struct t_list
{
    struct t_node node;
    struct t_list *next;
} list_t;

list_t* list_get_next(list_t *node);
void list_add_last(list_t **head, char *data, char *procedence);
void list_remove_single(list_t **head, list_t *node_to_remove);
void list_clear(list_t **head);
void list_print(list_t *head);

#endif