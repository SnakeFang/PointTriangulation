#include "main.h"

std::vector<line*> triangulate_brute_force(const std::vector<point*>& points)
{
    std::vector<line*> lines;

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            line l(points[i], points[j]);
            bool intersects_any = true;

            if (!std::any_of(points.begin(), points.end(), std::bind(&line_contains_point, &l, std::placeholders::_1))
             && !std::any_of(lines.begin(), lines.end(), std::bind(&lines_intersect, &l, std::placeholders::_1)))
            {
                lines.push_back(new line(l));
            }
        }
    }

    return lines;
}