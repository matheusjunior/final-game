#include <stdlib.h>
#include "Util.h"

#ifdef _WIN32

#include <time.h>
#include <Windows.h>
#include <SDL.h>

#else

#endif

#include <math.h>


int Util::GenerateRandom(int l, int u)
{
    double r = rand() % ((u - l) + 1);
    r = l + r;

	return (int) r;
}

double Util::CosDeg(double angle) {
	
	if (angle == 90) return 0;
	double angleradians = angle * M_PI / 180.0f;
	return cos(angleradians);
}

double Util::SinDeg(double angle) {
	double angleradians = angle * M_PI / 180.0f;
	return sin(angleradians);
}

// git reset --hard <sha1-commit-id>