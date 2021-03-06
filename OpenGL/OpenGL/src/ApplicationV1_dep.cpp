#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Set framerate
    glfwSwapInterval(1);

    // GLEW Setup
    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;

    // Check OpenGL Version
    std::cout << glGetString(GL_VERSION) << std::endl;


    // (C.O) Vertex buffer defined outside of frame loop
    float positions[] = {
       -50.0f,-50.0f, 0.0f, 0.0f,// 1, Bottom Left Texture Coord
        50.0f,-50.0f, 1.0f, 0.0f, // 2, Top Left Texture Coord 
        50.0f, 50.0f, 1.0f, 1.0f, // 3, Top Right Texture Coord
       -50.0f, 50.0f, 0.0f, 1.0f // 4, Bottom Right Texture Coord
    }; // an array to reprsent our positions along with texture coordinates to label each corner

    // Index Buffer
    unsigned int indicies[] = {
        0,1,2, //draws first triangle using position
        2,3,0
    };

    //Blend function 
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Create our VAO (vertex array object) that links our buffers with their appropriate layout. On Compatability mode a default VAO is given behind the scenes
    VertexArray va;

    // Set position vertex buffer
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    // Defines the layout of the buffer so the GPU knows whats what
    VertexBufferLayout layout;
    layout.Push<float>(2); //layout for vertex positons
    layout.Push<float>(2); //layout for texture coords
    va.AddBuffer(vb, layout);

    // Set Index Buffer, like setting the positions buffer but using ELEMENTS
    IndexBuffer ib(indicies, 6);


    //---------------------------------Model View Projection-------------------------------------------

    // Set 4x4 Projection Matrix (ortho) using glm
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); //values are 4:3 including the last too which are near/far values
    // Set the view matrix as if our camera moved to the left (which means we move our world to the right)
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    //---------------------------------------------------------------------------------------------------


    //Bind Shader
    Shader shader("res/shaders/Basic.shader");
    shader.Bind();

    // Define the color Uniform
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f); // Use 4f since we're passing 4 floats to represent a color 



    // Set Texture with PNG logo
    Texture texture("res/textures/Money.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);


    //Reset all bound buffers/shaders (for testing)
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    //Create our Renderer instance
    Renderer renderer;

    // imgui init
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    // Logic to update color dyamically
    float r = 0.0f;
    float increment = 0.05f;


    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);

    /* Loop until the user closes the window. Things here will update every frame */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        // Start new imgui frame
        ImGui_ImplGlfwGL3_NewFrame();

        // Render Object 1
        {
            // Create Model Matrix which represents the objects actual position
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            // Multiply our View/Projection/Model matrixes to be sent to the shader
            glm::mat4 mvp = proj * view * model;
            // Re Bind all buffers (testing)
            shader.Bind();
            // Define the matrix projection uniform
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }

        // Render Object 2
        {
            // Create Model Matrix which represents the objects actual position
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            // Multiply our View/Projection/Model matrixes to be sent to the shader
            glm::mat4 mvp = proj * view * model;
            // Re Bind all buffers (testing)
            shader.Bind();
            // Define the matrix projection uniform
            shader.SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(va, ib, shader);
        }


        // Logic to update color dyamically
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;
        r += increment;

        //-----------------------------------------imgui Window--------------------------------------------------------------
        {
            ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f); // allows you to modify the translation used to represent object1 position
            ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f); // allows you to modify the translation used to represent object2 position
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        //--------------------------------------------------------------------------------------------------------------------


        // Render imgui ui
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);



        /* Poll for and process events */
        glfwPollEvents();
    }

    // imgui cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}