#if !defined(SYSTEM_H)
# define SYSTEM_H

# if defined(__cplusplus)
extern "C"
{
# endif

# include "types.h"

void exec(const char* cmd);
bool rm(const char* path);
bool touch(const char* path);
bool link_service(const char* service);

# if defined(__cplusplus)
}
# endif

#endif

