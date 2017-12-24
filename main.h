#pragma once

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

struct point;
struct line;

struct point
{
    int x;
    int y;

    bool in_shell;
    int lines_shared;

    std::vector<line*> lines_connected;

    point(int x = 0, int y = 0)
        : x(x), y(y), in_shell(false), lines_shared(0), lines_connected()
    {
    }
};

struct line
{
    point* p1;
    point* p2;

    int x_min;
    int x_max;

    int y_min;
    int y_max;

    int a;
    int b;
    int c;

    int connections;

    line(point* p1, point* p2)
        :
        p1(p1),
        p2(p2),
        x_min(std::min(p1->x, p2->x)),
        x_max(std::max(p1->x, p2->x)),
        y_min(std::min(p1->y, p2->y)),
        y_max(std::max(p1->y, p2->y)),
        a(p2->y - p1->y),
        b(p1->x - p2->x),
        c(p1->x * p2->y - p1->y * p2->x),
        connections(0)
    {
    }
};

bool intersect(line*, line*);
bool intersect(line*, point*);

std::tuple<std::vector<point*>, int, int, int, int> read_points();
void svgify(const std::string&, int, int, int, int, const std::vector<point*>&, const std::vector<line*>&);
void txtify(const std::string&, const std::vector<line*>&);

std::vector<line*> triangulate_brute_force(const std::vector<point*>&);
std::vector<line*> triangulate_moving_shell(const std::vector<point*>&);