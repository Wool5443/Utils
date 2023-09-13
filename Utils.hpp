//! @file

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Represents colors for @see SetConsoleColor
 */
enum Color { RED, GREEN, WHITE };

/**
 * @brief Represents possible error codes for @see MyAssertHard()
 */
enum ErrorCode 
{
  EVERYTHING_FINE = 0, ERROR_NULLPTR, ERROR_BAD_NUMBER, ERROR_BAD_FILE, ERROR_OVERLAP,
  ERROR_INDEX_OUT_OF_BOUNDS, ERROR_NO_MEMORY
};

typedef int CompareFunction_t(const void* a, const void* b);

/**
 * @brief Hard assert which tells the file, function and line where the error occured.
 *
 * @param [in] STATEMENT - the condition to check.
 * @param [in] ERR_CODE - what can happen @see ErrorCode.
 * @param [in] EXIT_CMD - operation to perform before exiting the program.
 *
 * @note If there is nothing to perform pass nothing.
 */
#define MyAssertHard(STATEMENT, ERR_CODE, EXIT_CMD)                                                                 \
if (!(STATEMENT))                                                                                                   \
do {                                                                                                                \
    SetConsoleColor(stderr, RED);                                                                                   \
    fprintf(stderr, "%s in %s in %s in line: %d\n", #ERR_CODE, __FILE__, __PRETTY_FUNCTION__, __LINE__);            \
    SetConsoleColor(stderr, WHITE);                                                                                 \
    EXIT_CMD;                                                                                                       \
    exit(ERR_CODE);                                                                                                 \
} while(0);

/**
 * @brief Finds max of x, y.
 */
#define max(x, y)                                                                                                   \
({                                                                                                                  \
    __typeof__(x) _tx = x; __typeof__(y) _ty = y;                                                                   \
    _tx > _ty ? _tx : _ty;                                                                                          \
})

/**
 * @brief Finds min of x, y.
 */
#define min(x, y)                                                                                                   \
({                                                                                                                  \
    __typeof__(x) _tx = x; __typeof__(y) _ty = y;                                                                   \
    _tx < _ty ? _tx : _ty;                                                                                          \
})

#define SWAP(a, b, size)                                                                                            \
do                                                                                                                  \
{                                                                                                                   \
    char* _a = (char*)a;                                                                                            \
    char* _b = (char*)b;                                                                                            \
                                                                                                                    \
    for (size_t curByte = 0; curByte < size; curByte++)                                                             \
    {                                                                                                               \
        char _temp = _a[curByte];                                                                                   \
        _a[curByte] = _b[curByte];                                                                                  \
        _b[curByte] = _temp;                                                                                        \
    }                                                                                                               \
                                                                                                                    \
} while (0);                                                                                                        \

#define ArrayLength(array) (sizeof(array) / sizeof(array[0]))

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
 * @brief Copies <length> element from source to destination starting at zero index.
 *
 * @param destination
 * @param source
 * @param length
 */
void CopyArray(double destination[], double source[], int length);

const void* MinArray(const void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction);
const void* MaxArray(const void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction);

/**
 * @brief Sorts the given array according to the Compare Function
*/
void Sort(void* data, size_t elementCount, size_t elementSize, CompareFunction_t* compareFunction);

/**
 * @brief Clears stdin.
 */
void ClearBuffer(void);

/**
 * @brief Check if the user input contains anything but scanned data.
 *
 * @return true Everything is clear.
 * @return false User entered something odd.
 */
bool CheckInput(void);

/**
 * @brief Set the color of either stderr or stdout
 *
 * @param place - stderr or stdout
 * @param color - @see Color
 */
void SetConsoleColor(FILE* place, const enum Color color);

#endif