#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>
#include <stdbool.h>

/*
    Node of the doubly linked list.
    Stores:
    - user data (void* so it's generic).
    - an optional priority (used only if list is in priority mode).
    - links to the previous and next nodes.

    Basically the core building block of the whole list.
*/
typedef struct DListNode {
    void *data;
    int priority;
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;

/*
    Main list structure.
    Holds pointers to first and last node + size.
    Also stores:
    - priority_mode: if true, insertions will keep list sorted.
    - cmp: user-provided comparator (for custom orderings).
*/
typedef struct DList {
    DListNode *head;
    DListNode *tail;
    size_t size;

    bool priority_mode;
    int (*cmp)(void*, void*);
} DList;

/*
    Creates a new list.
    priority_mode:
        - false -> normal list.
        - true  -> insertions go through the priority logic.

    cmp:
        Optional comparator for custom sorting / searching.
*/
DList *dlist_create(bool priority_mode, int (*cmp)(void*, void*));

/*
    Frees the entire list.
    free_fn:
        If you stored dynamically allocated data inside the nodes,
        pass a function to free that data.
        If not, just pass NULL.
*/
void dlist_destroy(DList *list, void (*free_fn)(void*));

/*
    Basic insertions.
    push_front -> insert at the start.
    push_back  -> insert at the end.
*/
void dlist_push_front(DList *list, void *data);
void dlist_push_back(DList *list, void *data);

/*
    Basic removals.
    pop_front/pop_back return the data pointer so you can use it.
    They do NOT free the data — that's your responsibility.
*/
void *dlist_pop_front(DList *list);
void *dlist_pop_back(DList *list);

/*
    Removes a specific node from the list.
    This is O(1) because we already have the pointer to the node,
    no need to search the list.
*/
void dlist_remove_node(DList *list, DListNode *node, void (*free_fn)(void*));

/*
    Linear search using a custom comparator.
    cmp_fn must return 0 when two elements match.
*/
DListNode *dlist_find(DList *list, void *target, int (*cmp_fn)(void*, void*));

/*
    Priority insertion.
    Inserts the element in the correct position (according to 'priority').
    If priority_mode=false, this function should not be used.
*/
void dlist_insert_priority(DList *list, void *data, int priority);

/*
    Simple foreach macro to iterate nodes cleanly.
    Example:
        DLIST_FOREACH(list, cursor) {
            printf("%d\n", *(int*)cursor->data);
        }
*/
#define DLIST_FOREACH(list, node) \
    for (DListNode *node = (list)->head; node != NULL; node = node->next)

#endif
