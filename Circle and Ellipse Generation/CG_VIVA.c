#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ESC 27

int i=1,j=1;
int numberOfClicks = 0;
float slope;
int x0, y, x1, yy;

int mainWindow, subWindow1, subWindow2;

void Sprint( int x, int y, char *st)
{
    int l,ii;
    l=strlen(st);
    glColor3f(0, 0, 0);
    glRasterPos2i( x, y);
    for( ii=0; ii<l; ii++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[ii]);
    }
}

void points(int a, int b){
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2f(a,b);
    glEnd();
}
void drawCirclePolar(float cx, float cy, float r, int num_segments){
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * (ii) / (num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void circle(int x0, int y0) {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    float r = 80;
    float x = 0, y = r;
    float p = 1 - r;
    glBegin(GL_POINTS);
    while (x != y)
    {
        x++;
        if (p < 0) {
            p += 2 * (x + 1) + 1;
        }
        else {
            y--;
            p += 2 * (x + 1) + 1 - 2 * (y - 1);
        }
        glVertex2i(x+x0, y+y0);
        glVertex2i(-x+x0, y+y0);
        glVertex2i(x+x0, -y+y0);
        glVertex2i(-x+x0, -y+y0);
        
        glVertex2i(y+x0, x+y0);
        glVertex2i(-y+x0, x+y0);
        glVertex2i(y+x0, -x+y0);
        glVertex2i(-y+x0, -x+y0);
        
    }
    glEnd();
    glFlush();
}
void mouseClickSubW1(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        numberOfClicks++;
        x0 = mousex;
        y = 480-mousey;
        points(x0, y);
        glColor3f(1,0,0);
//
        circle(x0,y);
    }
    glutPostRedisplay();
}
void mouseClickSubW2(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        numberOfClicks++;
        x0 = mousex;
        y = 480-mousey;
        points(x0, y);
        glColor3f(1,1,1);
        drawCirclePolar(x0, y, 50, 50);
        
    }
//
    glutPostRedisplay();
}
void displaySub1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    circle(x0,y);
    
    Sprint(20, 440, "Nikita Juneja R110218098");
    Sprint(50, 20, "Circle Generation using Mid Point Algo");
    glFlush();
}

void displaySub2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClearColor(1, 1, 1, 0);
    drawCirclePolar(x0, y, 50, 50);
    Sprint(680, 440, "Nikita Juneja R110218098");
    Sprint(200, 20, "Circle generation using Polar Coordinates ");
    glFlush();
}
void displayMain(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 1290.0, 0.0, 500.0);
    glFlush();
}
void keyboard(unsigned char key, int mousex, int mousey){
    if(key==ESC){
        exit(0);
    }
    glutPostRedisplay();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1290,500);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    mainWindow = glutCreateWindow("Viva: NikitaJuneja");
    glutDisplayFunc(displayMain);
    
    subWindow1 = glutCreateSubWindow(mainWindow, 0, 10, 640, 480);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(displaySub1);
    
    glutMouseFunc(mouseClickSubW1);
    
    subWindow2 = glutCreateSubWindow(mainWindow, 640 + 10, 10, 640, 480);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(displaySub2);
    
    
    glutMouseFunc(mouseClickSubW2);
    
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
