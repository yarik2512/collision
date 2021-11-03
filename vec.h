#ifndef COLLISION_VEC_H
#define COLLISION_VEC_H

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

#endif
