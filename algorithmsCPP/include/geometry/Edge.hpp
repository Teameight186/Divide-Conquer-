#pragma once

#include "Point.hpp"

class Edge
{
public:
    Point org;
    Point dest;
    enum {
        COLLINEAR,
        PARALLEL,
        SCEW,
        SCEW_CROSS,
        SCEW_NO_CROSS
    };
public:
    Edge(const Point& org, const Point& dest);
    Edge();
    Edge& rot();
    Edge& flip();
    Point point(double);
    int intersect(Edge &, double &);
    int cross(Edge &, double &);
    bool isVertical();
    double slope();
    double y(double);
};