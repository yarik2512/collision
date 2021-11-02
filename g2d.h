#ifndef COLLISION_G2D_H
#define COLLISION_G2D_H

#include <limits>
#include <cmath>

#define INF 100000

class vec {
public:
    int x, y;
    double l;

    vec() : x(0), y(0), l(0) {};

    vec(int a, int b) : x(a), y(b), l(sqrt(a * a + b * b)) {};

    friend vec operator+(const vec &vec1, const vec &vec2);

    friend vec operator-(const vec &vec1);

    friend vec operator-(const vec &vec1, const vec &vec2);

    friend int operator*(const vec &vec1, const vec &vec2);
};

vec operator+(const vec &vec1, const vec &vec2) {
    return {vec1.x + vec2.x, vec1.y + vec2.y};
}

vec operator-(const vec &vec1) {
    return {-vec1.x, -vec1.y};
}

vec operator-(const vec &vec1, const vec &vec2) {
    return vec1 + (-vec2);
}

int operator*(const vec &vec1, const vec &vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

double cos(vec v1, vec v2) {
    if (v1.l == 0 || v2.l == 0) return 0;
    return v1 * v2 / (v1.l * v2.l);
}

double sin(vec v1, vec v2) {
    return sqrt(1 - cos(v1, v2) * cos(v1, v2));
}

class point {
public:
    int x, y;

    point() : x(INF), y(INF) {};

    point(int a, int b) : x(a), y(b) {};

    point(vec a) : x(a.x), y(a.y) {};

    friend double dist(point a, point b);
};

double dist(point a, point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

class line {
public:
    int a, b, c;

    line(int x, int y, int z) : a(x), b(y), c(z) {};

    line(int x1, int y1, int x2, int y2) {
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
        } else {
            b = x2 - x1;
            a = y2 - y1;
            c = b * y1 - a * x1;
            b = -b;
        }
    }

    line(point p1, point p2) {
        int x1 = p1.x, y1 = p1.y;
        int x2 = p2.x, y2 = p2.y;
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
        } else {
            b = x2 - x1;
            a = y2 - y1;
            c = b * y1 - a * x1;
            b = -b;
        }
    }

    friend point operator&(const line &a, const line &b);
};

point operator&(const line &a, const line &b) {
    int A1 = a.a, B1 = a.b, C1 = a.c, A2 = b.a, B2 = b.b, C2 = b.c;
    if (A1 * B2 == A2 * B1) return {};
    else return {-(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1), -(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1)};
}

#endif
