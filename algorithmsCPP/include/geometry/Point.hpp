#pragma once

class Edge;

class Point{
public:
    double x;
    double y;

    enum { LEFT, RIGHT, BEYOND, BEHIND, BETWEEN, ORIGIN, DESTINATION };

    Point(double x = 0.0, double y = 0.0);
    Point operator+(const Point&);
    Point operator-(const Point&);
    friend Point operator*(double s, const Point& p);
    double operator[](int);
    int operator==(const Point&);
    int operator!=(const Point&);
    int operator<(const Point&);
    int operator>(const Point&);
    int classify(Point&, Point&);
    int classify(const Edge&);
    double polarAngle();
    double length();
    Point& normalize();
    double distance(Edge &);
};