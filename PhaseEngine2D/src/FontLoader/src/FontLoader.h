#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

/*
* 文本加载工具类
*/
using namespace std;
class FontLoader {
public:
	//通过字体文件路径创建字体读取器对象
	FontLoader();
	FontLoader(string path);
	//释放占用资源
	~FontLoader();
	//当其中一项为0时，会自动计算它的值
	void setSize(int width,int height);
	//获取字形
	unsigned char* getCharBitmap(FT_ULong c,int *width,int *height);
private:
	int charWidth = 0;
	int charHeight = 10;
	FT_Library libruary;
	FT_Face face;
};