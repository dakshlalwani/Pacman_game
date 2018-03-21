#include "main.h"

#ifndef SLAB1_H
#define SLAB1_H


class Slab1 {
public:
    Slab1() {}
    Slab1(float x, float y, color_t color, float radii, float face, float sp);
    glm::vec3 position;
    float rotation=0,radius,xc,yc;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,accn,speedy;
    int counti = 0, collide=0;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
