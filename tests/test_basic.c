#include <stdio.h>
#include "dlist.h"

int main() {
    DList *list = dlist_create(false, NULL);
    
    int a = 10, b = 20, c = 30;

    dlist_push_back(list, &a);
    dlist_push_back(list, &b);
    dlist_push_front(list, &c);

    printf("List size: %zu\n", list->size);

    DLIST_FOREACH(list, node)
        printf("%d ", *(int*)node->data);

    printf("\n");

    dlist_destroy(list, NULL);
    return 0;
}
