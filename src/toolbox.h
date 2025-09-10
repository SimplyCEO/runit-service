#ifndef TOOLBOX_HEADER
#define TOOLBOX_HEADER

#include "types.h"

char* strformat(const char* format, ...);
uint8_t mstrncmp(const char* target, const char* entrances[], uint8_t c);
bool iffile(const char* path);
bool ifdir(const char* path);
bool ifsymlink(const char* path);

#endif

