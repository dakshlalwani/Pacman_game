#include "main.h"

#ifndef POOL_H
#define POOL_H


class Pool {
public:
    Pool() {}
    Pool(float x, float y, color_t color);
    glm::vec3 position;
    float rotation=0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,accn,speedy;
    int counti = 0,flagi = 0;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
