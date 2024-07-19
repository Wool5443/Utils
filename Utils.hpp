#ifndef UTILS_HPP
#define UTILS_HPP

//! @file

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>

namespace Utils
{
/** @enum ConsoleColor
 * @brief Represents colors for @see SetConsoleColor
 */
enum class ConsoleColor
{
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
};

#define ArrayLength(array) sizeof(array) / sizeof(*(array))

 /**
  * @brief Tells if 2 doubles are equal.
  *
  * @param x1
  * @param x2
  *
  * @return true The numbers are equal.
  * @return false The numbers are not equal.
  */
bool IsEqual(const double x1, const double x2);

/**
 * @brief swaps 2 elements a and b in memory.
 *
 * @param [in] a, b - elements to swap.
 * @param [in] size - size of the elements.
*/
void Swap(void* a, void* b, std::size_t size);

/**
 * @brief Clears stdin.
 *
 * @param [in] where - file stream which buffer to clean.
 */
void ClearBuffer(FILE* where);

/**
 * @brief Check if the user input contains anything but scanned data.
 *
 * @param [in] where - file stream where to input.
 *
 * @return true Everything is clear.
 * @return false User entered something odd.
 */
bool CheckInput(FILE* where);

/**
 * @brief Reads a file to a buffer and returns it.
 *
 * @param [in] filePath path to the file.
 * @return char* buffer.
 */
char* ReadFileToBuf(const char* filePath);

/**
 * @brief Set the color of either stderr or stdout
 *
 * @param [in] where - stderr or stdout
 * @param [in] color - @see Color
 */
void SetConsoleColor(FILE* where, ConsoleColor color);

/**
 * @brief Get the file size.
 *
 * @param [in] path to the file.
 * @return size.
 */
std::size_t GetFileSize(const char* path);

/**
 * @brief Calculates hash
 *
 * @param [in] key - the object to hash
 * @param [in] length - length in bytes
 * @param [in] seed
 * 
 * @return uint64_t hash
 */
uint64_t CalculateHash(const void* key, std::size_t length, uint64_t seed);

/**
 * @brief Writes several spaces to a stream
 *
 * @param [in] where - where to emit spaces
 * @param [in] spacesCount - how much spaces to emit
 */
void WriteSpaces(FILE* where, std::size_t spacesCount);

/**
 * @brief Returns ticks passed since CPU start
 *
 * @return uint64_t - number of ticks
 */
static inline __attribute__((always_inline)) uint64_t GetCPUTicks()
{
    uint64_t lo, hi;
    asm("lfence;rdtsc;lfence" : "=a" (lo), "=d" (hi));
    return (hi << 32) + lo;
}

struct Timer
{
    uint64_t startTicks;
    uint64_t endTicks;

    /**
     * @brief Starts the timer
     */
    void     Start();

    /**
     * @brief Stops the timer and return how much ticks passed
     *
     * @return uint64_t ticks
     */
    uint64_t Stop();
};
}

#endif
