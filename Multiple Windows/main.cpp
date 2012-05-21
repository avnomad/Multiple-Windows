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

#include "moving window.h"
#include "OpenGL window.h"

int windowCounter = 0;

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE notUsed, LPSTR commandLine, int howToShow)
{
	HWND movingWindows[2];
	HWND openglWindows[2];

	// windows class registrations
	RegisterClass(&MovingWindow::commonAttributes);
	RegisterClass(&OpenGLWindow::commonAttributes);

	// windows creation,maniphestation,update
	for(int i = 0 ; i < length(movingWindows) ; ++i)
	{
		movingWindows[i] = CreateWindow(esquape(MovingWindow::commonAttributes),TEXT("Moving Window"),WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,currentInstance,NULL);
		ShowWindow(movingWindows[i],howToShow);
		UpdateWindow(movingWindows[i]);
	} // end for

	for(int i = 0 ; i < length(openglWindows) ; ++i)
	{
		openglWindows[i] = CreateWindow(esquape(OpenGLWindow::commonAttributes),TEXT("OpenGL Window"),WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,currentInstance,NULL);
		ShowWindow(openglWindows[i],howToShow);
		UpdateWindow(openglWindows[i]);
	} // end for

	// message loop
	MSG message;
	while(GetMessage(&message,NULL,0,0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	} // end while

	return message.wParam;
} // end function WinMain