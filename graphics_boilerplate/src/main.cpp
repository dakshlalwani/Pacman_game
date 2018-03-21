#include "main.h"

#include <cmath>
#include "timer.h"
#include "ball.h"
#include "obstacle.h"
#include "ground.h"
#include "grass.h"
#include "pool.h"
#include "trampoline.h"
#include "stand.h"
#include "spike.h"
#include "magnet.h"
#include "magnetstand.h"
#include "slab.h"
#include "slab1.h"

//#include <GL/glut.h>

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Obstacle obstacle[160];
Slab slab1;
Slab1 slab2, slab3;
Obstacle obstacle1, obstacle2, obstacle3;
Ground ground1;
Grass grass1;
Pool pool1;
Trampoline trampoline1;
Stand stand1;
Stand stand2;
Spike spike1;
Spike spike[5];
Magnet magnet1, magnet2;
Magnetstand magnetstand1, magnetstand2, magnetstand3, magnetstand4;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, limit=0;
int mousekey=0;
double curpos, prevpos;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */

void dragS() {
    mousekey = 1;
}

void dragE() {
    mousekey = 0;
}

void draw() {
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0),
                                glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

//    std::string text;
//    text = "12";
//    drawText(text.data(), static_cast<int>(text.size()), 0, 0);

    // Scene render
//    obstacle[0].draw(VP);
//    obstacle[1].draw(VP);
    magnet1.draw(VP);
    magnet2.draw(VP);
    magnetstand1.draw(VP);
    magnetstand2.draw(VP);
    magnetstand3.draw(VP);
    magnetstand4.draw(VP);
    ground1.draw(VP);
    grass1.draw(VP);
    pool1.draw(VP);
    trampoline1.draw(VP);
    stand1.draw(VP);
    stand2.draw(VP);
    for (int i = 0; i < 3; i++) {
        spike[i].draw(VP);
    }
    ball1.draw(VP);
    for (int i = 0; i < 15; i++) {
        obstacle[i].draw(VP);
    }
    obstacle1.draw(VP);
    obstacle2.draw(VP);
    obstacle3.draw(VP);
    slab1.draw(VP);
    slab2.draw(VP);
    slab3.draw(VP);
}

void tick_input(GLFWwindow *window) {
    glfwGetCursorPos(window, &curpos, &prevpos);
    int left = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_S);
    int zoomin = glfwGetKey(window, GLFW_KEY_W);
    int zoomout = glfwGetKey(window, GLFW_KEY_S);
    int padup = glfwGetKey(window, GLFW_KEY_UP);
    int paddown = glfwGetKey(window, GLFW_KEY_DOWN);
    int padleft = glfwGetKey(window, GLFW_KEY_LEFT);
    int padright = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (paddown) {
        if (screen_center_y <= 3.5)
            screen_center_y += 0.01;
        reset_screen();
    }
    if (padup) {
        if (screen_center_y >= -3.5)
            screen_center_y -= 0.01;
        reset_screen();
    }
    if (padright) {
//        if (screen_center_x >= -3.5)
        screen_center_x -= 0.01;
        reset_screen();
    }
    if (padleft) {
//        if (screen_cecout << "d\n";nter_x <= 3.5)
        screen_center_x += 0.01;
        reset_screen();
    }
    if (mousekey==1) {
        if (curpos - prevpos >0)
            right = 1;
        else if (curpos - prevpos <0)
            left = 1;
    }
    if (zoomin) {
        if (screen_zoom <= 1.5)
            screen_zoom += 0.01;
        reset_screen();
    }
    if (zoomout) {
        if (screen_zoom >= 0.5)
            screen_zoom -= 0.01;
        reset_screen();
    }
    if (left) {
        ball1.mleft = 1;
        ball1.mright = 0;
        if (ball1.inwater == 1)
            ball1.speed = 0.01;
//        else if (ball1.indicate==0)
        else
            ball1.speed = 0.04;

    }
    if (right) {
        ball1.mleft = 0;
        ball1.mright = 1;
        if (ball1.inwater == 1)
            ball1.speed = -0.01;
//        else if (ball1.indicate==0)
        else
            ball1.speed = -0.04;
    }
    if (up && ball1.counti == 0) {
        ball1.counti = 1;
        if (ball1.inwater == 0) {
            ball1.accn = 0.005;
            ball1.speedy = 0.13;
        } else {
            ball1.accn = 0.0015;
            ball1.speedy = 0.05;
        }
    }
    // if (down) {
    //     ball1.speedy = -0.13;
    // }
    prevpos = curpos;
}

