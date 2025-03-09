#include "svg_utils.h"

typedef struct {
    double x, y, width, height;
} SVG_RECT;

int svg_create (SVG* svg, char* path) {
    FILE *f = fopen(path, "w");
    if (f == NULL) return 1;

    fprintf(f, "<?xml version=\"1.0\"?>\n");
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    svg->f = f;

    return 0;
}

int svg_finalize(SVG* svg) {
    fprintf(svg->f, "</svg>\n");
    return fclose(svg->f);
}

int avg_add(SVG* svg, SVG_ELEMENT* elem) {
    switch (elem->type)
    {
    case RECT:
        return svg_rect(svg, elem);
    default:
        break;
    }
}

inline int svg_rect(SVG* svg, SVG_ELEMENT* elem) {
    SVG_RECT rect = *((SVG_RECT*) elem->element);
    if (rect.width < 0 || rect.height < 0) return 1;
    fprintf(svg->f, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" %s/>\n", rect.x, rect.y, rect.width, rect.height, STD_STYLE);
    return 0;
}
