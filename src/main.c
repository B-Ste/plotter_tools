#include <stdio.h>

#include "lib/svg_utils.h"

int main(int argc, char const *argv[])
{
    SVG s;
    svg_create(&s, "test.svg");
    svg_rect(&s, 10.0, 10.0, 10.0, 10.0);
    svg_finalize(&s);
    return 0;
}
