#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

/*
* �ı����ع�����
*/
using namespace std;
class FontLoader {
public:
	//ͨ�������ļ�·�����������ȡ������
	FontLoader();
	FontLoader(string path);
	//�ͷ�ռ����Դ
	~FontLoader();
	//������һ��Ϊ0ʱ�����Զ���������ֵ
	void setSize(int width,int height);
	//��ȡ����
	unsigned char* getCharBitmap(FT_ULong c,int *width,int *height);
private:
	int charWidth = 0;
	int charHeight = 10;
	FT_Library libruary;
	FT_Face face;
};