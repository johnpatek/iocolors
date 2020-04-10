#include "iocolors.h"

int encode_font(
    font_t * const font, 
    uint8_t style, 
    uint8_t foreground, 
    uint8_t background)
{
    int error;

    error = (font == NULL);

    if(error == 0)
    {
        switch(style)
        {
            case NONE:
                break;
            default:
                error = 1;
        }
    }

    if(error == 0)
    {
        switch(foreground)
        {
            case DEFAULT:
                foreground = 0;
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
                break;
            default:
                error = 1;
        }
    }

    if(error == 0)
    {
        switch (background)
        {
            case DEFAULT:
                background = 0;
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
                break;
            default:
                error = 1;
        }
    }

    error =  (error != 0) || (sprintf(
        (char*)font->buf,
        "\033[%hhu;%hhu;%hhum",
        style,
        foreground,
        background) < 0);
    
    font->good = (error == 0);

    return error;    
}

int decode_font(
    const font_t * const font, 
    uint8_t * const style, 
    uint8_t * const foreground, 
    uint8_t * const background)
{
    int error;
    uint8_t tmp_stl, tmp_fg, tmp_bg;

    error = (font->good != 0);

    error = error || (sscanf(
        (char*)font->buf,
        "\033[%hhu;%hhu;%hhu",
        &tmp_stl,
        &tmp_fg,
        &tmp_fg) < 0);

    if(!error)
    {
        *style = tmp_stl;

        if(tmp_fg != DEFAULT)
        {
            *foreground = tmp_fg % 39;
        }
        else
        {
            *foreground = DEFAULT;
        }
        
        if(tmp_bg != DEFAULT)
        {
            *background = tmp_bg % 39;
        }
        else
        {
            *background = DEFAULT;
        }
    }

    return error;
}

int ioc_eprintf(const font_t * const font, const char * const format, ...)
{
    int result;
    va_list args;

    va_start(args,format);

    result = ioc_set_stderr_font(font)?-1:0;

    result = (result < 0)?-1:vfprintf(stderr,format,args);

    result = (result < 0)?result:(
        ioc_reset_stderr_font() == 0)?result:-1;

    return result;
}

int ioc_eputs(const font_t * const font, const char * const str)
{
    int result;
    
    result = ioc_set_stderr_font(font)?-1:0;

    result = (result < 0)?-1:eputs(str);

    result = (result < 0)?result:(
        ioc_reset_stderr_font() == 0)?result:-1;

    return result;
}

int ioc_printf(const font_t * const font, const char * const format, ...)
{
    int result;
    va_list args;

    va_start(args,format);

    result = ioc_set_stdout_font(font)?-1:0;

    result = (result < 0)?-1:printf(format,args);

    result = (result < 0)?result:(
        ioc_reset_stdout_font() == 0)?result:-1;

    return result;
}

int ioc_puts(const font_t * const font, const char * const str)
{
    int result;
    
    result = ioc_set_stdout_font(font)?-1:0;

    result = (result < 0)?-1:puts(str);

    result = (result < 0)?result:(
        ioc_reset_stdout_font() == 0)?result:-1;

    return result;
}

int eprintf(const char * const format, ...)
{
    va_list args;
    va_start(args, format);
    return vfprintf(stderr, format, args);    
}

int eputs(const char * const str)
{
    return eprintf("%s\n",str);
}

int ioc_set_stderr_font(const font_t * const font)
{
    return (font->good !=0) || (eprintf(
        "%s",
        (char*)font->buf) < 0);
}

int ioc_set_stdout_font(const font_t * const font)
{
    return (font->good !=0) || (printf(
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