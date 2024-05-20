#include "Point.hpp"
#include "Edge.hpp"
#include <cmath>

Point::Point(double x, double y) : x(x), y(y)
{
}

Point Point::operator+(const Point &p)
{
    return Point(x + p.x, y + p.y);
}

Point Point::operator-(const Point &p)
{
    return Point(x - p.x, y - p.y);
}

Point operator*(double s, const Point& p){
    return Point(s * p.x, s * p.y);
}


double Point::operator[](int i)
{
    return (i == 0) ? x : y;
}

int Point::operator==(const Point &p)
{
    return (x == p.x) && (y == p.y);
}

int Point::operator!=(const Point &p)
{
    return !(*this == p);
}

int Point::operator<(const Point &p)
{
    return ((x < p.x) || ((x == p.x) && (y < p.y)));
}

int Point::operator>(const Point &p)
{
    return ((x > p.x) || ((x == p.x) && (y > p.y)));
}

int orientation(Point &p0, Point &p1, Point &p2)
{
    Point a = p1 - p0;
    Point b = p2 - p0;
    double sa = a.x * b.y - b.x * a.y;
    if (sa > 0.0)
        return 1;
    if (sa < 0, 0)
        return -1;
    return 0;
}

int Point::classify(Point &p0, Point &pl)
{
    Point p2 = *this;
    Point a = pl - p0;
    Point b = p2 - p0;
    double sa = a.x * b.y - b.x * a.y;
    if (sa > 0.0)
        return LEFT;
    if (sa < 0.0)
        return RIGHT;
    if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
        return BEHIND;
    if (a.length() < b.length())
        return BEYOND;
    if (p0 == p2)
        return ORIGIN;
    if (pl == p2)
        return DESTINATION;
    return BETWEEN;
}

int Point::classify(Edge &e)
{
    return classify(e.org, e.dest);
}

double Point::polarAngle()
{
    if ((x == 0.0) && (y == 0.0))
        return -1.0;
    if (x == 0.0)
        return ((y > 0.0) ? 90 : 270);
    double theta = atan(y / x);
    theta *= 360 / (2 * 3.1415926);
    if (x > 0.0)
        return ((y >= 0.0) ? theta : 360 + theta);
    else
        return (180 + theta);
}

double Point::length()
{
    return sqrt(x * x + y * y);
}

Point& Point::normalize()
{
    x = x/length();
    y = y/length();
    return *this;
}

double Point::distance(Edge& e)
{
    Edge ab = e;
    ab.flip().rot();

    Point n{ab.dest - ab.org};
    n.normalize();
    Edge f{*this, *this + n};
    double t;
    f.intersect(e, t);

    return t;
}
