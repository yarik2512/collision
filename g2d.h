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

    friend double cos(vec v1, vec v2);

    friend double sin(vec v1, vec v2);

    bool isNull();
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

bool vec::isNull() {
    return x == 0 && y == 0;
}

double cos(vec v1, vec v2) {
    if (v1.isNull() || v2.isNull()) return 0;
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

#endif
