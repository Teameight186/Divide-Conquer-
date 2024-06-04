#include "mergeHull.hpp"


int leftToRightCmp(Point *a, Point *b)
{
    if (*a < *b) return -1;
    if (*a > *b) return 1;
    return 0;
}

int rightToLeftCmp(Point *a, Point *b){
    return leftToRightCmp(b, a);    
}


Polygon *mergeHull(Point pts[], int n)
{
    Point **p = new (Point*[n]);   
    for (int i = 0; i < n; i++){
        p[i] = &pts[i];
    }
    mergeSort(p, n, leftToRightCmp);
    return mHull(p, n);
}


Polygon *mHull(Point *p[], int n)
{
    if (n == 1) {
        Polygon *q = new Polygon;
        q->insert(*p[0]);
        return q;
    } else {
        int m = n / 2;
        Polygon *L = mHull(p, m);
        Polygon *R = mHull(p+m, n-m);
        return merge(L, R);
    }
}

Vertex *leastVertex(Polygon &p, int (*cmp)(Point*,Point*))
{
    Vertex *bestV = p.v();
    p.advance(Vertex::CLOCKWISE);
    for (int i = 1; i < p.size(); p.advance(Vertex::CLOCKWISE), i++){
        if ((*cmp)(p.v(), bestV) < 0){
            bestV = p.v();
        }
    }
    p.setV(bestV);
    return bestV;
}

void supportingLine(Point &s, Polygon *p, int side)
{
    int rotation = (side == Point::LEFT) ? Vertex::CLOCKWISE : Vertex::COUNTER_CLOCKWISE;
    Vertex *a = p->v();
    Vertex *b = p->neighbour(rotation);
    int c = b->classify(s, *a);
    while ((c == side) || (c == Point::BEYOND) || (c == Point::BETWEEN)) {
        p->advance(rotation);
        a = p->v();
        b = p->neighbour(rotation);
        c = b->classify(s, *a);
    }
}

void bridge(Polygon *L, Polygon *R, Vertex* &vl, Vertex* &vr, int type)
{
    int sides[2] = { Point::LEFT, Point::RIGHT };
    int indx = (type == UPPER) ? 0 : 1;
    do {
        vl = L->v();
        vr = R->v();
        supportingLine(L->point(), R, sides[indx]);
        supportingLine(R->point(), L, sides[1-indx]);
    } while ((vl != L->v()) || (vr != R->v()));
}

Polygon *merge(Polygon *L, Polygon *R)
{
    Vertex *l1, *r1, *l2, *r2;
    Vertex *vl = leastVertex(*L, rightToLeftCmp);
    Vertex *vr = leastVertex(*R, leftToRightCmp);
    bridge(L, R, l1, r1, UPPER);
    L->setV(vl);
    R->setV(vr);
    bridge(L, R, l2, r2, LOWER);
    L->setV(l1);
    L->split(r1);
    R->setV(r2);
    delete R->split(l2);
    return R;
}