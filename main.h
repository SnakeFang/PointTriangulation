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

    int connected;
    bool reached;
    bool removed;
    
    point(int x, int y)
        : x(x), y(y), connected(0), reached(false), removed(false)
    {
    }

    point()
        : x(0), y(0), connected(0), reached(false), removed(false)
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

    bool removed;

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
        removed(false)
    {
    }

    line()
        :
        p1(nullptr),
        p2(nullptr),
        x_min(0),
        x_max(0),
        y_min(0),
        y_max(0),
        a(0),
        b(0),
        c(0),
        removed(false)
    {
    }
};

bool lines_intersect(line*, line*);
bool line_contains_point(line*, point*);

std::tuple<std::vector<point*>, int, int, int, int> read_points();
void svgify(const std::string&, int, int, int, int, const std::vector<point*>&, const std::vector<line*>&);
void txtify(const std::string&, const std::vector<line*>&);

std::vector<line*> triangulate_brute_force(const std::vector<point*>&);
std::vector<line*> triangulate_moving_shell(const std::vector<point*>&);