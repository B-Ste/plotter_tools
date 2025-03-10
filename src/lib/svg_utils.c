#include "svg_utils.h"

typedef struct _SVG {
    FILE* f;
} SVG;

typedef struct _SVG_PATH {
    FIFO* fifo;
} SVG_PATH;

SVG* svg_create (char* path) {
    FILE *f = fopen(path, "w");
    if (!f) return NULL;

    SVG* svg = malloc(sizeof(SVG));
    if (!svg) return NULL;

    fprintf(f, "<?xml version=\"1.0\"?>\n");
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\">\n");

    svg->f = f;

    return svg;
}

int svg_finalize(SVG* svg) {
    fprintf(svg->f, "</svg>\n");
    int t = fclose(svg->f);
    free(svg);
    return t;
}

SVG_PATH* svg_path_create() {
    SVG_PATH* path = malloc(sizeof(SVG_PATH));
    if (!path) return NULL;
    path->fifo = FIFO_create();
    if (!path->fifo) return NULL;
    return path;
}

void svg_path_destroy(SVG_PATH* path) {
    FIFO_destroy(path->fifo, true);
    free(path);
}
