#pragma once

#include "stdafx.h"
#include "Texture.h"

namespace newPix
{
	class TextureMgr
	{
	public:
		/*

		- GL_TEXTURE_MIN_FILTER

			GL_NEAREST_MIPMAP_NEAREST
			GL_LINEAR_MIPMAP_NEAREST
			GL_NEAREST_MIPMAP_LINEAR
			GL_LINEAR_MIPMAP_LINEAR
			GL_NEAREST
			GL_LINEAR

		- GL_TEXTURE_MAG_FILTER

			GL_LINEAR
			GL_NEAREST

		*/
		__declspec(dllexport) TextureMgr();
		__declspec(dllexport) ~TextureMgr();
		__declspec(dllexport) bool initialise();

		__declspec(dllexport) void addTexture(	char* filename, std::string alias,
												GLint min_filter = GL_LINEAR,
												GLint mag_filter = GL_LINEAR,
												GLint wrap_type = GL_REPEAT);

		__declspec(dllexport) void deleteTexture(std::string alias);
		__declspec(dllexport) Texture* getTexture(std::string alias);
		
		Texture* loadTexture(char* filename, GLint min, GLint mag, GLint wrap);
		std::map<std::string, Texture*> mTextureList;
	};
}