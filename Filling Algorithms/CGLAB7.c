#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define SPACE 32
#define ESC 27
int a,b;

void points(int xCoordinate, int yCoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xCoordinate, yCoordinate);
    glEnd();
    glFlush();
}


void Sprintf(int x, int y, char* st)
{
    int l,ii;
        l=strlen(st);
        glRasterPos2i( x, y);
        for( ii=0; ii<l; ii++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[ii]);
        }
}
int mainWindow, subWindow1, subWindow2;

void midPointCircle(int x0, int y0) {
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    float r = 70;
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
void boundaryFill(int x, int y, float *fillColor, float *bc)
{
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2]))
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        points(x, y);
        glFlush();
        boundaryFill(x + 2, y, fillColor, bc);
        boundaryFill(x - 2, y, fillColor, bc);
        boundaryFill(x, y + 2, fillColor, bc);
        boundaryFill(x, y - 2, fillColor, bc);
    }
}

void floodFill(int x, int y, float *fillColor, float *oc)
{
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    if ((color[0] == oc[0] && color[1] == oc[1] && color[2] == oc[2]))
    {
        glColor3f(fillColor[0], fillColor[1], fillColor[2]);
        points(x, y);
        glFlush();
        floodFill(x + 2, y, fillColor, oc);
        floodFill(x - 2, y, fillColor, oc);
        floodFill(x, y + 2, fillColor, oc);
        floodFill(x, y - 2, fillColor, oc);
    }
}

void mouseClickSubW1(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        a = x;
        b = 400 - y;
        glColor3f(0.3, 0.0, 0.9);
        midPointCircle(a, b);
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        float bCol[] = {1, 0, 0};
        float color[] = {1, 0, 1};
        
        boundaryFill(x, 400 - y, color, bCol);
    }
    glFlush();
}

void mouseClickSubW2(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        
        a = x;
        b = 400 - y;
        glColor3f(0.0, 0.0, 0.0);
        midPointCircle(a, b);
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        float bCol[] = {1, 1, 1};
        float color[] = {0, 0, 1};
        floodFill(x, 400 - y, color, bCol);
    }
}
void keyPressSubW1(unsigned char key, int x, int y)
{
    if (key == SPACE)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else if (key == ESC)
    {
        exit(0);
    }
}
void keyPressSubW2(unsigned char key, int x, int y)
{
    if (key == SPACE)
    {
       glClear(GL_COLOR_BUFFER_BIT);
    }
    else if (key == ESC)
    {
        exit(0);
    }
}
void displaySub1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0, 0, 0);
    Sprintf(15, 370, "Nikita Juneja R110218098");
    Sprintf(15, 15, "Boundary Fill Algorithm");
    glFlush();
}

void displaySub2()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    Sprintf(15, 370, "Nikita Juneja R110218098");
    Sprintf(15, 15, "Flood Fill Algorithm");
    glFlush();
}

void displayMain(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutSetWindow(mainWindow);
    
    glFlush();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(2 * 400, 2 * 400);
    
    mainWindow = glutCreateWindow("Lab6: Seed Fill Algorithms");
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(0, 2 * 400, 0, 2 * 400);
    glutDisplayFunc(displayMain);
    
    subWindow1 = glutCreateSubWindow(mainWindow, 0, 0, 400, 400);
    gluOrtho2D(0, 400, 0, 400);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(displaySub1);
    
    glutMouseFunc(mouseClickSubW1);
    glutKeyboardFunc(keyPressSubW1);
    
    subWindow2 = glutCreateSubWindow(mainWindow, 400, 400, 400, 400);
    gluOrtho2D(0, 400, 0, 400);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(displaySub2);
    
    glutMouseFunc(mouseClickSubW2);
    glutKeyboardFunc(keyPressSubW2);
    glutMainLoop();
}
