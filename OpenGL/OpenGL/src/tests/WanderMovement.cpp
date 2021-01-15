#include "WanderMovement.h"
#include "Renderer.h"
#include "imgui/imgui.h"

#include "pathing/Wandering.h"


namespace test {
	
	WanderMovement::WanderMovement()
        : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)), m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0), m_Target(300, 300, 0)
	{

        randArray[0] = glm::vec3(100, 200, 0);
        randArray[1] = glm::vec3(300, 400, 0);
        randArray[2] = glm::vec3(250, 50, 0);
        randArray[3] = glm::vec3(700, 500, 0);
        randArray[4] = glm::vec3(100, 200, 0);
        randArray[5] = glm::vec3(260, 350, 0);
        randArray[6] = glm::vec3(430, 120, 0);
        randArray[7] = glm::vec3(270, 200, 0);
        randArray[8] = glm::vec3(820, 500, 0);
        randArray[9] = glm::vec3(360, 200, 0);
        
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

	WanderMovement::~WanderMovement()
	{

	}

	void WanderMovement::OnUpdate(float deltaTime, double x_Mouse, double y_Mouse)
	{
        Wander(&m_TranslationA, &m_Target, randArray, counterPoint);
	}

	void WanderMovement::OnRender()
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

        /*// Render Object 2
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
        }*/
	}

	void WanderMovement::OnImGuiRender()
	{
        ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f); // allows you to modify the translation used to represent object1 position
        ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f); // allows you to modify the translation used to represent object2 position
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}