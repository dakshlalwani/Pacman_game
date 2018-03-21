#include "main.h"

#ifndef BALL_H
#define BALL_H

class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation=0,d=0.0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed,accn,speedy,speedmagnet;
    int counti = 0,flagi = 0,inwater = 0, mleft=0, mright=0, indicate=0, score=0, mageneton=0;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
