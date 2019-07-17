#pragma once
#include <glad/glad.h>
#include <map>
#include <string>
#include <iostream>

using namespace std;
//���ڼ��أ�����ͼ�������Դ
//�������趨ͼ���ļ���·������ʵ�ʲ��ʻ��������ж�̬����
//
class TextureResource
{
public:
	//���ʾ�����ݽṹ
	struct ImgInfo
	{
		//����ID
		GLuint textureID;
		//���
		int width;
		//�߶�
		int height;
		//ɫ��ͨ����
		int channels;
		ImgInfo(GLuint ID = 0, int w = 0, int h = 0, int channel = -1) :textureID(ID), width(w), height(h), channels(channel) {};
	};
private:
	string imgBaseDir;
	map<string, ImgInfo> textures;
	//��ò���������ImgInfo(0,0,0)����û���������
	ImgInfo getTexture(string imgName);
	//ƴ���ļ��к��ļ���
	inline string getAbsoluteDir(string imgName);
public:
	//ȷ��ָ���ļ��µĲ�����Դ������ ex: resource/img/
	TextureResource(string dir);
	//���һ������
	bool addTexture(string imgName);
	//���ò���һ��2D����
	bool applyTexture(string imgName);
	//���ò���һ��2D����,ͬʱ���ͼ����Ϣ
	bool applyTexture(string imgName, ImgInfo *imgInfo);
	//����
	~TextureResource();
};

