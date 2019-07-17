#include "BGT.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BGT::BGT::BGT(GLFWwindow * tragetWindow , string font)
{
	this->window = tragetWindow;
	glfwGetWindowSize(this->window, &this->windowWidth, &this->windowHeight);
	this->initLine();
	this->initRect();
	this->initCircle();
	this->initTriangle();
	this->initTextDrawer();
	this->initTextureDrawer();
	this->shaderID = compileShader("F:\\PhaseEngine2D\\PhaseEngine2D\\src\\BGT\\shader\\bgt.vert", "F:\\PhaseEngine2D\\PhaseEngine2D\\src\\BGT\\shader\\bgt.frag");
	this->textShaderID = compileShader("F:\\PhaseEngine2D\\PhaseEngine2D\\src\\BGT\\shader\\font.vert", "F:\\PhaseEngine2D\\PhaseEngine2D\\src\\BGT\\shader\\font.frag");
	this->reUploadProjection();
	this->loader = new FontLoader(font);
}

BGT::BGT::~BGT()
{
	delete this->unitCircle;
	glDeleteBuffers(1, &lineVBO);
	glDeleteVertexArrays(1, &lineVAO);
	glDeleteBuffers(1, &rectVBO);
	glDeleteVertexArrays(1, &rectVAO);
	glDeleteBuffers(1, &circleVBO);
	glDeleteVertexArrays(1, &circleVAO);
	glDeleteBuffers(1, &triangleVBO);
	glDeleteVertexArrays(1, &triangleVAO);
	glDeleteProgram(shaderID);
}

bool BGT::BGT::isReady()
{
	if (this->window == nullptr) {
		return false;
	}
	return true;
}

