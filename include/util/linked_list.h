#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

#include "util/types.h"
#include "util/log.h"

typedef struct _LINKED_LIST_NODE {
    void* data;
    struct _LINKED_LIST_NODE* next;
} _LINKED_LIST_NODE;

typedef struct LINKED_LIST {
    u32 length;
    _LINKED_LIST_NODE* first;
    _LINKED_LIST_NODE* last;
    void (*deinit_fn)(void*);
} LINKED_LIST;

#define LINKED_LIST_ITERATOR _LINKED_LIST_NODE

LINKED_LIST* LinkedList_create();
LINKED_LIST* LinkedList_create_with_delete(void (*deinit_fn)(void*));
void LinkedList_delete(LINKED_LIST* linked_list);

void* LinkedList_get(const LINKED_LIST* linked_list, u32 index);
u32 LinkedList_add(LINKED_LIST* linked_list, void* data);
u32 LinkedList_length(const LINKED_LIST* linked_list);

LINKED_LIST_ITERATOR* LinkedList_iterator(const LINKED_LIST* linked_list);
LINKED_LIST_ITERATOR* LinkedList_next(const LINKED_LIST_ITERATOR* iterator);
void* LinkedList_iterator_get(const LINKED_LIST_ITERATOR* iterator);
u32 LinkedList_iterator_is_valid(const LINKED_LIST_ITERATOR* iterator);

#endif  // LINKED_LIST_H