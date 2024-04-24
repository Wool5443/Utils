#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include "Utils.hpp"

const double ABSOLUTE_TOLERANCE = 1e-5;

bool IsEqual(const double x1, const double x2)
{
	return fabs(x1 - x2) < ABSOLUTE_TOLERANCE;
}

void Swap(void* a, void* b, size_t size)
{
    char* _a = (char*)a;
    char* _b = (char*)b;

    for (size_t curByte = 0; curByte < size; curByte++)
    {
        char _temp = _a[curByte];
        _a[curByte] = _b[curByte];
        _b[curByte] = _temp;
    }
}

void ClearBuffer(FILE* where)
{
	int c = fgetc(where);
	while (c != '\n' && c != EOF) { c = fgetc(where); }
}

bool CheckInput(FILE* where)
{
	int c = fgetc(where);
	while (c == ' ' || c == '\t') { c = fgetc(where); }

	return c == '\n';
}

char* ReadFileToBuf(const char* filePath)
{
	if (!filePath)
		return nullptr;

	size_t fileSize = GetFileSize(filePath);

	char* buf = (char*)calloc(fileSize + 2, 1);
	if (!buf)
		return nullptr;

	FILE* file = fopen(filePath, "r");
	if (!file)
		return nullptr;

	if (fread(buf, 1, fileSize, file) != fileSize)
		return nullptr;

	return buf;
}

void SetConsoleColor(FILE* where, enum Color color)
{
	fprintf(where, "\033[0;%dm", (int)color);
}

size_t GetFileSize(const char* path)
{
    MyAssertHard(path, ERROR_NULLPTR, );

    struct stat result = {};
    stat(path, &result);

    return (size_t)result.st_size;
}

#define mmix(h, k) do { k *= m; k ^= k >> r; k *= m; h *= m; h ^= k; } while (0)

uint64_t CalculateHash(const void *data, size_t length, uint64_t seed)
{
	const uint64_t m = 0x5bd1e9955bd1e995;
	const uint64_t r = 24;
	uint64_t       l = length;

	const unsigned char* d = (const unsigned char*)data;

	uint64_t h = seed;
	uint64_t k;

	while(length >= 4)
	{
		k = *(unsigned int*)d;

		mmix(h,k);

		d += 4;
		length -= 4;
	}

	uint64_t t = 0;

	switch(length)
	{
	case 3:
		t ^= (d[2] << 16);
		break;
	case 2:
		t ^= (d[1] << 8);
		break;
	case 1:
		t ^= d[0];
		break;
	default: 
		break;
	};

	mmix(h,t);
	mmix(h,l);

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

void WriteSpaces(FILE* where, size_t spacesCount)
{
	for (size_t i = 0; i < spacesCount; i++)
		fputc(' ', where);
}

void Timer::Start()
{
	this->startTicks = GetCPUTicks();
}

uint64_t Timer::Stop()
{
	this->endTicks   = GetCPUTicks();
	return endTicks - startTicks;
}
