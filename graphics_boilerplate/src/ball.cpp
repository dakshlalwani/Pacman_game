#include <tgmath.h>
#include "ball.h"
#include "pool.h"
#include "main.h"
#include "trampoline.h"

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->inwater = 0;
//    speed = 0;
    accn = 0;
    counti = 0;
    flagi = 0;
    speedy = 0;

    GLfloat g_vertex_buffer_data[10000];
    float oct_theta = 0.79, circle_theta = 0.017;
    g_vertex_buffer_data[0] = 0.0f;
    g_vertex_buffer_data[1] = 0.0f;
    g_vertex_buffer_data[2] = 0.0f;
    g_vertex_buffer_data[3] = 0.0f;
    g_vertex_buffer_data[4] = 0.2f;
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

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    if (this->inwater == 0 || this->counti == 1) {
        if (this->mleft) {
            if (this->inwater == 0 && this->position.y >= -0.85 && this->indicate == 0) {
                this->speed = 0.04;
            } else if (this->indicate == 0) {
                this->speed = 0.01;
            }
        } else if (this->mright) {
            if (this->inwater == 0 && this->position.y >= -0.85 && this->indicate == 0) {
                this->speed = -0.04;
            } else if (this->indicate == 0) {
                this->speed = -0.01;
            }
        }
        this->speedy -= this->accn;
        this->position.y += this->speedy;
        this->position.x -= this->speed;
    }
    if (this->position.y >= 1.6 && this->position.y <= 3 && this->mageneton == 1 && this->position.x >= -3.5) {
//        printf("%f=======speed\n",this->speed);
        this->mright=0;
        if (this->speed >= 0)
            this->speed = 0.05;
        else if (this->speed < 0)
            this->speed = 0.05;
        this->indicate = 0;
        this->position.x -= this->speed;
    }
    if (this->position.y <=
        static_cast<float>((sqrt(std::fabs(1 - (this->position.x * this->position.x))) * (-1)) - 0.8)) {

        this->position.y = static_cast<float>((sqrt(std::fabs(1 - (this->position.x * this->position.x))) * (-1)) -
                                              0.8);
        this->counti = 0;
    }
    if (this->position.y <= -0.8 && (this->position.x <= -1 || this->position.x >= 1)) {
        this->counti = 0;
        this->position.y = static_cast<float>(-0.8);
        this->inwater = 0;
    }
    if (this->position.y < -0.8 && this->inwater == 1 && this->counti == 0) {
        if (this->mleft) {
            this->indicate = 1;
            if (this->inwater == 0 && this->position.y >= -0.85) {
                this->speed = 0.04;
            } else {
                this->speed = 0.01;
            }
        } else if (this->mright) {
            this->indicate = 2;
            if (this->inwater == 0 && this->position.y >= -0.85) {
                this->speed = -0.04;
            } else {
                this->speed = -0.01;
            }
        }
        this->accn = 0.0015;
        this->speedy = -0.05;
        this->speedy -= this->accn;
        this->position.y += this->speedy;
        this->position.x -= this->speed;
//        this->speed=0;
        if (this->position.y <=
            static_cast<float>((sqrt(std::fabs(1 - (this->position.x * this->position.x))) * (-1)) - 0.8)) {
            this->position.y = static_cast<float>((sqrt(std::fabs(1 - (this->position.x * this->position.x))) * (-1)) -
                                                  0.8);
        }
    }
    if (this->counti == 0)
        this->speed = 0;
    if (counti == 0) {
        this->mright = 0;
        this->mleft = 0;
    }
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = {x, y, 0.4, 0.4};
    return bbox;
}
