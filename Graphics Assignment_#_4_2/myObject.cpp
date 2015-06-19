#include "myCircle.h"
#include "myPoint.h"
#include "myObject.h"

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
}
