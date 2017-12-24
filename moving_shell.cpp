#include "main.h"

std::vector<line*> triangulate_moving_shell(const std::vector<point*>& points)
{
    std::vector<point*> points_all = points;
    std::vector<point*> points_shell;
    std::vector<line*> lines_all;
    std::vector<line*> lines_shell;

    std::sort(points_all.begin(), points_all.end(), [](point* p1, point* p2) -> bool { return p1->x < p2->x; });

    for (point* point_new : points_all)
    {
        std::vector<point*> points_connected;

        for (point* point_shell : points_shell)
        {
            line line_candidate(point_new, point_shell);

            if (!std::any_of(lines_shell.begin(), lines_shell.end(), std::bind(&lines_intersect, &line_candidate, std::placeholders::_1)))
            {
                line* line_shell = new line(line_candidate);

                lines_all.push_back(line_shell);
                lines_shell.push_back(line_shell);
                points_connected.push_back(point_shell);
            }
        }

        for (point* point_connected : points_connected)
        {
            for (line* line_connected : point_connected->lines_connected)
            {
                line_connected->connections++;

                if (line_connected->connections == 2)
                {
                    line_connected->p1->lines_shared++;
                    line_connected->p2->lines_shared++;
                }
            }
        }

        lines_shell.erase(std::remove_if(lines_shell.begin(), lines_shell.end(), [](line* line_shell) -> bool { return line_shell->connections > 1 || line_shell->p1->lines_shared > 1 || line_shell->p2->lines_shared > 1; }), lines_shell.end());

        for (point* point_shell : points_shell)
        {
            point_shell->in_shell = false;
            point_shell->lines_shared = 0;
            point_shell->lines_connected.clear();
        }

        points_shell.clear();

        for (line* line_shell : lines_shell)
        {
            line_shell->connections = 0;

            line_shell->p1->lines_connected.push_back(line_shell);
            line_shell->p2->lines_connected.push_back(line_shell);

            if (!line_shell->p1->in_shell)
            {
                points_shell.push_back(line_shell->p1);
                line_shell->p1->in_shell = true;
            }

            if (!line_shell->p2->in_shell)
            {
                points_shell.push_back(line_shell->p2);
                line_shell->p1->in_shell = true;
            }
        }

        if (!point_new->in_shell)
        {
            points_shell.push_back(point_new);
        }
    }

    return lines_all;
}