#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
/*
一个用于创建着色器程序的类
着色器的基类，所有的着色器对象，应该都包含以下的组成部分：
1.编译好的着色器程序ID
2.着色器的启动函数
*/
class Shader
{
public:
	unsigned int ID;
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//Shader(const GLchar* shaderName);
	~Shader();
	void uploadUniform(const char* valueName, glm::mat4 value);
	void uploadUniform(const char* valueName, glm::vec4 value);
	//启动着色器程序进行接下来的绘制
	void use();
	//删除opengl的Shader资源
	static void removeShader(GLuint ID);
};

