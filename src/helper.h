#if !defined(HELPER_H)
# define HELPER_H

# if defined(__cplusplus)
extern "C"
{
# endif

# include "types.h"

void print_help(void);
void print_version(void);
bool print_usage(void);

# if defined(__cplusplus)
}
# endif

#endif

