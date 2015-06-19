#include <windows.h>
#include <gl\gl.h>
#include <GL\glut.h>
#include<math.h>
#include<iostream>
#include <stdlib.h>
using namespace std;
float theta = 0.0;     // angle to Open or Close house door

float gama = 0.0;      // angle to Open or Close house window 
float  CameraXPosition = 0 , CameraYPosition = 0 ;
bool Xaxis = false, Yaxis = false;
float segma = 0.0;     // angle to move Car forward or backward
int beta1 = 0.0 , beta2 = 0.0 , badal = 0;      // angle to rotate Car wheels left or right
float delta = 0.0;     // angel to move the car arround the house .
const int   A = 500;  /* length of a side of the monitor window */
const float B = 500;  /* length of a side of the clipping rectangle */
const float C = 200;  /* length of a side of the square the program draws */
int q=0;
int w=0;
int e=0;

void Init(void)
{
    glClearColor(0, 1.0, 0, 0.0); /* gray background */
    glMatrixMode(GL_PROJECTION);      /* In World coordinates: */
    glLoadIdentity();                 /* position the "clipping rectangle" */
    glOrtho(-B/2,B/2,-B/2,B/2,500,-500);

    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective correction
    glMatrixMode(GL_MODELVIEW);       /* edge at -B/2 and its top edge at +B/2 */
}


void Display()
{
     delta += 0.15;
     badal +=5;
     badal %=360;
     glutPostRedisplay(); // recall Display function
}

static void idle(void){
           glutPostRedisplay();    // recall display function
}

void myMouse(int mouse,int state,int x,int y){
	 if(mouse == GLUT_LEFT_BUTTON){
             glutIdleFunc(Display);
     }
     if(mouse == GLUT_RIGHT_BUTTON){
              glutIdleFunc(NULL);
     }
}

void specialKey(int key, int x, int y)
{

// The keys below are using the gluLookAt() function for navigation
// Check which key is pressed

    switch(key)
    {
    case GLUT_KEY_LEFT : 
        CameraXPosition -= 6;
        Yaxis = false;
        Xaxis = true;
        break;
    case GLUT_KEY_RIGHT : 
        CameraXPosition += 6;
        Yaxis = false;
        Xaxis = true;
        break;
    case GLUT_KEY_UP :
        CameraYPosition += 6;
        Xaxis = false;
        Yaxis = true;
        break;
    case GLUT_KEY_DOWN :
        CameraYPosition -= 6;
        Xaxis = false;
        Yaxis = true;
        break;
    }
    glutPostRedisplay(); // Redraw the scene
}

void keyUse(unsigned char key,int x,int y )
{
    if(key == 'o')  // to open  the house door with suitable angle.
    {
        if(theta < 45)
            theta += 10;
        glutPostRedisplay();
    }
    else if(key == 'c')  // to close the house door with suitable angle.
    {
        if(theta > 0)
            theta -= 10;
        glutPostRedisplay();
    }

    else if(key == 'O')  // to open  the house window with suitable angle.
    {
        if(gama < 40)
            gama += 10;
        glutPostRedisplay();
    }
    else if(key == 'C')  // to Close  the house window with suitable angle.
    {
        if(gama > 0)
            gama -= 10;
        glutPostRedisplay();
    }

    else if(key == '1')  // to Close  the house window with suitable angle.
    {
        q+=5;
        q%=360;
        glutPostRedisplay();
    }
    else if(key == '2' ) // to Close  the house window with suitable angle.
    {
        w+=5;
        w%=360;
        glutPostRedisplay();
    }
    else if(key == '3')// to Close  the house window with suitable angle.
    {
        e+=5;
        e%=360;
        glutPostRedisplay();
    }
    else if(key == 'f')  // to move the car forward in X-axis direction.
    {
    	badal +=5;
        badal %=360;
        
		beta1+=5;
        beta1%=360;
        
        beta2+=5;
        beta2%=360;
		
		segma += 3;
        glutPostRedisplay();
    }
    else if(key == 'b')  // to move the car backward in X-axis direction.
    {
    	badal -=5;
        badal %=360;
        
        beta1-=5;
        beta1%=360;
        
        beta2-=5;
        beta2%=360;
        
		segma -= 3;
        glutPostRedisplay();
    }

    else if(key == 'l')  // to rotate right the car wheels [ rotate only ]
    {
        beta1+=5;
        beta1%=360;
        glutPostRedisplay();
    }
    else if(key == 'r')  // to rotate left  the car wheels [ rotate only ]
    {
        beta2+=5;
        beta2%=360;
        glutPostRedisplay();
    }
}

