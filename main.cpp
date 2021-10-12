#include <iostream>
#include <vector>
#include "vec.h"
#include "TXLib.h"

class entity {
public:
    vec pos, v;

    entity(int x = 0, int y = 0, int vx = 0, int vy = 0) : pos(vec(x, y)), v(vec(vx, vy)) {};

    virtual ~entity() {};

    virtual void move() = 0;
};

class rect : public entity {
public:
    int w, h;

    rect(int x = 0, int y = 0, int vx = 0, int vy = 0, int a = 0, int b = 0) : entity(x, y, vx, vy), w(a), h(b) {};

    void move() override {
        pos.x += v.x;
        pos.y += v.y;
    }
};

class scene {
public:
    std::vector<entity *> objs;

    scene() : objs() {};


    int intersectX(entity *e1, entity *e2) {
        return std::max((std::min(e1->pos.x + dynamic_cast<rect *>(e1)->w, e2->pos.x + dynamic_cast<rect *>(e2)->w) -
                         std::max(e1->pos.x, e2->pos.x)), 0);
    }

    int intersectY(entity *e1, entity *e2) {
        return std::max((std::min(e1->pos.y, e2->pos.y) -
                         std::max(e1->pos.y - dynamic_cast<rect *>(e1)->h, e2->pos.y - dynamic_cast<rect *>(e2)->h)),
                        0);
    }

    bool collision(entity *e1, entity *e2) {
        return intersectX(e1, e2) && intersectY(e1, e2);
    }

    void render() {
        for (auto obj: objs) {
            txSetFillColor(RGB(255, 255, 255));
            txSetColor(RGB(255, 255, 255));
            int x = obj->pos.x;
            int y = obj->pos.y;
            int w = dynamic_cast<rect *>(obj)->w;
            int h = dynamic_cast<rect *>(obj)->h;
            txRectangle(x, txGetExtentY() - y, x + w, txGetExtentY() - y + h);
        }
    }

    void step() {
        txSetFillColor(TX_BLACK);
        txSetColor(TX_BLACK);
        txRectangle(0, 0, txGetExtentX(), txGetExtentY());
        for (int i = 0; static_cast<unsigned long long int>(i) < objs.size(); i++) {
            auto e1 = objs[static_cast<unsigned long long int>(i)];
            for (int j = i + 1; static_cast<unsigned long long int>(j) < objs.size(); j++) {
                auto e2 = objs[static_cast<unsigned long long int>(j)];
                if (e1 == e2) continue;
                if (collision(e1, e2)) {
                    int x1 = e1->v.x, x2 = e2->v.x, y1 = e1->v.y, y2 = e2->v.y;
                    cout << x1 << " " << y1 << "; " << x2 << " " << y2 << std::endl;
                    e1->v.x = ((x1 > 0 && x2 > 0) || (x1 < 0 && x2 < 0) ? std::abs(x2) * x1 / std::abs(x1) :
                               -std::abs(x2) * x1 / std::abs(x1));
                    e1->v.y = ((y1 > 0 && y2 > 0) || (y1 < 0 && y2 < 0) ? std::abs(y2) * y1 / std::abs(y1) :
                               -std::abs(y2) * y1 / std::abs(y1));
                    e2->v.x = ((x1 > 0 && x2 > 0) || (x1 < 0 && x2 < 0) ? std::abs(x1) * x2 / std::abs(x2) :
                               -std::abs(x1) * x2 / std::abs(x2));
                    e2->v.y = ((y1 > 0 && y2 > 0) || (y1 < 0 && y2 < 0) ? std::abs(y1) * y2 / std::abs(y2) :
                               -std::abs(y1) * y2 / std::abs(y2));
                    cout << e1->v.x << " " << e1->v.y << "; " << e2->v.x << " " << e2->v.y << std::endl;
                }
            }
        }
        for (auto obj: objs) {
            obj->move();
            txSetFillColor(TX_WHITE);
            txSetColor(TX_WHITE);
            int x = obj->pos.x;
            int y = obj->pos.y;
            int w = dynamic_cast<rect *>(obj)->w;
            int h = dynamic_cast<rect *>(obj)->h;
            txRectangle(x, txGetExtentY() - y, x + w, txGetExtentY() - y + h);
        }
    }
};

int main() {
    txCreateWindow(1000, 500);

    scene sc;
    sc.objs.push_back(new rect(3, 400, 10, -5, 100, 200));
    sc.objs.push_back(new rect(800, 300, -13, -5, 100, 200));
    sc.objs.push_back(new rect (700, 5, -10, 12, 100, 200));
    sc.objs.push_back(new rect (800, 700, -13, -15, 100, 200));
    sc.render();
    while (true) {
        sc.step();
        txSleep(100);
    }

    return 0;
}