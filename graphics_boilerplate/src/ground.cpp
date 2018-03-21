#include "ground.h"
#include "main.h"

Ground::Ground(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);

    static const GLfloat vertex_buffer_data[] = {
            -100, -4, 0, // vertex 1
            100, -4, 0, // vertex 2
            100, static_cast<const GLfloat>(-1.5), 0, // vertex 3

            100, static_cast<const GLfloat>(-1.5), 0, // vertex 3
            -100, static_cast<const GLfloat>(-1.5), 0, // vertex 4
            -100, -4, 0 // vertex 1
    };


    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ground::tick() {
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

bounding_box_t Ground::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = {x, y, 0.7, 0.7};
    return bbox;
}
