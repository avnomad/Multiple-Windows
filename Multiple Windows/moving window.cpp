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
		RECT r;	// for client area

		switch(message)
		{
		case WM_CREATE:
			++windowCounter;
			return 0;
		case WM_PAINT:
			BeginPaint(window,&ps);
				GetClientRect(window,&r);
				// draw lines and curves
				SelectObject(ps.hdc,CreatePen(PS_SOLID,1,RGB(255,255,0)));
				SetROP2(ps.hdc,R2_XORPEN);
					LineTo(ps.hdc,0,r.bottom-1);
					LineTo(ps.hdc,r.right-1,r.bottom-1);
					LineTo(ps.hdc,r.right-1,0);
					LineTo(ps.hdc,0,0);
					MoveToEx(ps.hdc,0,r.bottom>>1,NULL);
					LineTo(ps.hdc,r.right,r.bottom>>1);
					MoveToEx(ps.hdc,r.right>>1,0,NULL);
					LineTo(ps.hdc,r.right>>1,r.bottom);
					{
					POINT controlPoints[] = {{r.right-1,r.bottom>>1},
												{r.right-1,0},{r.right-1,0},{r.right>>1,0},
												{0,0},{0,0},{0,r.bottom>>1},
												{0,r.bottom-1},{0,r.bottom-1},{r.right>>1,r.bottom-1},
												{r.right-1,r.bottom-1},{r.right-1,r.bottom-1},{r.right-1,r.bottom>>1}
											};
					PolyBezier(ps.hdc,controlPoints,length(controlPoints));
					}
				// draw filled shapes
				SetROP2(ps.hdc,R2_COPYPEN);
				SetBkColor(ps.hdc,RGB(64,64,64));
				SetMapMode(ps.hdc,MM_ANISOTROPIC);
				SetViewportExtEx(ps.hdc,r.right,-r.bottom,NULL);
				SetWindowExtEx(ps.hdc,100,100,NULL);
				SetWindowOrgEx(ps.hdc,0,0,NULL);
				SetViewportOrgEx(ps.hdc,0,r.bottom-1,NULL);
				SelectObject(ps.hdc,CreateHatchBrush(HS_BDIAGONAL,RGB(192,192,192)));
				DeleteObject(SelectObject(ps.hdc,GetStockObject(NULL_PEN)));
					Ellipse(ps.hdc,60,60,90,90);
				DeleteObject(SelectObject(ps.hdc,CreateHatchBrush(HS_FDIAGONAL,RGB(192,192,192))));
					Chord(ps.hdc,60,60,90,90,50,60,90,100);
				DeleteObject(SelectObject(ps.hdc,GetStockObject(NULL_BRUSH)));
				SelectObject(ps.hdc,CreatePen(PS_DASH,1,RGB(0,32,0)));
					Ellipse(ps.hdc,60,60,90,90);
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