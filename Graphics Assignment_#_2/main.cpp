/*
Name_1  :    Mahmoud Mohamed Shaaban 
ID_1    :    20090307

Name_2  :   Mazen Yousry Amer 
ID_2    :   20090242
*/
#include <iostream>
#include <wchar.h>
#include <string>
#include <vector>
//#include <commdlg.h>   // for GetSaveFileName
#include <shlobj.h>  
#include <math.h>
#include <Windows.h>
#include "myLine.h"
#include "myCircle.h"
#define ID_FILE_OPEN 1
#define ID_FILE_SAVE 2
#define ID_FILE_EXIT 3
#define ID_FILE_Clear 4
#define ID_Line_Simple 5
#define ID_Line_DDA 6
#define ID_Line_Mid 7
#define ID_Circle_Simple 8
#define ID_Circle_Polar 9
#define ID_Circle_Mid 10

using namespace std;


wstring SaveFile(HWND owner = NULL , char *filter = "All Files (*.*)\0*.*\0" )
{

	/*OPENFILENAME ofn;
	char fileName[260] = "";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = (char*) fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";

	string fileNameStr;
	if (GetSaveFileName(&ofn))
		fileNameStr = fileName;

	return fileNameStr;*/
	cout << "save clicked\n";

	OPENFILENAME ofn;
	wchar_t fileName[260] = L"";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = (char*) fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "txt";

	wstring fileNameStr;
	if (GetSaveFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

vector<myLine>V;      // vector to hold lines 
vector<myCircle>G;

LONG WINAPI WndProc(HWND,UINT,WPARAM,LPARAM);
int APIENTRY WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int nCmdShow)
{
	WNDCLASSEX wcx;
	wcx.cbSize=sizeof(wcx);
	wcx.style=CS_HREDRAW|CS_VREDRAW;
	wcx.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
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
int x1 = 0, y11 = 0, xPos = 0, yPos = 0, x2 = 0, y2 = 0;
myPoint p1,p2;
myLine L;
myCircle C;
int alg = 0;


COLORREF color = RGB(255,0,255);

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
			p1 = myPoint(x1,y11);
			p2 = myPoint(x2,y2);
			
			if(alg<=2)
            {
			L = myLine(p1,p2,alg);
			L.color = color;
			L.drawLine(hdc);
			V.push_back(L);
        }
			else if(alg>=3)
            {
			C = myCircle(p1,p2,alg);
			C.color = color;
            C.drawCircle(hdc);
            G.push_back(C);
            }
			
			myPaint = 0;
			EndPaint(hWnd,&ps);
		
		break;
		
	case WM_LBUTTONDOWN:
		xPos = LOWORD(lp);
		yPos = HIWORD(lp);
		if(myPaint == 0)
		{
			x1 = xPos;
			y11 = yPos;
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
              
              for(int i=0; i<G.size();i++)
              G[i].drawCircle(hdc);
              EndPaint(hWnd,&ps);
              
         break;
	
	case WM_CREATE:
         {
                              
        HMENU hMenu, hSubMenu;
        hMenu = CreateMenu();
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "Open");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_SAVE, "Save");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_Clear, "C&lear");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_Line_Simple, "&Simple");
        AppendMenu(hSubMenu, MF_STRING, ID_Line_DDA, "&DDA");
        AppendMenu(hSubMenu, MF_STRING, ID_Line_Mid, "&Mid Point");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Line");
        
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_Circle_Simple, "&Simple");
        AppendMenu(hSubMenu, MF_STRING, ID_Circle_Polar, "&Polar");
        AppendMenu(hSubMenu, MF_STRING, ID_Circle_Mid, "&Mid Point");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Circle");

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
                 G.clear();
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
                 
                 case ID_Circle_Simple:
                 alg = 3;
                 break;
            case ID_Circle_Polar:
                 alg = 4;
                 break;
            case ID_Circle_Mid:
                 alg = 5;
                 break;
      		
        case ID_FILE_OPEN: 
             {

			cout << "open clicked\n";
			OPENFILENAME openFileName;
			wchar_t fileName[MAX_PATH] = { 0 };
			memset(&openFileName, 0, sizeof(openFileName));

			openFileName.lStructSize = sizeof(OPENFILENAME);
			openFileName.hwndOwner = hWnd;
			openFileName.lpstrFilter = TEXT("All Files (*.*)\0*.*\0");
			openFileName.lpstrFile = (char*) fileName;
			openFileName.nMaxFile = MAX_PATH;
			openFileName.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			openFileName.lpstrDefExt = "";

			if (GetOpenFileName(&openFileName))
				std::wstring selectedFile = fileName;
			cout << "ana hna ! \n";
			
			// open file and read
		}
		break;
		
		         	case ID_FILE_SAVE:{
			//SaveFile();
		
			cout << "save clicked\n";

			OPENFILENAME ofn;
			wchar_t fileName[260] = L"";
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
			ofn.lpstrFile = (char*) fileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = "txt";

			wstring fileNameStr;
			if (GetSaveFileName(&ofn))
				fileNameStr = fileName;
				
			// create file and write in it 
		}
		break;
		
        }
		break;
		
        default: return DefWindowProc(hWnd,m,wp,lp);
	}
}
	return 0;
}
