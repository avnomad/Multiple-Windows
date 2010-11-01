#include "moving window.h"

namespace MovingWindow
{
	WNDCLASS commonAttributes = {
		CS_HREDRAW | CS_VREDRAW,
		messageHandler,
		0,0,
		GetModuleHandle(NULL),	// messageHandler's maching code should be in this .exe file...
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)GetStockObject(BLACK_BRUSH),
		NULL,
		esquape(MovingWindow::commonAttributes)
	};

	LRESULT CALLBACK messageHandler(HWND window,UINT message,WPARAM argW,LPARAM argL)
	{
		PAINTSTRUCT ps;
		RECT clientArea;

		switch(message)
		{
		case WM_CREATE:
			++windowCounter;
			return 0;
		case WM_PAINT:
			BeginPaint(window,&ps);
				GetClientRect(window,&clientArea);
				SelectObject(ps.hdc,CreatePen(PS_SOLID,1,RGB(255,255,0)));
					//MoveToEx(ps.hdc,0,0,NULL);
					LineTo(ps.hdc,0,clientArea.bottom-1);
					LineTo(ps.hdc,clientArea.right-1,clientArea.bottom-1);
					LineTo(ps.hdc,clientArea.right-1,0);
					LineTo(ps.hdc,0,0);
				DeleteObject(SelectObject(ps.hdc,GetStockObject(NULL_PEN)));
			EndPaint(window,&ps);
			return 0;
		case WM_DESTROY:
			if(--windowCounter == 0)
				PostQuitMessage(0);
			return 0;
		} // end switch
		return DefWindowProc(window,message,argW,argL);
	} // end function messageHandler

} // end namespace MovingWindow