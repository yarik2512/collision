#ifndef COLLISION_LINE_H
#define COLLISION_LINE_H

class line {
public:
    int a, b, c;

    line(int x, int y, int z) : a(x), b(y), c(z) {};

    line(int x1, int y1, int x2, int y2) : a(y2 - y1), b(x1 - x2), c((x2 - x1) * y1 - (y2 - y1) * x1) {
        if (x1 == x2 && y1 == y2) {
            a = b = c = 0;
        } else if (x1 == x2) {
            b = 0;
            a = 1;
            c = -x1;
        } else if (y1 == y2) {
            a = 0;
            b = 1;
            c = -y1;
        }
    }

    line(point p1, point p2) : a(p2.y - p1.y), b(p1.x - p2.x), c((p2.x - p1.x) * p1.y - (p2.y - p1.y) * p1.x) {
        if (p1.x == p2.x && p1.y == p2.y) {
            a = b = c = 0;
        } else if (p1.x == p2.x) {
            b = 0;
            a = 1;
            c = -p1.x;
        } else if (p1.y == p2.y) {
            a = 0;
            b = 1;
            c = -p1.y;
        }
    }

    friend point operator&(const line &a, const line &b);
};

point operator&(const line &a, const line &b) {
    if (a.a * b.b == b.a * a.b) return {};
    else
        return {-(a.c * b.b - b.c * a.b) / (a.a * b.b - b.a * a.b), -(a.a * b.c - b.a * a.c) / (a.a * b.b - b.a * a.b)};
}

#endif //COLLISION_LINE_H
