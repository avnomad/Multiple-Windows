#ifndef MOVING_WINDOW_H
#define MOVING_WINDOW_H

#include "common.h"

namespace MovingWindow
{
	extern WNDCLASS commonAttributes;
	LRESULT CALLBACK messageHandler(HWND window,UINT message,WPARAM argW,LPARAM argL);
} // end namespace MovingWindow

#endif // MOVING_WINDOW_H