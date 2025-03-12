#include <stdio.h>

#include "lib/svg_utils.h"
#include "lib/list.h"

int main(int argc, char const *argv[])
{
    SVG_PATH* p = svg_path_create();
    SVG_PATH_ELEMENT* a = svg_path_element_lineto(10.0, 12);
    SVG_PATH_ELEMENT* b = svg_path_element_lineto_rel(10.0, 13);
    SVG_PATH_ELEMENT* c = svg_path_element_lineto(10.5, 14);
    svg_path_add(p, a);
    svg_path_add(p, b);
    svg_path_add(p, c);
    svg_path_destroy(p);
    return 0;
}
