#include "svg_utils.h"

typedef struct _SVG {
    FILE* f;
} SVG;

typedef struct _SVG_PATH {
    LIST* list;
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
    path->list = list_create();
    if (!path->list) return NULL;
    return path;
}

void svg_path_destroy(SVG_PATH* path) {
    list_destroy(path->list);
    free(path);
}

int svg_path_add(SVG_PATH* path, SVG_PATH_ELEMENT* elem){
    return list_append(path->list, elem);
}

SVG_PATH_ELEMENT* svg_path_element_create(double args[SVG_PATH_ELEMENT_ARG_NUM], SVG_PATH_ELEMENT_TYPE type) {
    SVG_PATH_ELEMENT* elem = malloc(sizeof(SVG_PATH_ELEMENT));
    elem->type = type;
    for (int i = 0; i < SVG_PATH_ELEMENT_ARG_NUM; i++) elem->args[i] = args[i];
    return elem;
}
