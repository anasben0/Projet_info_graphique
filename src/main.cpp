#include "viewer.h"
#include "textured_sphere.h"
#include "textured_cylinder.h"
#include "lighting_sphere.h"
#include "texture.h"
#include "skybox.h"
#include "node.h"
#include "shader.h"
#include <string>
#include <ctime>
#include <GLFW/glfw3.h>
#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

#ifndef TEXTURE_DIR
#error "TEXTURE_DIR not defined"
#endif

//void update(Node* node) {
//    if (node != nullptr) {
//        double time = glfwGetTime(); // Temps en secondes depuis le début
//
//        glm::mat4 Terre_mat =
//            glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -2.0f)) *
//            glm::rotate(glm::mat4(1.0f), glm::radians((float)time * 30.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
//            glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
//
//        node->set_transform(Terre_mat);
//    }
//}

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer = Viewer(600,400);

    if (!glfwInit())    // initialize window system glfw
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
    }

    std::vector<std::string> faces
    {
        "C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/skybox/right.png",
        "C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/skybox/left.png",
        "C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/skybox/top.png",
        "C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/skybox/bottom.png",
        "C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/skybox/front.png",
        "C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/skybox/back.png",
    };

    Skybox* skybox = new Skybox(faces);
    viewer.skybox = skybox;

    // get shader directory
    std::string shader_dir = SHADER_DIR;
    std::string texture_dir = TEXTURE_DIR;

    Shader* texture_shader = new Shader(shader_dir + "texture.vert", shader_dir + "texture.frag");
    Texture* texture_Terre = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/terre.png");
    Shape* Terre = new TexturedSphere(texture_shader, texture_Terre);
    glm::mat4 Terre_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -2.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    Node* Terre_node = new Node(Terre_mat);

    Terre_node->add(Terre);
    viewer.Terre_node = Terre_node;
    viewer.scene_root->add(Terre_node);

    double start_time = glfwGetTime();

    Texture* texture_Mars = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/mars.png");
    Shape* Mars = new TexturedSphere(texture_shader, texture_Mars);
    glm::mat4 Mars_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -2.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* Mars_node = new Node(Mars_mat);

    Mars_node->add(Mars);

    viewer.scene_root->add(Mars_node);

    Texture* texture_Soleil = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/soleil.jpg");
    Shape* Soleil = new TexturedSphere(texture_shader, texture_Soleil);
    glm::mat4 Soleil_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* Soleil_node = new Node(Soleil_mat);

    Soleil_node->add(Soleil);

    viewer.scene_root->add(Soleil_node);

    Texture* texture_Saturne = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/saturne.jpg");
    Shape* Saturne = new TexturedSphere(texture_shader, texture_Saturne);
    glm::mat4 Saturne_mat = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -3.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* Saturne_node = new Node(Saturne_mat);

    Saturne_node->add(Saturne);

    viewer.scene_root->add(Saturne_node);

    Texture* texture_Jupiter = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/jupiter.jpg");
    Shape* Jupiter = new TexturedSphere(texture_shader, texture_Jupiter);
    glm::mat4 Jupiter_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, -2.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.75f,0.75f,0.75f))
        //* glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f)); // ou autour de Z selon le cas

    Node* Jupiter_node = new Node(Jupiter_mat);

    Jupiter_node->add(Jupiter);

    viewer.scene_root->add(Jupiter_node);

    Texture* texture_Mercure = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/mercure.png");
    Shape* Mercure = new TexturedSphere(texture_shader, texture_Mercure);
    glm::mat4 Mercure_mat = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -5.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* Mercure_node = new Node(Mercure_mat);

    Mercure_node->add(Mercure);

    viewer.scene_root->add(Mercure_node);

    Texture* texture_Venus = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/venus.jpg");
    Shape* Venus = new TexturedSphere(texture_shader, texture_Venus);
    glm::mat4 Venus_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -5.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* Venus_node = new Node(Venus_mat);

    Venus_node->add(Venus);

    viewer.scene_root->add(Venus_node);

    Texture* texture_Neptune = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/neptune.jpg");
    Shape* Neptune = new TexturedSphere(texture_shader, texture_Neptune);
    glm::mat4 Neptune_mat = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -5.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* Neptune_node = new Node(Neptune_mat);

    Neptune_node->add(Neptune);

    viewer.scene_root->add(Neptune_node);

    Texture* texture_Uranus = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/uranus.jpg");
    Shape* Uranus = new TexturedSphere(texture_shader, texture_Uranus);
    glm::mat4 Uranus_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* Uranus_node = new Node(Uranus_mat);

    Uranus_node->add(Uranus);

    viewer.scene_root->add(Uranus_node);

    viewer.run();
    //while (!glfwWindowShouldClose(viewer.win)) {
    //    //update(Terre_node);
    //}
    
    //Texture* texture_Anneau = new Texture("C:/Users/raph_/Downloads/cg_intro_public-branch-TP4_material/cg_intro_public-branch-TP4_material/TP4_material/textures/anneau.png");
    //Shape* Anneau = new TexturedCylinder(texture_shader, texture_Anneau);

    //Shader* phong_shader = new Shader(shader_dir + "phong.vert", shader_dir + "phong.frag");
    //Shape* sphere2 = new LightingSphere(phong_shader, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 sphere2_mat = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -4.0f))
    //    * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
    //    * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //Node* sphere2_node = new Node(sphere2_mat);
    //sphere2_node->add(sphere2);

    //// On ajoute la sphère à la scène
    //viewer.scene_root->add(sphere2_node);

}