#if !defined(MAIN_H)
# define MAIN_H

# if defined(__cplusplus)
extern "C"
{
# endif

# include "types.h"

# define VERSION_PREFIX 'a'
# define VERSION_MAJOR 0
# define VERSION_MINOR 2
# define VERSION_PATCH 3

# define RUNIT_AVAILABLE_SERVICES "/etc/runit/sv"
# define RUNIT_LOADED_SERVICE_PATH "/run/runit/service"
# define RUNIT_DEFAULT_SERVICE_PATH "/etc/runit/runsvdir/default"

typedef enum
{
  MODE_NONE,
  MODE_UNLINK,
  MODE_LINK,
  MODE_DISABLE,
  MODE_ENABLE,
  MODE_STATUS,
  MODE_STOP,
  MODE_RESTART,
  MODE_START,
  MODE_PURGE,
  MODE_LIST,
  MODE_ENABLED,
  MODE_JOURNAL
} service_mode;

extern const char* appname;

# if defined(__cplusplus)
}
# endif

#endif

