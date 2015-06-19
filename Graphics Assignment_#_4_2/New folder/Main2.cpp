
#include <Windows.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <String>
#include "Line.cpp"
#include "circle.cpp"
#include "Hermite_Curve.h"

using namespace std;

#define simpleLine 1
#define DDALine 2
#define MidPointLine 3
#define DirectCartesian 4
#define PolarDirect 5
//#define IterativePolar 6
#define Bresenham 7
//#define FasterBresenhom 8
#define HERMITE 9
#define BEZIER 10
#define CARDINAL 11
#define CLEAR 12
#define EXIT 13
#define SAVE 14
#define LOAD 15

int mypaint = 0;
int xPos, yPos;

struct Graph {
	int X1;
	int X2;
	int X3;
	int X4;
	int Y1;
	int Y2;
	int Y3;
	int Y4;
	int alg;
	COLORREF color;
};

vector<Graph> graph;
Graph g;

LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
void saveGraph(string filename);
void loadGraph(string filename, HWND hwnd);

string FileOpen(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	string fileNameStr;

	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;

	return fileNameStr;
}

string FileSave(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	string fileNameStr;

	if (GetSaveFileName(&ofn))
		fileNameStr = fileName;

	return fileNameStr;
}


COLORREF colorDialog(HWND hwnd) {
	CHOOSECOLOR color;//the struct for the dialog
	COLORREF ccref[16];//custom colors
	COLORREF selcolor = 0x000000;//the default selected color

	memset(&color, 0, sizeof(color));
	color.lStructSize = sizeof(CHOOSECOLOR);
	color.hwndOwner = hwnd;
	color.lpCustColors = ccref;
	color.rgbResult = selcolor;
	color.Flags = CC_RGBINIT;

	if (ChooseColor(&color)) {
		selcolor = color.rgbResult;
		//redraw with the new color
	}
	return selcolor;
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
	WNDCLASSEX wcx;
	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wcx.hCursor = LoadCursor(hInst, IDC_ARROW);
	wcx.hIcon = LoadIcon(hInst, IDI_WINLOGO);
	wcx.hIconSm = LoadIcon(hInst, IDI_WINLOGO);
	wcx.hInstance = hInst;
	wcx.lpfnWndProc = WndProc;
	wcx.lpszClassName = "lines";
	wcx.lpszMenuName = NULL;
	wcx.cbClsExtra = wcx.cbWndExtra = 0;
	RegisterClassEx(&wcx);
	HWND hWnd = CreateWindowEx(0, wcx.lpszClassName, "Graphics Drawing Algorithms",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg) {
	case WM_CREATE: {
		HMENU hMenu, LineSubMenu, CircleSubMenu, CurveSubMenu, hSubMenu2;
		hMenu = CreateMenu();
		LineSubMenu = CreatePopupMenu();
		CircleSubMenu = CreatePopupMenu();
		CurveSubMenu = CreatePopupMenu();
		hSubMenu2 = CreatePopupMenu();
		AppendMenu(hSubMenu2, MF_STRING, CLEAR, "Clear");
		AppendMenu(hSubMenu2, MF_STRING, SAVE, "Save");
		AppendMenu(hSubMenu2, MF_STRING, LOAD, "Load");
		AppendMenu(hSubMenu2, MF_STRING, EXIT, "Exit");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) hSubMenu2, "&File");
		SetMenu(hwnd, hMenu);

		AppendMenu(LineSubMenu, MF_STRING, simpleLine, "Direct method");
		AppendMenu(LineSubMenu, MF_STRING, DDALine, "Simple DDA");
		AppendMenu(LineSubMenu, MF_STRING, MidPointLine, "Integer DDA");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) LineSubMenu, "&Lines");
		SetMenu(hwnd, hMenu);

		AppendMenu(CircleSubMenu, MF_STRING, DirectCartesian,"Direct Cartesian");
		AppendMenu(CircleSubMenu, MF_STRING, PolarDirect, "Polar Direct");
		//AppendMenu(CircleSubMenu, MF_STRING, IterativePolar, "Iterative Polar");
		AppendMenu(CircleSubMenu, MF_STRING, Bresenham, "Bresenham");
		//AppendMenu(CircleSubMenu, MF_STRING, FasterBresenhom,"Faster Bresenhom");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) CircleSubMenu,"&Circles");
		SetMenu(hwnd, hMenu);

		AppendMenu(CurveSubMenu, MF_STRING, HERMITE, "Hermite");
		AppendMenu(CurveSubMenu, MF_STRING, BEZIER, "Bezier");
		AppendMenu(CurveSubMenu, MF_STRING, CARDINAL, "Cardinal");
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT) CurveSubMenu, "&Curves");
		SetMenu(hwnd, hMenu);
	}

	case WM_SIZE: {
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < (int) graph.size(); ++i) {
			if (graph[i].alg <= 3) {
				Line l(graph[i].X1, graph[i].X2, graph[i].Y1, graph[i].Y2,
						graph[i].alg, graph[i].color);
				l.drawLine(hdc, hwnd);
			} else if (graph[i].alg < 9) {
				Circle c(graph[i].X1, graph[i].X2, graph[i].Y1, graph[i].Y2,
						graph[i].alg, graph[i].color);
				c.drawCircle(hdc, hwnd);
			} else {
				HermiteCurve curve(graph[i].X1, graph[i].X2, graph[i].X3,
						graph[i].X4, graph[i].Y1, graph[i].Y2, graph[i].Y3,
						graph[i].Y4, graph[i].alg, graph[i].color);

				curve.DrawCurve(hdc);
			}
		}
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_COMMAND: {
		if (LOWORD(wParam) <= 11) {
			g.alg = LOWORD(wParam);
			g.color = colorDialog(hwnd);
		} else if (LOWORD(wParam) == 12) {
			InvalidateRect(hwnd, NULL, true);
			graph.clear();
		} else if (LOWORD(wParam) == 13) {
			DestroyWindow(hwnd);
		} else if (LOWORD(wParam) == 14) {
			string filename = FileSave();
			saveGraph(filename);
		} else if (LOWORD(wParam) == 15) {
			string filename = FileOpen();
			loadGraph(filename, hwnd);
		}
		break;
	}

	case WM_PAINT:{
		int i = (int) graph.size() - 1;
		if (mypaint == 2 && g.alg <= 8) {
			hdc = BeginPaint(hwnd, &ps);
			if (graph[i].alg <= 3) {
				Line l(graph[i].X1, graph[i].X2, graph[i].Y1, graph[i].Y2,
						graph[i].alg, graph[i].color);
				l.drawLine(hdc, hwnd);
			} else {
				Circle c(graph[i].X1, graph[i].X2, graph[i].Y1, graph[i].Y2,
						graph[i].alg, graph[i].color);
				c.drawCircle(hdc, hwnd);
			}
			EndPaint(hwnd, &ps);
			mypaint = 0;
		} else if (mypaint == 4) {
			hdc = BeginPaint(hwnd, &ps);
			HermiteCurve curve(graph[i].X1, graph[i].X2, graph[i].X3,
					graph[i].X4, graph[i].Y1, graph[i].Y2, graph[i].Y3,
					graph[i].Y4, graph[i].alg, graph[i].color);

			curve.DrawCurve(hdc);

			EndPaint(hwnd, &ps);
			mypaint = 0;
		}
		}
		break;
	case WM_LBUTTONDOWN:
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		if (mypaint == 0) {
			g.X1 = xPos;
			g.Y1 = yPos;
			mypaint++;
		} else if (mypaint == 1) {
			g.X2 = xPos;
			g.Y2 = yPos;
			if (g.alg <= 8) {
				graph.push_back(g);
			}
			mypaint++;
		} else if (mypaint == 2) {
			g.X3 = xPos;
			g.Y3 = yPos;
			mypaint++;
		} else if (mypaint == 3) {
			g.X4 = xPos;
			g.Y4 = yPos;
			graph.push_back(g);
			mypaint++;
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void loadGraph(string filename, HWND hwnd) {
	InvalidateRect(hwnd, NULL, true);
	graph.clear();
	string line;
	ifstream myfile(filename.c_str());
	if (myfile.is_open()) {
		while (myfile.good()) {
			getline(myfile, line);
			string temp = "";
			int n = 0;
			for (int i = 0; i < (int) line.size(); ++i) {
				if (line[i] == ' ' || i == (int) line.size() - 1) {
					if (i == (int) line.size() - 1) {
						temp += line[i];
					}
					if (n == 0) {
						g.alg = atoi(temp.c_str());
					} else if (n == 1) {
						g.color = atoi(temp.c_str());
					} else if (n == 2) {
						g.X1 = atoi(temp.c_str());
					} else if (n == 3) {
						g.X2 = atoi(temp.c_str());
					} else if (n == 4) {
						g.Y1 = atoi(temp.c_str());
					} else if (n == 5) {
						g.Y2 = atoi(temp.c_str());
					} else if (n == 6) {
						g.X3 = atoi(temp.c_str());
					} else if (n == 7) {
						g.X4 = atoi(temp.c_str());
					} else if (n == 8) {
						g.Y3 = atoi(temp.c_str());
					} else if (n == 9) {
						g.Y4 = atoi(temp.c_str());
					}
					temp = "";
					n++;
				} else {
					temp += line[i];
				}
			}
			graph.push_back(g);
		}
		myfile.close();
	} else {
		cout << "Unable to open file !\n";
	}

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	for (int i = 0; i < (int) graph.size(); ++i) {
		if (graph[i].alg <= 3) {
			Line l(graph[i].X1, graph[i].X2, graph[i].Y1, graph[i].Y2,
					graph[i].alg, graph[i].color);
			l.drawLine(hdc, hwnd);
		} else if (graph[i].alg < 9) {
			Circle c(graph[i].X1, graph[i].X2, graph[i].Y1, graph[i].Y2,
					graph[i].alg, graph[i].color);
			c.drawCircle(hdc, hwnd);
		} else {
			HermiteCurve curve(graph[i].X1, graph[i].X2, graph[i].X3,
					graph[i].X4, graph[i].Y1, graph[i].Y2, graph[i].Y3,
					graph[i].Y4, graph[i].alg, graph[i].color);

			curve.DrawCurve(hdc);
		}
	}
	EndPaint(hwnd, &ps);
}

void saveGraph(string filename) {
	ofstream myfile;
	myfile.open(filename.c_str());
	for (int i = 0; i < (int) graph.size(); ++i) {
		myfile << graph[i].alg << " " << graph[i].color << " " << graph[i].X1
				<< " " << graph[i].X2 << " " << graph[i].Y1 << " "
				<< graph[i].Y2;
		if (graph[i].alg >= 9 && graph[i].alg <= 11) {
			myfile << " " << graph[i].X3 << " " << graph[i].X4 << " "
					<< graph[i].Y3 << " " << graph[i].Y4;
		}
		myfile << endl;
	}
	myfile.close();
}
