#include "svg_utils.h"

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

int svg_rect(SVG* svg, double x, double y, double width, double height) {
    if (width < 0 || height < 0) return 1;
    fprintf(svg->f, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" %s/>\n", x, y, width, height, STD_STYLE);
    return 0;
}
