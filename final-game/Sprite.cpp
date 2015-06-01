#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#else
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#endif

#include <string>
#include <stdio.h>
#include <iostream>

#include "Util.h"
#include "Sprite.h"


bool Sprite::loadFromFile(std::string path, int n)
{
	_nframes = n;
	free();
	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	//Color key image
	Uint8 r, g, b, a = 190;
	SDL_GetRGB(((Uint32 *)loadedSurface->pixels)[0], loadedSurface->format, &r, &g, &b);
	
	//printf ("cores = %d %d %d\n", r, g, b);

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));

	//	SDL_SetColorKey (loadedSurface, SDL_TRUE, SDL_MapRGB (loadedSurface->format, 0, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(_gRenderer, loadedSurface);

	if (newTexture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	//Get image dimensions
	_Width = loadedSurface->w / n;
	_Height = loadedSurface->h;

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	//Return success
	
	

	_Texture = newTexture;

	SDL_SetTextureBlendMode(_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(_Texture, a);

	return _Texture != NULL;
}

void Sprite::free()
{
	if (_Texture != NULL) {
		SDL_DestroyTexture(_Texture);
		_Texture = NULL;
		_Height = 0;
		_Width = 0;
	}
}

void Sprite::setRenderer(SDL_Renderer * gRend) {
	_gRenderer = gRend;
}

void Sprite::render(int x, int y) {

	SDL_Rect renderQuad = { x, y, (int) _Width, (int) _Height};

	SDL_RenderCopyEx(_gRenderer, _Texture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);

}

void Sprite::render(int x, int y, SDL_Rect* cam) {

	SDL_Rect renderQuad = { x, y, cam->w, cam->h };

	SDL_RenderCopyEx(_gRenderer, _Texture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
}

bool Sprite::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	TTF_Font *gFont = TTF_OpenFont("media/emulogic.ttf", 20);

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		_Texture = SDL_CreateTextureFromSurface(_gRenderer, textSurface);
		if (_Texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_Width = textSurface->w;
			_Height = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}


	//Return success
	return _Texture != NULL;
}


