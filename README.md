# IOColors

IOColors is a simple, cross-platform library for adding text colors 
and effects to your print statements. Written entirely
in C, a thin layer is built on top of stdio to provide you with
a quick and reliable solution with no dependencies.

## Using the IOColors API

The API allows you to add some style to your print statements to 
either stderr or stdout.

### Printing to stderr

Like `printf()` and `puts()`, IOColors adds the stderr equivalents
`eprintf()` and `eputs()` functions. They take identical parameters
and provide identical return values.

### Creating a font

Before printing your colored output, you must create a font. A font 
can easily be created using the `ioc_encode_font()` function.

```c
font_t font;
ioc_encode_font(&font, BRIGHT, GREEN, BLUE);
```

For more information on available font options, see `iocolors.h`.

### Printing a single line

One option for printing output with style is use the single line 
functions provided by `ioc_printf()` and other functions prepended by
`ioc_`.

```c
ioc_puts(&font,"This is a formatted string printed to stdout.");
```
All following print statements will have the default terminal colors
set.

### Printing multiple lines

Another option for printing output with style is using the API to set
the font and then make regular stdio calls. This can be done using
`ioc_stdout_set_font()` or `ioc_stdout_set_font()`. When you want to
revert the colors to the terminal default, you can use the functions
`ioc_stdout_reset_font()` or `ioc_stdout_set_font()`.

```c
ioc_stderr_set_font(&font);
puts("Print a line to stderr");
puts("Print another line to stderr");
ioc_stderr_reset_font();
puts("This is a line with the default colors");
```
