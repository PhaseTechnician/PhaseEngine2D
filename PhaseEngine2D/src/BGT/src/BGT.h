#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "..\..\FontLoader\src\FontLoader.h"

using namespace glm;
/*
* 创建一个BGT必须与window绑定
* 绘制基于屏幕像素坐标，左下角为原点
* 如果存在多个语境，他可以自动处理语境切换，但是耗费更多的资源【该特性暂时禁止使用】
*/
namespace BGT {
	// 点 vec2
	typedef vec2 Point;
	// 矩形 vec4
	typedef vec4 Rect;
	//BGT 颜色 RGBA vec4
	typedef vec4 Color;//

	class BGT
	{
	public:
		//简单的图形绘制工具集
		//BGT();
		BGT(GLFWwindow* tragetWindow,string font);
		//清理绘图资源
		~BGT();
		//工具完备性检查
		bool isReady();
		//画线
		void drawLine(float p1x, float p1y, float p2x, float p2y);
		void drawLine(Point p1,Point p2);
		//画矩形
		void drawRect(float p1x, float p1y, float p2x, float p2y);
		void drawRect(Point p1,Point p2);
		//画圆	   
		void drawCircle(float p1x, float p1y, float radius);
		void drawCircle(Point center, float radius);
		//画三角
		void drawTriangle(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);
		void drawTriangle(Point p1, Point p2, Point p3);
		//字符书写 注意使用L''
		void write(FT_Long Char, float x, float y);
		//文字书写 注意使用L""
		void write(wstring message, float x, float y);
		//文字垂直书写 注意使用L""
		void writeVertical(wstring message, float x, float y);
		//绘制属性设置
		void changePen(Color color);
		void changeBrush(Color color);
		void changeTextSize(int width,int height);
		//绑定窗口回调
		void bindWindowFallback(GLFWwindow * window, int width, int height);
	private:
		int windowWidth = 800;
		int windowHeight = 600;
		GLFWwindow* window;
		unsigned int shaderID;
		unsigned int textShaderID;
		Color penColor;
		Color brushColor;
		//避免多次重复创建显存，对定长图元进行保存
		unsigned int lineVAO, lineVBO;
		unsigned int rectVAO, rectVBO;
		unsigned int circleVAO, circleVBO;
		unsigned int triangleVAO, triangleVBO;
		unsigned int textVAO, textVBO, textTexture;
		float *unitCircle;
		FontLoader *loader;
		//临时字符尺寸
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