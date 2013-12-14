// TextureObject
// Represents 1 texture in OpenGL
// Assumes all textures are GL_TEXTURE_2D
//
// Written by Jibran Syed

#ifndef TEXTURE_OBJ
#define TEXTURE_OBJ

#include <string>		// May find an alternative later

#include <GL/glew.h>

#if defined(_MSC_VER)
#include <SDL_opengl.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

class TextureObject
{
public:
	// Ctors/Dstor ========

	TextureObject(GLuint textureUnit);
	TextureObject(GLuint textureUnit, GLenum textureUnitEnum);
	~TextureObject();

	// Routines ============

	GLenum GetTextureUnitEnum();								// Getter for texUnit
	GLuint GetTextureUnitNum();									// Getter fpr texUnitNum
	GLuint GetTextureID();										// Getter for texId
	const char* GetTextureName();								// Getter for the texture's name in the shaders
	void SetNameInShader(const char* name);						// Set the texture's name in the shaders
	void LoadTextureFileIntoOpenGL(const char* texturePath);	// Load texture data into OpenGL
	void SetupProperties(GLenum wrapping, GLenum filtering);	// Set texture properties like wrap and min/mag filtering


private:

	// Helpers =============

	void determineTexUnitEnum();				// Determines texUnit bases off texUnitNum
	bool isCorrectWrapValue(GLenum wrap);		// Determine if the wrap parameter is valid
	bool isCorrectFilterValue(GLenum filter);	// Determine if the filter parameter is valid

	// Data ================

	GLenum texUnit;				// The texture unit as a GL enum
	GLuint texUnitNum;			// The texture unit as a number
	std::string nameInShader;	// Name of texture uniform in shader
	GLuint texId;				// The texture ID (not the same thing as texture unit)

};

#endif