# LIST

---

## PRESENTATION

Generic doubly linked list implementation in ANSI C.

---

##  PREREQUISITES

- C99 (or higer) compiler.

---

## EXAMPLE

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

typedef struct {
    int   id;
    const char *name;
} Task;

int main(void)
{
    List *tasks = list_create();
    if (!tasks) {
        return 1;
    }

    Task t1 = { .id = 1, .name = "Write code" };
    Task t2 = { .id = 2, .name = "Review code" };
    Task t3 = { .id = 3, .name = "Ship code" };

    list_push_back(tasks, &t1);
    list_push_back(tasks, &t2);
    list_push_front(tasks, &t3);

    printf("List size: %zu\n", list_size(tasks));

    Task *head = list_head(tasks);
    Task *tail = list_tail(tasks);

    printf("Head: %d - %s\n", head->id, head->name);
    printf("Tail: %d - %s\n", tail->id, tail->name);

    Task *popped;
    list_pop_front(tasks, (void **)&popped);
    printf("Popped: %d - %s\n", popped->id, popped->name);

    list_remove(tasks, &t2);

    printf("List size after removal: %zu\n", list_size(tasks));

    list_destroy(tasks);
    return 0;
}
```
