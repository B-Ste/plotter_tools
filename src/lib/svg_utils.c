#include "svg_utils.h"

typedef struct _SVG {
    FILE* f;
} SVG;

typedef struct _SVG_PATH {
    LIST* list;
} SVG_PATH;

/*
    Creates a new SVG with the objective of creating a SVG-File.

    Argument: Path to new SVG-File

    Returns:
        - Pointer to new SVG on success
        - NULL otherwise
*/
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

/*
    Makes XML of SVG-File valid, closes file safely and frees SVG.

    Argument: SVG to finalize

    Returns:
        - 0 on success
        - not 0 otherwise
*/
int svg_finalize(SVG* svg) {
    fprintf(svg->f, "</svg>\n");
    int t = fclose(svg->f);
    free(svg);
    return t;
}

/*
    Returns the string-representation of a SVG path element.
 */
void* svg_path_element_to_string(void* e) {
    SVG_PATH_ELEMENT* elem = (SVG_PATH_ELEMENT*) e;
    double max_arg = 0;
    for (int i = 0; i < SVG_PATH_ELEMENT_ARG_NUM; i++) {
        double k = fabs(elem->args[i]);
        if (k > max_arg) max_arg = k;
    }
    // Compute number of decimal places to store largest number, counting in negative sign and whitespace
    int len = (int) ceil(log10(max_arg)) + 3;
    // add space for letter and whitespace in front and null terminator
    int str_len = 3 + len * SVG_PATH_ELEMENT_ARG_NUM;
    char* str = malloc (str_len);
    if (!str) return NULL;
    switch (elem->type) {
    case MOVETO:
        sprintf(str, "M %f %f ", elem->args[0], elem->args[1]);
        break;
    case MOVETO_REL:
        sprintf(str, "m %f %f ", elem->args[0], elem->args[1]);
        break;
    case CLOSEPATH:
        sprintf(str, "Z ");
        break;
    case LINETO:
        sprintf(str, "L %f %f ", elem->args[0], elem->args[1]);
        break;
    case LINETO_REL:
        sprintf(str, "l %f %f ", elem->args[0], elem->args[1]);
        break;
    case HORIZONTAL_LINETO:
        sprintf(str, "H %f", elem->args[0]);
        break;
    case HORIZONTAL_LINETO_REL:
        sprintf(str, "h %f", elem->args[0]);
        break;
    case VERTICAL_LINETO:
        sprintf(str, "V %f", elem->args[0]);
        break;
    case VERTICAL_LINETO_REL:
        sprintf(str, "v %f", elem->args[0]);
        break;
    case CURVETO:
        sprintf(str, "C %f %f %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3], elem->args[4], elem->args[5]);
        break;
    case CURVETO_REL:
        sprintf(str, "c %f %f %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3], elem->args[4], elem->args[5]);
        break;
    case SMOOTH_CURVETO:
        sprintf(str, "S %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3]);
        break;
    case SMOOTH_CURVETO_REL:
        sprintf(str, "s %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3]);
        break;
    case QUAD_BEZ:
        sprintf(str, "Q %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3]);
        break;
    case QUAD_BEZ_REL:
        sprintf(str, "q %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3]);
        break;
    case SMOOTH_QUAD_BEZ:
        sprintf(str, "T %f %f ", elem->args[0], elem->args[1]);
        break;
    case SMOOTH_QUAD_BEZ_REL:
        sprintf(str, "t %f %f ", elem->args[0], elem->args[1]);
        break;
    case ELLIPTICAL_ARC:
        sprintf(str, "A %f %f %f %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3], elem->args[4], elem->args[5], elem->args[6]);
        break;
    case ELLIPTICAL_ARC_REL:
        sprintf(str, "a %f %f %f %f %f %f %f ", elem->args[0], elem->args[1], elem->args[2], elem->args[3], elem->args[4], elem->args[5], elem->args[6]);
        break;
    default:
        break;
    }
    return str;
}

/*
    Adds a SVG path to a SVG.

    Arguments:
        - SVG to add path to
        - path to add

    Returns:
        - 0 on success
        - not 0 otherwise
*/
int svg_add(SVG* svg, SVG_PATH* path) {
    fprintf(svg->f, "<path d=\"");
    LIST* str_list = list_map(path->list, &svg_path_element_to_string);
    if (!str_list) return 1;
    for (int i = 0; i < list_length(str_list); i++) {
        fprintf(svg->f, "%s", (char*) list_get(str_list, i));
    }
    list_destroy(str_list);
    fprintf(svg->f,"\" %s />\n", STD_STYLE);
    return 0;
}

/*
    Creates a new SVG path.

    Returns:
        - Pointer to new SVG path on success
        - NULL otherwisew
*/
SVG_PATH* svg_path_create() {
    SVG_PATH* path = malloc(sizeof(SVG_PATH));
    if (!path) return NULL;
    path->list = list_create();
    if (!path->list) return NULL;
    return path;
}

/*
    Deallocates SVG path.

    Argument: SVG path to destroy
*/
void svg_path_destroy(SVG_PATH* path) {
    list_destroy(path->list);
    free(path);
}

/*
    Adds a SVG path-element to a SVG path

    Arguments:
        - path to add element to
        - element to add

    Returns:
        - 0 on success
        - 1 otherwise
*/
int svg_path_add(SVG_PATH* path, SVG_PATH_ELEMENT* elem){
    return list_append(path->list, elem);
}

/*
    Creates a new SVG path element.

    Arguments:
        - array of arguments as specified by SVG documentation
        - type of svg path element
    
    Returns:
        - Pointer to new SVG path element on success
        - NULL otherwise
*/
SVG_PATH_ELEMENT* svg_path_element_create(double args[SVG_PATH_ELEMENT_ARG_NUM], SVG_PATH_ELEMENT_TYPE type) {
    SVG_PATH_ELEMENT* elem = malloc(sizeof(SVG_PATH_ELEMENT));
    if (!elem) return NULL;
    elem->type = type;
    for (int i = 0; i < SVG_PATH_ELEMENT_ARG_NUM; i++) elem->args[i] = args[i];
    return elem;
}
