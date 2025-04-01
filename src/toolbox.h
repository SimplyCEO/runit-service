#ifndef TOOLBOX_HEADER
#define TOOLBOX_HEADER

unsigned char mstrncmp(const char *target, const char *entrances[], unsigned char c);
unsigned char iffile(const char *format, ...);
unsigned char ifdir(const char *format, ...);
unsigned char ifsymlink(const char *format, ...);

#endif

