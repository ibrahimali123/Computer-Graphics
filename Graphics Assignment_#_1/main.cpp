#include <Windows.h>
#include "myLine.h"
#define ID_FILE_EXIT 1
#define ID_FILE_Clear 2
#define ID_Line_Simple 3
#define ID_Line_DDA 4
#define ID_Line_Mid 5
#include <vector>

using namespace std;

vector<myLine>V;  // vector to hold lines 

LONG WINAPI WndProc(HWND,UINT,WPARAM,LPARAM);
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int nCmdShow)
{
	WNDCLASSEX wcx;
	wcx.cbSize=sizeof(wcx);
	wcx.style=CS_HREDRAW|CS_VREDRAW;
	wcx.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wcx.hCursor=LoadCursor(hInst,IDC_ARROW);
	wcx.hIcon=LoadIcon(hInst,IDI_WINLOGO);
	wcx.hIconSm=LoadIcon(hInst,IDI_WINLOGO);
	wcx.hInstance=hInst;
	wcx.lpfnWndProc=WndProc;
	wcx.lpszClassName="myclass";
	wcx.lpszMenuName=NULL;
	wcx.cbClsExtra=wcx.cbWndExtra=0;
	RegisterClassEx(&wcx);
	HWND hWnd=CreateWindowEx(0,wcx.lpszClassName,"Sheboo",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInst,NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

int myPaint = 0;
int x1 = 0, y1 = 0, xPos = 0, yPos = 0, x2 = 0, y2 = 0;
myPoint p1,p2;
myLine L;
int alg = 0;
COLORREF color = RGB(0,0,255);

LONG WINAPI WndProc(HWND hWnd,UINT m,WPARAM wp,LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch(m)
	{
	case WM_PAINT:
		if(myPaint == 2)
        {
			hdc=BeginPaint(hWnd,&ps);
			p1 = myPoint(x1,y1);
			p2 = myPoint(x2,y2);
			L = myLine(p1,p2,alg);
			L.color = color;
			V.push_back(L);
			L.drawLine(hdc);
			myPaint = 0;
			EndPaint(hWnd,&ps);
		}
		break;
		
	case WM_LBUTTONDOWN:
		xPos = LOWORD(lp);
		yPos = HIWORD(lp);
		if(myPaint == 0)
		{
			x1 = xPos;
			y1 = yPos;
			myPaint++;
		}
		else if(myPaint == 1)
		{
			x2 = xPos;
			y2 = yPos;
			myPaint++;
			InvalidateRect(hWnd, NULL, false);
		}
		break;
		
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
		
	case WM_SIZE:
              hdc=BeginPaint(hWnd,&ps);
              for(int i=0; i<V.size();i++)
                      V[i].drawLine(hdc);
              EndPaint(hWnd,&ps);
         break;
	
	case WM_CREATE:
         {
                              
        HMENU hMenu, hSubMenu;
        hMenu = CreateMenu();
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_Clear, "C&lear");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_Line_Simple, "&Simple");
        AppendMenu(hSubMenu, MF_STRING, ID_Line_DDA, "&DDA");
        AppendMenu(hSubMenu, MF_STRING, ID_Line_Mid, "&Mid Point");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Line");

        SetMenu(hWnd, hMenu);
         }
         break;
         
	case WM_DESTROY:
	   	PostQuitMessage(0);
		
  	  case WM_COMMAND:
        switch(LOWORD(wp))
        {
            case ID_FILE_EXIT:
                PostMessage(hWnd, WM_CLOSE, 0, 0);
                break;
            case ID_FILE_Clear:
                 InvalidateRect(hWnd, NULL, true);
                 V.clear();
                 break;
            case ID_Line_Simple:
                 alg = 0;
                 break;
            case ID_Line_DDA:
                 alg = 1;
                 break;
            case ID_Line_Mid:
                 alg = 2;
                 break;
        }
		break;
		
        default: return DefWindowProc(hWnd,m,wp,lp);
	}
	return 0;
}
