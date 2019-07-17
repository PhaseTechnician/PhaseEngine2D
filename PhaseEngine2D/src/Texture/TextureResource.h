#pragma once
#include <glad/glad.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;
//用于加载，管理图像材质资源
//请首先设定图像文件夹路径，但实际材质会在运行中动态加载
//
class TextureResource
{
public:
	//材质句柄数据结构
	struct ImgInfo
	{
		//材质ID
		GLuint textureID;
		//宽度
		int width;
		//高度
		int height;
		//色彩通道数
		int channels;
		ImgInfo(GLuint ID = 0, int w = 0, int h = 0, int channel = -1) :textureID(ID), width(w), height(h), channels(channel) {};
	};
private:
	string imgBaseDir;
	map<string, ImgInfo> textures;
	//获得材质索引，ImgInfo(0,0,0)表明没有这个材质
	ImgInfo getTexture(string imgName);
	//拼接文件夹和文件名
	inline string getAbsoluteDir(string imgName);
public:
	//确定指定文件下的材质资源管理器 ex: resource/img/
	TextureResource(string dir);
	//添加一个材质
	bool addTexture(string imgName);
	//启用并绑定一个2D纹理
	bool applyTexture(string imgName);
	//启用并绑定一个2D纹理,同时获得图像信息
	bool applyTexture(string imgName, ImgInfo *imgInfo);
	//析构
	~TextureResource();
};

