#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
/*
һ�����ڴ�����ɫ���������
��ɫ���Ļ��࣬���е���ɫ������Ӧ�ö��������µ���ɲ��֣�
1.����õ���ɫ������ID
2.��ɫ������������
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
	//������ɫ��������н������Ļ���
	void use();
	//ɾ��opengl��Shader��Դ
	static void removeShader(GLuint ID);
};

