//! @file

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/** @enum ConsoleColor
 * @brief Represents colors for @see SetConsoleColor
 */
enum class ConsoleColor
{
    COLOR_BLACK = 30,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
};

/** @enum ErrorCode
 * @brief Represents possible error codes for @see MyAssertHard()
 */
enum ErrorCode
{
    EVERYTHING_FINE = 0, ERROR_NULLPTR, ERROR_BAD_NUMBER, ERROR_BAD_FILE, ERROR_OVERLAP,
    ERROR_INDEX_OUT_OF_BOUNDS, ERROR_NO_MEMORY, ERROR_NO_COMPARATOR, ERROR_BAD_SIZE,
    ERROR_BAD_VALUE, ERROR_DEAD_CANARY, ERROR_BAD_HASH, ERROR_ZERO_DIVISION,
    ERROR_SYNTAX, ERROR_WRONG_LABEL_SIZE, ERROR_TOO_MANY_LABELS,
    ERROR_NOT_FOUND, ERROR_BAD_FIELDS, ERROR_BAD_TREE, ERROR_NO_ROOT,
    ERROR_TREE_LOOP, ERROR_SDL, ERROR_NOT_OWNER, EXIT,
};

static const size_t SIZET_POISON = (size_t)-1;

#define GET_FILE_NAME()       __FILE__
#define GET_LINE()            __LINE__
#define GET_PRETTY_FUNCTION() __PRETTY_FUNCTION__
#define CREATE_ERROR(code) Error(code, GET_FILE_NAME(), GET_LINE(), GET_PRETTY_FUNCTION())

struct Error
{
    ErrorCode   code;
    const char* file;
    size_t      line;
    const char* function;

    Error(ErrorCode code, const char* file, size_t line, const char* function) noexcept;

    const char* GetErrorName() const noexcept;
};

/**
 * @brief Prints colored error to stderr
 *
 * @param error
 */
#define PRINT_ERROR(error)                                                  \
do                                                                          \
{                                                                           \
    __typeof__(error) _print_error = error;                                 \
    if (_print_error) SetConsoleColor(stdout, COLOR_RED);                   \
    else SetConsoleColor(stdout, COLOR_GREEN);                              \
    fprintf(stdout, "%s in %s:%d in %s\n",                                  \
            ERROR_CODE_NAMES[_print_error], __FILE__, __LINE__,             \
            __PRETTY_FUNCTION__);                                           \
    SetConsoleColor(stdout, COLOR_WHITE);                                   \
    fflush(stdout);                                                         \
} while (0)


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
void Swap(void* a, void* b, size_t size);

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
size_t GetFileSize(const char* path);

/**
 * @brief Calculates hash
 *
 * @param [in] key - the object to hash
 * @param [in] len - length in bytes
 * @param [in] - salt
 * @return unsigned int hash
 */
uint64_t CalculateHash(const void* key, size_t length, uint64_t seed);

/**
 * @brief Writes several spaces to a stream
 *
 * @param [in] where - where to emit spaces
 * @param [in] spacesCount - how much spaces to emit
 */
void WriteSpaces(FILE* where, size_t spacesCount);

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
