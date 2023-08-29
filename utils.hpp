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
enum ErrorCode {
  EVERYTHING_FINE = 0, ERROR_NULLPTR, ERROR_BAD_NUMBER, ERROR_BAD_FILE, ERROR_OVERLAP,
  ERROR_INDEX_OUT_OF_BOUNDS
};

/**
 * @brief Represtents ErrorCode names
 */
static const char* ErrorNames[] = { "OKAY", "ERROR_NULLPTR", "ERROR_BAD_NUMBER",
                                    "ERROR_BAD_FILE", "ERROR_OVERLAP",
                                    "ERROR_INDEX_OUT_OF_BOUNDS" };

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
({                                                                                                                  \
    SetConsoleColor(stderr, RED);                                                                                   \
    fprintf(stderr, "%s in %s in %s in line: %d\n", ErrorNames[ERR_CODE], __FILE__, __PRETTY_FUNCTION__, __LINE__); \
    SetConsoleColor(stderr, WHITE);                                                                                 \
    EXIT_CMD;                                                                                                       \
    exit(ERR_CODE);                                                                                                 \
})

 /**
  * @brief Finds max of x, y.
  */
#define max(x, y)                                                                                                   \
({                                                                                                                  \
    __typeof__(x) _tx = x; __typeof__(y) _ty = y;                                                                   \
    _tx > _ty ? _tx : _ty;                                                                                          \
})

#define min(x, y)                                                                                                   \
({                                                                                                                  \
    __typeof__(x) _tx = x; __typeof__(y) _ty = y;                                                                   \
    _tx < _ty ? _tx : _ty;                                                                                          \
})

#define ArrayLength(array) sizeof(array) / sizeof(array[0])

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