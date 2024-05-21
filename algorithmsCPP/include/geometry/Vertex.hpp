#pragma once

#include "Node.hpp"
#include "Point.hpp"

class Polygon;

class Vertex: public Node, public Point{
public:

    enum{
        CLOCKWISE,
        COUNTER_CLOCKWISE
    };
    Vertex(double x, double y);
    Vertex(const Point&);
    Vertex* cw();
    Vertex* ccw();
    Vertex* neighbour(int rotation);
    Point point() const;
    Vertex* insert(Vertex*);
    Vertex* remove();
    void splice(Vertex* b);
    Vertex* split(Vertex* b);
    friend class Polygon;
};