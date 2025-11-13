#include <stdlib.h>
#include <dlist.h>
#include "internal.h"

/*
    Helper to allocate and initialize a node.
    Always returns a fully set-up node or NULL if malloc fails.
*/
Node *dlist_create_node(void *data, int priority) {
    Node *node = malloc(sizeof(Node));
    if (!node)
        return NULL;

    node->data = data;
    node->priority = priority;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

/*
    Creates and initializes a new list.
    Keeping everything zeroed and clean avoids undefined behavior.
*/
DList *dlist_create(bool priority_mode, int (*cmp)(void*, void*)) {
    DList *list = malloc(sizeof(DList));
    if (!list)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->priority_mode = priority_mode;
    list->cmp = cmp;

    return list;
}

/*
    Full cleanup of the list.
    Walk node by node, free data (if free_fn provided), free nodes, free list.
*/
void dlist_destroy(DList *list, void (*free_fn)(void*)) {
    Node *curr = list->head;

    while (curr) {
        Node *next = curr->next;

        if (free_fn)
            free_fn(curr->data);

        free(curr);
        curr = next;
    }

    free(list);
}

/*
    Insert at head.
    O(1) always.
*/
void dlist_push_front(DList *list, void *data) {
    Node *node = dlist_create_node(data, 0);
    if (!node)
        return;

    node->next = list->head;

    if (list->head)
        list->head->prev = node;
    else
        list->tail = node; // first node ever.

    list->head = node;
    list->size++;
}

/*
    Insert at tail.
    Also O(1).
*/
void dlist_push_back(DList *list, void *data) {
    Node *node = dlist_create_node(data, 0);
    if (!node)
        return;

    node->prev = list->tail;

    if (list->tail)
        list->tail->next = node;
    else
        list->head = node;

    list->tail = node;
    list->size++;
}

/*
    Remove from head.
    Return stored data so caller can use it.
*/
void *dlist_pop_front(DList *list) {
    if (!list->head)
        return NULL;

    Node *node = list->head;
    void *data = node->data;

    list->head = node->next;

    if (list->head)
        list->head->prev = NULL;
    else
        list->tail = NULL; // list became empty.

    free(node);
    list->size--;

    return data;
}

/*
    Remove from tail.
    Same as pop_front but mirrored.
*/
void *dlist_pop_back(DList *list) {
    if (!list->tail)
        return NULL;

    Node *node = list->tail;
    void *data = node->data;

    list->tail = node->prev;

    if (list->tail)
        list->tail->next = NULL;
    else
        list->head = NULL;

    free(node);
    list->size--;

    return data;
}

/*
    Remove specific node.
    O(1), which is the number one advantage of linked lists.
*/
void dlist_remove_node(DList *list, Node *node, void (*free_fn)(void*)) {
    if (!node)
        return;

    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;

    if (free_fn)
        free_fn(node->data);

    free(node);
    list->size--;
}

/*
    Linear search.
    Uses user-provided comparator so list works with any data type.
*/
DListNode *dlist_find(DList *list, void *target, int (*cmp_fn)(void*, void*)) {
    for (Node *curr = list->head; curr; curr = curr->next)
        if (cmp_fn(curr->data, target) == 0)
            return curr;

    return NULL;
}
