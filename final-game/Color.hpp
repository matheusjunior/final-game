#pragma once

#include <stdint.h> // uint8_t
#include <string>

#ifdef _WIN32
#include <SDL.h>

#else
#include <SDL2/SDL.h>
#endif

class Color
{
public:

	Color();

	/// Creates a RGBA color.
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a=255);

	/// Creates a opaque color based on a color name.
	///
	/// You know, "red", "black", "cyan"...
	Color(std::string colorName);

	/// Adds the RGB values of two colors.
	///
	/// @note If the alpha value is different, defaults to opacque.
	/// @note If the value is out of range, it's padded.
	///
	Color operator+(const Color& color) const;

	/// Subtracts the RGB values of two colors.
	///
	/// @note If the alpha value is different, defaults to opacque.
	/// @note If the value is out of range, it's padded.
	Color operator-(const Color& color) const;

	/// Tests if two RGBA colors are completely equal.
	bool  operator==(const Color& color) const;

	/// Tests if two RGBA colors are different.
	bool  operator!=(const Color& color) const;

	uint8_t r(); ///< Returns the Red part of the color.
	uint8_t g(); ///< Returns the Green part of the color.
	uint8_t b(); ///< Returns the Blue part of the color.
	uint8_t a(); ///< Returns the Alpha part of the color.

	/// Transforms this color into a random one.
	///
	/// @note This doesn't touch the alpha - for that you
	///       need to call randomizeAlpha().
	void randomize();

	/// Transforms this color's alpha into a random one.
	void randomizeAlpha();

	/// Inverts whole color or individial components.
	void invert(bool R=true, bool G=true, bool B=true);

	SDL_Color getSDLColor();

private:
	uint8_t red;   ///< Red component (0 is none, 255 is full).
	uint8_t green; ///< Green component (0 is none, 255 is full).
	uint8_t blue;  ///< Blue component  (0 is none, 255 is full).
	uint8_t alpha; ///< Alpha component (0 is transparent, 255 is opacque).
	SDL_Color mColor;
};

