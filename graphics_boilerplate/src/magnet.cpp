#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    GLfloat g_vertex_buffer_data[10000];
    float oct_theta = 0.79, circle_theta = 0.017;
    g_vertex_buffer_data[0] = 0.0f;
    g_vertex_buffer_data[1] = 0.0f;
    g_vertex_buffer_data[2] = 0.0f;
    g_vertex_buffer_data[3] = 0.0f;
    g_vertex_buffer_data[4] = 0.6f;
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


    this->object = create3DObject(GL_TRIANGLES, 555, g_vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->speedy -= this->accn;
    // this->position.y += this->speedy;
    //    this->position.x -= speed;
    //    if (this->position.y<=0)
    //    {
    //    	this->counti = 0;
    //    	this->position.y=0;
    //    	this->speedy=0;
    //    }

    // this->position.y -= speed;
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = {x, y, 0.7, 0.7};
    return bbox;
}
