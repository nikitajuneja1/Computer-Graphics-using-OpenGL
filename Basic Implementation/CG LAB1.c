#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>


void init()
{
    glClearColor(0.529, 0.808, 0.98, 0.0);
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

void home()
{
    
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.8, 0.8, 0);
    DrawCircle(150, 500, 50.0, 300);
    
    
//  cloud
    glColor3f(1.29, 1.65, 1.86);
    DrawCircle(350, 500, 35.0, 300);
    DrawCircle(400, 500, 35.0, 300);
    DrawCircle(450, 500, 35.0, 300);
    DrawCircle(375, 475, 35.0, 300);
    DrawCircle(425, 475, 35.0, 300);
    DrawCircle(425, 525, 35.0, 300);
    DrawCircle(375, 525, 35.0, 300);
    
    DrawCircle(650, 500, 35.0, 300);
    DrawCircle(700, 500, 35.0, 300);
    DrawCircle(750, 500, 35.0, 300);
    DrawCircle(675, 475, 35.0, 300);
    DrawCircle(725, 475, 35.0, 300);
    DrawCircle(725, 525, 35.0, 300);
    DrawCircle(675, 525, 35.0, 300);
    
//  roof
    glColor4f(0.6, 0, 0, 0.8);
    glBegin(GL_POLYGON);
    glVertex2i(300, 400);
    glVertex2i(600, 400);
    glVertex2i(700, 250);
    glVertex2i(400, 250);
    glEnd();
    
//  Top of Front Wall
    glColor3f(0.8, 0.8, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(300, 400);
    glVertex2i(200, 250);
    glVertex2i(400, 250);
    glEnd();
    
//   Front Wall
    glColor3f(0.8, 0.8, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(200, 250);
    glVertex2i(400, 250);
    glVertex2i(400, 100);
    glVertex2i(200, 100);
    glEnd();
    
//  Line between front wall and top of front wall
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(200,250);
    glVertex2i(400,250);
    glEnd();
    
//  Side Wall
    glColor3f(0.71, 0.396, 0.114);
    glBegin(GL_POLYGON);
    glVertex2i(400, 100);
    glVertex2i(700, 100);
    glVertex2i(700, 250);
    glVertex2i(400, 250);
    glEnd();
    

    glColor3f(0.39, 0.26, 0.129);
    glBegin(GL_POLYGON);
    glVertex2i(250, 100);
    glVertex2i(350, 100);
    glVertex2i(350, 180);
    glVertex2i(250, 180);
    glEnd();
// Front Door Lock
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(15);
    glBegin(GL_POINTS);
    glVertex2i(340, 125);
    glEnd();

// window
    glColor3f(0.39, 0.26, 0.129);
    glBegin(GL_POLYGON);
    glVertex2i(500, 125);
    glVertex2i(620, 125);
    glVertex2i(620, 200);
    glVertex2i(500, 200);
    glEnd();
    
// lines of window
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2i(540, 125);
    glVertex2i(540, 200);
    glVertex2i(580, 125);
    glVertex2i(580, 200);
    glEnd();
    
// grass
    glColor3f(0.0, 0.8, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(1000, 0);
    glVertex2i(1000, 100);
    glVertex2i(0, 100);
    glEnd();

//  tree
    glColor3f(0.39, 0.26, 0.129);
    glBegin(GL_POLYGON);
    glVertex2i(100, 100);
    glVertex2i(120, 100);
    glVertex2i(120, 210);
    glVertex2i(100, 210);
    glEnd();
    
    glColor3f(0.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(50,200);
    glVertex2i(170,200);
    glVertex2i(110,300);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(50,250);
    glVertex2i(170,250);
    glVertex2i(110,350);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(50,300);
    glVertex2i(170,300);
    glVertex2i(110,400);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(50,350);
    glVertex2i(170,350);
    glVertex2i(110,425);
    glEnd();
    
    Sprint( 10, 10, "Nikita Juneja R110218098");
    glFlush();
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Exp No. 1: Scenery with Hut");
    init();
    glutDisplayFunc(home);
    glutMainLoop();
}
