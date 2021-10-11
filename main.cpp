#include <iostream>
#include <cmath>
#include <vector>
#include "vec.h"
#include "TXLib.h"

class entity
{
public:
    vec pos, v;

    entity (int x = 0, int y = 0, int vx = 0, int vy = 0) : pos(vec(x,y)), v(vec(vx, vy)) {};

    virtual ~entity() {};
    virtual int intersectX(entity* r) = 0;
    virtual int intersectY(entity* r) = 0;
    virtual bool collision(entity* r) = 0;
    virtual void move () = 0;
};

class rect : public entity
{
public:
    int w, h;

    rect (int x = 0, int y = 0, int vx = 0, int vy = 0, int a = 0, int b = 0) : entity(x, y, vx, vy), w(a), h(b) {};

    int intersectX (entity* r) override
    {
        return std::max((std::min(pos.x+w, r->pos.x+dynamic_cast<rect*>(r)->w) - std::max(pos.x, r->pos.x)), 0);
    }
    int intersectY (entity* r) override
    {
        return std::max((std::min(pos.y, r->pos.y) - std::max(pos.y-h, r->pos.y-dynamic_cast<rect*>(r)->h)), 0);
    }
    bool collision (entity* r) override
    {
        return intersectX(r) && intersectY(r);
    }
    void move () override
    {
        pos.x += v.x;
        pos.y += v.y;
    }
};

class scene
{
public:
    std::vector<entity*> objs;

    scene() :objs() {};

    void render ()
    {
        for (auto obj : objs)
        {
            txSetFillColor(RGB(255, 255, 255));
            txSetColor(RGB(255, 255, 255));
            int x = obj->pos.x;
            int y = obj->pos.y;
            int w = dynamic_cast<rect*>(obj)->w;
            int h = dynamic_cast<rect*>(obj)->h;
            txRectangle(x, y, x+w, y-h);
        }
    }

    void step ()
    {
        for (auto obj : objs)
        {
            txSetFillColor(RGB(0, 0, 0));
            txSetColor(RGB(0, 0, 0));
            int x = obj->pos.x;
            int y = obj->pos.y;
            int w = dynamic_cast<rect*>(obj)->w;
            int h = dynamic_cast<rect*>(obj)->h;
            txRectangle(x, y, x+w, y-h);
            obj->move();
            txSetFillColor(RGB(255, 255, 255));
            txSetColor(RGB(255, 255, 255));
            x = obj->pos.x;
            y = obj->pos.y;
            w = dynamic_cast<rect*>(obj)->w;
            h = dynamic_cast<rect*>(obj)->h;
            txRectangle(x, y, x+w, y-h);
        }
    }
};

int main ()
{
    txCreateWindow(1000, 500);

    scene sc;
    sc.objs.push_back(new rect (3, 4, 10, 20, 100, 200));
    sc.render();
    while (true)
    {
        sc.step();
        txSleep(100);
    }

    return 0;
}