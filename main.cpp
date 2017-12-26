#include "main.h"

int main()
{
    std::vector<point*> points;
    std::vector<line*> lines;

    int bounding_box_x_min;
    int bounding_box_x_max;

    int bounding_box_y_min;
    int bounding_box_y_max;

    std::tie(points, bounding_box_x_min, bounding_box_x_max, bounding_box_y_min, bounding_box_y_max) = read_points();

    lines = triangulate_brute_force(points);
    svgify("brute_force.svg", bounding_box_x_min, bounding_box_x_max, bounding_box_y_min, bounding_box_y_max, points, lines);

    lines = triangulate_moving_shell(points);
    svgify("moving_shell.svg", bounding_box_x_min, bounding_box_x_max, bounding_box_y_min, bounding_box_y_max, points, lines);
}
