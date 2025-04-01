#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

unsigned char
mstrncmp(const char *target, const char *entrances[], unsigned char c)
{
  unsigned char i = 0;
  for (i=0; i<c; i++)
  {
    switch (strncmp(target, entrances[i], 8))
    {
      case 0: return i+1;
      default: break;
    }
  }
  return 0;
}

unsigned char
iffile(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char path[1024] = {0};
  vsprintf(path, format, args);
  va_end(args);

  FILE *stream = fopen(path, "rb");
  if (stream == NULL)
  { return 0; }
  fclose(stream);

  return 1;
}

unsigned char
ifdir(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char path[1024] = {0};
  vsprintf(path, format, args);
  va_end(args);

  struct stat statbuf;
  if (stat(path, &statbuf) != 0)
  { return 0; }
  return S_ISDIR(statbuf.st_mode);
}

unsigned char
ifsymlink(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char path[1024] = {0};
  vsprintf(path, format, args);
  va_end(args);

  struct stat statbuf;
  if (lstat(path, &statbuf) < 0)
  { return 1; }
  return S_ISLNK(statbuf.st_mode);
}

