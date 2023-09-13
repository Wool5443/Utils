#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "Utils.hpp"

const double ABSOLUTE_TOLERANCE = 1e-5;

void selectionSort(void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction);

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

const void* MinArray(const void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction)
{
	const void* min = data;
	for (size_t i = 1; i < elementCount; i++)
		if (compareFunction(min, data + i * elementSize) > 0)
		{
			min = data + i * elementSize;
		}
	return min;	
}

const void* MaxArray(const void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction)
{
	const void* max = data;
	for (size_t i = elementSize; i < elementCount; i++)
		if (compareFunction(max, data + i * elementSize) < 0)
			max = data + i * elementSize;
	return max;	
}

void Sort(void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction)
{
	selectionSort(data, elementCount, elementSize, compareFunction);
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

void selectionSort(void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction)
{
	for (size_t i = 0; i < elementCount; i++)
	{
		const void* temp = MinArray(data + i * elementSize, elementCount - i, elementSize, compareFunction);
		SWAP(data + i * elementSize, temp, elementSize);
	}
}
