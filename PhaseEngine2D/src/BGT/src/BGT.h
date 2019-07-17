#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "..\..\FontLoader\src\FontLoader.h"

using namespace glm;
/*
* ����һ��BGT������window��
* ���ƻ�����Ļ�������꣬���½�Ϊԭ��
* ������ڶ���ﾳ���������Զ������ﾳ�л������ǺķѸ������Դ����������ʱ��ֹʹ�á�
*/
namespace BGT {
	// �� vec2
	typedef vec2 Point;
	// ���� vec4
	typedef vec4 Rect;
	//BGT ��ɫ RGBA vec4
	typedef vec4 Color;//

	class BGT
	{
	public:
		//�򵥵�ͼ�λ��ƹ��߼�
		//BGT();
		BGT(GLFWwindow* tragetWindow,string font);
		//�����ͼ��Դ
		~BGT();
		//�����걸�Լ��
		bool isReady();
		//����
		void drawLine(float p1x, float p1y, float p2x, float p2y);
		void drawLine(Point p1,Point p2);
		//������
		void drawRect(float p1x, float p1y, float p2x, float p2y);
		void drawRect(Point p1,Point p2);
		//��Բ	   
		void drawCircle(float p1x, float p1y, float radius);
		void drawCircle(Point center, float radius);
		//������
		void drawTriangle(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);
		void drawTriangle(Point p1, Point p2, Point p3);
		//�ַ���д ע��ʹ��L''
		void write(FT_Long Char, float x, float y);
		//������д ע��ʹ��L""
		void write(wstring message, float x, float y);
		//���ִ�ֱ��д ע��ʹ��L""
		void writeVertical(wstring message, float x, float y);
		//������������
		void changePen(Color color);
		void changeBrush(Color color);
		void changeTextSize(int width,int height);
		//�󶨴��ڻص�
		void bindWindowFallback(GLFWwindow * window, int width, int height);
	private:
		int windowWidth = 800;
		int windowHeight = 600;
		GLFWwindow* window;
		unsigned int shaderID;
		unsigned int textShaderID;
		Color penColor;
		Color brushColor;
		//�������ظ������Դ棬�Զ���ͼԪ���б���
		unsigned int lineVAO, lineVBO;
		unsigned int rectVAO, rectVBO;
		unsigned int circleVAO, circleVBO;
		unsigned int triangleVAO, triangleVBO;
		unsigned int textVAO, textVBO, textTexture;
		float *unitCircle;
		FontLoader *loader;
		//��ʱ�ַ��ߴ�
		int charWidth, charHeight;

		void initLine();
		void initRect();
		void initCircle();
		void initTriangle();
		void initTextDrawer();
		unsigned int compileShader(string vertShader, string fragShader);
		void reUploadProjection();
	};
}