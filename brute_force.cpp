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

            for (point* other : points)
            {
                if (intersect(&l, other))
                {
                    intersects_any = false;
                    break;
                }
            }

            if (!intersects_any)
            {
                continue;
            }

            for (line* other : lines)
            {
                if (intersect(&l, other))
                {
                    intersects_any = false;
                    break;
                }
            }

            if (!intersects_any)
            {
                continue;
            }

            lines.push_back(new line(l));
        }
    }

    return lines;
}