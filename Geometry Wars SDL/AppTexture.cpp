#include "AppTexture.h"

AppTexture::AppTexture()
{
}

AppTexture::~AppTexture()
{
}

// Loads the texture from an image file
bool AppTexture::loadFromFile(std::string path, SDL_Renderer* renderer, float sizeMultiplier)
{
	// Free the old texture and sets a new one
	free();
	SDL_Texture* newTexture = NULL;

	// Loads a surface from the image file
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Sets the surface into the texture
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			// Sets the width and height of the texture according to the surface
			mWidth = (int)(loadedSurface->w * sizeMultiplier);
			mHeight = (int)(loadedSurface->h * sizeMultiplier);
		}

		// Free the temporary surface
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
// Creates a texture from text
bool AppTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font)
{
	// Free the old texture
	free();

	// Creates a temporary surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Sets the texture width and height according to the surface size
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Free the temporary surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	return mTexture != NULL;
}
#endif

// Frees the texture
void AppTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

// Sets the color of the texture
void AppTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

// Sets the blend mode of the texture
void AppTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

// Sets the alpha of the texture
void AppTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

// Renders the texture
void AppTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect * clip, double angle, SDL_Point * center, SDL_RendererFlip flip)
{
	// Sets the position and size of the render
	renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int AppTexture::getWidth()
{
	return mWidth;
}

int AppTexture::getHeight()
{
	return mHeight;
}

SDL_Rect AppTexture::getRenderQuad()
{
	return renderQuad;
}