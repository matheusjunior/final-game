#pragma once

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <direct.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#endif

#include <stdio.h>
#include <string>

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setTransparency(Uint8 alpha) {
		SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(mTexture, alpha);
	}

	//Gets image dimensions
	int getWidth();
	int getHeight();

	void setRenderer(SDL_Renderer *renderer);

private:
	//The actual hardware texture
	SDL_Texture  *mTexture;
	SDL_Renderer *mRenderer;

	//Image dimensions
	int mWidth;
	int mHeight;
};