void BGT::BGT::initLine()
{
	glGenVertexArrays(1, &this->lineVAO);
	glGenBuffers(1, &this->lineVBO);
	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, 4*sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

void BGT::BGT::initRect()
{
	glGenVertexArrays(1, &this->rectVAO);
	glGenBuffers(1, &this->rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

void BGT::BGT::initCircle()
{
	glGenVertexArrays(1, &this->circleVAO);
	glGenBuffers(1, &this->circleVBO);
	glBindVertexArray(circleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
	this->unitCircle = new float[48];
	glBufferData(GL_ARRAY_BUFFER, 50 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	for (int i = 0; i < 24; i++) {
		unitCircle[2 * i] = cos(glm::radians(15.0)*i);
		unitCircle[2*i+1] = sin(glm::radians(15.0)*i);
	}
}

void BGT::BGT::initTriangle()
{
	glGenVertexArrays(1, &this->triangleVAO);
	glGenBuffers(1, &this->triangleVBO);
	glBindVertexArray(triangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

void BGT::BGT::initTextDrawer()
{
	glGenVertexArrays(1, &this->textVAO);
	glGenBuffers(1, &this->textVBO);
	glGenTextures(1, &this->textTexture);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	float coord[] = {
			 0.1f,0.1f,-0.1f,0.1f,-0.1f,-0.1f, 0.1f,-0.1f,
			 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(8*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

void BGT::BGT::initTextureDrawer()
{
	glGenVertexArrays(1, &this->bitmapVAO);
	glGenBuffers(1, &this->bitmapVBO);
	glBindVertexArray(bitmapVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->bitmapVBO);
	float coord[] = {
			 0.1f,0.1f,-0.1f,0.1f,-0.1f,-0.1f, 0.1f,-0.1f,
			 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

unsigned int BGT::BGT::compileShader(string vertShader, string fragShader)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// 打开文件
		vShaderFile.open(vertShader);
		fShaderFile.open(fragShader);
		std::stringstream vShaderStream, fShaderStream;
		// 读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();
		// 转换数据流到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// build and compile our shader program
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	unsigned int shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);
	// check for linking errors
	glGetProgramiv(this->shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderID;
}

void BGT::BGT::reUploadProjection()
{
	mat4 projection = glm::ortho(0.0f, (float)this->windowWidth, 0.0f, (float)this->windowHeight, -1.0f, 1.0f);
	glUseProgram(this->shaderID);
	int location = glGetUniformLocation(this->shaderID, "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
	glUseProgram(this->textShaderID);
	location = glGetUniformLocation(this->textShaderID, "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
}

void BGT::BGT::drawLine(float p1x, float p1y, float p2x, float p2y)
{
	glUseProgram(this->shaderID);
	float coord[] = { p1x,p1y,p2x,p2y };
	glBindVertexArray(lineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINES, 0, 2);
}

void BGT::BGT::drawLine(Point p1, Point p2)
{
	this->drawLine(p1.x, p1.y, p2.x, p2.y);
}

void BGT::BGT::drawRect(float p1x, float p1y, float p2x, float p2y)
{
	glUseProgram(this->shaderID);
	float coord[] = { p1x,p1y,p1x,p2y,p2x,p2y,p2x,p1y };
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void BGT::BGT::drawRect(Point p1, Point p2)
{
	this->drawRect(p1.x, p1.y, p2.x, p2.y);
}

void BGT::BGT::drawCircle(float p1x, float p1y, float radius)
{
	glUseProgram(this->shaderID);
	float coord[52];
	coord[0] = p1x;
	coord[1] = p1y;
	for (int i = 0; i < 24; i++) {
		coord[2 * i + 2] = p1x + unitCircle[2 * i] * radius;
		coord[2 * i + 3] = p1y + unitCircle[2 * i + 1] * radius;
	}
	coord[50] = p1x + unitCircle[0] * radius;
	coord[51] = p1y + unitCircle[1] * radius;
	glBindVertexArray(circleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 26);

}

void BGT::BGT::drawCircle(Point center, float radius)
{
	this->drawCircle(center.x, center.y, radius);
}

void BGT::BGT::drawTriangle(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y)
{
	glUseProgram(this->shaderID);
	float coord[] = { p1x,p1y,p2x,p2y,p3x,p3y };
	glBindVertexArray(triangleVAO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coord), coord, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void BGT::BGT::drawTriangle(Point p1, Point p2, Point p3)
{
	this->drawTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

void BGT::BGT::write(FT_Long Char, float x, float y)
{
	glBindTexture(GL_TEXTURE_2D, this->textTexture);
	unsigned char* data = loader->getCharBitmap(Char, &charWidth, &charHeight);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, charWidth, charHeight, 0, GL_RED, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glUseProgram(textShaderID);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	float coord[8] = { x + charWidth,y + charHeight,x ,y + charHeight,x ,y ,x + charWidth,y };
	glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), coord);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void BGT::BGT::write(wstring message, float x, float y)
{
	int tempx = x;
	for (int i = 0; i < message.size(); i++) {
		FT_Long Char = message[i];
		write(Char, tempx, y);
		tempx += charWidth;
	}
}

void BGT::BGT::writeVertical(wstring message, float x, float y)
{
	int tempy = y;
	for (int i = 0; i < message.size(); i++) {
		FT_Long Char = message[i];
		write(Char, x, tempy);
		tempy -= charHeight;
	}
}

void BGT::BGT::drawBitmap(string imgPath, float x, float y)
{
	TextureResource::ImgInfo info;
	if (!textureResource->applyTexture(imgPath, &info)) {
		//出现错误
		return;
	}
	glUseProgram(textShaderID);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	float coord[8] = { x + info.width,y + info.height,x ,y + info.height,x ,y ,x + info.width,y };
	glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(float), coord);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void BGT::BGT::changePen(Color color)
{
	glUseProgram(shaderID);
	int location = glGetUniformLocation(this->shaderID, "penColor");
	glUniform4fv(location, 1, value_ptr(color));
	glUseProgram(textShaderID);
	location = glGetUniformLocation(this->shaderID, "penColor");
	glUniform4fv(location, 1, value_ptr(color));
}

void BGT::BGT::changeBrush(Color color)
{
	glUseProgram(shaderID);
	int location = glGetUniformLocation(this->shaderID, "brushColor");
	glUniform4fv(location, 1, value_ptr(color));
}

void BGT::BGT::changeTextSize(int width, int height)
{
	loader->setSize(width, height);
}

void BGT::BGT::bindWindowFallback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	this->windowHeight = height;
	this->windowWidth = width;
	reUploadProjection();
}

