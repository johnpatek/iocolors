#include <stdio.h>
#include <stdarg.h>

enum colors
{
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    BOLD_RED,
    BOLD_GREEN,
    BOLD_YELLOW,
    BOLD_BLUE,
    BOLD_MAGENTA,
    BOLD_CYAN,
    DEFAULT
};

/**
 * @brief Formatted print to standard error in a specific color
 * @param[in] color Desired color for the text.
 * @param[in] format C string containing text to be printed, with
 *                   optional format specifiers embedded.
 * @param[in] ... Values to be printed if format specifiers are
 *                present
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int color_eprintf(int color, const char * const format, ...);

/**
 * @brief Write string to standard error in a specific color and 
 *        append newline
 * @param[in] str C string to be printed.
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int color_eputs(int color, const char * const str);

/**
 * @brief Formatted print to standard output in a specific color
 * @param[in] color Desired color for the text.
 * @param[in] format C string containing text to be printed, with
 *                   optional format specifiers embedded.
 * @param[in] ... Values to be printed if format specifiers are
 *                present
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int color_printf(int color, const char * const format, ...);


int color_puts(int color, const char * const str);

/**
 * @brief Formatted print to standard error
 * @param[in] format C string containing text to be printed, with
 *                   optional format specifiers embedded.
 * @param[in] ... Values to be printed if format specifiers are
 *                present
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int eprintf(const char * const format, ...);

/**
 * @brief Write string to standard error and append newline
 * @param[in] str C string to be printed.
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int eputs(const char * const str);

int set_stderr_color(int color);

int set_stdout_color(int color);

int reset_stderr_color();

int reset_stdout_color();