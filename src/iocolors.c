#include "iocolors.h"

// Helper function for ioc_decode_font()
static int count_semicolons(
    const uint8_t* const buf,
    const uint32_t len);

int ioc_encode_font(
    ioc_font_t* const font,
    uint8_t style,
    uint8_t foreground,
    uint8_t background)
{
    int error;
    char* buf;
    int32_t len;
    int32_t off;

    error = (font == NULL);
    len = IOC_BUFFER_SIZE;
    buf = NULL;

    if (error == 0)
    {
        buf = (char*)font->buf;
#ifdef _WIN32
        off = sprintf_s(
            buf,
            len,
            "\033[");
#else
        off = sprintf(
            buf,
            "\033[");
#endif
        buf += off;
        len -= off;
        error = (off < 0) || (len < 0);
    }

    if (error == 0)
    {
        switch (style)
        {
        case NONE:
        case BRIGHT:
        case DIM:
        case UNDERSCORE:
        case BLINK:
        case REVERSE:
        case HIDDEN:
#ifdef _WIN32
            off = sprintf_s(
                buf,
                len,
                "%hhu",
                style);
#else
            off = sprintf(
                buf,
                "%hhu", style);
#endif
            buf += off;
            len -= off;
            error = (off < 0) || (len < 0);
            break;
        default:
            error = 1;
        }
    }

    if (error == 0)
    {
        switch (foreground)
        {
        case DEFAULT:
            break;
        case BLACK:
        case RED:
        case GREEN:
        case YELLOW:
        case BLUE:
        case MAGENTA:
        case CYAN:
        case WHITE:
            foreground += 29;
#ifdef _WIN32
            off = sprintf_s(
                buf,
                len,
                ";%hhu",
                foreground);
#else
            off = sprintf(
                buf,
                ";%hhu",
                foreground);
#endif
            buf += off;
            len -= off;
            error = (off < 0) || (len < 0);
            break;
        default:
            error = 1;
        }
    }

    if (error == 0)
    {
        switch (background)
        {
        case DEFAULT:
            break;
        case BLACK:
        case RED:
        case GREEN:
        case YELLOW:
        case BLUE:
        case MAGENTA:
        case CYAN:
        case WHITE:
            background += 39;
#ifdef _WIN32
            off = sprintf_s(
                buf,
                len,
                ";%hhu",
                background);
#else
            off = sprintf(
                buf,
                ";%hhu",
                background);
#endif
            buf += off;
            len -= off;
            error = (off < 0) || (len < 0);
            break;
        default:
            error = 1;
        }
    }

#ifdef _WIN32
    error = (error != 0) || (sprintf_s(
        buf,
        len,
        "m") < 0);
#else
    error = (error != 0) || (sprintf(
        buf,
        "m") < 0);
#endif

    return error;
}

int ioc_decode_font(
    const ioc_font_t* const font,
    uint8_t* const style,
    uint8_t* const foreground,
    uint8_t* const background)
{
    int error;
    char* buf;
    uint32_t data_buf[3];

    error = (font == NULL) || (font->good == 0);

    if (error == 0)
    {
        buf = (char*)font->buf;
        switch (
            count_semicolons(
                (const uint8_t * const)buf,
                (uint32_t)strlen(buf)))
        {
        case 2:
            printf("2\n");
#ifdef _WIN32
            error = (error != 0) || (sscanf_s(
                buf,
                "\033[%d;%d;%d",
                &data_buf[0],
                &data_buf[1],
                &data_buf[2]) < 0);
#else
            error = (error != 0) || (sscanf(
                buf,
                "\033[%d;%d;%d",
                &data_buf[0],
                &data_buf[1],
                &data_buf[2]) < 0);
#endif
            if (error == 0)
            {
                *style = (uint8_t)data_buf[0];
                *foreground = (uint8_t)(data_buf[1] % 29);
                *background = (uint8_t)(data_buf[2] % 39);
            }
            break;
        case 1:
            printf("1\n");
#ifdef _WIN32
            error = (error != 0) || (sscanf_s(
                buf,
                "\033[%d;%d",
                &data_buf[0],
                &data_buf[1]) < 0);
#else
            error = (error != 0) || (sscanf(
                buf,
                "\033[%d;%d",
                &data_buf[0],
                &data_buf[1]) < 0);
#endif
            if (error == 0)
            {
                *style = (uint8_t)data_buf[0];
                if (data_buf[1] < 40)
                {
                    *foreground = (uint8_t)(data_buf[1] % 29);
                    *background = DEFAULT;
                }
                else
                {
                    *foreground = DEFAULT;
                    *background = (uint8_t)(data_buf[1] % 39);
                }
            }
            break;
        case 0:
            printf("0\n");
            *style = NONE;
            *foreground = DEFAULT;
            *background = DEFAULT;
            break;
        default:
            printf("error\n");
            error = 1;
        }
    }

    return error;
}

int ioc_eprintf(const ioc_font_t* const font, const char* const format, ...)
{
    int result;
    va_list args;

    va_start(args, format);

    result = ioc_set_stderr_font(font) ? -1 : 0;

    result = (result < 0) ? -1 : vfprintf(stderr, format, args);

    result = (result < 0) ? result : (
        ioc_reset_stderr_font() == 0) ? result : -1;

    return result;
}

int ioc_eputs(const ioc_font_t* const font, const char* const str)
{
    int result;

    result = ioc_set_stderr_font(font) ? -1 : 0;

    result = (result < 0) ? -1 : eputs(str);

    result = (result < 0) ? result : (
        ioc_reset_stderr_font() == 0) ? result : -1;

    return result;
}

int ioc_printf(const ioc_font_t* const font, const char* const format, ...)
{
    int result;
    va_list args;

    va_start(args, format);

    result = ioc_set_stdout_font(font) ? -1 : 0;

    result = (result < 0) ? -1 : vprintf(format, args);

    result = (result < 0) ? result : (
        ioc_reset_stdout_font() == 0) ? result : -1;

    return result;
}

int ioc_puts(const ioc_font_t* const font, const char* const str)
{
    int result;

    result = ioc_set_stdout_font(font) ? -1 : 0;

    result = (result < 0) ? -1 : puts(str);

    result = (result < 0) ? result : (
        ioc_reset_stdout_font() == 0) ? result : -1;

    return result;
}

int eprintf(const char* const format, ...)
{
    va_list args;
    va_start(args, format);
    return vfprintf(stderr, format, args);
}

int eputs(const char* const str)
{
    return eprintf("%s\n", str);
}

int ioc_set_stderr_font(const ioc_font_t* const font)
{
    return (font->good == 0) || (eprintf(
        "%s",
        (char*)font->buf) < 0);
}

int ioc_set_stdout_font(const ioc_font_t* const font)
{
    return (font->good == 0) || (printf(
        "%s",
        (char*)font->buf) < 0);
}

int ioc_reset_stderr_font()
{
    return eprintf("\033[0m") < 0;
}

int ioc_reset_stdout_font()
{
    return printf("\033[0m") < 0;
}

static int count_semicolons(
    const uint8_t* const buf,
    const uint32_t len)
{
    uint32_t res, off;

    res = 0;

    for (off = 0; off < len; off++)
    {
        res += ((char)(*(buf + off)) == ';');
    }

    return res;
}