#include "Color.hpp"
#include "Util.h"

Color::Color()
	: red(0), green(0), blue(0), alpha(255)
{ }

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: red(r), green(g), blue(b), alpha(a)
{ }

Color::Color(std::string colorName)
{
	uint8_t r, g, b;

	if (colorName == "white")        { r = 255; g = 255; b = 255; }
	else if (colorName == "black")   { r = 0;   g = 0;   b = 0;   }
	else if (colorName == "red")     { r = 255; g = 0;   b = 0;   }
	else if (colorName == "green")   { r = 0;   g = 255; b = 0;   }
	else if (colorName == "blue")    { r = 0;   g = 0;   b = 255; }
	else if (colorName == "cyan")    { r = 0;   g = 255; b = 255; }
	else if (colorName == "yellow")  { r = 255; g = 255; b = 0;   }
	else if (colorName == "magenta") { r = 255; g = 0;   b = 255; }

	this->red   = r;
	this->blue  = b;
	this->green = g;
	this->alpha = 255;
}
Color Color::operator+(const Color& color) const
{
	int tmp  = 0;

	uint8_t tmpR = 0;
	tmp = this->red + color.red;
	if (tmp > 255) tmpR = 255;
	if (tmp < 0)   tmpR = 0;

	uint8_t tmpG = 0;
	tmp = this->green + color.green;
	if (tmp > 255) tmpG = 255;
	if (tmp < 0)   tmpG = 0;

	uint8_t tmpB = 0;
	tmp = this->blue + color.blue;
	if (tmp > 255) tmpB = 255;
	if (tmp < 0)   tmpB = 0;

	uint8_t tmpA = 255;
	if (this->alpha == color.alpha)
		tmpA = this->alpha;

	Color result(tmpR, tmpG, tmpB, tmpA);
	return result;
}
Color Color::operator-(const Color& color) const
{
	int tmp  = 0;

	uint8_t tmpR = 0;
	tmp = this->red - color.red;
	if (tmp > 255) tmpR = 255;
	if (tmp < 0)   tmpR = 0;

	uint8_t tmpG = 0;
	tmp = this->green - color.green;
	if (tmp > 255) tmpG = 255;
	if (tmp < 0)   tmpG = 0;

	uint8_t tmpB = 0;
	tmp = this->blue - color.blue;
	if (tmp > 255) tmpB = 255;
	if (tmp < 0)   tmpB = 0;

	uint8_t tmpA = 255;
	if (this->alpha == color.alpha)
		tmpA = this->alpha;

	Color result(tmpR, tmpG, tmpB, tmpA);
	return result;
}
bool Color::operator==(const Color& color) const
{
	return ((this->red   == color.red)   &&
	        (this->green == color.green) &&
	        (this->blue  == color.blue)  &&
	        (this->alpha == color.alpha));
}
bool Color::operator!=(const Color& color) const
{
	return ((this->red   != color.red)   &&
	        (this->green != color.green) &&
	        (this->blue  != color.blue)  &&
	        (this->alpha != color.alpha));
}
uint8_t Color::r()
{
	return (this->red);
}
uint8_t Color::g()
{
	return (this->green);
}
uint8_t Color::b()
{
	return (this->blue);
}
uint8_t Color::a()
{
	return (this->alpha);
}
void Color::randomize()
{
	this->red   = Util::GenerateRandom(0, 255);
	this->green = Util::GenerateRandom(0, 255);
	this->blue  = Util::GenerateRandom(0, 255);
}
void Color::randomizeAlpha()
{
	this->alpha = Util::GenerateRandom(0, 255);
}
void Color::invert(bool R, bool G, bool B)
{
	if (R) this->red   = (255 - this->red);
	if (G) this->green = (255 - this->green);
	if (B) this->blue  = (255 - this->blue);
}

SDL_Color Color::getSDLColor() {
	mColor.r = red;
	mColor.g = green;
	mColor.b = blue;
	mColor.a = alpha;

	return mColor;
}
