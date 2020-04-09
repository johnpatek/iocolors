#include "iocolors.h"


static int encode_color(int color, const char ** code);

int color_eprintf(int color, const char * const format, ...)
{
    int result;
    va_list args;
    
    set_stderr_color(color);
    
    va_start(args, format);
    
    result = vfprintf(stderr, format, args);
    
    reset_stderr_color();
    
    return result;
}

int color_eputs(int color, const char * const str)
{
    int result; 

    set_stderr_color(color);
    
    result = eputs(str);
    
    reset_stderr_color();

    return result;
}

int color_printf(int color, const char * const format, ...)
{
    int result;
    va_list args;

    set_stdout_color(color);
    
    va_start(args, format);
    
    result = printf(format,args);
    
    reset_stdout_color();
    
    return result ;
}

int color_puts(int color, const char * const str)
{
    int result;
    
    set_stdout_color(color);
    
    result = puts(str);
    
    reset_stdout_color();
    
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

int set_stderr_color(int color)
{
    char * code;
    int error;

    error = encode_color(color,&code);

    error = (error > 0) || (eprintf((const char * const)code) < 0);
    
    return error;
}

int set_stdout_color(int color)
{
    char * code;
    int error;

    error = encode_color(color,&code);

    error = (error > 0) || (printf((const char * const)code) < 0);

    return error;
}

int reset_stderr_color()
{
    return set_stderr_color(DEFAULT);
}

int reset_stdout_color()
{
    return set_stdout_color(DEFAULT);
}

static int encode_color(int color, const char ** code)
{
    int result = 0;
    switch (color)
    {
    case RED:
        *code = "\033[0;31m";
        break;
    case GREEN:
        *code = "\033[0;32m";
        break;
    case YELLOW:
        *code = "\033[0;33m";
        break;
    case BLUE:
        *code = "\033[0;34m";
        break;
    case MAGENTA:
        *code = "\033[0;35m";
        break;
    case CYAN:
        *code = "\033[0;36m";
        break;
    case BOLD_RED:
        *code = "\033[1;31m";
        break;
    case BOLD_GREEN:
        *code = "\033[1;32m";
        break;
    case BOLD_YELLOW:
        *code = "\033[1;33m";
        break;
    case BOLD_BLUE:
        *code = "\033[1;34m";
        break;
    case BOLD_MAGENTA:
        *code = "\033[1;35m";
        break;
    case BOLD_CYAN:
        *code = "\033[1;36m";
        break;
    case DEFAULT:
        *code = "\033[0m";
        break;
    default:
        *code = NULL;
        result = 1;
        break;
    }
    return result;
}