void tick_elements() {
    ball1.tick();
    for (int i = 0; i < 15; i++) {
        obstacle[i].tick();
    }
    for (int i = 0; i < 3; i++) {
        spike[i].tick();
    }
    ground1.tick();
    obstacle1.tick();
    obstacle2.tick();
    obstacle3.tick();
    slab1.tick();
    slab2.tick();
    slab3.tick();
    for (int i = 0; i < 15; i++) {
        if (std::sqrt((ball1.position.x - obstacle[i].position.x) * (ball1.position.x - obstacle[i].position.x) +
                      ((ball1.position.y - obstacle[i].position.y) * (ball1.position.y - obstacle[i].position.y))) <
            (0.2 + obstacle[i].radius)) {
            if (ball1.position.y > obstacle[i].position.y && ball1.speedy < 0) {
//                ball1.speed = 0;
                ball1.score += 10;
                std::string title = "Pop 'em All     Score : ";
                std::string sco = std::to_string(ball1.score);
                sco = title + sco;
                glfwSetWindowTitle(window, const_cast<char*>(sco.c_str()));
                ball1.counti = 1;
                ball1.accn = 0.0035;
                ball1.speedy = 0.13;
                float yc, rd;
                yc = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 4));
                yc -= 0.5;
                rd = static_cast<float>(0.07 +
                                        static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.3 - 0.07))));
                if (i % 4 == 0)
                    obstacle[i] = Obstacle(static_cast<float>(-4.5), yc, COLOR_YELLOW, rd, 0, 0.02);
                if (i % 4 == 1)
                    obstacle[i] = Obstacle(static_cast<float>(-4.5), yc, COLOR_CREAMBLUE, rd, 0, 0.01);
                if (i % 4 == 2)
                    obstacle[i] = Obstacle(static_cast<float>(-4.5), yc, COLOR_WHITEPURPLE, rd, 0, 0.015);
                if (i % 4 == 3)
                    obstacle[i] = Obstacle(static_cast<float>(-4.5), yc, COLOR_ORANGE, rd, 0, 0.025);
            }
        }
    }
    if ((ball1.position.x >= screen_center_x + 3.75 || ball1.position.x <= screen_center_x - 3.75)) {
        if (ball1.position.x >= screen_center_x + 3.75)
            screen_center_x += 0.04;
//            this->position.x = 3.75;
        if (ball1.position.x <= screen_center_x - 3.75)
            screen_center_x -= 0.04;
        reset_screen();
//            this->position.x = static_cast<float>(-3.75);
//        this->speed = (-1)*this->speed;
    }
