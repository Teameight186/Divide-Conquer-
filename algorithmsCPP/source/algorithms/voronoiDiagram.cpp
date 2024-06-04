#include "voronoiDiagram.hpp"

Polygon *voronoiRegion(Point &p, Point s[], int n, Polygon &box)
{
    Edge *edges = new Edge[n];
    for (int i = 0; i < n; i++) {
        edges[i] = Edge(p, s[i]);
        edges[i].rot();
    }
    Polygon *r = halfplaneIntersect(edges, n, box);
    delete edges;
    return r;
}

List<Polygon*> *voronoiDiagram(Point s[], int n, Polygon &box){
    List<Polygon*> *regions = new List<Polygon*>;
    for (int i = 0; i < n; i++) {
        Point p = s[i];
        s[i] = s[n-1];
        regions->append(voronoiRegion(p, s, n-1, box));
        s[i] = p;
    }   
    return regions; 
}