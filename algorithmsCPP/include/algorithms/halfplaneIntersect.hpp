#pragma once
#include "Polygon.hpp"
enum {
    UNKNOWN,
    P_IS_INSIDE,
    Q_IS_INSIDE
};

Polygon* halfplaneIntersect(Edge H[], int n, Polygon& box);