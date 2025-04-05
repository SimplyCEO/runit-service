#include <stdio.h>

#include "main.h"
 
void
print_help(void)
{
  printf("%s: A custom tool to manage runit services.\n\
          \r\n\
          \rUsage: %s <mode> <service>\n\
          \r\n\
          \rAvailable modes:\n\
          \r\tlist    -  List the services located at '/etc/runit/sv'.\n\
          \r\tunlink  -  Unlink the service from '/etc/runit/runsvdir/default'.\n\
          \r\tlink    -  Link the service from '/etc/runit/sv' to '/etc/runit/runsvdir/default'.\n\
          \r\tenabled -  List the enabled services located at '/etc/runit/runsvdir/default'.\n\
          \r\tdisable -  Disable a service from activating at boot.\n\
          \r\tenable  -  Enable a service activation after boot.\n\
          \r\tstatus  -  Display the service information.\n\
          \r\tstart   -  Start the service.\n\
          \r\trestart -  Stop and start the service.\n\
          \r\tstop    -  Stop the service.\n\
          \r\tpurge   -  Will stop, unlink, and remove the service permanently.\n\
          \r\tjournal -  Listen kernel logs.\n\
          \r\0", appname, appname);
}

void
print_version(void)
{
  printf("%s a0.2.1:\n\
          \r\tGitHub: https://github.com/SimplyCEO/runit-service.git\n\
          \r\tGitLab: https://gitlab.com/SimplyCEO/runit-service.git\n", appname);
}

unsigned char
print_usage(void)
{
  fprintf(stderr, "Usage: %s <mode> <service>\nMore info: -h.\n", appname);
  return 1;
}

