#pragma once

#include "Test.h"

#include"VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include<memory>

namespace test {

	class WanderMovement : public Test
	{
	public:
		WanderMovement();
		~WanderMovement();

		void OnUpdate(float deltaTime, double x_Mouse, double y_Mouse) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;


		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;

		glm::vec3 m_Target;

		int counter = 3;
		int* counterPoint = &counter;

		glm::mat4 m_Proj, m_View;

		glm::vec3* randArray = new glm::vec3[10];
	};
}
