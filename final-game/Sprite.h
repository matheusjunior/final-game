
#pragma once

#ifdef _WIN32
#include <SDL.h>

#else
#include <SDL2/SDL.h>
#endif

#include <time.h>
#include <math.h>

class Sprite {
public:	
	float ax0, ay0, ax1, ay1, ax2, ay2, ax3, ay3;
	SDL_Texture *_Texture;
	float _Width, _Height;
	int _nframes;
	
	float _step = 1;
	void setStep(int n) { _step = n; };

	Sprite() { _Texture = NULL; _Width = 0; _Height = 0; };

	Sprite(SDL_Renderer *rend) { 
		_Texture = NULL; 
		_Width = 0; 
		_Height = 0; 
	    _gRenderer = rend;
	};
	
	~Sprite() { free(); };

	bool loadFromFile(std::string, int);

	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue){
		SDL_SetTextureColorMod(_Texture, red, green, blue);
	};
	void setBlendMode(SDL_BlendMode blending) {
		SDL_SetTextureBlendMode(_Texture, blending);
	}
	void setAlpha(Uint8 alpha) {
		SDL_SetTextureAlphaMod(_Texture, alpha);
	}

	void setRenderer(SDL_Renderer* gRend);

	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	void render(int x, int y);

	void render(int x, int y, SDL_Rect* cam);

	void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		//Set rendering space and render to screen
		SDL_Rect renderQuad = {x, y, (int) _Width, (int) _Height};

		//Set clip rendering dimensions
		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(_gRenderer, _Texture, clip, &renderQuad, angle, center, flip);
	}

private:
	SDL_Renderer* _gRenderer;
};
