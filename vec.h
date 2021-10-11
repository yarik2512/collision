#include <cmath>

class vec
{
public:
    int x, y;
    
    vec (int a = 0, int b = 0) : x(a), y(b) {};

    friend vec operator+(const vec& vec1, const vec& vec2);
    friend vec operator-(const vec& vec1);
    friend vec operator-(const vec& vec1, const vec& vec2);
    friend int operator*(const vec& vec1, const vec& vec2);
};

vec operator+(const vec& vec1, const vec& vec2)
{
    return vec(vec1.x+vec2.x, vec1.y+vec2.y);
}

vec operator-(const vec& vec1)
{
    return vec(-vec1.x, -vec1.y);
}

vec operator-(const vec& vec1, const vec& vec2)
{
    return vec1+(-vec2);
}

int operator*(const vec& vec1, const vec& vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y;
}