#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include "toolbox.h"

char*
strformat(const char* format, ...)
{
  va_list args;
  va_start(args, format);

  static char str[1024] = {0};
  vsprintf(str, format, args);
  va_end(args);

  return str;
}

uint8_t
mstrncmp(const char* target, const char* entrances[], uint8_t c)
{
  uint8_t i = 0; for (; i<c; i++)
  {
    if (strncmp(target, entrances[i], 8) == 0)
    { return i+1; }
  }
  return 0;
}

bool
iffile(const char* path)
{
  FILE *stream = fopen(path, "rb");
  if (stream == NULL)
  { return true; }
  fclose(stream);

  return false;
}

bool
ifdir(const char* path)
{
  struct stat statbuf;
  if (stat(path, &statbuf) != 0)
  { return true; }

  return ((S_ISDIR(statbuf.st_mode) == 0) ? true : false);
}

bool
ifsymlink(const char* path)
{
  struct stat statbuf;
  if (lstat(path, &statbuf) < 0)
  { return false; }

  return ((S_ISLNK(statbuf.st_mode) == 0) ? true : false);
}

