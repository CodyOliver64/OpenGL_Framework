#pragma once

#include <functional>
#include <vector>
#include <string>

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime, double x_Mouse, double y_Mouse) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			//std::cout << "Registering test " << name << std::endl;
			
			m_Tests.push_back(std::make_pair(name, []() {return new T(); })); // makes a pair of a string name with a lambda that creates a new Test based on the type T
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests; // vector of pairs, where each pair contains a string label and a lambda which creates a new Test instance and returns a pointer
	};
}
