#include "List.hpp"
#include "Polygon.hpp"

List<Polygon*> *triangulate(Polygon &p);
void findConvexVertex(Polygon &p);
Vertex *findIntrudingvertex(Polygon &p);
bool pointInTriangle(Point p, Point a, Point b, Point c);