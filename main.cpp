#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <random>

#include "main.h"

static std::mt19937_64 random_generator(1);

static int random(int n)
{
    return std::uniform_int_distribution<int>(0, n)(random_generator);
}

void randomize(std::vector<point*>& points)
{
    int limit = 2 * (int) std::sqrt(points.size());

    std::vector<point> candidates;
    candidates.reserve(points.size() * points.size());

    for (int x = 0; x < limit; x++)
    {
        for (int y = 0; y < limit; y++)
        {
            candidates.emplace_back(x, y);
        }
    }

    std::shuffle(candidates.begin(), candidates.end(), random_generator);

    for (point* p : points)
    {
        *p = candidates.back();
        candidates.pop_back();
    }
}

void test()
{
    int point_count;
    int test_count;
    int group_size;
    int time_total = 0;

    std::cout << "point count: " << std::flush;
    std::cin >> point_count;

    std::cout << "test count: " << std::flush;
    std::cin >> test_count;

    std::cout << "group size: " << std::flush;
    std::cin >> group_size;

    std::vector<std::vector<point*>> points(group_size, std::vector<point*>(point_count, nullptr));
    std::vector<line> lines;

    for (int group = 0; group < group_size; group++)
    {
        for (int i = 0; i < point_count; i++)
        {
            points[group][i] = new point();
        }
    }

    for (int test = 0; test < test_count; test += group_size)
    {
        for (int group = 0; group < group_size; group++)
        {
            randomize(points[group]);
        }

        int time_start = std::clock();

        for (int group = 0; group < group_size; group++)
        {
            triangulate_moving_shell(points[group]);
        }

        int time_end = std::clock();

        time_total += time_end - time_start;
    }

    std::cout.precision(2);
    std::cout << std::fixed;

    std::cout << std::endl;
    std::cout << "time total: " << time_total << " ms" << std::endl;
    std::cout << "time average: " << ((double)time_total / (double)test_count) << " ms" << std::endl;

    std::system("pause");
}

int main()
{
    std::vector<point*> points;
    std::vector<line> lines;

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