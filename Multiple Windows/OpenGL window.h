#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "common.h"

namespace OpenGLWindow
{
	extern WNDCLASS commonAttributes;
	LRESULT CALLBACK messageHandler(HWND window,UINT message,WPARAM argW,LPARAM argL);
	DWORD WINAPI rerpetualPaint(int howToShow);	// should be a window with CS_OWNDC
} // end namespace OpenGLWindow

#endif // OPENGL_WINDOW_H