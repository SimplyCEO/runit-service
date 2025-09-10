#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#include "main.h"
#include "toolbox.h"
#include "types.h"

void
exec(const char* cmd)
{
  system(cmd);
}

bool
rm(const char* path)
{
  if ((ifdir(path) == 0) || (ifsymlink(path) != 0))
  { return remove(path); }

  return rmdir(path);
}

bool
touch(const char* path)
{
  FILE *stream = fopen(path, "wb");
  if (stream == NULL)
  { return false; }
  fclose(stream);

  return true;
}

bool
link_service(const char* service)
{
  char src[1024] = {0}, dest[1024] = {0};

  strcpy(src, RUNIT_AVAILABLE_SERVICES);
  strcpy(dest, RUNIT_DEFAULT_SERVICE_PATH);
  strcat(src, "/");
  strcat(dest, "/");
  strcat(src, service);
  strcat(dest, service);

  return symlink(src, dest);
}

