#include "moving window.h"

int windowCounter = 0;

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE notUsed, LPSTR commandLine, int howToShow)
{
	// windows class registrations
	RegisterClass(&MovingWindow::commonAttributes);

	HWND movingWindow = CreateWindow(esquape(MovingWindow::commonAttributes),TEXT("Moving Window"),WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,currentInstance,NULL);
	ShowWindow(movingWindow,howToShow);
	UpdateWindow(movingWindow);


	MSG message;
	while(GetMessage(&message,NULL,0,0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	} // end while

	return message.wParam;
} // end function WinMain