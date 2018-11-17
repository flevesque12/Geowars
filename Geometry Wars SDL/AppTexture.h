#pragma once

#ifndef APPTEXTURE_H
#define APPTEXTURE_H

#include "AppIncludes.h"

class AppTexture
{
public:

	// Constructors
	AppTexture();
	~AppTexture();

	// Methods
	bool loadFromFile(std::string path, SDL_Renderer* renderer, float sizeMultiplier);
#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font);
#endif
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
	SDL_Rect getRenderQuad();

private:
	// Parameters
	SDL_Texture* mTexture;
	SDL_Rect renderQuad;
	int mWidth;
	int mHeight;
};

#endif // !APPTEXTURE_H
