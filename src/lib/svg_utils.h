#ifndef SVG_UTILS_H
#define SVG_UTILS_H

#define STD_STYLE "fill=\"none\" stroke=\"black\" stroke-width=\"1\" vector-effect=\"non-scaling-stroke\""

#include <stdio.h>

typedef struct SVG {
    FILE* f;
} SVG;

int svg_create(SVG*, char*);
int svg_finalize(SVG*);

int svg_rect(SVG*, double, double, double, double);

#endif