//    if (sqrt(((obstacle1.position.x+0.4)*(obstacle1.position.x+0.4)+(pow(sqrt((slab1.position.x+0.3-ball1.position.x)*(slab1.position.x+0.3-ball1.position.x)+(slab1.position.y+0.3-ball1.position.y)*(slab1.position.y+0.3-ball1.position.y)),2))))<=sqrt(pow(ball1.position.x-obstacle1.position.x,2)+pow(ball1.position.y-obstacle1.position.y,2)))
    if (sqrt(pow(ball1.position.x - obstacle1.position.x, 2) + pow(ball1.position.y - obstacle1.position.y, 2)) <=
        0.65) {
        if (ball1.position.x >= obstacle1.position.x && ball1.position.y >= obstacle1.position.y &&
            obstacle1.rotateface == 1) {
            ball1.indicate = 1;
            ball1.speed = -0.05;
            ball1.accn = 0.0035;
            ball1.speedy = 0.13;
        }
    }
    if (sqrt(pow(ball1.position.x - obstacle2.position.x, 2) + pow(ball1.position.y - obstacle2.position.y, 2)) <=
        0.65) {
        if (ball1.position.x <= obstacle2.position.x && ball1.position.y >= obstacle2.position.y &&
            obstacle2.rotateface == -1) {
            ball1.indicate = 1;
            ball1.speed = 0.05;
            ball1.accn = 0.0035;
            ball1.speedy = 0.13;
        }
    }
    if (sqrt(pow(ball1.position.x - obstacle3.position.x, 2) + pow(ball1.position.y - obstacle3.position.y, 2)) <=
        0.65) {
        if (ball1.position.x <= obstacle3.position.x && ball1.position.y >= obstacle3.position.y &&
            obstacle3.rotateface == -1) {
            ball1.indicate = 1;
            ball1.speed = 0.05;
            ball1.accn = 0.0035;
            ball1.speedy = 0.13;
        }
    }
    if (ball1.score >= 50) {
        magnet1.position.x = -3;
        magnet2.position.x = static_cast<float>(-2.5);
        magnetstand1.position.x = 0;
        magnetstand2.position.x = 0;
        magnetstand3.position.x = 0.5;
        magnetstand4.position.x = 0.5;
        ball1.mageneton = 1;
    } else {
        magnet1.position.x = -10;
        magnet2.position.x = static_cast<float>(-10);
        magnetstand1.position.x = -10;
        magnetstand2.position.x = -10;
        magnetstand3.position.x = -10;
        magnetstand4.position.x = -10;
        ball1.mageneton = 0;
    }
    if (ball1.score >= 20) {
        float sp = 0.4;
        for (int i = 0; i < 2; i++) {
            spike[i].position.x = i * sp;
            spike[i].tick();
        }
        spike[2].position.x = 1.5;
        spike[2].tick();
    } else {
        for (int i = 0; i < 3; i++) {
            spike[i].position.x = -10;
        }
    }
    if (ball1.counti == 0 || ball1.inwater == 1)
        ball1.indicate = 0;
    for (int i = 0; i < 3; i++) {
        if (std::fabs(ball1.position.x - spike[i].position.x + 3.2) < 0.35 &&
                (((ball1.position.y - spike[i].position.y) >= -0.81) &&
                        ((ball1.position.y - spike[i].position.y) <= -0.2))) {
            spike[i].position.x = -10;
            if (ball1.score > 500) {
                ball1.score -= 500;
            }
            else
                ball1.score=0;
            std::string title = "Pop 'em All     Score : ";
            std::string sco = std::to_string(ball1.score);
            sco = title + sco;
            glfwSetWindowTitle(window, const_cast<char*>(sco.c_str()));
            ball1.position.x = 2;
        }
    }
    if (int m = detect_Trampcollision(ball1.bounding_box(), trampoline1.bounding_box())) {
        if (m == 1) {
            ball1.indicate = 0;
            ball1.counti = 1;
            ball1.accn = 0.0035;
            ball1.speedy = 0.16;
        }
    }
    if (int m = detect_Poolcollision(ball1.bounding_box(), pool1.bounding_box())) {
        if (m == 1) {
            ball1.indicate = 0;
            pool1.flagi = 1;
            ball1.inwater = 1;
        } else if (m == 2) {
            pool1.flagi = 0;
        }
    }
}

