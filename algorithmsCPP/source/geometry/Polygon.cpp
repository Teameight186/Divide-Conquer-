#include "Polygon.hpp"


Polygon::Polygon(Vertex * v) : m_v{v}
{
    resize();
}

Polygon::~Polygon()
{
}

Vertex* Polygon::v()
{
    return m_v;
}

int Polygon::size()
{
    return m_size;
}

Point Polygon::point() const
{
    return Point();
}

Edge Polygon::edge()
{
    return Edge(point(), m_v->cw()->point());
}

Vertex* Polygon::cw()
{
    return nullptr;
}

Vertex* Polygon::cww()
{
    return nullptr;
}

Vertex* Polygon::neighbour(int rotation)
{
    return m_v->neighbour(rotation);
}

Vertex* Polygon::advance(int rotation)
{
    return m_v = m_v->neighbour(rotation);
}

Vertex* Polygon::setV(Vertex* ver)
{
    return m_v = ver;
}

Vertex* Polygon::insert(Point& p)
{
    if(m_size++ == 0)
        m_v = new Vertex(p);
    else
        m_v = m_v->insert(new Vertex(p));
    return m_v;
}

void Polygon::remove()
{
    Vertex* v = m_v;
    m_v = (--m_size == 0) ? nullptr : m_v->ccw();
    delete v->remove();
}

Polygon* Polygon::split(Vertex* p)
{
    Vertex* bp = m_v->split(p);
    resize();
    return new Polygon(bp);
}

void Polygon::resize()
{
    if (m_v == nullptr) m_size = 0;
    else{
        Vertex* v = m_v->cw();
        for(m_size = 1; v != m_v; ++m_size, v=v->cw());
    }
}
