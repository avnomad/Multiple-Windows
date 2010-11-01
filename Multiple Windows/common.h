#ifndef COMMON_H
#define COMMON_H

#include <Windows.h>

#define length(A) (sizeof(A)/sizeof((A)[0]))
#define esquape(A) TEXT(#A)

extern int windowCounter;

#endif // COMMON_H