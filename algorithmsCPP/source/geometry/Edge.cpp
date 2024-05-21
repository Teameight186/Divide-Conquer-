#include "Edge.hpp"
#include <float.h>

double dotProduct(const Point& a, const Point& b){
    return a.x*b.x + a.y*b.y;
}

Edge::Edge(const Point& org, const Point& dest) : org(org), dest(dest)
{
}

Edge::Edge():
    org(Point(0, 0)),
    dest(Point(1, 0))
{
}

Edge& Edge::rot()
{
    Point m = 0.5 * (org + dest);
    Point v = dest - org;
    Point n{v.y, -v.x};
    org = m - 0.5*n;
    dest = m + 0.5*n;
    return *this;
}

Edge& Edge::flip()
{
    return rot().rot();
}

Point Edge::point(double t)
{
    return Point(org + t*(dest-org));
}

int Edge::intersect(const Edge& e, double& t)
{
    Point a = org;
    Point b = dest;
    Point c = e.org;
    Point d = e.dest;
    Point n = Point((d-c).y, (c-d).x);
    double denom = dotProduct(n, b-a);
    if(denom == 0.0){
        int aclass = org.classify(e);
        if (aclass == Point::LEFT || aclass == Point::RIGHT)
            return PARALLEL;
        else
            return COLLINEAR;
    } 
    double num = dotProduct(n, a-c);
    t = -num/denom;
    return SCEW;
}

int Edge::cross(Edge& e, double& t)
{
    double s;
    int crossType = e.intersect(*this, s);
    if( crossType == COLLINEAR || crossType == PARALLEL)
        return crossType;
    if( (s< 0.0) || (s > 1.0))
        return SCEW_NO_CROSS;
    intersect(e, t);
    if( (0.0 <= t) && (t <= 1.0))
        return SCEW_CROSS;
    else
        return SCEW_NO_CROSS;
}

bool Edge::isVertical()
{
    return org.x == dest.x;
}

double Edge::slope()
{
    if(org.x != dest.x)
        return (dest.y - org.y) / (dest.x - org.x);
    return DBL_MAX;
}

double Edge::y(double x)
{
    return slope()*(x-org.x) + org.y;
}
