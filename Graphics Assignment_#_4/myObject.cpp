#include "myCircle.h"
#include "myPoint.h"
#include "myObject.h"
#include "myCurve.h"

void myObject::drawshape(HDC hdc)
{
     if ( shape == 1 )
     {              
			L = myLine(p1,p2,alg);
			L.color = color;
			L.drawLine(hdc);
      }

     if ( shape == 2 )
     {
            C = myCircle(p1,p2,alg);
			C.color = color;
            C.drawCircle(hdc);        
     }
     if ( shape == 3 )
     {
            U = myCurve(x1,y1,x2,y2,x3,y3,x4,y4,alg);
			U.color = color;
            U.DrawCurve(hdc);        
     }
}
