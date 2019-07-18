#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shader/Shader.h"
#include "BGT/src/BGT.h"
#include "FontLoader/src/FontLoader.h"

using namespace std;
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// 创建窗口  
	GLFWwindow* window = glfwCreateWindow(800, 600, "233", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 载入Opengl-Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	BGT::BGT bgt = BGT::BGT(window,"C:\\Windows\\Fonts\\SIMYOU.TTF","F:\\PhaseEngine2D\\img");

	while (!glfwWindowShouldClose(window))
	{
		/*渲染部分*/
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		bgt.changePen(BGT::Color(1.0f, 1.0f, 0.0f, 1.0f));
		bgt.drawBitmap("steal.png", 0, 0, 800, 600);
		bgt.changeTextSize(0, 40);
		bgt.write(L"测试场景", 0, 560);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}