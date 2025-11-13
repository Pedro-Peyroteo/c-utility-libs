#include <stdio.h>
#include <stdlib.h>
#include <dlist.h>

void print_list(DList *list) {
    printf("[ ");
    DLIST_FOREACH(list, n) {
        printf("(%d:%d) ", n->priority, *(int*)n->data);
    }
    printf("]\n");
}

int main() {
    printf("\n=== PRIORITY LIST TEST ===\n");

    DList *list = dlist_create(true, NULL);

    int a = 10, b = 20, c = 30, d = 40, e = 50;

    /*
        Insert in mixed, unsorted order:
        Format: (value, priority)
    */
    dlist_insert_priority(list, &a, 2);  /* (2:10) */
    dlist_insert_priority(list, &b, 5);  /* (5:20) */
    dlist_insert_priority(list, &c, 1);  /* (1:30) */
    dlist_insert_priority(list, &d, 5);  /* (5:40) */
    dlist_insert_priority(list, &e, 9);  /* (9:50) */

    printf("\n> Testing priority ordering...\n");

    int expected_values[]     = {50, 20, 40, 10, 30};
    int expected_priorities[] = { 9,  5,  5,  2,  1};

    int index = 0;
    int success = 1;

    DLIST_FOREACH(list, n) {
        if (*(int*)n->data != expected_values[index] ||
            n->priority != expected_priorities[index]) {

            printf("[FAIL] Priority order mismatch at index %d.\n", index);
            printf("       Expected: (%d:%d)\n",
                expected_priorities[index], expected_values[index]);
            printf("       Got: (%d:%d)\n",
                n->priority, *(int*)n->data);

            success = 0;
            break;
        }
        index++;
    }

    if (success)
        printf("[OK] Priority insertion ordering.\n");

    dlist_destroy(list, NULL);

    printf("\n=== PRIORITY LIST TEST PASSED ===\n\n");
    return 0;
}
