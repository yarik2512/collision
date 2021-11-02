#include <iostream>
#include <vector>
#include <typeinfo>
#include <cmath>
#include "TXLib.h"
#include "g2d.h"

#define RECT "4rect"
#define CIRC "4circ"

class entity {
public:
    vec pos, v;

    explicit entity(int x = 0, int y = 0, int vx = 0, int vy = 0) : pos(vec(x, y)), v(vec(vx, vy)) {};

    virtual void move(int t) {
        pos.x += v.x * t;
        pos.y += v.y * t;
    };

    virtual ~entity() = default;
};

class rect : public entity {
public:
    int w, h;

    explicit rect(int x = 0, int y = 0, int vx = 0, int vy = 0, int a = 0, int b = 0) : entity(x, y, vx, vy), w(a),
                                                                                        h(b) {};

    void move(int t) override {
        pos.x += v.x * t;
        pos.y += v.y * t;
        if (pos.x<0 || pos.x + w>txGetExtentX()) v.x = -v.x;
        if (pos.y - h < 0 || pos.y > txGetExtentY()) v.y = -v.y;
    };
};

class circ : public entity {
public:
    int r;

    explicit circ(int x = 0, int y = 0, int vx = 0, int vy = 0, int a = 0) : entity(x, y, vx, vy), r(a) {};

    void move(int t) override {
        pos.x += v.x * t;
        pos.y += v.y * t;
        if (pos.x - r < 0 || pos.x + r > txGetExtentX()) v.x = -v.x;
        if (pos.y - r < 0 || pos.y + r > txGetExtentY()) v.y = -v.y;
    }
};

class scene {
public:
    std::vector<entity *> objs;

    scene() : objs() {};


    static int intersectX(entity *e1, entity *e2) {
        return std::max((std::min(e1->pos.x + dynamic_cast<rect *>(e1)->w, e2->pos.x + dynamic_cast<rect *>(e2)->w) -
                         std::max(e1->pos.x, e2->pos.x)), 0);
    }

    static int intersectY(entity *e1, entity *e2) {
        return std::max((std::min(e1->pos.y, e2->pos.y) -
                         std::max(e1->pos.y - dynamic_cast<rect *>(e1)->h, e2->pos.y - dynamic_cast<rect *>(e2)->h)),
                        0);
    }

    static bool collision(entity *e1, entity *e2) {
        if (!strcmp(typeid(*e1).name(), CIRC) && !strcmp(typeid(*e2).name(), CIRC)) {
            int x1 = e1->pos.x, y1 = e1->pos.y, r1 = dynamic_cast<circ *>(e1)->r, x2 = e2->pos.x, y2 = e2->pos.y, r2 = dynamic_cast<circ *>(e2)->r;
            return vec(x2-x1, y2-y1).l <= (double) r1 + r2;
        }
        if (!strcmp(typeid(*e1).name(), RECT) && !strcmp(typeid(*e2).name(), RECT)) {
            return intersectX(e1, e2) && intersectY(e1, e2);
        }
        if (!strcmp(typeid(*e1).name(), CIRC) && !strcmp(typeid(*e2).name(), RECT)) {
            auto tmp = e1;
            e1 = e2;
            e2 = tmp;
        }
        if (!strcmp(typeid(*e1).name(), RECT) && !strcmp(typeid(*e2).name(), CIRC)) {
            int x1 = e1->pos.x + dynamic_cast<rect *>(e1)->w / 2, y1 =
                    e1->pos.y - dynamic_cast<rect *>(e1)->h / 2;
            int r = dynamic_cast<circ *>(e2)->r;
            line c({x1, y1}, e2->pos);
            line vert(e1->pos, {e1->pos.x, e1->pos.y - dynamic_cast<rect *>(e1)->h});
            line horizon(e1->pos, {e1->pos.x+dynamic_cast<rect *>(e1)->w, e1->pos.y});
            double vertDist = dist(c&vert, {x1, y1});
            double horizonDist = dist(c&horizon, {x1, y1});
            double max = dist(e1->pos, {x1, y1});
//            cout << max << " " << vertDist << " " << horizonDist << std::endl;
//            if (vertDist > max && horizonDist > max) return false;
//            cout << x1 << " " << y1 << " " << e2->pos.x << " " << e2->pos.y << ": " << dist({x1, y1}, e2->pos) << ": " << std::min(vertDist, horizonDist) << ": " << r << std::endl;
            if (dist({x1, y1}, e2->pos) <= std::min(vertDist, horizonDist) + r)
            {
//                cout << x1 << " " << y1 << " " << e2->pos.x << " " << e2->pos.y << std::endl;
                cout << c.a << " " << c.b << " " << c.c << std::endl;
//                cout << e1->pos.x << " " << e1->pos.y << " " << e1->pos.x << " " << e1->pos.y - dynamic_cast<rect *>(e1)->h << " " << e1->pos.x+dynamic_cast<rect *>(e1)->w << " " << e1->pos.y << std::endl;
                cout << vert.a << " " << vert.b << " " << vert.c << std::endl;
                cout << horizon.a << " " << horizon.b << " " << horizon.c << std::endl;
                cout << (c&vert).x << " " << (c&vert).y << " " << (c&horizon).x << " " << (c&horizon).y << std::endl;
                cout << max << " " << vertDist << " " << horizonDist << std::endl;
//                cout << x1 << " " << y1 << " " << e2->pos.x << " " << e2->pos.y << ": " << dist({x1, y1}, e2->pos) << ": " << std::min(vertDist, horizonDist) << ": " << r << std::endl;
            }
            return dist({x1, y1}, e2->pos) <= std::min(vertDist, horizonDist) + r;
        }
    }

