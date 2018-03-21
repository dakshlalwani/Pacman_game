#include "main.h"

#ifndef MAGNETSTAND_H
#define MAGNETSTAND_H


class Magnetstand {
public:
    Magnetstand() {}
    Magnetstand(float x, float y, color_t color);
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

#endif // MAGNETSTAND_H
