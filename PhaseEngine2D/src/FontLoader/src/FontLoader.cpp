#include <glad/glad.h>
#include "FontLoader.h"
#include <iostream>

FontLoader::FontLoader()
{
}

FontLoader::FontLoader(string path)
{
	if (FT_Init_FreeType(&libruary)) {
		std::cout << "FT ERROR INIT LIB" << std::endl;
	}
	if (FT_New_Face(libruary, path.c_str(), 0, &face)) {
		std::cout << "FT ERROR INIT FACE" << std::endl;
	}
}

FontLoader::~FontLoader()
{
	if (face != nullptr) {
		FT_Done_Face(face);
	}
	if (libruary != nullptr) {
		FT_Done_FreeType(libruary);
	}
}

void FontLoader::setSize(int width, int height)
{
	if (width + height) {
		this->charWidth = width;
		this->charHeight = height;
	}
	else {
		this->charWidth = 0;
		this->charHeight = 10;
	}
}

unsigned char * FontLoader::getCharBitmap(FT_ULong c, int *width, int *height)
{
	if (FT_Set_Pixel_Sizes(face,this->charWidth, this->charHeight)) {
		std::cout << "FT ERROR INIT SIZE" << std::endl;
		return nullptr;
	}
	if (FT_Set_Char_Size(face, this->charWidth *64, this->charHeight *64,0,0)) {
		std::cout << "FT ERROR INIT SIZE" << std::endl;
		return nullptr;
	}
	int index = FT_Get_Char_Index(face, c);
	int error = FT_Load_Glyph(face, index, FT_LOAD_DEFAULT);
	if (error) {
		std::cout << "FT ERROR LOAD" << std::endl;
		return nullptr;
	}
	if (face->glyph->format!= FT_GLYPH_FORMAT_BITMAP) {
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if (error) {
			std::cout << "FT RENDER ERROR" << std::endl;
		}
	}
	*width = face->glyph->bitmap.width;
	*height = face->glyph->bitmap.rows;
	return face->glyph->bitmap.buffer;
}
