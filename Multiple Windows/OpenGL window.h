//	Copyright (C) 2010, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Multiple Windows.
 *
 *	Multiple Windows is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Multiple Windows is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Multiple Windows.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "common.h"

namespace OpenGLWindow
{
	extern WNDCLASS commonAttributes;
	LRESULT CALLBACK messageHandler(HWND window,UINT message,WPARAM argW,LPARAM argL);
	DWORD WINAPI perpetualPaint(HWND window);	// should be a window with CS_OWNDC
} // end namespace OpenGLWindow

#endif // OPENGL_WINDOW_H