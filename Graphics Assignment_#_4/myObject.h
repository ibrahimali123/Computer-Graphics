#pragma once
#include <windows.h>
#include "myCircle.h"
#include "myLine.h"
#include "myPoint.h"
#include "myCurve.h"


class myObject
{
      public :
      int shape;
      int alg;
      myPoint p1,p2;
      myLine L ;
      myCircle C;
      myCurve U;
      COLORREF color ;
      void drawshape(HDC hdc);
      int X1;
      int X2;
      int X3;
      int X4;
      int Y1;
      int Y2;
   	  int Y3;
      int Y4;    
};
