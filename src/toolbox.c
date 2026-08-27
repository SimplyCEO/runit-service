#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>

#include "types.h"

#if (__STDC_VERSION__ < 199901L) && !defined(__cplusplus)
int32_t
_vsprintf(char* src, const char* format, va_list ap)
{
  int count = 0;

  while (*format != '\0')
  {
    switch (*format)
    {
      case '%':
      {
        format++;
        switch (*format)
        {
          case 'c':
          {
            if (src != NULL)
            { *src++ = (char)va_arg(ap, int); }
            count++;
          } break;
          case 's':
          {
            char* s = va_arg(ap, char*);
            int s_len = 0; for (; *s != '\0'; s++)
            {
              if (src != NULL)
              { *src++ = *s; }
              s_len++;
            }
            count += s_len;
          } break;
          case 'd':
          {
            int num = va_arg(ap, int);
            char buffer[20] = {0};
            int len = sprintf(buffer, "%d", num);
            int i = 0; for (; i < len; i++)
            {
              if (src != NULL)
              { *src++ = buffer[i]; }
              count++;
            }
          } break;
          case '%':
          {
            if (src != NULL)
            { *src++ = '%'; }
            count++;
          } break;
          default:
          {
            if (src != NULL)
            { *src++ = *format; }
            count++;
          } break;
        }
      } break;
      default:
      {
        if (src != NULL)
        { *src++ = *format; }
        count++;
      } break;
    }
    format++;
  }
  if (src != NULL)
  { *src = '\0'; }

  return count;
}
#endif

char*
strfmt(const char* format, ...)
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
  int32_t i = 0;
  for (; i<c; i++)
  {
    if (strncmp(target, entrances[i], 8) == 0)
    { return i+1; }
  }
  return 0;
}

bool
iffile(const char* path)
{
  FILE* stream = fopen(path, "rb");
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

