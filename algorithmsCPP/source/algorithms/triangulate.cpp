#include "triangulate.hpp"

List<Polygon*> *triangulate(Polygon &p){
    List<Polygon*> *triangles = new List<Polygon*>;
    if (p.size() == 3){
        triangles->append(&p);
    }
    else {
        findConvexVertex(p);
        Vertex *d = findIntrudingvertex(p);
        if (d == nullptr) {    
            Vertex *c = p.neighbour(Vertex::CLOCKWISE);
            p.advance(Vertex::COUNTER_CLOCKWISE);
            Polygon *q = p.split(c);
            triangles->append(triangulate(p));
            triangles->append(q);
        } else { 
            Polygon *q = p.split(d);
            triangles->append(triangulate(*q));
            triangles->append(triangulate(p));
        }
    }
    return triangles;
}

void findConvexVertex(Polygon &p){
    Vertex *a = p.neighbour(Vertex::COUNTER_CLOCKWISE);
    Vertex *b = p.v();
    Vertex *c = p.neighbour(Vertex::CLOCKWISE);
    while (c->classify(*a, *b) != Point::RIGHT) {
        a = b;
        b = p.advance(Vertex::CLOCKWISE);
        c = p.neighbour(Vertex::CLOCKWISE);
    }
}

Vertex *findIntrudingvertex(Polygon &p)
{
    Vertex *a = p.neighbour(Vertex::COUNTER_CLOCKWISE);
    Vertex *b = p.v();
    Vertex *c = p.advance(Vertex::CLOCKWISE);
    Vertex *d = nullptr; 
    double bestD = -1.0; // distance to best candidate
    Edge ca(c->point(), a->point());
    Vertex *v = p.advance(Vertex::CLOCKWISE);
    while (v != a) {
        if (pointInTriangle(*v, *a, *b, *c)) {
            double dist = v->distance(ca);
            if (dist > bestD) {
                d = v;
                bestD = dist;
            }
        }
        v = p.advance(Vertex::CLOCKWISE);
    }
    p.setV (b);
    return d;
}

bool pointInTriangle(Point p, Point a, Point b, Point c){
    return ((p.classify(a, b) != Point::LEFT) && (p.classify(b, c) != Point::LEFT) && (p.classify(c, a) != Point::LEFT));
}