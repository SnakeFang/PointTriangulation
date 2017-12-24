#include <fstream>
#include <iostream>

#include "main.h"

std::tuple<std::vector<point*>, int, int, int, int> read_points()
{
    int point_count;
    std::cin >> point_count;

    std::tuple<std::vector<point*>, int, int, int, int> return_value(std::vector<point*>(), std::numeric_limits<int>::max(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), std::numeric_limits<int>::min());

    std::vector<point*>& points = std::get<0>(return_value);

    int& bounding_box_x_min = std::get<1>(return_value);
    int& bounding_box_x_max = std::get<2>(return_value);

    int& bounding_box_y_min = std::get<3>(return_value);
    int& bounding_box_y_max = std::get<4>(return_value);

    for (int i = 0; i < point_count; i++)
    {
        int x, y;
        std::cin >> x >> y;

        bounding_box_x_min = std::min(bounding_box_x_min, x);
        bounding_box_y_min = std::min(bounding_box_y_min, y);

        bounding_box_x_max = std::max(bounding_box_x_max, x);
        bounding_box_y_max = std::max(bounding_box_y_max, y);

        points.push_back(new point(x, y));
    }

    return return_value;
}

void svgify(const std::string& file_name, int bounding_box_x_min, int bounding_box_x_max, int bounding_box_y_min, int bounding_box_y_max, const std::vector<point*>& points, const std::vector<line*>& lines)
{
    double x_scale, y_scale;

    x_scale = 500.0 / (bounding_box_x_max - bounding_box_x_min);
    y_scale = 500.0 / (bounding_box_y_max - bounding_box_y_min);

    std::ofstream file(file_name);

    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"600\" width=\"600\">\n";

    for (point* p : points)
    {
        double x = 50 + x_scale * (p->x - bounding_box_x_min);
        double y = 50 + y_scale * (p->y - bounding_box_y_min);

        file << "  <circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"10\" fill=\"black\" />\n";
    }

    file << '\n';

    for (line* l : lines)
    {
        double x1 = 50 + x_scale * (l->p1->x - bounding_box_x_min);
        double y1 = 50 + y_scale * (l->p1->y - bounding_box_y_min);

        double x2 = 50 + x_scale * (l->p2->x - bounding_box_x_min);
        double y2 = 50 + y_scale * (l->p2->y - bounding_box_y_min);

        file << "  <line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" stroke=\"black\" stroke-width=\"2\" />\n";
    }

    file << "</svg>\n";
    file << std::flush;
}

void txtify(const std::string& file_name, const std::vector<line*> lines)
{
    std::ofstream file(file_name);

    for (line* l : lines)
    {
        file << '(' << l->p1->x << ", " << l->p1->y << "), (" << l->p2->x << ", " << l->p2->y << ")\n";
    }

    file.flush();
}