#include "main.h"

#ifndef SLAB_H
#define SLAB_H


class Slab {
public:
    Slab() {}
    Slab(float x, float y, color_t color, float radii, float face, float sp);
    glm::vec3 position;
    float rotation=0,radius,xc,yc,rotateface;
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
