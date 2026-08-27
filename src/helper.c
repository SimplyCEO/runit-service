#include <stdio.h>

#include "main.h"
 
void
print_help(void)
{
  printf(
    "%s: A custom tool to manage runit services.\n\n"
    "Usage: %s <mode> <service>\n\n"
    "Available modes:\n"
    "  list    -  List all available services.\n"
    "  unlink  -  Detach the service from directory.\n"
    "  link    -  Create a symbolic link of the service to the `runsvdir` directory.\n"
    "  enabled -  List the enabled services.\n"
    "  disable -  Disable a service from activating at boot.\n"
    "  enable  -  Enable a service activation after boot.\n"
    "  status  -  Display the service information.\n"
    "  start   -  Start the service.\n"
    "  restart -  Stop and start the service.\n"
    "  stop    -  Stop the service.\n"
    "  purge   -  Will stop, unlink, and remove the service permanently.\n"
    "  journal -  Listen kernel logs.\n",
    appname, appname
  );
}

void
print_version(void)
{
  printf(
    "%s %c%d.%d.%d:\n"
    "  GitHub: https://github.com/SimplyCEO/runit-service.git\n"
    "  GitLab: https://gitlab.com/SimplyCEO/runit-service.git\n",
    appname, VERSION_PREFIX, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH
  );
}

bool
print_usage(void)
{
  fprintf(stderr, "Usage: %s <mode> <service>\nMore info: -h.\n", appname);
  return 1;
}

