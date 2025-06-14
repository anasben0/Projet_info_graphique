﻿#include "viewer.h"
#include "skybox.h"
#include "node.h"
#include "texture.h"
#include "textured_sphere.h"

#include <iostream>
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <glm/gtc/matrix_transform.hpp>

Viewer::Viewer(int width, int height)
{
    skybox = nullptr;
    if (!glfwInit())    // initialize window system glfw
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
    }

    // version hints: create GL window with >= OpenGL 3.3 and core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    win = glfwCreateWindow(width, height, "Viewer", NULL, NULL);

    if (win == NULL) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
    }

    // make win's OpenGL context current; no OpenGL calls can happen before
    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    // Set user pointer for GLFW window to this Viewer instance
    glfwSetWindowUserPointer(win, this);

    // register event handlers
    glfwSetKeyCallback(win, key_callback_static);

    // useful message to check OpenGL renderer characteristics
    std::cout << glGetString(GL_VERSION) << ", GLSL "
        << glGetString(GL_SHADING_LANGUAGE_VERSION) << ", Renderer "
        << glGetString(GL_RENDERER) << std::endl;

    // initialize GL by setting viewport and default render characteristics
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

    /* tell GL to only draw onto a pixel if the shape is closer to the viewer
    than anything already drawn at that pixel */
    glEnable(GL_DEPTH_TEST); /* enable depth-testing */
    /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
    glDepthFunc(GL_LESS);

    // initialize our scene_root
    scene_root = new Node();
}

void Viewer::run()
{
    double start_time = glfwGetTime();

    while (!glfwWindowShouldClose(win))
    {
        // clear draw buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 rot_mat = glm::mat4(1.0f);
        rot_mat = glm::rotate(rot_mat, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation autour de X
        rot_mat = glm::rotate(rot_mat, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));   // rotation autour de Y
        glm::mat4 tra_mat = glm::mat4(1.0f);
        glm::mat4 sca_mat = glm::mat4(1.0f);
        glm::mat4 view = tra_mat * rot_mat * sca_mat;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 10.0f);

        if (skybox) {
            skybox->draw(view, projection);
        }
        update();
        scene_root->draw(model, view, projection);

        // Poll for and process events
        glfwPollEvents();

        // flush render commands, and swap draw buffers
        glfwSwapBuffers(win);
    }
    /* close GL context and any other GLFW resources */
    glfwTerminate();
}

void Viewer::key_callback_static(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Viewer* viewer = static_cast<Viewer*>(glfwGetWindowUserPointer(window));
    viewer->on_key(key);
}

void Viewer::on_key(int key)
{
    // 'Q' or 'Escape' quits
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)
    {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_LEFT)
    {
        yaw -= 5.0f; // tourner à gauche
    }
    else if (key == GLFW_KEY_RIGHT)
    {
        yaw += 5.0f; // tourner à droite
    }
    else if (key == GLFW_KEY_UP)
    {
        pitch -= 5.0f; // lever la tête
    }
    else if (key == GLFW_KEY_DOWN)
    {
        pitch += 5.0f; // baisser la tête
    }
}

void Viewer::update() {
    if (Terre_node != nullptr) {
        double time = glfwGetTime(); // temps global

        glm::mat4 Terre_mat =
            glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -2.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians((float)time * 30.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

        Terre_node->set_transform(Terre_mat);
    }
}