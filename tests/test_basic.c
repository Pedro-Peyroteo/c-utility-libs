#include <stdio.h>
#include <stdlib.h>
#include <dlist.h>

/* Basic integer comparator (not strictly needed for basic tests). */
int cmp_int(void *a, void *b) {
    return (*(int*)a) - (*(int*)b);
}

int main() {
    printf("\n=== BASIC LIST TEST ===\n");

    DList *list = dlist_create(false, cmp_int);

    int a = 10, b = 20, c = 30;

    /* Insert in basic mode (no priority). */
    dlist_push_back(list, &a);
    dlist_push_back(list, &b);
    dlist_push_back(list, &c);

    printf("\n> Testing push_back and basic ordering...\n");

    /* Verify order: 10, 20, 30 */
    int expected[] = {10, 20, 30};
    int index = 0;

    DLIST_FOREACH(list, n) {
        if (*(int*)n->data != expected[index]) {
            printf("[FAIL] Basic insertion order incorrect.\n");
            printf("       Expected: %d\n", expected[index]);
            printf("       Got: %d\n", *(int*)n->data);
            return 1;
        }
        index++;
    }

    printf("[OK] Basic insertion ordering.\n");

    /* Test pop operations */
    printf("\n> Testing pop_front...\n");
    int *v1 = dlist_pop_front(list);
    if (*v1 != 10) {
        printf("[FAIL] pop_front returned incorrect value.\n");
        printf("       Expected: 10, got: %d\n", *v1);
        return 1;
    }
    printf("[OK] pop_front.\n");

    printf("\n> Testing pop_back...\n");
    int *v2 = dlist_pop_back(list);
    if (*v2 != 30) {
        printf("[FAIL] pop_back returned incorrect value.\n");
        printf("       Expected: 30, got: %d\n", *v2);
        return 1;
    }
    printf("[OK] pop_back.\n");

    /* Test dlist_find */
    printf("\n> Testing dlist_find...\n");
    DListNode *found = dlist_find(list, &b, cmp_int);
    if (!found || *(int*)found->data != 20) {
        printf("[FAIL] dlist_find failed to locate 20.\n");
        return 1;
    }
    printf("[OK] dlist_find.\n");

    dlist_destroy(list, NULL);

    printf("\n=== BASIC LIST TEST PASSED ===\n\n");
    return 0;
}
