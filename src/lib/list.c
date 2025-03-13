#include "list.h"

typedef struct _LIST {
    void** content;
    int32_t capacity;
    int32_t length;
} LIST;

/*
    Creates a new list.

    Returns:
        - pointer to list on success
        - NULL otherwise
*/
LIST* list_create() {
    LIST* list = malloc(sizeof(list));
    if (!list) return NULL;
    list->content = malloc(START_SIZE * sizeof(void*));
    if (!list->content) return NULL;
    list->capacity = START_SIZE;
    list->length = 0;
    return list;
}

/*
    Destroys (deallocates) a list.

    Argument: List to destroy
*/
void list_destroy(LIST* list) {
    free(list-> content);
    free(list);
}

/*
    Appends an element to the list.

    Arguments:
        - list to append to
        - element to append

    Returns:
        - 0 on success
        - 1 otherwise
*/
int32_t list_append(LIST* list, void* element) {
    if (list->length < list->capacity) {
        list->content[list->length++] = element;
        return 0;
    }
    void** new_content = realloc(list->content, list->capacity * 2 * sizeof(void*));
    if (!new_content) return 1;
    list->content = new_content;
    list->capacity *= 2;
    list->content[list->length++] = element;
    return 0;
}

/*
    Gets an element at a specific location.

    Arguments:
        - list to access
        - position to access list at

    Returns:
        - element on success
        - NULL otherwise
*/
void* list_get(LIST* list, int32_t i) {
    return (i >= 0 && i < list->length) ? list->content[i] : NULL;
}
