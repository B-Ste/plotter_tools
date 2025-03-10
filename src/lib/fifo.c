#include "fifo.h"

typedef struct _FIFO_ELEMENT {
    void* element;
    struct _FIFO_ELEMENT* next;
} FIFO_ELEMENT;

typedef struct _FIFO {
    int size;
    FIFO_ELEMENT* head;
    FIFO_ELEMENT* tail;
} FIFO;

/*
    Creates new empty FIFO.
    Returns:
        - Pointer to new FIFO on success
        - NULL on error
*/
FIFO* FIFO_create() {
    FIFO* fifo = malloc(sizeof(FIFO));
    if (!fifo) return NULL;
    fifo->size = 0;
    fifo->head = NULL;
    fifo->tail = NULL;
    return fifo;
}

/*
    Destroys FIFO and frees used memory.
    Arguments:
        - f : FIFO to be destroyed
        - r : Set to true to also free saved pointers.
    Returns: nothing
*/
void FIFO_destroy(FIFO* f, bool r) {
    if (f->size > 0) {
        FIFO_ELEMENT* e = f->head;
        do {
            FIFO_ELEMENT* tmp = e->next;
            if (r) free(e->element);
            free(e);
            e = tmp;
        } while (e);
    }
    free(f);
}

/*
    Adds new element to FIFO.
    Arguments:
        - f : FIFO to add to
        - e : Pointer to to be added element
    Returns:
        - 0 on success
        - 1 otherwise
*/
int FIFO_add(FIFO* f, void* e) {
    FIFO_ELEMENT* fe = malloc(sizeof(FIFO_ELEMENT));
    if (!fe) return 1;
    fe->element = e;
    fe->next = NULL;
    if (f->size > 0) {
        f->tail->next = fe;
        f->tail = fe;
    } else {
        f->head = fe;
        f->tail = fe;
    }
    f->size++;
    return 0;
}

/*
    Gives Pointer of next FIFO-Element and removes it from the FIFO.
    Arguments: FIFO to remove next element from
    Returns:
        - Pointer to next element in FIFO on success
        - NULL otherwise
*/
void* FIFO_remove(FIFO* f) {
    if (f->size == 0) return NULL;
    void* e = f->head->element;
    f->head = f->head->next;
    f->size--;
    return e;
}
