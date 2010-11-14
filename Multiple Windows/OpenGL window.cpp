#include <iostream>
#include <GL/glew.h>
#include "OpenGL window.h"

extern HANDLE openglThreads[2];
extern DWORD openglThreadIDs[length(openglThreads)];

namespace OpenGLWindow
{
	WNDCLASS commonAttributes = {
		CS_OWNDC,
		messageHandler,
		0,0,
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
			return 0;
		case WM_PAINT:
			BeginPaint(window,&ps);
			EndPaint(window,&ps);
			return 0;
		case WM_ERASEBKGND:
			return 1;
		case WM_DESTROY:	// should stop the thread too...
			for(int i = 0 ; i < length(openglThreads) ; ++i)
				PostThreadMessage(openglThreadIDs[i],WM_USER+1,0,(LPARAM)window);	// should check if succeeds...
													// should not call before recieving thead creates message queue...
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
			if(PeekMessage(&message,NULL,WM_USER+1,WM_USER+1,PM_REMOVE) && message.message == WM_USER+1 && (HWND)message.lParam == window)
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
		ReleaseDC(window,deviceContext);
		return 0;
	} // end function rerpetualPaint
} // end namespace OpenGLWindow