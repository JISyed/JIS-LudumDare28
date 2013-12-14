#include "TextureObject.h"

#include <FreeImage.h>
#include <iostream>

// Constructor
TextureObject::TextureObject(GLuint textureUnit) : 
	texUnitNum(textureUnit)
{
	this->determineTexUnitEnum();

	// Generate the texture for OpenGL
	glGenTextures(1, &(this->texId));
}

TextureObject::TextureObject(GLuint textureUnit, GLenum textureUnitEnum) : 
	texUnitNum(textureUnit) , 
	texUnit(textureUnitEnum)
{
	// Generate the texture for OpenGL
	glGenTextures(1, &(this->texId));
}

// Destructor
TextureObject::~TextureObject()
{
	// Free the texture
	glDeleteTextures(1, &(this->texId));
}

// Determines texUnit bases off texUnitNum
void TextureObject::determineTexUnitEnum()
{
	switch (this->texUnitNum)
	{
		case 0: texUnit = GL_TEXTURE0; break;
		case 1: texUnit = GL_TEXTURE1; break;
		case 2: texUnit = GL_TEXTURE2; break;
		case 3: texUnit = GL_TEXTURE3; break;
		case 4: texUnit = GL_TEXTURE4; break;
		case 5: texUnit = GL_TEXTURE5; break;
		case 6: texUnit = GL_TEXTURE6; break;
		case 7: texUnit = GL_TEXTURE7; break;
		case 8: texUnit = GL_TEXTURE8; break;
		case 9: texUnit = GL_TEXTURE9; break;
		case 10: texUnit = GL_TEXTURE10; break;
		case 11: texUnit = GL_TEXTURE11; break;
		case 12: texUnit = GL_TEXTURE12; break;
		case 13: texUnit = GL_TEXTURE13; break;
		case 14: texUnit = GL_TEXTURE14; break;
		case 15: texUnit = GL_TEXTURE15; break;
		case 16: texUnit = GL_TEXTURE16; break;
		case 17: texUnit = GL_TEXTURE17; break;
		case 18: texUnit = GL_TEXTURE18; break;
		case 19: texUnit = GL_TEXTURE19; break;
		case 20: texUnit = GL_TEXTURE20; break;
		case 21: texUnit = GL_TEXTURE21; break;
		case 22: texUnit = GL_TEXTURE22; break;
		case 23: texUnit = GL_TEXTURE23; break;
		case 24: texUnit = GL_TEXTURE24; break;
		case 25: texUnit = GL_TEXTURE25; break;
		case 26: texUnit = GL_TEXTURE26; break;
		case 27: texUnit = GL_TEXTURE27; break;
		case 28: texUnit = GL_TEXTURE28; break;
		case 29: texUnit = GL_TEXTURE29; break;
		case 30: texUnit = GL_TEXTURE30; break;
		case 31: texUnit = GL_TEXTURE31; break;

		default: texUnit = GL_NONE; break;
	}
}

// Determine if the wrap parameter is valid
bool TextureObject::isCorrectWrapValue(GLenum wrap)
{
	if( wrap == GL_REPEAT ||			// The integer part of the coordinate will be ignored and a repeating pattern is formed.
		wrap == GL_CLAMP_TO_BORDER ||	// The coordinates that fall outside the range will be given a specified border color.
		wrap == GL_MIRRORED_REPEAT ||	// The texture will also be repeated, but it will be mirrored when the integer part of the coordinate is odd.
		wrap == GL_CLAMP_TO_EDGE )		// The coordinate will simply be clamped between 0 and 1.
	{
		return true;
	}

	// Invalid GLenum
	return false;
}		

// Determine if the filter parameter is valid
bool TextureObject::isCorrectFilterValue(GLenum filter)
{
	if( filter == GL_NEAREST ||					// Returns the pixel that is closest to the coordinates.
		filter == GL_LINEAR ||					// Returns the weighted average of the 4 pixels surrounding the given coordinates.
		filter == GL_NEAREST_MIPMAP_NEAREST ||	// Sample from mipmaps instead.
		filter == GL_LINEAR_MIPMAP_NEAREST ||	// Sample from mipmaps instead.
		filter == GL_NEAREST_MIPMAP_LINEAR ||	// Sample from mipmaps instead. (Bilinear)
		filter == GL_LINEAR_MIPMAP_LINEAR)		// Sample from mipmaps instead. (Trilinear)
	{
		return true;
	}

	// Invalid GLenum
	return false;
}	

// Getter for texUnit
GLenum TextureObject::GetTextureUnitEnum()
{
	return this->texUnit;
}					

// Getter fpr texUnitNum
GLuint TextureObject::GetTextureUnitNum()
{
	return this->texUnitNum;
}									

// Getter for texId
GLuint TextureObject::GetTextureID()
{
	return this->texId;
}									

// Getter for the texture's name in the shaders
const char* TextureObject::GetTextureName()
{
	return this->nameInShader.c_str();
}

// Set the texture's name in the shaders
void TextureObject::SetNameInShader(const char* name)
{
	this->nameInShader = std::string(name);
}

// Load texture data into OpenGL
void TextureObject::LoadTextureFileIntoOpenGL(const char* texturePath)
{
	// Make sure this texture object is the current active texture
	glActiveTexture(this->texUnit);
	glBindTexture(GL_TEXTURE_2D, this->texId);

	// Load the image file
	GLubyte * imageBuffer = NULL;

	FIBITMAP* imageFile = FreeImage_Load(FreeImage_GetFileType(texturePath, 0), texturePath);
	FIBITMAP* imageFile32 = FreeImage_ConvertTo32Bits(imageFile);
	FreeImage_Unload(imageFile);
	FreeImage_FlipVertical(imageFile32); // Don't load upside-down
	int width = FreeImage_GetWidth(imageFile32);
	int height = FreeImage_GetHeight(imageFile32);

	// Create texture in OpenGL friendly format
	imageBuffer = FreeImage_GetBits(imageFile32);

	// Load the textures into OpenGL
	// FreeImage has strange bit arrangement, thus the GL_BGRA
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGRA,
				  GL_UNSIGNED_BYTE, (GLvoid*) imageBuffer);

	FreeImage_Unload(imageFile32);
}

// Set texture properties like wrap and min/mag filtering
void TextureObject::SetupProperties(GLenum wrapping, GLenum filtering)
{
	// Check valid parameters
	if( ! isCorrectWrapValue(wrapping))
	{
		std::cout << "Warning: Invalid wrapping enumeration in TextureObject::SetupProperties()\n";
		std::cout << "         Defaulting to GL_REPEAT\n";
		
		wrapping = GL_REPEAT;
	}

	if( ! isCorrectFilterValue(filtering))
	{
		std::cout << "Warning: Invalid filtering enumeration in TextureObject::SetupProperties()\n";
		std::cout << "         Defaulting to GL_NEAREST\n";

		filtering = GL_NEAREST;
	}

	// Make sure this texture object is the current active texture
	glActiveTexture(this->texUnit);
	glBindTexture(GL_TEXTURE_2D, this->texId);

	// Set UV values out of range to repeat the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

	// Set the texture border color (if using GL_CLAMP_TO_BORDER)
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// Set minification and magnification filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

	// Generate mipmaps for the current texture
	glGenerateMipmap(GL_TEXTURE_2D);
}