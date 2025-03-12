#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <inttypes.h>

#define START_SIZE 2

typedef struct _LIST LIST;

LIST* list_create();
void list_destroy(LIST*);

int32_t list_append(LIST*, void*);
void* list_get(LIST*, int32_t);

#endif