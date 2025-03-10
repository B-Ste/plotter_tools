#ifndef FIFO_H
#define FIFO_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct _FIFO FIFO;

FIFO* FIFO_create();
void FIFO_destroy(FIFO*, bool);

int FIFO_add(FIFO*, void*);
void* FIFO_remove(FIFO*);

#endif