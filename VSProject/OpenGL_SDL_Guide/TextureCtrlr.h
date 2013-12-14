// Texture Controller (TextureCtrlr)
// Manages multiple textures
//
// Written by Jibran Syed

#ifndef TEXTURE_CTRLR
#define TEXTURE_CTRLR

#include <GL/glew.h>

#if defined(_MSC_VER)
#include <SDL_opengl.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

#include <list>

class TextureObject;

typedef std::list<TextureObject*> TextureList;


class TextureCtrlr
{
public:
	TextureCtrlr();
	~TextureCtrlr();

	// Creates a new texture given the image file into OpenGL
	void CreateNewTexture(GLuint textureUnit, const char* textureFilePath, const char* nameInShader);

	// Sets up the texture unit's wrapping and min/mag filters
	void SetupTextureProperties(GLuint textureUnit, GLenum wrapping, GLenum filtering);

	TextureObject* FindTextureByUnit(GLuint textureUnit);	// Find a texture by it's texture unit
	TextureObject* FindTextureByID(GLuint textureID);	// Find a texture by it's texture ID

	const char* GetTextureName(GLuint textureUnit);		// Get the texture's name in the shaders assigned to the texture unit
	int GetNumberOfTextures();							// Get the amount of textures handled internally

private:

	TextureList allTextures;	// Link list of all texture objects

};

#endif