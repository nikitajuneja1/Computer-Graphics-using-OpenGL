#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include<math.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ESC 27
#define SPACE 32

char buffer[100];

int n = 2;
float R = 100, r = 37.5, S=0;
float m=4, d = 40;
float angleX = 0, angleY = 0;
int mainWindow, subWindow1, subWindow2;
void Sprint(float x, float y, char *str) {
    glRasterPos2f(x, y);
    
    for (char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}


float arr[4][4];
void squares(float a, float b, float x, int id)
{
    int i;
    glColor3f(0.894, 0.729, 0.831);
    arr[0][0] = a-x, arr[0][1] = b;
    arr[1][0] = a, arr[1][1] = b;
    arr[2][0] = a, arr[2][1] = b+x;
    arr[3][0] = a-x, arr[3][1] = b+x;

    if(id==0){
        glColor3f(0.965,0.875, 0.92);
        arr[0][0] = a+x, arr[0][1] = b;
        arr[1][0] = a, arr[1][1] = b;
        arr[2][0] = a, arr[2][1] = b+x;
        arr[3][0] = a+x, arr[3][1] = b+x;
    }
    if(id==1){
        glColor3f(0.929,1,0.925);
        arr[0][0] = a-x, arr[0][1] = b;
        arr[1][0] = a, arr[1][1] = b;
        arr[2][0] = a, arr[2][1] = b-x;
        arr[3][0] = a-x, arr[3][1] = b-x;
    }
    if(id==2){
        glColor3f(0.792,0.969,0.89);
        arr[0][0] = a+x, arr[0][1] = b;
        arr[1][0] = a, arr[1][1] = b;
        arr[2][0] = a, arr[2][1] = b-x;
        arr[3][0] = a+x, arr[3][1] = b-x;
    }
    glBegin(GL_POLYGON);
    for (i = 0; i < 4; i++){
        glVertex2f(arr[i][0], arr[i][1]);
    }
    glEnd();
    
}

int AniFlag=0, rFlag = 0, SFlag = 0;
float ax, ay, bx, by, cx, cy;

void Animate()
{
    if(AniFlag == 1)
    {
        
        if(R>-50 && rFlag == 1)
            R = R - 0.5;
        
        if(R<=-50 && rFlag == 1)
            rFlag = 0;
        
        if(R<50 && rFlag == 0)
            R = R + 0.5;
        
        if(R>=50 && rFlag == 0)
            rFlag = 1;
        
    }
    if(S<=3600 && SFlag ==1 )
        S+=30;
    glutPostRedisplay();
}

void draw(){
    glPointSize(4);
    glBegin(GL_POINTS);

    for(int i=0; i<1440; i++){
    ax = (133)*cos(i);
    ay = (133)*sin(i);
    glColor3f(0.29,0.565, 0.216);
    glVertex2f(ax, ay);
    }
    for(int i=0; i<S; i++){
        
    bx = (R+100/n)*cos(i)-d*cos(m*i);
    by = (R+100/n)*sin(i)-d*sin(m*i);
    cx = (R-100/n)*cos(i) + d*cos(m*i);
    cy = (R-100/n)*sin(i) - d*sin(m*i);
    glColor3f(0.216, 0.565, 0.494);
    glVertex2f(bx, by);
    glColor3f(0.56, 0.22, 0.46);
    glVertex2f(cx, cy);
    }
glEnd();

}

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * (ii) / (num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(-400.0, 400.0, -400.0, 400);
    glColor3f(0.816, 0.918, 0.784);
    DrawCircle(0, 0, 130, 300);
    draw();
    
    
    glFlush();
    
}
void display1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//multiply the current matrix by identity matrix
    //    gluOrtho2D(-400.0, 400.0, -400.0, 400);
    glColor3f(0.816, 0.918, 0.784);
    DrawCircle(0, 0, 130, 300);
    draw();
    glColor3f(0, 0, 0);
    Sprint(10, -380, "Nikita Juneja R110218098");
    Sprint(-180, 350, "Epitrochoids and Hypotrochoids");
    glFlush();
    
}
void drawLine(float x1, float ya1, float x2, float ya2, float R, float G, float B)
{
    glLineWidth(2);
    glColor3f(R, G, B);
    glBegin(GL_LINES);
    glVertex2f(x1, ya1);
    glVertex2f(x2, ya2);
    glEnd();
    glFlush();
}
void drawCoordinates(){
    drawLine(-400,0, 400, 0, 1, 1, 1);
    drawLine(0,-400, 0, 400, 1, 1, 1);
}
void display2(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//multiply the current matrix by identity matrix
    drawCoordinates();
    glColor3f(1, 1, 1);
    Sprint(-180, 350, "Basic Resursive Fractal using Reflection");
    Sprint(10, -380, "Nikita Juneja R110218098");
    squares(0,0,100,4);
    squares(-100, 100, 50,4);
    squares(-150, 150, 25,4);
    squares(-175, 175, 12.5,4);
    squares(-187.5, 187.5, 6.25,4);
    squares(-193.75, 193.75, 3.125,4);
    glFlush();
    
}
void keyboard(unsigned char key, int mousex, int mousey){
    if(key==ESC){
        exit(0);
    }
    if(key==SPACE){
        AniFlag = 0;
        
    }
    glutPostRedisplay();
}

void Menu(int id){
    if(id==0){
        SFlag = 1;
    }
    
    if(id==1){
        AniFlag = 1;
    }
    if(id==2){
        AniFlag = 0;
    }
    if(id==3){
        m++;
    }
    if(id==4){
        m--;
    }
    glutPostRedisplay();
}
void Menu2(int id){
    
    if(id==0){
        squares(0,0,100,0);
        squares(100, 100, 50, 0);
        squares(150, 150, 25, 0);
        squares(175, 175, 12.5, 0);
        squares(187.5, 187.5, 6.25, 0);
        squares(193.75, 193.75, 3.125, 0);
    }
    if(id==1){
        squares(0,0,100,1);
        squares(-100, -100, 50,1);
        squares(-150, -150, 25,1);
        squares(-175, -175, 12.5,1);
        squares(-187.5, -187.5, 6.25,1);
        squares(-193.75, -193.75, 3.125,1);
    }
    if(id==2){
        squares(0,0,100,2);
        squares(100, -100, 50,2);
        squares(150, -150, 25,2);
        squares(175, -175, 12.5,2);
        squares(187.5, -187.5, 6.25,2);
        squares(193.75, -193.75, 3.125,2);
    }
     glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(1500, 1500);
    mainWindow = glutCreateWindow("Nikita Juneja - Fractals");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    subWindow1 = glutCreateSubWindow(mainWindow, 0, 0, 750, 750);
    gluOrtho2D(-400.0, 400.0, -400.0, 400);
    glutDisplayFunc(display1);
    glutIdleFunc(Animate);
    int id=glutCreateMenu(Menu);
    glutAddMenuEntry("Draw Fractal",0);
    glutAddMenuEntry("Start animation",1);
    glutAddMenuEntry("Stop animation",2);
    glutAddMenuEntry("Increment",3);
    glutAddMenuEntry("Decrement", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
//    glutMouseFunc(mouse);
    
    subWindow2 = glutCreateSubWindow(mainWindow, 750 , 0, 750, 750);
    gluOrtho2D(-400.0, 400.0, -400.0, 400);
    glutDisplayFunc(display2);

    int id2=glutCreateMenu(Menu2);
    glutAddMenuEntry("1st Quadrant",0);
    glutAddMenuEntry("3rd Quadrant",1);
    glutAddMenuEntry("4th Quadrant",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
