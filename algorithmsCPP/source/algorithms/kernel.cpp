#include "kernel.hpp"

Polygon *kernel(Polygon &p)
{
    Edge *edges = new Edge[p.size()];
    for (int i = 0; i < p.size(); i++, p.advance(Vertex::CLOCKWISE)){
        edges[i] = p.edge();
        Polygon box;    
        box.insert(Point(-DBL_MAX, -DBL_MAX)); 
        box.insert(Point(-DBL_MAX, DBL_MAX)); 
        box.insert(Point(DBL_MAX, DBL_MAX));
        box.insert(Point(DBL_MAX, -DBL_MAX));
        Polygon *r = halfplaneIntersect(edges, p.size(), box);
        delete edges;
        return r;
    }
}