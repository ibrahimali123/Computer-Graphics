#pragma once
#include <windows.h>
#include "myPoint.h"

class myCircle
{
public:
       
	int x;
	int y;
	int R;
	myPoint Center;
	int drawingAlgorithm;
	COLORREF color;
	myCircle();
    myCircle(myPoint p1, myPoint p2, int alg);
	void drawCircle(HDC hdc);
	void drawSimple(HDC hdc);
	void DrawPoints(HDC hdc, int xc, int yc, int x, int y);
	void PolarAlgorithm(HDC hdc);
	void MidPoint(HDC hdc);
	int round(double x);
	
};
