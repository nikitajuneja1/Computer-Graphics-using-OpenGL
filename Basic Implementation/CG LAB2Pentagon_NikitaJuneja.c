#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SPACE 32
#define ESC 27


int x[50],y[50],i=1,j=1;
float r,g,b;
int a=1, f=1;
int numberOfClicks = 0, numOfSegments = 5;
float radius = 50.0;

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

void DrawPentagon(float cx, float cy, float r, int num_segments) {
    
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * (ii) / (num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
    numberOfClicks++;
    
}
void colourPentagon(float cx, float cy, float r, int num_segments){
    
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * (ii) / (num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
    
}
void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        x[i] = mousex;
        y[i] = 480-mousey;
        DrawPentagon(x[i], y[i],radius,numOfSegments);
        i++;
    }
    else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//undo(clear)the drawing
    {
//        while(a<=i){
        if(a>numberOfClicks){
            return;
        }
        else{
            r=(float)rand() / (float)RAND_MAX;
            g=(float)rand() / (float)RAND_MAX;
            b=(float)rand() / (float)RAND_MAX;
            glColor3f(r,g,b);
            colourPentagon(x[a], y[a],radius,numOfSegments);
            a++;
        }

    }
    glutPostRedisplay();
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    Sprint(10, 10, "Nikita Juneja R110218098");
    glFlush();
}
void keyboard(unsigned char key, int mousex, int mousey){
    if(key==SPACE){
        glColor3f(1,1,1);
        colourPentagon(x[f], y[f],50.0,5);
        f++;
    }
    if(key==ESC){
        exit(0);
    }
    glutPostRedisplay();
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Exp-2: Event Handling");

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
