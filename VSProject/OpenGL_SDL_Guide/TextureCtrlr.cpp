#include "TextureCtrlr.h"
#include "TextureObject.h"

#include <iostream>

// Constructor
TextureCtrlr::TextureCtrlr()
{

}

// Destructor
TextureCtrlr::~TextureCtrlr()
{
	TextureList::iterator itr;
	for(itr = this->allTextures.begin(); itr != this->allTextures.end(); itr++)
	{
		delete *itr;
	}

	this->allTextures.clear();
}

// Creates a new texture given the image file into OpenGL
void TextureCtrlr::CreateNewTexture(GLuint textureUnit, const char* textureFilePath, const char* nameInShader)
{
	// Create new texture object
	TextureObject* newTexture = new TextureObject(textureUnit);
	newTexture->SetNameInShader(nameInShader);
	newTexture->LoadTextureFileIntoOpenGL(textureFilePath);

	// Add new texture to the list
	this->allTextures.push_back(newTexture);
}

// Sets up the texture unit's wrapping and min/mag filters
void TextureCtrlr::SetupTextureProperties(GLuint textureUnit, GLenum wrapping, GLenum filtering)
{
	// Find the texture by given unit
	TextureObject* identfiedTexture = this->FindTextureByUnit(textureUnit);
	
	// Complain if texture not found
	if(identfiedTexture == NULL)
	{
		std::cout << "Warning: TextureCtrlr::SetupTextureProperties(): Texture unit not found!" << std::endl;
		return;
	}

	// Set up properties
	identfiedTexture->SetupProperties(wrapping, filtering);
}

// Find a texture by it's texture unit
TextureObject* TextureCtrlr::FindTextureByUnit(GLuint textureUnit)
{
	TextureObject* foundTexture = NULL;

	TextureList::iterator itr;
	for(itr = this->allTextures.begin(); itr != this->allTextures.end(); itr++)
	{
		GLuint currentUnit = static_cast<TextureObject*>(*itr)->GetTextureUnitNum();
		if(currentUnit == textureUnit)
		{
			foundTexture = static_cast<TextureObject*>(*itr);
			break;
		}
	}

	return foundTexture;
}

// Find a texture by it's texture ID
TextureObject* TextureCtrlr::FindTextureByID(GLuint textureID)
{
	TextureObject* foundTexture = NULL;

	TextureList::iterator itr;
	for(itr = this->allTextures.begin(); itr != this->allTextures.end(); itr++)
	{
		GLuint currentID = static_cast<TextureObject*>(*itr)->GetTextureID();
		if(currentID == textureID)
		{
			foundTexture = static_cast<TextureObject*>(*itr);
			break;
		}
	}

	return foundTexture;
}

// Get the texture's name in the shaders assigned to the texture unit
const char* TextureCtrlr::GetTextureName(GLuint textureUnit)
{
	TextureObject* theTexture = this->FindTextureByUnit(textureUnit);

	if(theTexture == NULL)
	{
		std::cout << "Warning: TextureCtrlr::GetTextureName(): Texture not found!" << std::endl;
		return NULL;
	}

	return theTexture->GetTextureName();
}

// Get the amount of textures handled internally
int TextureCtrlr::GetNumberOfTextures()
{
	return this->allTextures.size();
}