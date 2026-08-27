#if !defined(TYPES_H)
# define TYPES_H

# if defined(__cplusplus)
extern "C"
{
# endif

# include <stdarg.h>

# if (__STDC_VERSION__ < 199901L) && !defined(__cplusplus)
typedef unsigned char    bool;
typedef signed   char    int8_t;
typedef signed   short   int16_t;
typedef signed   int     int32_t;
typedef unsigned char    uint8_t;
typedef unsigned short   uint16_t;
typedef unsigned int     uint32_t;
#   define false 0
#   define true 1
# else
#   include <stdbool.h>
#   include <stdint.h>
# endif

# define COLOUR_RESET          "\033[0m"
# define COLOUR_RED            "\033[31m"
# define COLOUR_BOLD_RED       "\033[1;31m"
# define COLOUR_GREEN          "\033[32m"
# define COLOUR_BOLD_GREEN     "\033[1;32m"
# define COLOUR_YELLOW         "\033[33m"
# define COLOUR_BOLD_YELLOW    "\033[1;33m"
# define COLOUR_BLUE           "\033[34m"
# define COLOUR_BOLD_BLUE      "\033[1;34m"
# define COLOUR_MAGENTA        "\033[35m"
# define COLOUR_BOLD_MAGENTA   "\033[1;35m"
# define COLOUR_CYAN           "\033[36m"
# define COLOUR_BOLD_CYAN      "\033[1;36m"

# define errprintf(str) fprintf(stderr, "%serror%s: %s\n", COLOUR_RED, COLOUR_RESET, str);

# if defined(__cplusplus)
}
# endif

#endif

