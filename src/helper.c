#include <stdio.h>

#include "main.h"
 
void
print_help(void)
{
  printf("%s%s\n\n%s%s%s\n\n%s\n  %s\n  %s\n  %s\n  %s\n  %s\n  %s\n  %s\n  %s\n  %s\n  %s\n  %s\n  %s\n",
    appname, ": A custom tool to manage runit services.",
    "Usage: ", appname, " <mode> <service>",
    "Available modes:",
    "list    -  List all available services.",
    "unlink  -  Detach the service from directory.",
    "link    -  Create a symbolic link of the service to the `runsvdir` directory.",
    "enabled -  List the enabled services.",
    "disable -  Disable a service from activating at boot.",
    "enable  -  Enable a service activation after boot.",
    "status  -  Display the service information.",
    "start   -  Start the service.",
    "restart -  Stop and start the service.",
    "stop    -  Stop the service.",
    "purge   -  Will stop, unlink, and remove the service permanently.",
    "journal -  Listen kernel logs."
  );
}

void
print_version(void)
{
  printf("%s %s%d.%d.%d:\n  %s\n  %s\n",
    appname, VERSION_PREFIX, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH,
    "GitHub: https://github.com/SimplyCEO/runit-service.git",
    "GitLab: https://gitlab.com/SimplyCEO/runit-service.git"
  );
}

unsigned char
print_usage(void)
{
  fprintf(stderr, "Usage: %s <mode> <service>\nMore info: -h.\n", appname);
  return 1;
}

