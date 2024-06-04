#pragma once
#include "Point.hpp"
#include <float.h>
#include "mergeHull.hpp"

double closestPoints(Point s[], int n, Edge &c);
int bottomToTopCmp(Point *a, Point *b);
double cPoints(Point *x[], Point *y[], int n, Edge &c);
void splitY(Point *y[], int n, Point *p, Point *yL[], Point *yR[]);
double checkStrip(Point *y[], int n, Point *p, double delta, Edge &c);

