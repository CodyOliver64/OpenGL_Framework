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

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"
#include "tests/TestMovement.h"
#include "tests/FleeMovement.h"
#include "tests/WanderMovement.h"
#include "tests/SpaceBattle.h"

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

    
    //Blend function 
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


    //Create our Renderer instance
    Renderer renderer;

    // imgui init
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    
    //Create testMenu
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    // Load testMenu with Tests
    testMenu->RegisterTest<test::TestClearColor>("Clear Color"); // takes in a template for the type of test and a string for its name
    testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
    testMenu->RegisterTest<test::TestMovement>("Chasing");
    testMenu->RegisterTest<test::FleeMovement>("Fleeing");
    testMenu->RegisterTest<test::WanderMovement>("Wandering");
    testMenu->RegisterTest<test::SpaceBattle>("Space Battle");


    /* Loop until the user closes the window. Things here will update every frame */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();

        // Get Mouse Position
        double x_Mouse, y_Mouse;
        glfwGetCursorPos(window, &x_Mouse, &y_Mouse);

        // Start new imgui frame
        ImGui_ImplGlfwGL3_NewFrame();

        if (currentTest)
        {
            currentTest->OnUpdate(0.0f, x_Mouse, y_Mouse);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }

        // Render imgui ui
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    // Clean up tests & test menu
    delete currentTest;
    if (currentTest != testMenu)
        delete testMenu;
    
    // imgui cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    
    glfwTerminate();
    return 0;
}