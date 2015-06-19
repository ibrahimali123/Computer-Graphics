#pragma once
#include <windows.h>
#include "myCircle.h"
#include "myLine.h"
#include "myPoint.h"

class myObject
{
      public :
      int shape;
      int alg;
      myPoint p1,p2;
      //myPoint p3,p4;   for curve class
      //myCurve CV;
      myLine L ;
      myCircle C ;
      COLORREF color ;
      void drawshape(HDC hdc);
      
};
