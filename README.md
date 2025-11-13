# DList — Generic Doubly Linked List for C

A small, reusable C library that implements:

- A generic **doubly linked list** (`void*` data)
- Optional **priority sorting**
- O(1) insertion/removal at head or tail
- O(1) removal when you already have the node
- Helper utilities (peek, clear, size, etc.)

This library is written to be **simple**, **clean**, and **easy to integrate** into any C project — including our AED-Library project.

---

# 📦 Features

### ✔ Generic data (`void*`)

You can store any struct or type.

### ✔ Normal mode _or_ sorted priority mode

Useful for queues, schedulers, or recommendation lists.

### ✔ O(1) push/pop at both ends

Fast and predictable.

### ✔ Easy iteration

Through a simple macro.

### ✔ Clean API

With helper utilities to simplify usage.

---

# 📂 File Structure

```
include/
    dlist.h           → public header

src/
    dlist.c           → base list implementation
    dlist_priority.c  → priority insertion logic
    internal.h        → internal helpers

build/
    libdlist.a        → generated static library

tests/
    test_basic.c
    test_priority.c
    test_helpers.c

Makefile
```

---

# 🧠 How the List Works

The list is made of **nodes**, linked both forward and backward:

```
NULL <- [prev | data | next] <-> [prev | data | next] <-> [prev | data | next] -> NULL
```

Each node contains:

```c
typedef struct DListNode {
    void *data;          // your data (generic)
    int priority;        // used only in priority mode
    struct DListNode *prev;
    struct DListNode *next;
} DListNode;
```

The list struct tracks:

```c
typedef struct DList {
    DListNode *head;
    DListNode *tail;
    size_t size;
    bool priority_mode;
    int (*cmp)(void*, void*);
} DList;
```

---

# 🔧 Building the Library

Inside this project folder:

```bash
mingw32-make
```

This produces:

```
build/libdlist.a
```

To run all tests:

```bash
mingw32-make test_all
```

---

# 🚀 Using the Library in Another Project

Include the header:

```c
#include <dlist.h>
```

Link the library:

```
gcc myfile.c -Iinclude -Lbuild -ldlist -o myprog
```

---

# 🧭 Creating Lists

## Normal list

```c
DList *list = dlist_create(false, NULL);
```

## Priority list

```c
DList *plist = dlist_create(true, NULL);
```

---

# ➕ Adding Elements

### Insert at head

```c
dlist_push_front(list, data_ptr);
```

### Insert at tail

```c
dlist_push_back(list, data_ptr);
```

### Insert with priority

```c
dlist_insert_priority(plist, data_ptr, priority_value);
```

Priority rules:

- Higher priority = closer to the head
- Equal priorities preserve original order (stable sorting)

---

# ➖ Removing Elements

### Remove first element

```c
void *data = dlist_pop_front(list);
```

### Remove last element

```c
void *data = dlist_pop_back(list);
```

### Remove specific node (O(1))

```c
dlist_remove_node(list, nodePointer, free_fn);
```

---

# 🔍 Searching for Elements

If you provide a comparator:

```c
int cmp_int(void *a, void *b) {
    return (*(int*)a) - (*(int*)b);
}

DListNode *found = dlist_find(list, &value, cmp_int);
```

---

# 🧰 Helper Functions

### Peek front / back

```c
void *dlist_peek_front(list);
void *dlist_peek_back(list);
```

### Check if empty

```c
bool dlist_is_empty(list);
```

### Get list size

```c
size_t dlist_size(list);
```

### Clear the list (keep list struct)

```c
dlist_clear(list, free_fn);
```

### Highest priority (priority mode only)

```c
void *dlist_peek_highest_priority(plist);
```

---

# 🔁 Iterating Over the List

The library provides a simple macro:

```c
DLIST_FOREACH(list, node) {
    printf("%d\n", *(int*)node->data);
}
```

This hides the pointer walking logic.

---

# 🧼 Memory Management

You own the memory of whatever you put into the list.

Meaning:

- the list frees nodes
- **you** decide whether the list should also free your data

During destruction:

```c
dlist_destroy(list, free);
```

If your data doesn't need to be freed:

```c
dlist_destroy(list, NULL);
```

---

# 🏫 Integrating Into Our AED-Library Project

Here’s how our group should use this library:

### 📚 Books list

- Normal list (`priority_mode = false`)
- Comparator based on ISBN

### 👥 Clients list

- Normal list
- Custom search comparator

### 📖 Suggestions list

- Priority list (`priority_mode = true`)
- Priority = relevance score / frequency

### 📑 Loans

- Could be:
  - Dynamic array (your group decides), or
  - Another DList if needed

### 💡 Example in AED project

```c
Book *b = malloc(sizeof(Book));
strcpy(b->title, "C Programming");

DList *books = dlist_create(false, cmp_books);

dlist_push_back(books, b);

dlist_destroy(books, free);
```

---

# ✔ Summary

This library gives us:

- A generic, stable, easy-to-use list structure
- Priority support for specialized features
- Clean iteration
- Fully tested, reusable code
- A consistent API for our entire AED project

Everyone on the team can use it reliably and confidently.

---

# 📞 If you need anything

Ask Pedro — he might help.. for a coffe hehe
Or check the tests for usage examples.
