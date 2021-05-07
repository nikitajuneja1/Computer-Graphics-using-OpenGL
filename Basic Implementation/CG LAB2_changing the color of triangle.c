#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int click_no=0;
void init()
{
    glClearColor(1, 1, 1, 0.0);
    glMatrixMode(GL_PROJECTION);
    // Set 2D Transformation as gluOrtho2D(Min Width, Max Width, Min Height, Max Height)
    gluOrtho2D(0.0, 800, 0.0, 600);
    
}

void Sprint( int x, int y, char *st)
{
    int l,i;
    
    l=strlen(st);
    glColor3f(0, 0, 0);
    glRasterPos2i( x, y);
    for( i=0; i<l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(click_no==0){
        glColor3f(0.0, 1.0, 0.0);
    }
    else{
        glColor3f(0.0, 0.0, 1.0);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(200,200);
    glVertex2i(400,400);
    glVertex2i(600,200);
    glEnd();
    
    glColor3f(1, 1, 1);
    Sprint( 10, 10, "Nikita Juneja R110218098");
    glFlush();
}

void MyMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(click_no==0)
            click_no=1;
        else if(click_no==1)
            click_no=0;
        glutPostRedisplay();
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lab 2: Changing color of triangle");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(MyMouse);
    glutMainLoop();
}
