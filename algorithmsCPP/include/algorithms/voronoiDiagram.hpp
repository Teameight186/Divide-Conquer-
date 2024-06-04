#pragma once
#include "Polygon.hpp"
#include "List.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "halfplaneIntersect.hpp"

Polygon* voronoiDiagram(Polygon& box);
Polygon *voronoiRegion(Point &p, Point s[], int n, Polygon &box);