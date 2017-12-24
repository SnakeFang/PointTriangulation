#include "main.h"

static int signum(int n)
{
    return (int) (n > 0) - (int) (n < 0);
}

bool lines_intersect(line* l1, line* l2)
{
    if (l1->p1 == l2->p1 || l1->p1 == l2->p2 || l1->p2 == l2->p1 || l1->p2 == l2->p2)
    {
        return false;
    }

    if (l1->x_max < l2->x_min || l1->y_max < l2->y_min || l2->x_max < l1->x_min || l2->y_max < l1->y_min)
    {
        return false;
    }

    int x_denominator = l1->a * l2->b - l1->b * l2->a;
    int y_denominator = l1->b * l2->a - l1->a * l2->b;

    if (x_denominator == 0 || y_denominator == 0)
    {
        return false;
    }

    int x_numerator = (l1->c * l2->b - l1->b * l2->c) * signum(x_denominator);
    int y_numerator = (l1->c * l2->a - l1->a * l2->c) * signum(y_denominator);

    int overlap_x_min = std::max(l1->x_min, l2->x_min) * std::abs(x_denominator);
    int overlap_y_min = std::max(l1->y_min, l2->y_min) * std::abs(y_denominator);

    int overlap_x_max = std::min(l1->x_max, l2->x_max) * std::abs(x_denominator);
    int overlap_y_max = std::min(l1->y_max, l2->y_max) * std::abs(y_denominator);

    return overlap_x_min <= x_numerator && x_numerator <= overlap_x_max && overlap_y_min <= y_numerator && y_numerator <= overlap_y_max;
}

bool line_contains_point(line* l, point* p)
{
    if (l->p1 == p || l->p2 == p)
    {
        return false;
    }

    return (l->a * p->x + l->b * p->y == l->c) && l->x_min <= p->x && p->x <= l->x_max && l->y_min <= p->y && p->y <= l->y_max;
}