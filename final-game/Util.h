

#pragma once

#ifdef _WIN32

#include <time.h>
#include <SDL.h>
#include <math.h>

#else

#endif

class Util
{
public:    
    int static GenerateRandom(int l, int u);

	double static CosDeg(double angle);

	double static SinDeg(double angle);
};