void displayHome()
{

    glScaled(.5,.5,.5);
    glPushMatrix();

    glRotatef(q,1,0,0);
    glRotatef(w,0,1,0);
    glRotatef(e,0,0,1);

    glBegin(GL_POLYGON) ;         //roof
    glColor3f ( 1, 1, 0.0);       /* draw in light red */
    glVertex3f( 75, 250 ,75);
    glVertex3f( 0, 150 ,0);
    glVertex3f( 150, 150,0);
    glVertex3f( 150,150,150);
    glVertex3f( 0,150,150);
    glEnd();

    glBegin(GL_TRIANGLES);		 //roof
    glColor3f ( 1, 1, 0.0);       /* draw in light red */
    glVertex3f( 75, 250 ,75);
    glVertex3f( 0, 150,0);
    glVertex3f( 0,150,150);
    glEnd();

    glBegin(GL_POLYGON) ;             //front
    glColor3f ( 1.0, 0, 0);       /* draw in light red */
    glVertex3f( 0, -150 ,0);
    glVertex3f( 0, 150,0);
    glVertex3f( 150,150,0);
    glVertex3f( 150,-150,0);
    glEnd();

    glBegin(GL_LINES) ;             //line front
    glColor3f ( 0, 0, 0);       /* draw in front red */
    glVertex3f( 0, 0 ,0);
    glVertex3f( 150, 0,0);
    glEnd();

    //    glBegin(GL_QUAD_STRIP);         //floor second
    //    glColor3f ( 1, 1, 0);       /* draw in light red */
    //    glVertex3f( 0, 0 ,0);
    //    glVertex3f( 150, 0,0);
    //    glVertex3f( 0, 0,150);
    //    glVertex3f( 150, 0,150);
    //    glEnd();

    glBegin(GL_POLYGON) ;             //left
    glColor3f ( 0, 1.0, 1);
    glVertex3f( 0, -150 ,0);
    glVertex3f( 0, 150,0);
    glVertex3f( 0,150,150);
    glVertex3f( 0,-150,150);
    glEnd();

    glBegin(GL_LINES) ;             //line left
    glColor3f ( 0, 0, 0);       /* draw in left red */
    glVertex3f( 0, 0,150);
    glVertex3f( 0, 0,0);
    glEnd();

    glBegin(GL_POLYGON) ;             //right
    glColor3f ( 0, 0, 1);
    glVertex3f( 150, -150, 0 );
    glVertex3f( 150, 150,0);
    glVertex3f( 150,150,150);
    glVertex3f( 150,-150,150);
    glEnd();

    glBegin(GL_LINES) ;             //line left
    glColor3f ( 0, 0, 0);       /* draw in left red */
    glVertex3f( 150, 0,150);
    glVertex3f( 150, 0,0);
    glEnd();

    glBegin(GL_POLYGON) ;             //right
    glColor3f ( 1, 0, 1);
    glVertex3f( 0, -150 ,150);
    glVertex3f( 0, 150,150);
    glVertex3f( 150,150,150);
    glVertex3f( 150,-150,150);
    glEnd();

    glBegin(GL_LINES) ;             //line left
    glColor3f ( 0, 0, 0);       /* draw in left red */
    glVertex3f( 0, 0,150);
    glVertex3f( 150, 0,150);
    glEnd();


    /********************  Door ****************/
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 0, 0, 0);
    glVertex3f( 60, -150 ,0);
    glVertex3f( 90, -150 ,0);
    glVertex3f( 60,-90,0);
    glVertex3f( 90,-90,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glRotatef(35,1,1,0);     // rotate by 35 on x,y
    glRotatef(theta,0,1,0);  // to open  the house door by theta
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 1, 1, 0);
    glVertex3f( 60, -150 ,0);
    glVertex3f( 90, -150 ,0);
    glVertex3f( 60,-90,0);
    glVertex3f( 90,-90,0);
    glEnd();
    glPopMatrix();

    /********************  Window ****************/
    // Window # 1
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 0, 0, 0);
    glVertex3f( 20, -20 ,0);
    glVertex3f( 50, -20 ,0);
    glVertex3f( 20,-60,0);
    glVertex3f( 50,-60,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glRotatef(35,1,1,0);     // rotate by 35 on x,y
    glRotatef(gama,0,1,0);  // to open  the house door by theta
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 1, 1, 0);
    glVertex3f( 20, -20 ,0);
    glVertex3f( 50, -20 ,0);
    glVertex3f( 20,-60,0);
    glVertex3f( 50,-60,0);
    glEnd();
    glPopMatrix();

    // Window # 2
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 0, 0, 0);
    glVertex3f( 100, -20 ,0);
    glVertex3f( 130, -20 ,0);
    glVertex3f( 100,-60,0);
    glVertex3f( 130,-60,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glRotatef(35,1,1,0);     // rotate by 35 on x,y
    glRotatef(gama,0,1,0);  // to open  the house door by theta
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 1, 1, 0);
    glVertex3f( 100, -20 ,0);
    glVertex3f( 130, -20 ,0);
    glVertex3f( 100,-60,0);
    glVertex3f( 130,-60,0);
    glEnd();
    glPopMatrix();

    ///////////////////////
    // Window # 3
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 0, 0, 0);
    glVertex3f( 20, 120 ,0);
    glVertex3f( 50, 120 ,0);
    glVertex3f( 20, 80,0);
    glVertex3f( 50, 80,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glRotatef(35,1,1,0);     // rotate by 35 on x,y
    glRotatef(gama,0,1,0);  // to open  the house door by theta
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 1, 1, 0);
    glVertex3f( 20, 120 ,0);
    glVertex3f( 50, 120 ,0);
    glVertex3f( 20, 80,0);
    glVertex3f( 50, 80,0);
    glEnd();
    glPopMatrix();

    // Window # 4
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 0, 0, 0);
    glVertex3f( 100, 120 ,0);
    glVertex3f( 130, 120 ,0);
    glVertex3f( 100, 80,0);
    glVertex3f( 130, 80,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    //glRotatef(35,1,1,0);     // rotate by 35 on x,y
    glRotatef(gama,0,1,0);  // to open  the house door by theta
    glBegin(GL_QUAD_STRIP);
    glColor3f ( 1, 1, 0);
    glVertex3f( 100, 120 ,0);
    glVertex3f( 130, 120 ,0);
    glVertex3f( 100, 80,0);
    glVertex3f( 130, 80,0);
    glEnd();
    glPopMatrix();
}

