#include "moving window.h"
#include <tpcshrd.h>

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
		static POINT clientAreaPosition;	// in screen physical coordinates

		switch(message)
		{
		case WM_CREATE:
			++windowCounter;
			return 0;
		case WM_MOVE:
			ScrollWindow(window,clientAreaPosition.x-(short)LOWORD(argL),clientAreaPosition.y-(short)HIWORD(argL),NULL,NULL);
			UpdateWindow(window);
			clientAreaPosition.x = (short)LOWORD(argL);
			clientAreaPosition.y = (short)HIWORD(argL);
			return 0;
		case WM_ERASEBKGND:
			return 1;
		case WM_ENTERSIZEMOVE:
		case WM_EXITSIZEMOVE:
			return 0;
		case WM_GESTURENOTIFY:
		case WM_GESTURE:
		case WM_TABLET_FLICK:
			PostQuitMessage(0);
			return 1;
		case WM_PAINT:
			BeginPaint(window,&ps);
				GetClientRect(window,&r);
				FillRect(ps.hdc,&r,(HBRUSH)GetStockObject(BLACK_BRUSH));
				r.left = r.top = 0;
				ClientToScreen(window,(LPPOINT)&r.left);
				r.right = GetDeviceCaps(ps.hdc,HORZRES);
				r.bottom = GetDeviceCaps(ps.hdc,VERTRES);
				SetViewportOrgEx(ps.hdc,-r.left,-r.top,NULL);
				// draw lines and curves
				SelectObject(ps.hdc,CreatePen(PS_SOLID,1,RGB(255,255,0)));
				//SetROP2(ps.hdc,R2_XORPEN);
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
				//SetROP2(ps.hdc,R2_COPYPEN);
				SetBkColor(ps.hdc,RGB(64,64,64));
				SetMapMode(ps.hdc,MM_ANISOTROPIC);
				SetViewportExtEx(ps.hdc,r.right,-r.bottom,NULL);
				SetWindowExtEx(ps.hdc,100,100,NULL);
				SetViewportOrgEx(ps.hdc,-r.left,r.bottom-1-r.top,NULL);
				SetWindowOrgEx(ps.hdc,0,0,NULL);
				SelectObject(ps.hdc,CreateHatchBrush(HS_BDIAGONAL,RGB(192,192,192)));
				DeleteObject(SelectObject(ps.hdc,GetStockObject(NULL_PEN)));
					Ellipse(ps.hdc,60,60,90,90);
				DeleteObject(SelectObject(ps.hdc,CreateHatchBrush(HS_FDIAGONAL,RGB(192,192,192))));
					Chord(ps.hdc,60,60,90,90,50,60,90,100);
				DeleteObject(SelectObject(ps.hdc,GetStockObject(NULL_BRUSH)));
				SelectObject(ps.hdc,CreatePen(PS_DASH,1,RGB(0,32,0)));
					Ellipse(ps.hdc,60,60,90,90);
				DeleteObject(SelectObject(ps.hdc,GetStockObject(NULL_PEN)));
				SetBkColor(ps.hdc,RGB(32,32,32));
				SelectObject(ps.hdc,CreateHatchBrush(HS_CROSS,RGB(0,128,0)));
					RoundRect(ps.hdc,5,95,45,55,10,10);
				DeleteObject(SelectObject(ps.hdc,CreateHatchBrush(HS_HORIZONTAL,RGB(0,128,0))));
					Pie(ps.hdc,10,90,40,60,40,50,0,75);
				DeleteObject(SelectObject(ps.hdc,CreateHatchBrush(HS_DIAGCROSS,RGB(0,0,128))));
					{
						POINT vertices[] = {{15,10},{35,10},{35,30},{25,35},{15,30},{15,10}};
						Polygon(ps.hdc,vertices,length(vertices));
					}
				DeleteObject(SelectObject(ps.hdc,GetStockObject(DKGRAY_BRUSH)));
				SelectObject(ps.hdc,GetStockObject(WHITE_PEN));
					SetRect(&r,55,35,70,25);
					FillRect(ps.hdc,&r,(HBRUSH)GetStockObject(GRAY_BRUSH));
					OffsetRect(&r,25,0);
					FrameRect(ps.hdc,&r,(HBRUSH)GetStockObject(GRAY_BRUSH));	// doesn't seem to work
					OffsetRect(&r,-15,-5);
					InvertRect(ps.hdc,&r);
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