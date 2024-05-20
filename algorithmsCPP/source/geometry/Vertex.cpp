#include "Vertex.hpp"
Vertex::Vertex(double x, double y): Point(x,y){

}

Vertex::Vertex(const Point& point): Point(point){

}

Vertex *Vertex::cw()
{
    return reinterpret_cast<Vertex*>(m_next);
}

Vertex *Vertex::ccw()
{
    return reinterpret_cast<Vertex*>(m_prev);
}

Vertex *Vertex::neighbour(int rotation)
{
    return (rotation == Vertex::CLOCKWISE) ? cw() : ccw();
}

Point Vertex::point() const //могут быть траблы, говнокод от методички, либо думать самому, либо никак
{
    return *((Point*)(this));
}

Vertex* Vertex::insert(Vertex* v)
{
    return reinterpret_cast<Vertex*>(Node::insert(v));
}

Vertex* Vertex::remove()
{
    return reinterpret_cast<Vertex*>(Node::remove());
}

void Vertex::splice(Vertex* b)
{
    Node::splice(b);
}

Vertex *Vertex::split(Vertex* b)
{
    Vertex* bp = b->ccw()->insert(new Vertex(b->point()));
    insert(new Vertex(point()));
    splice(bp);
    return bp;
}
