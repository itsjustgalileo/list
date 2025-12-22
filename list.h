#ifndef LIST_H_
#define LIST_H_ 1

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct List List;

    extern List *list_create(void);
    extern void list_destroy(List *list);

    extern bool list_push_back(List *list, void *data);
    extern bool list_push_front(List *list, void *data);

    extern bool list_pop_back(List *list, void **out);
    extern bool list_pop_front(List *list, void **out);

    extern bool list_remove(List *list, void *elem);
    extern void list_clear(List *list);

    extern void *list_head(const List *list);
    extern void *list_tail(const List *list);

    extern size_t list_size(const List *list);
    extern bool list_empty(const List *list);
    
/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif

#endif /* !LIST_H_ */