void displayCar(){
	
	/***************** Car Wheel ********************/
    glPopMatrix();
    
	glTranslatef(40,0,3);   //  transelate the car on x , z axis
    glScalef( 1.5,1.5,0);     //  to control car size
    glTranslatef(0, 40,9);
    glPushMatrix();
    
    glTranslatef(0.0,160,-10);
    glRotatef(delta,0,.8,.4);      // to move or stop the car arround the house.
    glTranslatef(0.0,-160,10);

    glPushMatrix();
    //glRotatef(-20,1,0,0);            // rotate by -20 on x , y
    glTranslatef(segma,0,0);
    //glRotatef(segma,1,1,0);         //to move the car forward or backward in X-axis direction.
    
	// right front Car wheel
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(60,-250,0);
    glRotatef(beta1,0 , 0 , -1);
    glutSolidTorus(5, 7, 3, 9);  // Draw car wheel
    glPopMatrix();
    
    // left front Car wheel
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(95,-250,0);
    glRotatef(beta2,0 , 0 , -1);
    glutSolidTorus(5, 7, 3, 9);  // Draw car wheel
    glPopMatrix();

	// badal
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(77,-240,0); 
    glRotatef(badal,0 , 0 , -1);
    glutSolidTorus(2, 3, 3, 9);  // Draw car wheel
    glPopMatrix();
     
    glBegin(GL_LINES) ;         //line
    glColor3f ( 0, 0, 0);       /* draw in left red */
    glVertex3f( 40, -235,0);
    glVertex3f( 110, -235,0);
    glEnd();

    glBegin(GL_QUAD_STRIP) ;         //line
    glColor3f ( 0, 0, 0);       /* draw in left red */
    glVertex3f( 80, -235,0);
    glVertex3f( 100, -235,0);
    glVertex3f( 90, -215,0);
    glVertex3f( 95, -215,0);
    glEnd();

    glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(65, -206,0);
    glutSolidTorus(3, 3, 3, 8);
    glPopMatrix();

    glBegin(GL_QUAD_STRIP) ;     //ensan
    glColor3f ( 0, 0, 0);       /* draw in left red */
    glVertex3f( 60, -214,0);
    glVertex3f( 70, -214,0);
    glVertex3f( 60, -235,0);
    glVertex3f( 70, -235,0);
    glEnd();

    glBegin(GL_LINES) ;         //line
    glColor3f ( 0, 0, 0);       /* draw in left red */
    glVertex3f( 70, -220,0);
    glVertex3f( 90, -214,0);
    glEnd();

    glPopMatrix();
}
void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     /* clear the window */
    glMatrixMode(GL_MODELVIEW);       /* The following coordinates are expressed */
    glLoadIdentity();    /* in terms of World coordinates */
 
    if(Xaxis)
    	glTranslatef(CameraXPosition,CameraYPosition,0);
    else if(Yaxis)
		glTranslatef(CameraXPosition,CameraYPosition,0);	
    // display the home
    displayHome();
    displayCar();
    //glBegin(gl_)
    glPopMatrix();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1000,700);
    glutCreateWindow("OpenGL Window");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKey); // set window's to specialKey callback
    glutMouseFunc(myMouse);
    glutKeyboardFunc(keyUse);
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
}

