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

#include <iostream>
#include <GL/glew.h>
#include "OpenGL window.h"

namespace OpenGLWindow
{
	WNDCLASS commonAttributes = {
		CS_OWNDC,
		messageHandler,
		0,sizeof(HANDLE),
		GetModuleHandle(NULL),	// messageHandler's maching code should be in this .exe file...
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		NULL,
		NULL,
		esquape(OpenGLWindow::commonAttributes)
	};

	LRESULT CALLBACK messageHandler(HWND window,UINT message,WPARAM argW,LPARAM argL)
	{
		PAINTSTRUCT ps;

		switch(message)
		{
		case WM_CREATE:
			++windowCounter;
			{
				DWORD threadID;
				CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)OpenGLWindow::perpetualPaint,window,0,&threadID);
				SetWindowLongPtr(window,0,threadID);
			} // end block
			return 0;
		case WM_PAINT:
			BeginPaint(window,&ps);
			EndPaint(window,&ps);
			return 0;
		case WM_ERASEBKGND:
			return 1;
		case WM_DESTROY:
			PostThreadMessage(GetWindowLongPtr(window,0),WM_USER+1,0,0);	// should check if succeeds...
													// should not call before receiving thread creates message queue...
													// should wait for thread to finish before returning?
			if(--windowCounter == 0)
				PostQuitMessage(0);
			return 0;
		} // end switch
		return DefWindowProc(window,message,argW,argL);
	} // end function messageHandler

	DWORD WINAPI perpetualPaint(HWND window)	// should be a window with CS_OWNDC
	{
		HDC deviceContext = GetDC(window);
		PIXELFORMATDESCRIPTOR pixelFormatDescription = {0};

		pixelFormatDescription.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDescription.nVersion = 1;
		pixelFormatDescription.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER|PFD_STEREO_DONTCARE;
		pixelFormatDescription.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDescription.cColorBits = 48;
		pixelFormatDescription.cAlphaBits = 16;
		pixelFormatDescription.cAccumBits = 128;
		pixelFormatDescription.cDepthBits = 64;
		pixelFormatDescription.cStencilBits = 32;
		pixelFormatDescription.cAuxBuffers = 16;

		int pixelFormat = ChoosePixelFormat(deviceContext,&pixelFormatDescription);
		/**/std::cout << pixelFormat << std::endl;
		SetPixelFormat(deviceContext,pixelFormat,&pixelFormatDescription);
		HGLRC renderingContext = wglCreateContext(deviceContext);
		wglMakeCurrent(deviceContext,renderingContext);

		double degAngle = 0;
		RECT r;
		MSG message;
		while(1)
		{
			if(PeekMessage(&message,(HWND)-1,WM_USER+1,WM_USER+1,PM_REMOVE) && message.message == WM_USER+1)
				break;
			glClear(GL_COLOR_BUFFER_BIT);
			GetClientRect(window,&r);
			glViewport(0,0,r.right,r.bottom);

			glColor3f(1,1,0);	// yellow
			glLoadIdentity();
			glRotated(degAngle,0,0,1);
			degAngle += 0.5;

			glRectf(-0.5,-0.5,0.5,0.5);

			SwapBuffers(deviceContext);
		} // end while(1)
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(renderingContext);
		//ReleaseDC(window,deviceContext);	documentation says it has no effect with CS_OWNDC...
		return 0;
	} // end function rerpetualPaint
} // end namespace OpenGLWindow