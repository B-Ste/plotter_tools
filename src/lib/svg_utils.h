#ifndef SVG_UTILS_H
#define SVG_UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "list.h"

#define STD_STYLE "fill=\"none\" stroke=\"black\" stroke-width=\"1\" vector-effect=\"non-scaling-stroke\""
#define SVG_PATH_ELEMENT_ARG_NUM 7

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
int svg_add(SVG*, SVG_PATH*);

SVG_PATH* svg_path_create();
void svg_path_destroy(SVG_PATH*);
int svg_path_add(SVG_PATH*, SVG_PATH_ELEMENT*);

SVG_PATH_ELEMENT* svg_path_element_create(double[SVG_PATH_ELEMENT_ARG_NUM], SVG_PATH_ELEMENT_TYPE);
#define svg_path_element_moveto(x, y) svg_path_element_create((double[]){x, y, 0, 0, 0, 0, 0}, MOVETO)
#define svg_path_element_moveto_rel(x, y) svg_path_element_create((double[]){x, y, 0, 0, 0, 0, 0}, MOVETO_REL)
#define svg_path_element_closepath() svg_path_element_create((double[]){0, 0, 0, 0, 0, 0, 0}, CLOSEPATH)
#define svg_path_element_lineto(x, y) svg_path_element_create((double[]){x, y, 0, 0, 0, 0, 0}, LINETO)
#define svg_path_element_lineto_rel(x, y) svg_path_element_create((double[]){x, y, 0, 0, 0, 0, 0}, LINETO_REL)
#define svg_path_element_horizontal_lineto(x) svg_path_element_create((double[]){x, 0, 0, 0, 0, 0, 0}, HORIZONTAL_LINETO)
#define svg_path_element_horizontal_lineto_rel(x) svg_path_element_create((double[]){x, 0, 0, 0, 0, 0, 0}, HORIZONTAL_LINETO_REL)
#define svg_path_element_vertical_lineto(y) svg_path_element_create((double[]){y, 0, 0, 0, 0, 0, 0}, VERTICAL_LINETO)
#define svg_path_element_vertical_lineto_rel(y) svg_path_element_create((double[]){y, 0, 0, 0, 0, 0, 0}, VERTICAL_LINETO_REL)
#define svg_path_element_curveto(x1, y1, x2, y2, x, y) svg_path_element_create((double[]){x1, y1, x2, y2, x, y, 0}, CURVETO)
#define svg_path_element_curveto_rel(x1, y1, x2, y2, x, y) svg_path_element_create((double[]){x1, y1, x2, y2, x, y, 0}, CURVETO_REL)
#define svg_path_element_smooth_curveto(x2, y2, x, y) svg_path_element_create((double[]){x2, y2, x, y, 0, 0, 0}, SMOOTH_CURVETO)
#define svg_path_element_smooth_curveto_rel(x2, y2, x, y) svg_path_element_create((double[]){x2, y2, x, y, 0, 0, 0}, SMOOTH_CURVETO_REL)
#define svg_path_element_quad_bezier(x1, y1, x, y) svg_path_element_create((double[]){x1, y1, x, y, 0, 0, 0}, QUAD_BEZ)
#define svg_path_element_quad_bezier_rel(x1, y1, x, y) svg_path_element_create((double[]){x1, y1, x, y, 0, 0, 0}, QUAD_BEZ_REL)
#define svg_path_element_smooth_quad_bezier(x, y) svg_path_element_create((double[]){x, y, 0, 0, 0, 0, 0}, SMOOTH_QUAD_BEZ)
#define svg_path_element_smooth_quad_bezier_rel(x, y) svg_path_element_create((double[]){x, y, 0, 0, 0, 0, 0}, SMOOTH_QUAD_BEZ_REL)
#define svg_path_element_elliptical_arc(rx, ry, xar, laf, sf, x, y) svg_path_element_create((double[]){rx, ry, xar, laf, sf, x, y}, ELLIPTICAL_ARC)
#define svg_path_element_elliptical_arc_rel(rx, ry, xar, laf, sf, x, y) svg_path_element_create((double[]){rx, ry, xar, laf, sf, x, y}, ELLIPTICAL_ARC_REL)

#define svg_path_element_destroy(p) free(p)

#endif