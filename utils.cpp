#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "utils.hpp"

const double ABSOLUTE_TOLERANCE = 1e-5;

bool IsEqual(const double x1, const double x2)
{
	return fabs(x1 - x2) < ABSOLUTE_TOLERANCE;
}

void CopyArray(double destination[], double source[], int length)
{
	MyAssertHard(destination, ERROR_NULLPTR, );
	MyAssertHard(source, ERROR_NULLPTR, );

	for (int i = 0; i < length; i++)
		destination[i] = source[i];
}

void ClearBuffer(void)
{
	while (getchar() != '\n') { ; }
}

bool CheckInput()
{
	int c = getchar();
	while (c == ' ' || c == '\t') { c = getchar(); }

	return c == '\n';
}

void SetConsoleColor(FILE* place, const enum Color color)
{
	switch (color)
	{
	case RED:
		fprintf(place, "\033[0;31m");
		break;
	case GREEN:
		fprintf(place, "\033[0;32m");
		break;
	case WHITE:
		fprintf(place, "\033[0;37m");
		break;
	default: //set the color to white
		fprintf(place, "\033[0;37m");
		break;
	}
}