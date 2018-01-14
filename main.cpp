#include <stdlib.h>
#include<Windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include<stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/GLAUX.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define PI 3.1416
float angle=0.0,deltaAngle = 0.0,ratio;
float x=0.0f,y=1.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int font=(int)GLUT_BITMAP_TIMES_ROMAN_24;
static GLint snowman_display_list;
int bitmapHeight=13;
static float	tx	=  0.0;
static float	ty	=  0.0;

int frame,time,timebase=0;
char s[30];

void initWindow();
void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

	glEnd();
}
void changeSize(int w1, int h1)
 {
 if(h1 == 0)
  h1 = 1;

 w = w1;
 h = h1;
 ratio = 1.0f * w / h;

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

    glViewport(0, 0, w, h);

 gluPerspective(45,ratio,0.1,1000);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(x, y, z,
        x + lx,y + ly,z + lz,
     0.0f,1.0f,0.0f);
 }
void pyra(){
     glBegin(GL_TRIANGLES);
     glColor3f(1.0f, 0.84, 1.0f);
//right
      glVertex3f(2.0f, -1.8f, 1.0f);
     glVertex3f(4.0f, -4.8f, 2.0f);
     glVertex3f(4.0f, -4.8f, 0.0f);			// Bottom front Of The Quad (right)

//left
      glVertex3f( 2.0f, -1.8f, 1.0f);
     glVertex3f(0.0f,-4.8f,0.0f);
      glVertex3f(0.0f,-4.8f, 2.0f);
        // Back

     glVertex3f(2.0f, -1.8f, 1.0f);
      glVertex3f(4.0f, -4.8f, 0.0f);
     glVertex3f(0.0f, -4.8f, 0.0f);

             // Front
    glVertex3f( 2.0f, -1.8f, 1.0f);
    glVertex3f(0.0f, -4.8f, 2.0f);
   glVertex3f(4.0f, -4.8f, 2.0f);				// Bottom Right Of The Quad (Front)

        glEnd();

}
void robot() {
 // body
 glColor3f(1.0f, 1.0f, 0.0f);
 glTranslatef(0.0f ,0.75f, 0.0f);
 glutSolidSphere(0.75f,5,170);

// Draw Head
 glColor3f(1.0f, 0.84, 0.0f);
 glTranslatef(0.0f, 1.0f, 0.0f);
 glutSolidSphere(0.85f,60,80);

 // eyes
 glPushMatrix();
 glColor3f(0.0f,0.0f,0.0f);
 glTranslatef(-0.2,0.3,0.8);
 circle(.07,.07);
 glTranslatef(0.3,0.008,0.029);
 circle(.065,.065);
 glPopMatrix();

// Draw Nose
 glColor3f(1.0f, 0.0f , 0.0f);
 glRotatef(0.0f,1.0f, 0.0f, 0.0f);
 glutSolidCone(0.38f,1.0f,20,1);

    glBegin(GL_QUADS);
    // leg1
      glColor3f(1.0f, 0.0, 0.0f);
      glVertex3f( 0.0f,  -0.0f, 0.0f);
      glVertex3f(-0.2,  -0.0f, 0.0f);
      glVertex3f(-0.2f, -3.9f, 0.0f);
      glVertex3f( 0.0f, -3.9f, 0.0f);
//leg2
      glColor3f(1.0f, 0.0, 0.0f);
      glVertex3f( 0.3f,  0.0f, 0.0f);
      glVertex3f(0.1,  0.0f, 0.0f);
      glVertex3f(0.1f, -4.9f, 0.0f);
      glVertex3f( 0.3f, -4.9f, 0.0f);


     //hand1
      glColor3f(1.0f, 0.84, 0.0f);
      glVertex3f( 1.3f,  -0.8f, 0.0f);
      glVertex3f(0.7f,  -0.8f, 0.0f);
      glVertex3f(0.5f, -0.92f, 0.0f);
      glVertex3f( 1.2f, -0.94f, 0.0f);

      //hand2
      glColor3f(1.0f, 0.84, 0.0f);
      glVertex3f( -1.4f,  -0.78f, 0.0f);
      glVertex3f(-0.2f,  -0.8f, 0.0f);
      glVertex3f(-0.5f, -0.92f, 0.0f);
      glVertex3f( -1.2f, -0.92f, 0.0f);

      glEnd();

//hand
    glPushMatrix();
     glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(-1.3,-0.8,0.06);
    circle(0.13,0.12);
    glPopMatrix();

    glPushMatrix();
     glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(1.2,-0.8,0.06);
    circle(0.13,0.12);
    glPopMatrix();
//lip
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.1,-0.2,0.8);
    circle(0.3,0.1);
    glPopMatrix();

    //headcircle
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(0.0,1.1,0.08);
    circle(0.5,0.1);
    glPopMatrix();

    //head2
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0,1.1,0.08);
    circle(0.3,0.3);
    glPopMatrix();

    //middle
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0,-0.4,0.8);
    circle(0.3,0.3);
    glPopMatrix();

    //legc
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(-0.1,-1.7,0.18);
    circle(0.09,0.09);
    glPopMatrix();

     //legc2
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.19,-1.7,0.18);
    circle(0.09,0.09);
    glPopMatrix();

}

