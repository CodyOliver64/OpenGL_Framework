#pragma once

#include "Test.h"

#include"VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include<memory>

namespace test {

	class SpaceBattle : public Test
	{
	public:
		SpaceBattle();
		~SpaceBattle();

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

		glm::vec3 m_A1;
		glm::vec3 m_A2;
		glm::vec3 m_B1;
		glm::vec3 m_B2;

		glm::vec3 m_TargetA;
		glm::vec3 m_TargetB;

		glm::mat4 m_Proj, m_View;
	};
}
