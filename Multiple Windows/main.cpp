#include "moving window.h"

int windowCounter = 0;

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE notUsed, LPSTR commandLine, int howToShow)
{
	HWND movingWindows[3];

	// windows class registrations
	RegisterClass(&MovingWindow::commonAttributes);

	// windows creation,maniphestation,update
	for(int i = 0 ; i < length(movingWindows) ; ++i)
	{
		movingWindows[i] = CreateWindow(esquape(MovingWindow::commonAttributes),TEXT("Moving Window"),WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,currentInstance,NULL);
		ShowWindow(movingWindows[i],howToShow);
		UpdateWindow(movingWindows[i]);
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