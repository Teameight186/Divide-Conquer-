#pragma once
#include "Vertex.hpp"
#include "Edge.hpp"

class Polygon{
public:
    Polygon() = default;
    Polygon(const Polygon& p) = delete;
    Polygon(Vertex*);
    ~Polygon();
    Vertex* v();
    int size();
    Point point() const;
    Edge edge();
    Vertex* cw();
    Vertex* cww();
    Vertex* neighbour(int rotation);
    Vertex* advance(int rotation);
    Vertex* setV(Vertex*);
    Vertex* insert(Point&);
    void remove();
    Polygon* split(Vertex*);
private:
    void resize();
public:
    Vertex* m_v = nullptr;
    int m_size{0};
};