#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include "Utils.hpp"

Utils::Error::Error(ErrorCode code, const char* file, std::size_t line, const char* function) noexcept
	: code(code), file(file), line(line), function(function) {}

static const char* ERROR_CODE_NAMES[] =
{
    "EVERYTHING_FINE", "ERROR_NULLPTR", "ERROR_BAD_NUMBER", "ERROR_BAD_FILE", "ERROR_OVERLAP",
    "ERROR_INDEX_OUT_OF_BOUNDS", "ERROR_NO_MEMORY", "ERROR_NO_COMPARATOR", "ERROR_BAD_SIZE",
    "ERROR_BAD_VALUE", "ERROR_DEAD_CANARY", "ERROR_BAD_HASH", "ERROR_ZERO_DIVISION",
    "ERROR_SYNTAX", "ERROR_WRONG_LABEL_SIZE", "ERROR_TOO_MANY_LABELS",
    "ERROR_NOT_FOUND", "ERROR_BAD_FIELDS", "ERROR_BAD_TREE", "ERROR_NO_ROOT",
    "ERROR_TREE_LOOP", "ERROR_SDL", "ERROR_NOT_OWNER", "EXIT",
};
const char* Utils::Error::GetErrorName() const noexcept
{
	return ERROR_CODE_NAMES[(std::size_t)this->code];
}

void Utils::Error::Print() const noexcept
{
	if (*this) SetConsoleColor(stdout, ConsoleColor::RED);
	else       SetConsoleColor(stdout, ConsoleColor::GREEN);
	Print(stdout);
	SetConsoleColor(stdout, ConsoleColor::WHITE);
	fflush(stdout);
}

void Utils::Error::Print(FILE* file) const noexcept
{
	fprintf(file, "%s in %s:%zu in %s\n",
			GetErrorName(), this->file, line,
			function);
	fflush(file);
}

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

	FILE* file = fopen(filePath, "r");
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
