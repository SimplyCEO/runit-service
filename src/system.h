#ifndef SYSTEM_HEADER
#define SYSTEM_HEADER

#include "types.h"

void exec(const char* cmd);
bool rm(const char* path);
bool touch(const char* path);
bool link_service(const char* service);

#endif

