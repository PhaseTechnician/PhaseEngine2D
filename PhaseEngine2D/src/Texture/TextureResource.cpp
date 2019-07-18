#include "TextureResource.h"

#define STB_IMAGE_IMPLEMENTATION
#include "..\..\3rdparty\opengl\src\stb_image.h"


TextureResource::TextureResource(string dir)
{
	this->imgBaseDir = dir;
}

TextureResource::~TextureResource()
{
	map<string, ImgInfo>::iterator iter = textures.begin();
	while (iter != textures.end())
	{
		glDeleteTextures(1, &iter->second.textureID);
		iter++;
	}
	textures.clear();
}

inline string TextureResource::getAbsoluteDir(string imgName)
{
	return this->imgBaseDir.append(imgName);
}

bool TextureResource::addTexture(string imgName)
{
	//stbi_set_flip_vertically_on_load(true);
	ImgInfo info;
	unsigned char *data = stbi_load(getAbsoluteDir(imgName).c_str(), &info.width, &info.height, &info.channels, 0);
	if (data == nullptr) {
		return false;
	}
	glGenTextures(1, &info.textureID);
	glBindTexture(GL_TEXTURE_2D, info.textureID);
	if (info.channels == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.width, info.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if(info.channels==4){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.width, info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	this->textures.insert(pair<string, ImgInfo>(imgName, info));
	stbi_image_free(data);
	return true;
}

TextureResource::ImgInfo TextureResource::getTexture(string imgName)
{
	map<string, ImgInfo>::iterator iter = textures.find(imgName);
	if (iter == textures.end())
	{
		return ImgInfo();
	}
	return iter->second;
}


bool TextureResource::applyTexture(string imgName)
{
	ImgInfo info = getTexture(imgName);
	if (info.width != 0)
	{
		glBindTexture(GL_TEXTURE_2D, info.textureID);
		return true;
	}
	else {
		//材质尚未加载，试图动态加载
		if (addTexture(imgName)) {
			applyTexture(imgName);
			return true;
		}
	}
	//内存中和文件夹目录下都没有
	return false;
}

bool TextureResource::applyTexture(string imgName, ImgInfo *imgInfo)
{
	*imgInfo = getTexture(imgName);
	if (imgInfo->width != 0)
	{
		glBindTexture(GL_TEXTURE_2D, imgInfo->textureID);
		return true;
	}
	else {
		//材质尚未加载，试图动态加载
		if (addTexture(imgName)) {
			applyTexture(imgName, imgInfo);
			return true;
		}
	}
	//内存中和文件夹目录下都没有
	return false;
}


