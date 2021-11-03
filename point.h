#ifndef COLLISION_POINT_H
#define COLLISION_POINT_H

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

#endif
