#ifndef TYPES_HEADER_FILE
#define TYPES_HEADER_FILE

#ifndef true
#define true  1
#endif
#ifndef false
#define false 0
#endif

#define COLOUR_RESET          "\033[0m"
#define COLOUR_RED            "\033[31m"
#define COLOUR_BOLD_RED       "\033[1;31m"
#define COLOUR_GREEN          "\033[32m"
#define COLOUR_BOLD_GREEN     "\033[1;32m"
#define COLOUR_YELLOW         "\033[33m"
#define COLOUR_BOLD_YELLOW    "\033[1;33m"
#define COLOUR_BLUE           "\033[34m"
#define COLOUR_BOLD_BLUE      "\033[1;34m"
#define COLOUR_MAGENTA        "\033[35m"
#define COLOUR_BOLD_MAGENTA   "\033[1;35m"
#define COLOUR_CYAN           "\033[36m"
#define COLOUR_BOLD_CYAN      "\033[1;36m"

#define errprintf(str) fprintf(stderr, "%serror%s: %s\n", COLOUR_RED, COLOUR_RESET, str);

#ifndef int8_t
#define int8_t signed char
#endif
#ifndef int16_t
#define int16_t signed short
#endif
#ifndef int32_t
#define int32_t signed int
#endif
#ifndef uint8_t
#define uint8_t unsigned char
#endif
#ifndef uint16_t
#define uint16_t unsigned short
#endif
#ifndef uint32_t
#define uint32_t unsigned int
#endif
#ifndef bool
#define bool unsigned char
#endif

#endif

