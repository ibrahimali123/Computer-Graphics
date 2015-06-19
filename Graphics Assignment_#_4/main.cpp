
//  Name_1  :    Mahmoud Mohamed Shaaban 
//  ID_1    :    20090307

#include <iostream>
#include <fstream>
#include <wchar.h>
#include <string>
#include <vector>
#include <shlobj.h>  
#include <math.h>
#include <Windows.h>
#include "myObject.h"
#include "myLine.h"
#include "myCircle.h"
#include "myCurve.h"
#define ID_FILE_OPEN 1
#define ID_FILE_SAVE 2
#define ID_FILE_UNDO 3
#define ID_FILE_Clear 4
#define ID_FILE_EXIT 5
#define ID_Line_Simple 6
#define ID_Line_DDA 7
#define ID_Line_Mid 8
#define ID_Circle_Direct 9
#define ID_Circle_Polar 10
#define ID_Circle_Mid 11
#define ID_Draw_Hermite_Curve 12
#define ID_Draw_Bezier_Curve 13
#define ID_Draw_Cardinal_Spline 14

using namespace std;



vector<myObject>V;

wstring FileOpen(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) 
{
    cout << "Open clicked\n";   
     
	OPENFILENAME ofn;
	wchar_t fileName[260] = L"";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	wstring fileNameStr;

	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;

	return fileNameStr;
}
////////////////////////////////////////////////////////////////////////////////

