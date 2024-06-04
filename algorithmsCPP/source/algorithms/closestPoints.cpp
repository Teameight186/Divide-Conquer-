#include "closestPoints.hpp"

double closestPoints(Point s[], int n, Edge &c)
{
    Point **x = new (Point*[n]);
    Point **y = new (Point*[n]);
    for (int i = 0; i < n; i++){
        x[i] = y[i] =&s[i];
    }
    mergeSort(x, n, leftToRightCmp);
    mergeSort(y, n, bottomToTopCmp);
    return cPoints(x, y, n, c);
}

int bottomToTopCmp(Point *a, Point *b){

    if ((a->y<b->y) || ((a->y==b->y) && (a->x<b->x))){
        return -1;
    }
    else if ((a->y>b->y) || ((a->y==b->y) && (a->x>b->x))){
        return 1;
    }
    return 0;
}


double cPoints(Point *x[], Point *y[], int n, Edge &c)
{
    if (n == 1){
        return DBL_MAX;
    }
    else{
        int m = n / 2;
        Point **yL = new (Point*[m]);
        Point **yR = new (Point*[n-m]);
        splitY(y, n, x[m], yL, yR);
        Edge a, b;
        double deltaL = cPoints(x, yL, m, a);
        double deltaR = cPoints(x+m, yR, n-m, b);
        delete yL;
        delete yR;
        double delta;
        if (deltaL < deltaR) {
            delta = deltaL;
            c = a;
        } 
        else {
            delta = deltaR;
            c = b;
        }
        return checkStrip(y, n, x[m], delta, c);
    }
}

void splitY(Point *y[], int n, Point *p, Point *yL[], Point *yR[])
{
    int i, lindx, rindx;
    i = lindx = rindx = 0;
    while (i < n){
        if (*y[i] < *p){    
            yL[lindx++] = y[i++];
        }
        else{
            yR[rindx++] = y[i++];
        }
    }
}

double checkStrip(Point *y[], int n, Point *p, double delta, Edge &c)
{
    int i, striplen;
    Point *s = new Point[n];
    for (i = striplen = 0; i < n; i++){
        if ((p->x - delta < y[i]->x) && (y[i]->x < p->x + delta)){
            s[striplen++] = *y[i];
        }
    }
    for (i = 0; i < striplen; i++){
        for (int j = i+1; j < striplen; j++){
            if (s[j].y - s[i].y > delta){
                break;
            }
            if ((s[i] - s[j]).length() < delta){
                delta = (s[i] - s[j]).length()  ;
                c = Edge(s[i], s[j]);
            }
        }  
    }
    delete s;
    return delta;
}