GLuint createDL() {
 GLuint robott;

 // Create the id for the list
 robott = glGenLists(2);

 glNewList(robott+1,GL_COMPILE);
  robot();
  pyra();
  //android();
 glEndList();
 // start list
 glNewList(robott,GL_COMPILE);

 // call the function that contains the rendering commands
 for(int i = -1; i < 2; i++)
  for(int j=-1; j < 3; j++) {
   glPushMatrix();
   glTranslatef(i*10.0,0,j * 10.0);
   glCallList(robott+1);
   glPopMatrix();
  }
 // endList
 glEndList();
 return(robott);
}
void initScene() {

 glEnable(GL_DEPTH_TEST);
 snowman_display_list = createDL();

}
void orientMe(float ang) {

 lx = sin(ang);
 lz = -cos(ang);
 glLoadIdentity();
 gluLookAt(x, y, z,
        x + lx,y + ly,z + lz,
     0.0f,1.0f,0.0f);
}

void moveMeFlat(int i) {
 x = x + i*(lx)*0.1;
 z = z + i*(lz)*0.1;
 glLoadIdentity();
 gluLookAt(x, y, z,
        x + lx,y + ly,z + lz,
     0.0f,1.0f,0.0f);
}
void setOrthographicProjection() {

 // switch to projection mode
 glMatrixMode(GL_PROJECTION);

 glPushMatrix();
 glLoadIdentity();

 gluOrtho2D(0, w, 0, h);

 glScalef(1, -1, 1);

 glTranslatef(0, -h, 0);
 glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
 // set the current matrix to GL_PROJECTION
 glMatrixMode(GL_PROJECTION);
 // restore previous settings
 glPopMatrix();
 // get back to GL_MODELVIEW matrix
 glMatrixMode(GL_MODELVIEW);
}
void renderBitmapString(float x, float y, void *font,char *string)
{
  char *c;
  glRasterPos2f(x, y);
  // loop all the characters in the string
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void renderScene(void) {

 if (deltaMove)
  moveMeFlat(deltaMove);
 if (deltaAngle) {
  angle += deltaAngle;
  orientMe(angle);
 }

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// ground
 glBegin(GL_QUADS);
 glColor3f(0.52f, 0.80f, 0.921f);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glColor3f(0.69f, 0.87f, 0.90f);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glColor3f(0.67f, 0.84f, 0.9f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glColor3f(0.52f, 0.8f, 0.98f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
 glEnd();

 glCallList(snowman_display_list);

 frame++;
 time=glutGet(GLUT_ELAPSED_TIME);
 if (time - timebase > 1000) {
  sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
  timebase = time;
  frame = 0;
 }

 glColor3f(0.0f,1.0f,1.0f);
 setOrthographicProjection();
 glPushMatrix();
 glLoadIdentity();
 renderBitmapString(30,40,(void *)font,"Click ->,<- for left,right,up,down");
 glPopMatrix();
 resetPerspectiveProjection();

 glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

 if (key == 27)
  exit(0);
}

void pressKey(int key, int x, int y) {

 switch (key) {
  case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
  case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
  case GLUT_KEY_UP : deltaMove = 1;break;
  case GLUT_KEY_DOWN : deltaMove = -1;break;
 }

}
void releaseKey(int key, int x, int y) {

 switch (key) {
  case GLUT_KEY_LEFT : if (deltaAngle < 0.0f)
         deltaAngle = 0.0f;
        break;
  case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
         deltaAngle = 0.0f;
        break;
  case GLUT_KEY_UP :  if (deltaMove > 0)
         deltaMove = 0;
        break;
  case GLUT_KEY_DOWN : if (deltaMove < 0)
         deltaMove = 0;
        break;
 }
}
void initWindow() {
 glutIgnoreKeyRepeat(1);
 glutKeyboardFunc(processNormalKeys);
 glutSpecialFunc(pressKey);
 glutSpecialUpFunc(releaseKey);
 glutDisplayFunc(renderScene);
 glutIdleFunc(renderScene);
 glutReshapeFunc(changeSize);
 initScene();

}
int main(int argc, char **argv)
{
 PlaySound("Candy_Crush_Soda_Saga.wav", NULL, SND_FILENAME| SND_ASYNC);
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(640,360);
 glutCreateWindow("Smiley Robots");
 initWindow();

 glutMainLoop();

 return(0);
}