void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(2, static_cast<float>(-0.8), COLOR_PINK);
    for (int i = 0; i < 15; i++) {
        float xc, yc, rd;
        xc = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 7));
        xc -= 3.5;
        yc = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 3.5));
        yc -= 0.5;
        rd = static_cast<float>(0.07 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.3 - 0.07))));
        if (i % 4 == 0)
            obstacle[i] = Obstacle(xc, yc, COLOR_CREAMBLUE, rd, 0, 0.05);
        if (i % 4 == 1)
            obstacle[i] = Obstacle(xc, yc, COLOR_YELLOW, rd, 0, 0.01);
        if (i % 4 == 2)
            obstacle[i] = Obstacle(xc, yc, COLOR_ORANGE, rd, 0, 0.015);
        if (i % 4 == 3)
            obstacle[i] = Obstacle(xc, yc, COLOR_WHITEPURPLE, rd, 0, 0.025);
    }
    obstacle1 = Obstacle(-3, 0, COLOR_REDRAINBOW, 0.3, 1, 0.02);
    obstacle1.counti = 1;
    obstacle2 = Obstacle(-4, 2, COLOR_REDRAINBOW, 0.3, -1, 0.01);
    obstacle2.counti = 1;
    obstacle3 = Obstacle(-5, 1, COLOR_REDRAINBOW, 0.3, -1, 0.01);
    obstacle3.counti = 1;
    slab1 = Slab(-3, 0, COLOR_BROWN, 0.3, 1, 0.02);
    slab2 = Slab1(-4, 2, COLOR_BROWN, 0.3, 1, 0.01);
    slab3 = Slab1(-5, 1, COLOR_BROWN, 0.3, 1, 0.01);
    grass1 = Grass(0, static_cast<float>(0), COLOR_GREEN);
    ground1 = Ground(0, static_cast<float>(0), COLOR_BROWN);
    pool1 = Pool(0, static_cast<float>(-1), COLOR_BLUE);
    trampoline1 = Trampoline(3, static_cast<float>(-0.3), COLOR_RED);
    stand1 = Stand(0, static_cast<float>(0), COLOR_RED);
    stand2 = Stand(1.25, static_cast<float>(0), COLOR_RED);
//    spike1 = Spike(0, static_cast<float>(0), COLOR_BLUE);
    for (int i = 0; i < 3; i++) {
        spike[i] = Spike(-10, 0, COLOR_BLUE);
    }
    magnet1 = Magnet(-10, static_cast<float>(2.5), COLOR_RED);
    magnet2 = Magnet(static_cast<float>(-10), static_cast<float>(2.5), COLOR_BLACK);
    magnetstand1 = Magnetstand(static_cast<float>(-10), static_cast<float>(0), COLOR_RED);
    magnetstand2 = Magnetstand(static_cast<float>(-10), static_cast<float>(-0.9), COLOR_RED);
    magnetstand3 = Magnetstand(static_cast<float>(-10), static_cast<float>(0), COLOR_SILVER);
    magnetstand4 = Magnetstand(static_cast<float>(-10), static_cast<float>(-0.9), COLOR_SILVER);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow(window, width, height);

    // Background1 color of the scene
    glClearColor(0, 0, 0, 0.0f); // R, G, B, A
    glClearDepth(2.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
//        printf("%f==yyyyyyy==%f\n", ball1.position.x, ball1.position.y);//-3,-0.8
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

int detect_Trampcollision(bounding_box_t a, bounding_box_t b) {
    if ((abs(a.x - b.x) <= b.width / 2) &&
        (abs(a.y - b.y) <= a.height / 2)) {
        if (a.y > b.y && trampoline1.flagi == 0)
            return 1;
        else {
            trampoline1.flagi = 1;
            return 2;
        }
    }
    trampoline1.flagi = 0;
    return 0;
}

int detect_Poolcollision(bounding_box_t a, bounding_box_t b) {
    if ((abs(a.x - b.x) < b.width / 2) &&
        (abs(a.y - b.y) < a.height / 2)) {
        if (a.y > b.y && pool1.flagi == 0)
            return 1;
        else if (pool1.flagi == 1 && ball1.inwater == 1)
            return 2;
    }
    return 0;
}

void reset_screen() {
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
