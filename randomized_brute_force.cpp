#include <functional>
#include <random>

#include "main.h"

std::vector<line*> triangulate_randomized_brute_force(const std::vector<point*>& points)
{
    std::vector<line*> lines;
    std::vector<line> all_lines;
    all_lines.reserve(points.size() * (points.size() - 1) / 2);

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            all_lines.emplace_back(points[i], points[j]);
        }
    }

    std::random_device seeder;

    std::shuffle(all_lines.begin(), all_lines.end(), std::mt19937_64(seeder()));
    std::shuffle(all_lines.begin(), all_lines.end(), std::mt19937_64(seeder()));
    std::shuffle(all_lines.begin(), all_lines.end(), std::mt19937_64(seeder()));
    std::shuffle(all_lines.begin(), all_lines.end(), std::mt19937_64(seeder()));

    for (line& l : all_lines)
    {
        if (!std::any_of(points.begin(), points.end(), std::bind(&line_contains_point, &l, std::placeholders::_1))
            && !std::any_of(lines.begin(), lines.end(), std::bind(&lines_intersect, &l, std::placeholders::_1)))
        {
            lines.push_back(new line(l));
        }
    }

    return lines;
}