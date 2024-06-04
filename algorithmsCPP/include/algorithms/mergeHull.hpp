#pragma once
#include "Polygon.hpp"
#include "Sorts.hpp"
#include "Vertex.hpp"

Polygon *mergeHull(Point pts[], int n);
Polygon *mHull(Point *p[], int n);
Vertex *leastVertex(Polygon &p, int (*cmp)(Point*,Point*));
Polygon *merge(Polygon *L, Polygon *R);
void bridge(Polygon *L, Polygon *R, Vertex* &vl, Vertex* &vr, int type);
void supportingLine(Point &s, Polygon *p, int side);
int rightToLeftCmp(Point *a, Point *b);
int leftToRightCmp(Point *a, Point *b);