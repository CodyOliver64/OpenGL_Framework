#pragma once

#include "Test.h"

#include"VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include<memory>

namespace test {

	class TestMovement : public Test
	{
	public:
		TestMovement();
		~TestMovement();

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

		glm::mat4 m_Proj, m_View;
	};
}
