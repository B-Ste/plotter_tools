#ifndef SVG_UTILS_H
#define SVG_UTILS_H

#define STD_STYLE "fill=\"none\" stroke=\"black\" stroke-width=\"1\" vector-effect=\"non-scaling-stroke\""

#include <stdio.h>

typedef struct {
    FILE* f;
} SVG;

typedef enum _SVG_ELEMENT_TYPE {
    RECT
} SVG_ELEMENT_TYPE;

typedef struct {
    void* element;
    SVG_ELEMENT_TYPE type;
} SVG_ELEMENT;

int svg_create(SVG*, char*);
int svg_finalize(SVG*);

int svg_add(SVG*, SVG_ELEMENT*);

#endif