    void render() {
        for (auto obj: objs) {
            if (!strcmp(typeid(*obj).name(), RECT)) {
                txSetFillColor(RGB(255, 255, 255));
                txSetColor(RGB(255, 255, 255));
                int x = obj->pos.x;
                int y = obj->pos.y;
                int w = dynamic_cast<rect *>(obj)->w;
                int h = dynamic_cast<rect *>(obj)->h;
                txRectangle(x, txGetExtentY() - y, x + w, txGetExtentY() - y + h);
            } else if (!strcmp(typeid(*obj).name(), CIRC)) {
                txSetFillColor(TX_WHITE);
                txSetColor(TX_WHITE);
                int x = obj->pos.x;
                int y = obj->pos.y;
                int r = dynamic_cast<circ *>(obj)->r;
                txCircle(x, txGetExtentY() - y, r);
            }
        }
    }

    void step(int t) {
        txSetFillColor(TX_BLACK);
        txSetColor(TX_BLACK);
        txRectangle(0, 0, txGetExtentX(), txGetExtentY());
        for (int i = 0; static_cast<unsigned long long int>(i) < objs.size(); i++) {
            auto e1 = objs[static_cast<unsigned long long int>(i)];
            for (int j = i + 1; static_cast<unsigned long long int>(j) < objs.size(); j++) {
                auto e2 = objs[static_cast<unsigned long long int>(j)];
                if (e1 == e2) continue;
                if (collision(e1, e2)) {
                    e1->v.x = 0;
                    e1->v.y = 0;
                    e2->v.x = 0;
                    e2->v.y = 0;
                }
            }
        }
        for (auto obj: objs) {
            obj->move(t);
            if (!strcmp(typeid(*obj).name(), RECT)) {
                txSetFillColor(TX_WHITE);
                txSetColor(TX_WHITE);
                int x = obj->pos.x;
                int y = obj->pos.y;
                int w = dynamic_cast<rect *>(obj)->w;
                int h = dynamic_cast<rect *>(obj)->h;
                txRectangle(x, txGetExtentY() - y, x + w, txGetExtentY() - y + h);
            } else if (!strcmp(typeid(*obj).name(), CIRC)) {
                txSetFillColor(TX_WHITE);
                txSetColor(TX_WHITE);
                int x = obj->pos.x;
                int y = obj->pos.y;
                int r = dynamic_cast<circ *>(obj)->r;
                txCircle(x, txGetExtentY() - y, r);
            }
        }
        txSleep(t);
    }
};

int main() {
    txCreateWindow(1000, 500);

    scene sc;
    sc.objs.push_back(new rect(200, 400, 1, 0, 100, 100));
//    sc.objs.push_back(new rect(800, 200, 1, 1, 100, 100));
//    sc.objs.push_back(new rect(400, 400, 1, 0, 100, 100));
//    sc.objs.push_back(new circ(200, 400, 1, -1, 100));
    sc.objs.push_back(new circ(700, 200, 1, 1, 100));
    sc.render();
    while (true) {
        sc.step(1);
    }

    return 0;
}