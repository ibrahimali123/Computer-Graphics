#include "myCircle.h"
#include "myPoint.h"
#include <math.h>

myCircle::myCircle()
{
                             Center = myPoint(0,0);
                             R = 0;
                             drawingAlgorithm = 0;
}

myCircle::myCircle(myPoint p1, myPoint p2, int alg)
{
    x=p1.x;
    y=p1.y;
    Center = myPoint(x,y);
    
     R = (int)sqrt( pow((p1.x-p2.x),2) +pow((p1.y-p2.y),2) );
     drawingAlgorithm = alg;
}

void myCircle::drawCircle(HDC hdc)
{
     switch(drawingAlgorithm)
     {
                             case 3:
                                  drawSimple(hdc);
                                  break;
                             case 4:
                                  PolarAlgorithm(hdc);
                                  break;
                             case 5:
                                  MidPoint(hdc);
                                  break;
                             default:
                                     break;
     }
}

void myCircle::DrawPoints(HDC hdc, int xc, int yc, int x, int y)
{
     SetPixel(hdc, xc+x,yc+y,color);
     SetPixel(hdc, xc-x,yc+y,color);
     SetPixel(hdc, xc-x,yc-y,color);
     SetPixel(hdc, xc+x,yc-y,color);
     SetPixel(hdc, xc+y,yc+x,color);
     SetPixel(hdc, xc-y,yc+x,color);
     SetPixel(hdc, xc-y,yc-x,color);
     SetPixel(hdc, xc+y,yc-x,color);
}

int myCircle::round(double x)
{
	return (int)(x+0.5);
}

void myCircle::drawSimple(HDC hdc)
{
     int x = 0, y = R;
     DrawPoints(hdc, Center.x,Center.y,x,y);
     
     while(x < y)
     {
               x++;
               y = (int)(sqrt(R*R - x*x));
               DrawPoints(hdc,Center.x,Center.y,x,y);
     }
}

void myCircle::PolarAlgorithm(HDC hdc)
{
    double x = R, y = 0;
    double dtheta = 1.0/R;
    double cdtheta = cos(dtheta), sdtheta = sin(dtheta);
    DrawPoints(hdc,Center.x,Center.y,R,0);
    while(x>y)
    {
              double x1 = x*cdtheta - y*sdtheta;
              y = x*sdtheta + y*cdtheta;
              x = x1;
              DrawPoints(hdc,Center.x,Center.y,round(x),round(y));
    }     
}

void myCircle::MidPoint(HDC hdc)
{
     int x = 0, y = R, d = 1-R, dch1 = 3, dch2 = (5-2*R);
     DrawPoints(hdc,Center.x,Center.y,x,y);
     
     while(x<y)
     {
               if(d<0)
               {
                      d += dch1;
                      dch2 += 2;
               }
               else
               {
                   d += dch2;
                   y--;
                   dch2 += 4;
               }
               dch1 += 2;
               x++;
               DrawPoints(hdc,Center.x,Center.y,x,y);
     }
}