wstring SaveFile(HWND owner = NULL , char *filter = "All Files (*.*)\0*.*\0" )
{
	cout << "save clicked\n";

	OPENFILENAME ofn;
	wchar_t fileName[260] = L"";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = "Text Files (*.sheboo)\0*.sheboo\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = (char*) fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "sheboo";

	wstring fileNameStr;
	if (GetSaveFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

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
	HWND hWnd=CreateWindowEx(0,wcx.lpszClassName,"Graphics Drawing Algorithms Methods ",
    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInst,NULL);
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
    myCurve U;   
    int alg = 0;
    int shape ;
    myObject O ;
    int xs,xe,ys,ye,type=14,counter=0,flag=0,xs1,ys1,tx,ty ;


COLORREF color = RGB(255,0,255);

LONG WINAPI WndProc(HWND hWnd,UINT m,WPARAM wp,LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch(m)
	{
	case WM_PAINT:
         
         int i = (int) V.size() - 1;
		if (mypaint == 2 && V.alg <= 8) 
        {
			hdc = BeginPaint(hwnd, &ps);
			if (V[i].alg <= 2) 
            {
				myLine L(V[i].X1, V[i].X2, V[i].Y1, V[i].Y2,V[i].alg, V[i].color);
				L.drawLine(hdc, hwnd);
			} 
            else 
            {
				myCircle C(V[i].X1, V[i].X2, V[i].Y1, V[i].Y2,
						V[i].alg, V[i].color);
				C.drawCircle(hdc, hwnd);
			}
			EndPaint(hwnd, &ps);
			mypaint = 0;
		} 
        else if (mypaint == 4) 
        {
			hdc = BeginPaint(hwnd, &ps);
			myCurve U(V[i].X1, V[i].X2, V[i].X3,
					V[i].X4, V[i].Y1, V[i].Y2, V[i].Y3,
					V[i].Y4, V[i].alg, V[i].color);

			        U.DrawCurve(hdc);

			EndPaint(hwnd, &ps);
			mypaint = 0;
		}
         
		if(myPaint == 2)
        {
         	hdc=BeginPaint(hWnd,&ps);
			O.p1 = myPoint(x1,y11);
			O.p2 = myPoint(x2,y2);
            O.shape = shape ;
            O.alg = alg;
            O.color = color;
            V.push_back(O);
            O.drawshape(hdc);
			
			myPaint = 0;
			EndPaint(hWnd,&ps);
		}
		if(myPaint == 4)
        {
         	hdc=BeginPaint(hWnd,&ps);
			O.p1 = myPoint(x1,y11);
			O.p2 = myPoint(x2,y2);
			O.p2 = myPoint(x3,y3);
			O.p2 = myPoint(x4,y4);
            O.shape = shape ;
            O.alg = alg;
            O.color = color;
            V.push_back(O);
            O.drawshape(hdc);
			
			myPaint = 0;
			EndPaint(hWnd,&ps);
		}
		break;
		
	case WM_LBUTTONDOWN:
		xPos = LOWORD(lp);
		yPos = HIWORD(lp);
		if(myPaint == 0)
		{
			O.x1 = xPos;
			O.y1 = yPos;
			myPaint++;
		}
		else if(myPaint == 1)
		{
			O.x2 = xPos;
			O.y2 = yPos;
			myPaint++;
		}
		else if(myPaint == 2)
		{
			O.x3 = xPos;
			O.y3 = yPos;
			myPaint++;
		}
		else if(myPaint == 3)
		{
			O.x4 = xPos;
			O.y4 = yPos;
			myPaint++;
		}
		InvalidateRect(hWnd, NULL, false);
		break;
		
	case WM_CLOSE:
         {
	     	DestroyWindow(hWnd);
	      	break;
         }
		
	case WM_SIZE:
         {
             hdc = BeginPaint(hwnd, &ps);
        		for (int i = 0; i < (int) V.size(); ++i)
                 {
        			if (V[i].alg <= 2) 
                    {
        				myLine L(V[i].X1, V[i].X2, V[i].Y1, V[i].Y2,
        						V[i].alg, V[i].color);
        				L.drawLine(hdc, hwnd);
        			} else if (V[i].alg <= 5) 
                    {
        				myCircle C(V[i].X1, V[i].X2, V[i].Y1, V[i].Y2,
        						V[i].alg, V[i].color);
        				C.drawCircle(hdc, hwnd);
        			} 
                    else 
                    {
        				myCurve U(V[i].X1, V[i].X2, V[i].X3,
        						V[i].X4, V[i].Y1, V[i].Y2, V[i].Y3,
        						V[i].Y4, V[i].alg, V[i].color);
        
        				U.DrawCurve(hdc);
        			}
        		}
        		EndPaint(hwnd, &ps);
        		break;
        		
                 
         /////////////////////////////////////////
        //      hdc=BeginPaint(hWnd,&ps);
//              for(int i=0; i<V.size();i++)
//              V[i].drawshape(hdc);
//              EndPaint(hWnd,&ps);
//              
//         break;
         ////////////////////////////////////////
	
	case WM_CREATE:
         {
                              
        HMENU hMenu, hSubMenu;
        hMenu = CreateMenu();
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "Open");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_SAVE, "Save");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_UNDO, "Undo");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_Clear, "Clear");
        AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "Exit");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "File");
    
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_Line_Simple, "Simple");
        AppendMenu(hSubMenu, MF_STRING, ID_Line_DDA, "DDA");
        AppendMenu(hSubMenu, MF_STRING, ID_Line_Mid, "Mid Point");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "Line");
        
        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_Circle_Direct, "Direct");
        AppendMenu(hSubMenu, MF_STRING, ID_Circle_Polar, "Polar");
        AppendMenu(hSubMenu, MF_STRING, ID_Circle_Mid, "Mid Point");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "Circle");

        hSubMenu = CreatePopupMenu();
        AppendMenu(hSubMenu, MF_STRING, ID_Draw_Hermite_Curve, "Hermite");
        AppendMenu(hSubMenu, MF_STRING, ID_Draw_Bezier_Curve, "Bezier");
        AppendMenu(hSubMenu, MF_STRING, ID_Draw_Cardinal_Spline, "Spline");
        AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "Curve") ;	
        
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
                
            case ID_FILE_UNDO:
                 InvalidateRect(hWnd, NULL, true);
                 V.pop_back();
              hdc=BeginPaint(hWnd,&ps);
              for(int i=0; i<V.size();i++)
              V[i].drawshape(hdc);
              EndPaint(hWnd,&ps);
                 break;
                 
            case ID_FILE_Clear:
                 InvalidateRect(hWnd, NULL, true);
                 V.clear();
                 break;
            case ID_Line_Simple:
                 shape = 1;
                 alg = 0;
                 break;
            case ID_Line_DDA:
                 shape = 1;
                 alg = 1;
                 break;
            case ID_Line_Mid:
                 shape = 1;
                 alg = 2;
                 break;
                 
            case ID_Circle_Direct:
                 shape = 2;
                 alg = 3;
                 break;
                 
            case ID_Circle_Polar:
                 shape = 2;
                 alg = 4;
                 break;
                 
            case ID_Circle_Mid:
                 shape = 2;
                 alg = 5;
                 break;
                 
            case ID_Draw_Hermite_Curve:
                 shape = 3;
                 alg = 6;
                 break;
                 
            case ID_Draw_Bezier_Curve:
                 shape = 3;
                 alg = 7;
                 break;
                 
            case ID_Draw_Cardinal_Spline:
                 shape = 3;
                 alg = 8;
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
		         cout << "file open ! \n";
			
			         // open file and read
            }
	          	break;
		
           case ID_FILE_SAVE:
                {
			//SaveFile();
		
                  cout << "save clicked\n";

			      OPENFILENAME ofn;
			      wchar_t fileName[260] = L"";
			      ZeroMemory(&ofn, sizeof(ofn));

			      ofn.lStructSize = sizeof(OPENFILENAME);
			      ofn.hwndOwner = hWnd;
			      ofn.lpstrFilter = "Text Files (*.sheboo)\0*.sheboo\0All Files (*.*)\0*.*\0";
			      ofn.lpstrFile = (char*) fileName;
			      ofn.nMaxFile = MAX_PATH;
			      ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			      ofn.lpstrDefExt = "sheboo";

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
	return 0;
}
