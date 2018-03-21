#include "obstacle.h"
#include "main.h"

Obstacle::Obstacle(float x, float y, color_t color, float radii, int face, float sp) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radii;
    this->rotateface = face;
    this->xc = x;
    this->yc = y;
    this->collide = 0;
    this->speed = sp;
//    speed = 0.01;
    accn = 0;
    counti = 0;
    speedy = 0;

    GLfloat g_vertex_buffer_data[10000];
    float oct_theta = 0.79, circle_theta = 0.017;
    g_vertex_buffer_data[0] = 0.0f;
    g_vertex_buffer_data[1] = 0.0f;
    g_vertex_buffer_data[2] = 0.0f;
    g_vertex_buffer_data[3] = 0.0f;
    g_vertex_buffer_data[4] = radii;
    g_vertex_buffer_data[5] = 0.0f;
    g_vertex_buffer_data[8] = 0.0f;

    for (int i = 0; i < 1000; i++) {
        if (i == 0) {
            g_vertex_buffer_data[6] = (float) cos(circle_theta) * g_vertex_buffer_data[3] -
                                      (float) sin(circle_theta) * g_vertex_buffer_data[4];
            g_vertex_buffer_data[7] = (float) sin(circle_theta) * g_vertex_buffer_data[3] +
                                      (float) cos(circle_theta) * g_vertex_buffer_data[4];
        } else {
            g_vertex_buffer_data[i * 9] = 0.0f;
            g_vertex_buffer_data[i * 9 + 1] = 0.0f;
            g_vertex_buffer_data[i * 9 + 2] = 0.0f;
            g_vertex_buffer_data[i * 9 + 3] = g_vertex_buffer_data[(i - 1) * 9 + 6];
            g_vertex_buffer_data[i * 9 + 4] = g_vertex_buffer_data[(i - 1) * 9 + 7];
            g_vertex_buffer_data[i * 9 + 5] = 0.0f;
            g_vertex_buffer_data[i * 9 + 6] = (float) cos(circle_theta) * g_vertex_buffer_data[i * 9 + 3] -
                                              (float) sin(circle_theta) * g_vertex_buffer_data[i * 9 + 4];
            g_vertex_buffer_data[i * 9 + 7] = (float) sin(circle_theta) * g_vertex_buffer_data[i * 9 + 3] +
                                              (float) cos(circle_theta) * g_vertex_buffer_data[i * 9 + 4];
            g_vertex_buffer_data[i * 9 + 8] = 0.0f;
        }
    }


    this->object = create3DObject(GL_TRIANGLES, 3000, g_vertex_buffer_data, color, GL_FILL);
}

void Obstacle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Obstacle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Obstacle::tick() {
    this->position.x += speed;
    if (this->position.x > 7) {
        this->position.x = static_cast<float>(-7);
        if (this->counti == 0) {
            float yc = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
            this->position.y = yc;
        } else {
            this->position.y = static_cast<float>(this->position.y + 1);
            if (this->position.y >= 3)
                this->position.y = 0;
        }
    }
}

bounding_box_t Obstacle::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = {x, y, 0.4, 0.4};
    return bbox;
}
