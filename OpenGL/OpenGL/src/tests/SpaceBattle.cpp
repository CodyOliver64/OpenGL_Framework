#include "SpaceBattle.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "pathing/Fighting.h"


namespace test {
	
	SpaceBattle::SpaceBattle()
        : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(50, 200, 0), m_TranslationB(905, 200, 0), m_A1(50,50,0), m_A2(50,450,0), m_B1(905, 450, 0), m_B2(905, 50, 0), m_TargetA(50,50,0), m_TargetB(905,450,0)
	{

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
        m_VAO = std::make_unique<VertexArray>();
        

        // Set position vertex buffer
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

        // Defines the layout of the buffer so the GPU knows whats what
        VertexBufferLayout layout;
        layout.Push<float>(2); //layout for vertex positons
        layout.Push<float>(2); //layout for texture coords
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        // Set Index Buffer, like setting the positions buffer but using ELEMENTS
        m_IndexBuffer = std::make_unique<IndexBuffer>(indicies, 6);



        //Bind Shader
        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();

        // Define the color Uniform
        m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f); // Use 4f since we're passing 4 floats to represent a color 



        // Set Texture with PNG logo
        m_Texture = std::make_unique<Texture>("res/textures/Money.png");
        m_Shader->SetUniform1i("u_Texture", 0);
	}

	SpaceBattle::~SpaceBattle()
	{

	}

	void SpaceBattle::OnUpdate(float deltaTime, double x_Mouse, double y_Mouse)
	{
        Fight(&m_TranslationA, &m_TranslationB, &m_A1, &m_A2, &m_TargetA);
        Fight(&m_TranslationB, &m_TranslationA, &m_B1, &m_B2, &m_TargetB);
	}

	void SpaceBattle::OnRender()
	{
        Renderer renderer;
        m_Texture->Bind();


        
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // Render Object 1
        {
            // Create Model Matrix which represents the objects actual position
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            // Multiply our View/Projection/Model matrixes to be sent to the shader
            glm::mat4 mvp = m_Proj * m_View * model;
            // Re Bind all buffers (testing)
            m_Shader->Bind();
            // Define the matrix projection uniform
            m_Shader->SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        // Render Object 2
        {
            // Create Model Matrix which represents the objects actual position
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            // Multiply our View/Projection/Model matrixes to be sent to the shader
            glm::mat4 mvp = m_Proj * m_View * model;
            // Re Bind all buffers (testing)
            m_Shader->Bind();
            // Define the matrix projection uniform
            m_Shader->SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
	}

	void SpaceBattle::OnImGuiRender()
	{
        ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f); // allows you to modify the translation used to represent object1 position
        ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f); // allows you to modify the translation used to represent object2 position
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}