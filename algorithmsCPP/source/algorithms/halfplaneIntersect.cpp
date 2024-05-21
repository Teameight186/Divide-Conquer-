#include "halfplaneIntersect.hpp"
#define EPSILON2 1E-10

void advance(Polygon &A, Polygon &R, int inside)
{
    A.advance(Vertex::CLOCKWISE);
    if (inside && (R.point() != A.point()))
        R.insert(A.point());
}
bool pointInConvexPolygon(Point &s, Polygon &p)
{
    if (p.size() == 1)
        return s == p.point();
    if (p.size() == 2)
    {
        int c = s.classify(p.edge());
        return ((c == Point::BETWEEN) || (c == Point::ORIGIN) | (c == Point::DESTINATION));
    }

    Vertex *org = p.v();
    for (int i = 0; i < p.size(); i++, p.advance(Vertex::CLOCKWISE))
        if (s.classify(p.edge()) == Point::LEFT)
        {
            p.setV(org);
            return false;
        }
    return true;
}

bool aimsAt(Edge &a, Edge &b, int aclass, int crossType)
{
    Point va = a.dest - a.org;
    Point vb = b.dest - b.org;
    if (crossType != Edge::COLLINEAR) {
        if ((va.x * vb.y) >= (vb.x * va.y))
            return (aclass != Point::RIGHT);
        else
            return (aclass != Point::LEFT);
    } 
    else {
        return (aclass != Point::BEYOND);
    }
}

int crossingPoint(Edge &e, Edge &f, Point &p)
{
    double s, t;
    int classe = e.intersect(f, s);
    if ((classe == Edge::COLLINEAR) || (classe == Edge::PARALLEL))
        return classe;
    double lene = (e.dest - e.org).length();
    if ((s < -EPSILON2 * lene) || (s > 1.0+ EPSILON2 * lene))
        return Edge::SCEW_NO_CROSS;
    f.intersect(e, t);
    double lenf = (f.org - f.dest).length();
    if ((-EPSILON2 * lenf <= t) && (t <= 1.0 + EPSILON2 * lenf))
    {
        if (t <= EPSILON2 * lenf)
            p = f.org;
        else if (t >= 1.0 - EPSILON2 * lenf)
            p = f.dest;
        else if (s <= EPSILON2 * lene)
            p = e.org;
        else if (s >= 1.0 - EPSILON2 * lene)
            p = e.dest;
        else
            p = f.point(t);
        return Edge::SCEW_CROSS;
    }
    else
        return Edge::SCEW_NO_CROSS;
}

bool clipPolygonToEdge(Polygon &s, Edge &e, Polygon *&result)
{
    Polygon *p = new Polygon;
    Point crossingPt;
    for (int i = 0; i < s.size(); s.advance(Vertex::CLOCKWISE), ++i)
    {
        Point org = s.point();
        Point dest = s.cw()->point();
        int orgIsInside = (org.classify(e) != Point::LEFT);
        int destIsInside = (dest.classify(e) != Point::LEFT);
        if (orgIsInside != destIsInside)
        {
            double t;
            e.intersect(s.edge(), t);
            crossingPt = e.point(t);
        }
        else if (orgIsInside && !destIsInside)
        {
            if (org != crossingPt)
                p->insert(crossingPt);
        }
        else if (orgIsInside && !destIsInside);
        else
        {
            p->insert(crossingPt);
            if (dest != crossingPt)
                p->insert(dest);
        }
    }
    result = p;
    return (p->size() > 0);
}

Polygon* convexPolygonIntersect(Polygon &P, Polygon &Q)
{
    Polygon *R;
    Point iPnt, startPnt;
    int inflag = UNKNOWN;
    int phase = 1;
    int maxItns = 2 * (P.size() + Q.size());
    for (int i = 1; (i <= maxItns || phase == 2); ++i)
    {
        Edge p = P.edge();
        Edge q = Q.edge();
        int pclass = p.dest.classify(q);
        int qclass = q.dest.classify(p);
        int crossType = crossingPoint(p, q, iPnt);
        if (crossType == Edge::SCEW_CROSS)
        {
            if (phase == 1)
            {
                phase = 2;
                R = new Polygon;
                R->insert(iPnt);
                startPnt = iPnt;
            }
            else if (iPnt != R->point())
            {
                if (iPnt != startPnt)
                    R->insert(iPnt);
                else
                    return R;
            }
            if (pclass == Point::RIGHT)
                inflag = P_IS_INSIDE;
            else if (qclass == Point::RIGHT)
                inflag = Q_IS_INSIDE;
            else
                inflag = UNKNOWN;
        }
        else if (crossType == Edge::COLLINEAR && pclass != Point::BEHIND && qclass != Point::BEHIND)
        {
            inflag = UNKNOWN;
        }
        bool pAIMSq = aimsAt(p, q, pclass, crossType);
        bool qAIMSp = aimsAt(q, p, pclass, crossType);
        if (pAIMSq && qAIMSp)
        {
            if ((inflag == Q_IS_INSIDE) || ((inflag == UNKNOWN) && (pclass == Point::LEFT)))
                advance(P, *R, false);
            else
                advance(Q, *R, false);
        }
        else if (pAIMSq)
        {
            advance(P, *R, inflag == P_IS_INSIDE);
        }
        else if (qAIMSp)
        {
            advance(Q, *R, inflag == Q_IS_INSIDE);
        }
        else
        {
            if ((inflag == Q_IS_INSIDE) || (inflag == UNKNOWN && pclass == Point::LEFT))
                advance(P, *R, false);
            else
            {
                advance(Q, *R, false);
            }
        }
    }
    Point pp = P.point();
    Point qp = Q.point();
    if (pointInConvexPolygon(pp, Q))
        return new Polygon(P);
    else if (pointInConvexPolygon(qp, P))
        return new Polygon(Q);
    return new Polygon;
}

Polygon *halfplaneIntersect(Edge H[], int n, Polygon &box)
{
    Polygon *c;
    if (n == 1)
        clipPolygonToEdge(box, H[0], c);
    else
    {
        int m = n / 2;
        Polygon *a = halfplaneIntersect(H, m, box);
        Polygon *b = halfplaneIntersect(H + m, n - m, box);
        c = convexPolygonIntersect(*a, *b);
        delete a;
        delete b;
    }
    return c;
}