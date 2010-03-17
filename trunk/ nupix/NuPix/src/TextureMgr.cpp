#include "GeometryMgr.h"
#include "TextureMgr.h"

using namespace newPix;

TextureMgr::TextureMgr()
{

}

TextureMgr::~TextureMgr()
{
	printf("  -TextureMgr... ");

	std::map<std::string, Texture*>::iterator it = mTextureList.begin();
	uint32 id; 
	for (it; it != mTextureList.end(); it++)
	{
		id = (it->second->mID);
		glDeleteTextures(1,&id);
		delete (it->second);
	}
	printf("Done.\n");
}

bool TextureMgr::initialise()
{
	printf("  -TextureMgr... ");
	mTextureList["null"] = new Texture(0,1,1);
	printf("Done.\n");
	return true;
}

void TextureMgr::addTexture(char* filename, std::string alias, GLint min_filter, GLint mag_filter, GLint wrap_type)
{
	mTextureList[alias] = loadTexture(filename, min_filter, mag_filter, wrap_type);
}

void TextureMgr::deleteTexture(std::string alias)
{
	glDeleteTextures(1, &(mTextureList[alias]->mID));
}

Texture* TextureMgr::getTexture(std::string alias)
{
	return mTextureList[alias];
}

Texture* TextureMgr::loadTexture(char *filename, GLint min, GLint mag, GLint wrap)
{
	SDL_Surface* surface = IMG_Load(filename);
	GLuint texture;
	GLenum texture_format;
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	GLuint nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4)
	{
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	} 
	else if (nOfColors == 3)
	{
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	} 

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
	texture_format, GL_UNSIGNED_BYTE, surface->pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h, texture_format, GL_UNSIGNED_BYTE, surface->pixels);

	Texture* ret = new Texture(texture, surface->w, surface->h);

	SDL_FreeSurface(surface);

	return ret;
} 
