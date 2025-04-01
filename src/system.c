#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#include "main.h"
#include "toolbox.h"

void
exec(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char cmd[1024] = {0};
  vsprintf(cmd, format, args);
  va_end(args);

  system(cmd);
}

unsigned char
rm(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char path[1024] = {0};
  vsprintf(path, format, args);
  va_end(args);

  if ((ifdir(path) == 0) || (ifsymlink(path) != 0))
  { return remove(path); }
  return rmdir(path);
}

unsigned char
touch(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char path[1024] = {0};
  vsprintf(path, format, args);
  va_end(args);

  FILE *stream = fopen(path, "wb");
  if (stream == NULL)
  { return 0; }
  fclose(stream);

  return 1;
}

unsigned char
link_service(const char *service)
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

