#ifndef COLLISION_LINE_H
#define COLLISION_LINE_H

class line {
public:
    double a, b, c;
    line (double x, double y, double z) : a(x), b(y), c(z) {};
    line (double x1, double y1, double x2, double y2)
    {
        if (x1 == x2 && y1 == y2)
        {
            a = b = c = 0;
        }
        else if (x1 == x2)
        {
            b = 0;
            a = 1;
            c = -x1;
        }
        else if (y1 == y2)
        {
            a = 0;
            b = 1;
            c = -y1;
        }
        else {
            b = x1-x2;
            a = y1-y2;
            c = b*y1 - a*x1;
        }
    }
};

#endif
