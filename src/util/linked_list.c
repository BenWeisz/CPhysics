#include "util/linked_list.h"

LINKED_LIST* LinkedList_create()
{
    return LinkedList_create_with_delete(NULL);
}

LINKED_LIST* LinkedList_create_with_delete(void (*deinit_fn)(void*))
{
    LINKED_LIST* linked_list = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
    if (linked_list == NULL)
    {
        Log_error("Failed to allocate memory for new LINKED_LIST\n");
        return NULL;
    }   

    // Initialize the LINKED_LIST
    linked_list->length = 0;
    linked_list->first = NULL;
    linked_list->last = NULL;
    linked_list->deinit_fn = deinit_fn;

    return linked_list;
}

void LinkedList_delete(LINKED_LIST* linked_list)
{
    if (linked_list->first == NULL) {
        free((void*)linked_list);
        return;
    }

    _LINKED_LIST_NODE* curr_node = linked_list->first;
    _LINKED_LIST_NODE* next_node = curr_node->next;
    while (curr_node != NULL)
    {
        // Free the data
        if (linked_list->deinit_fn != NULL)
            linked_list->deinit_fn(curr_node->data);

        free((void*)curr_node);

        curr_node = next_node;

        if (next_node != NULL)
            next_node = next_node->next;
    }

    // Free the LINKED_LIST
    free((void*)linked_list);
}

void* LinkedList_get(const LINKED_LIST* linked_list, u32 index)
{
    _LINKED_LIST_NODE* curr_node = linked_list->first;
    
    u32 i = 0;
    while (i != index && curr_node != NULL)
    {
        curr_node = curr_node->next;
        i++;
    }

    if (curr_node == NULL)
        return NULL;
    else
        return curr_node->data;
}

u32 LinkedList_add(LINKED_LIST* linked_list, void* data)
{
    _LINKED_LIST_NODE* new_node = (_LINKED_LIST_NODE*)malloc(sizeof(_LINKED_LIST_NODE));
    if (new_node == NULL)
    {
        Log_error("Failed to allocate memory for new _LINKED_LIST_NODE\n");
        return 0;
    }

    new_node->data = data;
    new_node->next = NULL;

    if (linked_list->last == NULL) 
    {
        linked_list->first = new_node;
        linked_list->last = new_node;
    }
    else
    {
        linked_list->last->next = new_node;
        linked_list->last = linked_list->last->next;
    }

    linked_list->length++;
    return 1;
}

u32 LinkedList_length(const LINKED_LIST* linked_list)
{
    return linked_list->length;
}

LINKED_LIST_ITERATOR* LinkedList_iterator(const LINKED_LIST* linked_list)
{
    return linked_list->first;
}

LINKED_LIST_ITERATOR* LinkedList_next(const LINKED_LIST_ITERATOR* iterator)
{
    return iterator->next;
}

void* LinkedList_iterator_get(const LINKED_LIST_ITERATOR* iterator)
{
    return iterator->data;
}

u32 LinkedList_iterator_is_valid(const LINKED_LIST_ITERATOR* iterator)
{
    return iterator != NULL;
}