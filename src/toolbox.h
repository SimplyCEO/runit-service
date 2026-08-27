#if !defined(TOOLBOX_H)
# define TOOLBOX_H

# if defined(__cplusplus)
extern "C"
{
# endif

# include <stdarg.h>

# include "types.h"

# if (__STDC_VERSION__ < 199901L) && !defined(__cplusplus)
int32_t _vsprintf(char* src, const char* format, va_list ap);
#   define vsprintf _vsprintf
# endif

char* strfmt(const char* format, ...);
uint8_t mstrncmp(const char* target, const char* entrances[], uint8_t c);
bool iffile(const char* path);
bool ifdir(const char* path);
bool ifsymlink(const char* path);

# if defined(__cplusplus)
}
# endif

#endif

