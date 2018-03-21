#include "slab1.h"
#include "main.h"

Slab1::Slab1(float x, float y, color_t color, float radii, float face, float sp) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = radii;
    this->rotation = face;
    this->xc = x;
    this->yc = y;
    this->collide = 0;
    this->speed = sp;
//    speed = 0.01;
    accn = 0;
    counti = 0;
    speedy = 0;

    GLfloat g_vertex_buffer_data[10000];

    int i = 0;
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = radii * (sqrtf(2));
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = static_cast<GLfloat>(radii * (sqrtf(2)) + 0.2);
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = -radii * (sqrtf(2));
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = -radii * (sqrtf(2));
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = -static_cast<GLfloat>(radii * (sqrtf(2)) + 0.2);
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = 0;
    g_vertex_buffer_data[i++] = static_cast<GLfloat>(radii * (sqrtf(2)) + 0.2);
    g_vertex_buffer_data[i++] = 0;

    this->object = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data, color, GL_FILL);
}

void Slab1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Slab1::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Slab1::tick() {
    this->position.x += speed;
    if (this->position.x > 7) {
        this->position.x = static_cast<float>(-7);
//        float yc = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3));
//        this->position.y = yc;
        this->position.y = static_cast<float>(this->position.y + 1);
        if (this->position.y >= 3)
            this->position.y = 0;
    }
}

bounding_box_t Slab1::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = {x, y, 0.4, 0.4};
    return bbox;
}
