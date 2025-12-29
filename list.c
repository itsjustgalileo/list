#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "list.h"

struct ListNode {
    struct ListNode *prev;
    struct ListNode *next;
    void *data;
};

struct List {
    struct ListNode *head;
    struct ListNode *tail;
    size_t count;
};

List *list_create(void)
{
    List *list = (List *)malloc(sizeof(List));
    if (NULL == list) {
        return NULL;
    }

    list->head = list->tail = NULL;
    list->count = 0;
    
    return list;
}

void list_destroy(List *list)
{
    if (list) {
        list_clear(list);
        free(list);
    }

    return;
}

static struct ListNode *list_node_new(void *data)
{
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));

    if (NULL == node) {
        return NULL;
    }

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

bool list_push_back(List *list, void *data)
{
    assert(list != NULL);
    struct ListNode *node = list_node_new(data);
    if (NULL == node) {
        return false;
    }
    
    if (NULL == list->head) {
        list->head = list->tail = node;        
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    
    ++list->count;
    
    return true;
}

bool list_push_front(List *list, void *data)
{
    assert(list != NULL);

    struct ListNode *node = list_node_new(data);
    if (NULL == node) {
        return false;
    }
    
    if (NULL == list->head) {
        list->head = list->tail = node;
    } else {
        list->head->prev = node;
        node->next = list->head;
        list->head = node;
    }

    ++list->count;

    return true;
}

bool list_pop_back(List *list, void **out)
{
    assert(list != NULL);

    if (list->count == 0) {
        return false;
    }
        
    struct ListNode *tmp = list->tail;

    if (out) {        
        *out = tmp->data;    
    }
    
    if (list->count == 1) {
        list->head = list->tail = NULL;
    } else {
        list->tail = tmp->prev;
        list->tail->next = NULL;
    }    
        
    free(tmp);
    --list->count;
    
    return true;
}

bool list_pop_front(List *list, void **out)
{
    assert(list != NULL);

    if (list->count == 0) {
        return false;
    }
        
    struct ListNode *tmp = list->head;

    if (out) {        
        *out = tmp->data;    
    }
        
    if (list->count == 1) {
        list->head = list->tail = NULL;
    } else {
        list->head = tmp->next;
        list->head->prev = NULL;
    }    
        
    free(tmp);
    --list->count;
    
    return true;
}

bool list_remove(List *list, void *elem)
{
    assert(list != NULL);

    struct ListNode *node = list->head;

    while (node) {
        if (node->data == elem) {

            if (node->prev) {
                node->prev->next = node->next;
            } else {
                list->head = node->next;
            }

            if (node->next) {
                node->next->prev = node->prev;
            } else {
                list->tail = node->prev;
            }

            free(node);
            --list->count;
            return true;
        }

        node = node->next;
    }

    return false;
}

void list_clear(List *list)
{
    assert(list != NULL);

    struct ListNode *node = list->head;

    while (node) {
        struct ListNode *next = node->next;
        free(node);
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
}

void *list_head(const List *list)
{
    if (NULL == list || NULL == list->head) {
        return NULL;
    }

    return list->head->data;
}

void *list_tail(const List *list)
{
    if (NULL == list || NULL == list->tail) {
        return NULL;
    }

    return list->tail->data;
}

size_t list_size(const List *list)
{
    assert(list != NULL);
    return list->count;
}

bool list_empty(const List *list)
{
    assert(list != NULL);
    return (list->count == 0);
}
