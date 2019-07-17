#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "..\3rdparty\opengl\src\stb_image.h"

#include "Shader.h"
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

	BGT::BGT bgt = BGT::BGT(window,"C:\\Windows\\Fonts\\SIMYOU.TTF");


	while (!glfwWindowShouldClose(window))
	{
		/*渲染部分*/
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		bgt.changePen(BGT::Color(1.0f, 1.0f, 0.0f, 1.0f));
		bgt.drawLine(0, 0, 100, 100);
		bgt.drawRect(100, 100, 200, 200);
		bgt.changeTextSize(0, 100);
		wstring message = L"终于完成了";
		bgt.write(L'贪', 200, 200);
		bgt.write(L'吃', 230, 230);
		bgt.write(message, 15, 15);
		bgt.writeVertical(L"欢迎", 10, 400);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}