#ifndef VIEWER_H
#define VIEWER_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "node.h"
#include "skybox.h"

class Viewer {
public:
    Viewer(int width=640, int height=480);
    void update();
    void run();
    void on_key(int key);
    float yaw = 0.0f;   // angle horizontal (gauche/droite)
    float pitch = 0.0f; // angle vertical (haut/bas)
    Skybox* skybox;
    Node *scene_root;
    GLFWwindow* win;
    Node* Terre_node = nullptr;

private:
    static void key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // VIEWER_H
