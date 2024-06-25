//! @file

#pragma once

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

/** @enum ErrorCode
 * @brief Represents possible error codes
 */
enum class ErrorCode
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
#define CREATE_ERROR(errorCode) Utils::Error((errorCode), GET_FILE_NAME(), GET_LINE(), GET_PRETTY_FUNCTION())

/** @struct Error
 * @brief Struct for handling errors
 */
struct Error
{
    ErrorCode   code; /**< error code*/
    const char* file; /**< file where error occured*/
    size_t      line; /**< line where error occured*/
    const char* function; /**< function where error occured*/

    /**
     * @brief Construct a new Error object
     * 
     * @param code 
     * @param file 
     * @param line 
     * @param function 
     */
    Error(ErrorCode code, const char* file, size_t line, const char* function) noexcept;
    Error() noexcept
        : code(ErrorCode::EVERYTHING_FINE), file(""), line(0), function("") {}

    operator bool() const noexcept
    {
        return (bool)code;
    }
    operator int() const noexcept
    {
        return (int)code;
    }
    operator ErrorCode() const noexcept
    {
        return code;
    }
    operator double() const noexcept
    {
        return NAN;
    }

    /**
     * @brief Get what the error means
     * 
     * @return const char* 
     */
    const char* GetErrorName()    const noexcept;
    /**
     * @brief Prints error to stdout
     */
    void        Print()           const noexcept;
    /**
     * @brief Prints error into a file
     * 
     * @param file 
     */
    void        Print(FILE* file) const noexcept;
};

#ifdef NDEBUG
#define SoftAssert(...)
#define SoftAssertResult(...)
#else
/**
 * @brief Soft assert
 */
#define SoftAssert(expression, errorCode, ...)                      \
do                                                                  \
{                                                                   \
    if (!(expression))                                              \
    {                                                               \
        Utils::Error _error = CREATE_ERROR(errorCode);              \
        _error.Print();                                             \
        __VA_ARGS__;                                                \
        return _error;                                              \
    }                                                               \
} while(0)

/**
 * @brief Soft assert if function returns a result
 */
#define SoftAssertResult(expression, poison, errorCode, ...)        \
do                                                                  \
{                                                                   \
    if (!(expression))                                              \
    {                                                               \
        Error _error = CREATE_ERROR(errorCode);                     \
        _error.Print();                                             \
        __VA_ARGS__;                                                \
        return { poison, _error };                                  \
    }                                                               \
} while(0)
#endif

/**
 * @brief returns error if it is not EVERYTHING_FINE
 */
#define RETURN_ERROR(error, ...)                                    \
do                                                                  \
{                                                                   \
    Utils::Error _error = error;                                    \
    if (_error)                                                     \
    {                                                               \
        __VA_ARGS__;                                                \
        return _error;                                              \
    }                                                               \
} while(0)

/**
 * @brief returns error and poison if it is not EVERYTHING_FINE
 */
#define RETURN_ERROR_RESULT(error, poison, ...)                     \
do                                                                  \
{                                                                   \
    Utils::Error _error = error;                                    \
    if (_error)                                                     \
    {                                                               \
        __VA_ARGS__;                                                \
        return { poison, _error };                                  \
    }                                                               \
} while(0)

/**
 * @brief returns result if it contains an error
 */
#define RETURN_RESULT(result, ...)                                  \
do                                                                  \
{                                                                   \
    __typeof__(result) _result = result;                            \
    if (_result.error)                                              \
    {                                                               \
        __VA_ARGS__;                                                \
        return _result;                                             \
    }                                                               \
} while(0)

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
}
