#ifndef FIFO_H
#define FIFO_H

#include <stdlib.h>
#include <stdbool.h>

#define FIFO_destroy(a, b) FIFO_destroy_custom(a, b, &free);

typedef struct _FIFO FIFO;

FIFO* FIFO_create();
void FIFO_destroy_custom(FIFO*, bool, void (*)(void*));

int FIFO_add(FIFO*, void*);
void* FIFO_remove(FIFO*);

#endif