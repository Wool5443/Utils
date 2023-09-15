#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "Utils.hpp"

const double ABSOLUTE_TOLERANCE = 1e-5;

void selectionSort(void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction);

void quickSort(void* start, void* end, size_t elementSize, CompareFunction_t* compareFunction);

void* partion(void* left, void* right, size_t elementSize, CompareFunction_t compareFunction);

void sort3(void* data, size_t elementSize, CompareFunction_t compareFunction);

void sort2(void* data, size_t elementSize, CompareFunction_t compareFunction);

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
	MyAssertHard(data, ERROR_NULLPTR, );
	MyAssertHard(compareFunction, ERROR_NO_COMPARATOR, );

	quickSort(data, data + (elementCount - 1) * elementSize, elementSize, compareFunction);
}

void selectionSort(void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction)
{
	MyAssertHard(data, ERROR_NULLPTR, );
	MyAssertHard(compareFunction, ERROR_NO_COMPARATOR, );

	for (size_t i = 0; i < elementCount; i++)
	{
		const void* temp = MinArray(data + i * elementSize, elementCount - i, elementSize, compareFunction);
		SWAP(data + i * elementSize, temp, elementSize);
	}
}

void quickSort(void* start, void* end, size_t elementSize, CompareFunction_t* compareFunction)
{
	MyAssertHard(start, ERROR_NULLPTR, );
	MyAssertHard(end, ERROR_NULLPTR, );

	if (end <= start)
		return;
	size_t dataLength = (size_t)((char*)end - (char*)start) / elementSize + 1;

	switch (dataLength)
	{
	case 2:
		sort2(start, elementSize, compareFunction);
		return;
	case 3:
		sort3(start, elementSize, compareFunction);
		return;	
	default:
		break;
	}

	void* pivot = partion(start, end, elementSize, compareFunction);

	quickSort(start, pivot - elementSize, elementSize, compareFunction);
	quickSort(pivot + elementSize, end, elementSize, compareFunction);
}

void* partion(void* start, void* end, size_t elementSize, CompareFunction_t compareFunction)
{
	MyAssertHard(start, ERROR_NULLPTR, );
	MyAssertHard(end, ERROR_NULLPTR, );
	
	srand(time(NULL));
	size_t arrayLength = ((size_t)end - (size_t)start) / elementSize + 1;

	void* pivotPtr = start + (rand() % (arrayLength - 2) + 1) * elementSize;
	void* pivotValue = calloc(1, elementSize);
	memmove(pivotValue, pivotPtr, elementSize);

	// printf("Pivot = %d\n", *(int*)pivotValue);

	void* left  = start;
	void* right = end;

	while (left < right)
	{
		int comp1 = compareFunction(left, pivotValue);
		int comp2 = compareFunction(right, pivotValue);
		while (comp1 < 0)
		{
			left += elementSize;
			comp1 = compareFunction(left, pivotValue);
		}
		while (compareFunction(right, pivotValue) > 0) 
		{
			right -= elementSize;
			comp2 = compareFunction(right, pivotValue);
		}

		// printf("Left = %d Right = %d\n", *(int*)left, *(int*)right);

		// for (void* t = start; t <= end; t += elementSize)
		// 	printf("%d ", *(int*)t);
		// printf("\n");

		if(comp1 == 0 && comp2 == 0)
			right -= elementSize;
		else
			SWAP(left, right, elementSize);

		// for (void* t = start; t <= end; t += elementSize)
		// 	printf("%d ", *(int*)t);
		// printf("\n\n");
	}

	free(pivotValue);
	return left;
}

void sort3(void* data, size_t elementSize, CompareFunction_t compareFunction)
{
	if (compareFunction(data, data + elementSize) > 0)
		SWAP(data, data + elementSize, elementSize);
	if (compareFunction(data + elementSize, data + 2 * elementSize) > 0)
		SWAP(data + elementSize, data + 2 * elementSize, elementSize);
	if (compareFunction(data, data + elementSize) > 0)
		SWAP(data, data + elementSize, elementSize);
}

void sort2(void* data, size_t elementSize, CompareFunction_t compareFunction)
{
	if (compareFunction(data, data + elementSize) > 0)
		SWAP(data, data + elementSize, elementSize);
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
