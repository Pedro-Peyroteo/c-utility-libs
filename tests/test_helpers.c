#include <stdio.h>
#include <stdlib.h>
#include <dlist.h>

/* Comparator for ints */
int cmp_int(void *a, void *b) {
    return (*(int*)a) - (*(int*)b);
}

void print_list(DList *list) {
    printf("[ ");
    DLIST_FOREACH(list, n) {
        printf("(%d:%d) ", n->priority, *(int*)n->data);
    }
    printf("]\n");
}

int main() {
    printf("\n=== HELPER FUNCTIONS TEST ===\n");

    DList *list = dlist_create(false, cmp_int);

    int a = 10, b = 20, c = 30;

    /* === Test: empty list checks === */
    printf("\n> Testing empty list helpers...\n");

    if (!dlist_is_empty(list)) {
        printf("[FAIL] List should be empty at start.\n");
        return 1;
    }

    /* === Size tests (empty) === */
    if (dlist_size(list) != 0) {
        printf("[FAIL] dlist_size incorrect for empty list.\n");
        printf("       Expected: 0, got: %zu\n", dlist_size(list));
        return 1;
    }

    printf("[OK] Empty list helpers.\n");

    /* Insert some values */
    dlist_push_back(list, &a);
    dlist_push_back(list, &b);
    dlist_push_back(list, &c);

    printf("\n> Testing size after insertions...\n");

    if (dlist_size(list) != 3) {
        printf("[FAIL] dlist_size incorrect after insertions.\n");
        printf("       Expected: 3, got: %zu\n", dlist_size(list));
        return 1;
    }

    printf("[OK] dlist_size after insertions.\n");

    /* === Test peek_front / peek_back === */
    printf("\n> Testing peek_front / peek_back...\n");

    if (*(int*)dlist_peek_front(list) != 10) {
        printf("[FAIL] peek_front incorrect.\n");
        return 1;
    }
    if (*(int*)dlist_peek_back(list) != 30) {
        printf("[FAIL] peek_back incorrect.\n");
        return 1;
    }

    printf("[OK] peek_front / peek_back.\n");

    /* === Test: clear === */
    printf("\n> Testing dlist_clear...\n");

    dlist_clear(list, NULL);

    if (!dlist_is_empty(list)) {
        printf("[FAIL] List should be empty after clear.\n");
        return 1;
    }

    /* === Size test (after clear) === */
    if (dlist_size(list) != 0) {
        printf("[FAIL] dlist_size incorrect after clear.\n");
        printf("       Expected: 0, got: %zu\n", dlist_size(list));
        return 1;
    }

    printf("[OK] dlist_clear.\n");

    /* === Priority tests for size === */
    printf("\n> Testing dlist_size with priority insertion...\n");

    DList *plist = dlist_create(true, NULL);

    int x = 1, y = 2, z = 3;

    dlist_insert_priority(plist, &x, 5);
    dlist_insert_priority(plist, &y, 9);
    dlist_insert_priority(plist, &z, 2);

    if (dlist_size(plist) != 3) {
        printf("[FAIL] dlist_size incorrect in priority list.\n");
        printf("       Expected: 3, got: %zu\n", dlist_size(plist));
        return 1;
    }

    printf("[OK] dlist_size with priority insertions.\n");

    /* === Priority helper === */
    printf("\n> Testing peek_highest_priority...\n");

    if (*(int*)dlist_peek_highest_priority(plist) != 2) {
        printf("[FAIL] peek_highest_priority incorrect.\n");
        printf("       Expected: 2, got: %d\n",
               *(int*)dlist_peek_highest_priority(plist));
        return 1;
    }

    printf("[OK] peek_highest_priority.\n");

    dlist_destroy(list, NULL);
    dlist_destroy(plist, NULL);

    printf("\n=== ALL HELPER TESTS PASSED ===\n\n");
    return 0;
}
