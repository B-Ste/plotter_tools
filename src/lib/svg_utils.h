#ifndef SVG_UTILS_H
#define SVG_UTILS_H

#include <stdlib.h>
#include <stdio.h>

#include "fifo.h"

#define STD_STYLE "fill=\"none\" stroke=\"black\" stroke-width=\"1\" vector-effect=\"non-scaling-stroke\""
#define SVG_PATH_ELEMENT_ARG_NUM 6

typedef struct _SVG SVG;
typedef struct _SVG_PATH SVG_PATH;

typedef enum {
    MOVETO,
    MOVETO_REL,
    CLOSEPATH,
    LINETO,
    LINETO_REL,
    HORIZONTAL_LINETO,
    HORIZONTAL_LINETO_REL,
    VERTICAL_LINETO,
    VERTICAL_LINETO_REL,
    CURVETO,
    CURVETO_REL,
    SMOOTH_CURVETO,
    SMOOTH_CURVETO_REL,
    QUAD_BEZ,
    QUAD_BEZ_REL,
    SMOOTH_QUAD_BEZ,
    SMOOTH_QUAD_BEZ_REL,
    ELLIPTICAL_ARC,
    ELLIPTICAL_ARC_REL
} SVG_PATH_ELEMENT_TYPE;

typedef struct {
    double args[SVG_PATH_ELEMENT_ARG_NUM];
    SVG_PATH_ELEMENT_TYPE type;
} SVG_PATH_ELEMENT;

SVG* svg_create(char*);
int svg_finalize(SVG*);

SVG_PATH* svg_path_create();
void svg_path_destroy(SVG_PATH*);

#endif