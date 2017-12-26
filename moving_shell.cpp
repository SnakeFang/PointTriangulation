#include <functional>
#include <iostream>

#include "main.h"

std::vector<line*> triangulate_moving_shell(const std::vector<point*>& points)
{
    std::vector<point*> points_all = points;
    std::vector<point*> points_shell;
    std::vector<line*> lines_all;
    std::vector<line*> lines_shell;

    std::sort(points_all.begin(), points_all.end(), [](point* p1, point* p2) -> bool { return p1->x < p2->x || (p1->x == p2->x && p1->y < p2->y); });

    int n = 0;

    for (point* point_new : points_all)
    {
        point* point_min = nullptr;
        line line_min;

        point* point_max = nullptr;
        line line_max;
        
        for (point* point_shell : points_shell)
        {
            point_shell->reached = false;

            line line_new(point_new, point_shell);

            if (!std::any_of(lines_shell.begin(), lines_shell.end(), std::bind(&lines_intersect, &line_new, std::placeholders::_1)))
            {
                point_shell->reached = true;
                point_shell->connected++;

                if (point_min == nullptr || point_shell->y < point_min->y || (point_shell->y == point_min->y && point_shell->x < point_min->x))
                {
                    point_min = point_shell;
                    line_min = line_new;
                }

                if (point_max == nullptr || point_shell->y > point_max->y || (point_shell->y == point_max->y && point_shell->x > point_max->x))
                {
                    point_max = point_shell;
                    line_max = line_new;
                }
            }
        }

        points_shell.push_back(point_new);

        if (point_min != nullptr && point_max != nullptr)
        {
            if (point_min != point_max)
            {
                point_new->connected = 2;

                lines_shell.push_back(new line(line_min));
                lines_all.push_back(lines_shell.back());
                lines_shell.push_back(new line(line_max));
                lines_all.push_back(lines_shell.back());
            }
            else
            {
                point_new->connected = 1;

                lines_shell.push_back(new line(line_min));
                lines_all.push_back(lines_shell.back());
            }

            for (point* point_shell : points_shell)
            {
                if (point_shell->reached && point_shell != point_min && point_shell != point_max)
                {
                    point_shell->removed = true;
                }
            }

            for (line* line_shell : lines_shell)
            {
                if (line_shell->p1->removed || line_shell->p2->removed)
                {
                    line_shell->removed = true;
                    line_shell->p1->connected--;
                    line_shell->p2->connected--;
                }
            }

            for (line* line_shell : lines_shell)
            {
                if (line_shell->p1->connected >= 3 && line_shell->p2->connected >= 3)
                {
                    line_shell->removed = true;
                    line_shell->p1->connected--;
                    line_shell->p2->connected--;

                    if (n == 9)
                    {
                        std::cout << line_shell->p1->x << ' ' << line_shell->p1->y << ' ' << line_shell->p2->x << ' ' << line_shell->p2->y << std::endl;
                        std::cout << line_shell->p1->connected;
                        std::cout << line_shell->p2->connected;
                    }
                }
            }

            points_shell.erase(std::remove_if(points_shell.begin(), points_shell.end(), [](point* point_shell) -> bool { return point_shell->removed; }), points_shell.end());
            lines_shell.erase(std::remove_if(lines_shell.begin(), lines_shell.end(), [](line* line_shell) -> bool { return line_shell->removed; }), lines_shell.end());

        }

        svgify("partial_" + std::to_string(n) + ".svg", 0, 6, 0, 6, points_shell, lines_shell);

        ++n;
    }

    return lines_all;
}