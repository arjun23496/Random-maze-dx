// include the basic windows header files and the Direct3D header file
#include "CFrame.h"


#include<windows.h>
#include<windowsx.h>
#include<d3d9.h>
#include<d3dx9.h>
 

// include the Direct3D Library files
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// define the screen resolution
#define SCREEN_WIDTH 1366	//variable definning screen width
#define SCREEN_HEIGHT 768	//variable defining screen height



POINT pos;				//pointer to the mouse handling window
CFrame frame;				//object to call the frame class which handles the 3d 


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL,IDC_CROSS);
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL, "WindowClass", "Our Direct3D Program",
                          WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                          NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
	ShowCursor(FALSE);

	
    // set up and initialize Direct3D
    
	

	frame.initgraphics(hWnd);
	
	
	SetCursorPos(683,384);

    // enter the main loop:

    MSG msg;

    while(TRUE)
    {
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if(msg.message == WM_QUIT)
            break;

		GetCursorPos(&pos);
		
	if(ScreenToClient(hWnd,&pos))
						frame.modtarget(pos.x,pos.y);

        //Here the frame is set up
	frame.renderframe();
    }


    return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
		case WM_MOUSEMOVE:
			{
				 
				if(GetCursorPos(&pos))
				{
					if(ScreenToClient(hWnd,&pos))
						frame.modtarget(pos.x,pos.y);
					if(pos.x>800||pos.x<200||pos.y>600||pos.y<100)
						SetCursorPos(683,384);

						
				}
				break;
			}
		case WM_KEYDOWN:
			{
				switch(wParam)
				{
				case VK_ESCAPE:
					DestroyWindow(hWnd);
					PostQuitMessage(0);
					return 0;
					break;
				case 0x57:
					frame.KeyHandle(1);
				case 0x53:
					frame.KeyHandle(2);
				}
			}
		

			}
	

	

    return DefWindowProc (hWnd, message, wParam, lParam);
}