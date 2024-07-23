#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include "Utils.hpp"

const double ABSOLUTE_TOLERANCE = 1e-5;

bool Utils::IsEqual(const double x1, const double x2)
{
	return fabs(x1 - x2) < ABSOLUTE_TOLERANCE;
}

void Utils::Swap(void* a, void* b, std::size_t size)
{
    char* _a = (char*)a;
    char* _b = (char*)b;

    for (std::size_t curByte = 0; curByte < size; curByte++)
    {
        char _temp = _a[curByte];
        _a[curByte] = _b[curByte];
        _b[curByte] = _temp;
    }
}

void Utils::ClearBuffer(FILE* where)
{
	int c = fgetc(where);
	while (c != '\n' && c != EOF) { c = fgetc(where); }
}

bool Utils::CheckInput(FILE* where)
{
	int c = fgetc(where);
	while (c == ' ' || c == '\t') { c = fgetc(where); }

	return c == '\n';
}

char* Utils::ReadFileToBuf(const char* filePath)
{
	if (!filePath)
		return nullptr;

	std::size_t fileSize = GetFileSize(filePath);

	char* buf = (char*)calloc(fileSize + 2, 1);
	if (!buf)
		return nullptr;

	FILE* file = fopen(filePath, "rb");
	if (!file)
		return nullptr;

	if (fread(buf, 1, fileSize, file) != fileSize)
		return nullptr;

	return buf;
}

void Utils::SetConsoleColor(FILE* where, ConsoleColor color)
{
	fprintf(where, "\033[0;%dm", (int)color);
}

std::size_t Utils::GetFileSize(const char* path)
{
    struct stat result = {};
    stat(path, &result);

    return (std::size_t)result.st_size;
}

#define mmix(h, k) do { k *= m; k ^= k >> r; k *= m; h *= m; h ^= k; } while (0)

uint64_t Utils::CalculateHash(const void *data, std::size_t length, uint64_t seed)
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

void Utils::WriteSpaces(FILE* where, std::size_t spacesCount)
{
	for (std::size_t i = 0; i < spacesCount; i++)
		fputc(' ', where);
}

void Utils::Timer::Start()
{
	startTicks = GetCPUTicks();
}

uint64_t Utils::Timer::Stop()
{
	endTicks   = GetCPUTicks();
	return endTicks - startTicks;
}
