#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include "Utils.hpp"

const double ABSOLUTE_TOLERANCE = 1e-5;

bool Utils::DoubleEqual(const double x1, const double x2)
{
	return abs(x1 - x2) < ABSOLUTE_TOLERANCE;
}

std::size_t Utils::GetFileSize(const char* path)
{
    struct stat result = {};
    stat(path, &result);

    return (std::size_t)result.st_size;
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

void Utils::SetConsoleColor(std::ostream& out, ConsoleColor color)
{
	out << "\033[0;" << static_cast<int>(color) << "m";
}

uint64_t Utils::TickTimer::Stop()
{
	m_endTicks = GetCPUTicks();
	return m_endTicks - m_startTicks;
}

Utils::Timer::Timer()
	: m_start(m_clock.now()) {}

Utils::Timer::Clock::duration Utils::Timer::Stop()
{
	m_end = Clock::now();

	return m_end - m_start;
}
