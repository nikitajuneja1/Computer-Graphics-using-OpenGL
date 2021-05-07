#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ESC 27

int i=1,j=1;
int x0, y, x1, yy;
int a = 90;
int b = 75;
int numberOfCircles = 0, numberOfEllipses = 0;
int mainWindow, subWindow1, subWindow2;
char buffer[10];

void Sprint( int x, int y, char *st)
{
    int l,ii;
    l=strlen(st);
    glRasterPos2i( x, y);
    for( ii=0; ii<l; ii++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[ii]);
    }
}
void printCordinates(float X, float Y)
{
    gcvt(X,4,buffer); //function to convert float into string
    char str[20]={"( "};
    strcat(str, buffer); //function to concate string
    strcat(str, ", ");
    gcvt(Y,5,buffer);
    strcat(str, buffer);
    strcat(str, " )");
    Sprint(X, Y, str); // calling type function to display
}

void points(int c, int d){
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(c,d);
    glEnd();
}
void drawEllipse(int x0, int y0){
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);
    //initial distance parameter of region 1
    float p1 = b*b + (0.25*a*a) - a*a*b;
    float dx, dy;
    float x = 0;
    float y = b;
    dx = 2*b*b*x;
    dy = 2*a*a*y;
    
    // For region 1
    glBegin(GL_POINTS);
    while (dx < dy)
    {
        
        glVertex2i(x + x0, y + y0);
        glVertex2i(-x + x0, y + y0);
        glVertex2i(x + x0, -y + y0);
        glVertex2i(-x + x0, -y + y0);
        if (p1 < 0)
        {
            x++;
            dx = dx + (2 * b * b);
            p1 = p1 + dx + (b * b);
        }
        else
        {
            x++;
            y--;
            dx = dx + (2 * b * b);
            dy = dy - (2 * a * a);
            p1 = p1 + dx - dy + (b * b);
        }
    }
    glEnd();
    
    // Initial Decision parameter of region 2
    float p2 = ((b * b) * ((x + 0.5) * (x + 0.5))) + ((a * a) * ((y - 1) * (y - 1))) - (a * a * b * b);
    
    // For region 2
    glBegin(GL_POINTS);
    while (y >= 0)
    {
        
        glVertex2i(x + x0, y + y0);
        glVertex2i(-x + x0, y + y0);
        glVertex2i(x + x0, -y + y0);
        glVertex2i(-x + x0, -y + y0);
        
        if (p2 > 0)
        {
            y--;
            dy = dy - (2 * a * a);
            p2 = p2 + (a * a) - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + (2 * b * b);
            dy = dy - (2 * a * a);
            p2 = p2 + dx - dy + (a * a);
        }
    }
    glEnd();
    glFlush();
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
        x0 = mousex;
        y = 480-mousey;
        points(x0, y);
        if(numberOfCircles==0){
            circle(x0,y);
            glColor3f(0.0, 0.0, 0.0);
            printCordinates(x0-50, y-25);
            numberOfCircles++;
        }
        else{
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0, 1.0, 1.0, 1.0);
            numberOfCircles--;
        }
    }
    glutPostRedisplay();
}
void mouseClickSubW2(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        x0 = mousex;
        y = 480-mousey;
        points(x0, y);
        
        if(numberOfEllipses==0){
            drawEllipse(x0,y);
            glColor3f(1.0, 1.0, 1.0);
            printCordinates(x0-50, y-25);
            numberOfEllipses++;
        }
        else{
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 1.0);
            numberOfEllipses--;
        }
    }
    glutPostRedisplay();
}
void displaySub1()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0, 0, 0);
    Sprint(20, 440, "Nikita Juneja R110218098");
    Sprint(50, 20, "Circle Generation using Mid Point Algorithm");
    glFlush();
    glutPostRedisplay();
}

void displaySub2()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1, 1, 1);
    Sprint(20, 440, "Nikita Juneja R110218098");
    Sprint(150, 20, "Ellipse generation using Mid Point Algorithm");
    glFlush();
    glutPostRedisplay();
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
    glutInitWindowSize(1280,480);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    mainWindow = glutCreateWindow("Lab6: Circle and Ellipse Generation");
    glClearColor(1, 1, 1, 0);
    glutDisplayFunc(displayMain);
    glutKeyboardFunc(keyboard);
    
    subWindow1 = glutCreateSubWindow(mainWindow, 0, 0, 640, 480);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glutDisplayFunc(displaySub1);
    
    glutMouseFunc(mouseClickSubW1);
    
    subWindow2 = glutCreateSubWindow(mainWindow, 640 , 0, 640, 480);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glutDisplayFunc(displaySub2);
    
    
    glutMouseFunc(mouseClickSubW2);
    
    glutMainLoop();
}
