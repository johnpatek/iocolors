#ifndef IOCOLORS_H
#define IOCOLORS_H

/**
 * @file
 * @brief This file contains the functions from the iocolors API
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#define IOC_BUFFER_SIZE 12


typedef struct
{
    uint8_t buf[IOC_BUFFER_SIZE];
    uint8_t good;
} ioc_font_t;

enum styles
{
    NONE = 0,
    BRIGHT = 1,
    DIM = 2,
    UNDERSCORE = 4,
    BLINK = 5,
    REVERSE = 7,
    HIDDEN = 8
};

enum colors
{
    DEFAULT,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

/**
 * @brief Encode a font
 * @param[out] font A pointer to the encoded font
 * @param[in] style The desired formatting style
 * @param[in] foreground The desired foreground font
 * @param[in] background The desired background font
 * @return 0 on success, nonzero on failure.
 */
int ioc_encode_font(
    ioc_font_t * const font, 
    uint8_t style, 
    uint8_t foreground, 
    uint8_t background);

/**
 * @brief Decode a font
 * @param[in] font A previously encoded font
 * @param[out] style The decoded formatting style
 * @param[out] foreground The decoded foreground font
 * @param[out] background The decoded background font
 * @return 0 on success, nonzero on failure.
 */
int ioc_decode_font(
    const ioc_font_t * const font, 
    uint8_t * const style, 
    uint8_t * const foreground, 
    uint8_t * const background);

/**
 * @brief Formatted print to standard error in a specific font
 * @param[in] font Desired font for the text.
 * @param[in] format C string containing text to be printed, with
 *                   optional format specifiers embedded.
 * @param[in] ... Values to be printed if format specifiers are
 *                present
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int ioc_eprintf(const ioc_font_t * const font, const char * const format, ...);

/**
 * @brief Write string to standard error in a specific font and 
 *        append newline
 * @param[in] str C string to be printed.
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int ioc_eputs(const ioc_font_t * const font, const char * const str);

/**
 * @brief Formatted print to standard output in a specific font
 * @param[in] font Desired font for the text.
 * @param[in] format C string containing text to be printed, with
 *                   optional format specifiers embedded.
 * @param[in] ... Values to be printed if format specifiers are
 *                present
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int ioc_printf(const ioc_font_t * const font, const char * const format, ...);

/**
 * @brief Write string to standard output in a specific font and 
 *        append newline
 * @param[in] str C string to be printed.
 * @return On success, the total number of characters written is 
 *         returned. If error occurs, a negative number is returned.
 */
int ioc_puts(const ioc_font_t * const font, const char * const str);

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

/**
 * @brief Set stderr font
 * @param[in] font Desired font for stderr
 * @return 0 on success, nonzero on failure
 */
int ioc_set_stderr_font(const ioc_font_t * const font);

/**
 * @brief Set stdout font
 * @param[in] font Desired font for stderr
 * @return 0 on success, nonzero on failure
 */
int ioc_set_stdout_font(const ioc_font_t * const font);

/**
 * @brief Reset stderr font
 * @return 0 on success, nonzero on failure
 */
int ioc_reset_stderr_font();

/**
 * @brief Reset stdout font
 * @return 0 on success, nonzero on failure
 */
int ioc_reset_stdout_font();

#endif /* IOCOLORS_H */
