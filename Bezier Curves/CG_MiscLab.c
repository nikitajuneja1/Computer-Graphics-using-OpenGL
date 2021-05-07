#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ESC 27
#define SPACE 32

int looptime = 60;
GLfloat xa = 10, ra = 50;
float maxwidth = 750, maxheight = 750;

int yFlag = 1, xFlag = 1,AniFlag=0, rFlag = 0;


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

void Animate()
{
    if(AniFlag == 1)
    {
        if(ra>-10 && rFlag == 1)
            ra = ra - 0.2;

        if(ra<=-10 && rFlag == 1)
            rFlag = 0;

        if(ra<10 && rFlag == 0)
            ra = ra + 0.2;

        if(ra>=10 && rFlag == 0)
            rFlag = 1;


        if(xa>-10 && xFlag == 1)
            xa = xa - 0.2;

        if(xa<=-10 && xFlag == 1)
            xFlag = 0;

        if(xa<10 && xFlag == 0)
            xa = xa + 0.2;

        if(xa>=10 && xFlag == 0)
            xFlag = 1;

    }
    glutPostRedisplay();
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

void Draw()
{
    GLfloat x[4],y1[4],x2[4],y2[4],x3[4], y3[4], x4[4], y4[4], x5[4], y5[4], x6[4], y6[4], x7[4], y7[4], x8[4], y8[4], x9[4], y9[4], x10[4], y10[4], x11[4], y11[4], x12[4], y12[4], x13[4], y13[4], x14[4], y14[4],t;
    GLdouble xt[200],y1t[200],x2t[200], y2t[200], y3t[200], x3t[200], x4t[200], y4t[200], x5t[400], y5t[400], x6t[400], y6t[400], x7t[400], y7t[400], x8t[400], y8t[400], x9t[400], y9t[400], x10t[400], y10t[400], x11t[400], y11t[400], x12t[400], y12t[400], x13t[400], y13t[400], x14t[400], y14t[400] ;
    int i,c;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 0);
    DrawCircle(550, 620+ra, 50.0, 300);
    glColor3f(0,0,0);
    DrawCircle(235+xa, 575, 5, 300);
    DrawCircle(395+xa, 275, 5, 300);
    glColor3f(1, 1, 1);
    DrawCircle(350+70, 500+70, 35.0, 300);
    DrawCircle(400+70, 500+70, 35.0, 300);
    DrawCircle(450+70, 500+70, 35.0, 300);
    DrawCircle(375+70, 475+70, 35.0, 300);
    DrawCircle(425+70, 475+70, 35.0, 300);
    DrawCircle(425+70, 525+70, 35.0, 300);
    DrawCircle(375+70, 525+70, 35.0, 300);

    DrawCircle(350+240, 500+70, 35.0, 300);
    DrawCircle(400+240, 500+70, 35.0, 300);
    DrawCircle(450+240, 500+70, 35.0, 300);
    DrawCircle(375+240, 475+70, 35.0, 300);
    DrawCircle(425+240, 475+70, 35.0, 300);
    DrawCircle(425+240, 525+70, 35.0, 300);
    DrawCircle(375+240, 525+70, 35.0, 300);

    x[0] = 150+xa; x[1] = 165; x[2] = 185;  x[3] = 200+xa;
    y1[0] = 600; y1[1] = 550; y1[2] = 550;  y1[3] = 550;

    x2[0] = 200+xa; x2[1] = 205; x2[2] = 235;  x2[3] = 250+xa;
    y2[0] = 550; y2[1] = 600; y2[2] = 600;  y2[3] = 575;

    x3[0] = 250+xa; x3[1] = 220; x3[2] = 170;  x3[3] = 120+xa;
    y3[0] = 570; y3[1] = 440; y3[2] = 450;  y3[3] = 470;

    x4[0] = 150+xa; x4[1] = 140; x4[2] = 150;  x4[3] = 160+xa;
    y4[0] = 600; y4[1] = 570; y4[2] = 550;  y4[3] = 540;

    x5[0] = 160+xa; x5[1] = 160; x5[2] = 140;  x5[3] = 135+xa;
    y5[0] = 540; y5[1] = 540; y5[2] = 540;  y5[3] = 570;

    x6[0] = 135+xa; x6[1] = 120; x6[2] = 150;  x6[3] = 165+xa;
    y6[0] = 570; y6[1] = 530; y6[2] = 510;  y6[3] = 510;

    x7[0] = 165+xa; x7[1] = 155; x7[2] = 140;  x7[3] = 120+xa;
    y7[0] = 510; y7[1] = 480; y7[2] = 470;  y7[3] = 470;

    x8[0] = 310+xa; x8[1] = 325; x8[2] = 345;  x8[3] = 360+xa;
    y8[0] = 300; y8[1] = 250; y8[2] = 250;  y8[3] = 250;

    x9[0] = 360+xa; x9[1] = 365; x9[2] = 395;  x9[3] = 410+xa;
    y9[0] = 250; y9[1] = 300; y9[2] = 300;  y9[3] = 275;

    x10[0] = 410+xa; x10[1] = 380; x10[2] = 330;  x10[3] = 280+xa;
    y10[0] = 270; y10[1] = 140; y10[2] = 150;  y10[3] = 170;

    x11[0] = 310+xa; x11[1] = 300; x11[2] = 310;  x11[3] = 320+xa;
    y11[0] = 300; y11[1] = 270; y11[2] = 250;  y11[3] = 240;

    x12[0] = 320+xa; x12[1] = 320; x12[2] = 300;  x12[3] = 295+xa;
    y12[0] = 240; y12[1] = 240; y12[2] = 240;  y12[3] = 270;

    x13[0] = 295+xa; x13[1] = 280; x13[2] = 310;  x13[3] = 325+xa;
    y13[0] = 270; y13[1] = 230; y13[2] = 210;  y13[3] = 210;

    x14[0] = 325+xa; x14[1] = 315; x14[2] = 300;  x14[3] = 280+xa;
    y14[0] = 210; y14[1] = 180; y14[2] = 170;  y14[3] = 170;


    for(i=0,t=0,c=0;t<1;i++,t=t+0.01)
    {
        xt[i] = pow(1-t,3)*x[0]+3*t*pow(1-t,2)*x[1]+3*pow(t,2)*(1-t)*x[2]+pow(t,3)*x[3];
        y1t[i] = pow(1-t,3)*y1[0]+3*t*pow(1-t,2)*y1[1]+3*pow(t,2)*(1-t)*y1[2]+pow(t,3)*y1[3];
        y2t[i] = pow(1-t,3)*y2[0]+3*t*pow(1-t,2)*y2[1]+3*pow(t,2)*(1-t)*y2[2]+pow(t,3)*y2[3];
        x2t[i] = pow(1-t,3)*x2[0]+3*t*pow(1-t,2)*x2[1]+3*pow(t,2)*(1-t)*x2[2]+pow(t,3)*x2[3];
        y3t[i] = pow(1-t,3)*y3[0]+3*t*pow(1-t,2)*y3[1]+3*pow(t,2)*(1-t)*y3[2]+pow(t,3)*y3[3];
        x3t[i] = pow(1-t,3)*x3[0]+3*t*pow(1-t,2)*x3[1]+3*pow(t,2)*(1-t)*x3[2]+pow(t,3)*x3[3];
        y4t[i] = pow(1-t,3)*y4[0]+3*t*pow(1-t,2)*y4[1]+3*pow(t,2)*(1-t)*y4[2]+pow(t,3)*y4[3];
        x4t[i] = pow(1-t,3)*x4[0]+3*t*pow(1-t,2)*x4[1]+3*pow(t,2)*(1-t)*x4[2]+pow(t,3)*x4[3];
        x5t[i] = pow(1-t,3)*x5[0]+3*t*pow(1-t,2)*x5[1]+3*pow(t,2)*(1-t)*x5[2]+pow(t,3)*x5[3];
        y5t[i] = pow(1-t,3)*y5[0]+3*t*pow(1-t,2)*y5[1]+3*pow(t,2)*(1-t)*y5[2]+pow(t,3)*y5[3];
        x6t[i] = pow(1-t,3)*x6[0]+3*t*pow(1-t,2)*x6[1]+3*pow(t,2)*(1-t)*x6[2]+pow(t,3)*x6[3];
        y6t[i] = pow(1-t,3)*y6[0]+3*t*pow(1-t,2)*y6[1]+3*pow(t,2)*(1-t)*y6[2]+pow(t,3)*y6[3];
        x7t[i] = pow(1-t,3)*x7[0]+3*t*pow(1-t,2)*x7[1]+3*pow(t,2)*(1-t)*x7[2]+pow(t,3)*x7[3];
        y7t[i] = pow(1-t,3)*y7[0]+3*t*pow(1-t,2)*y7[1]+3*pow(t,2)*(1-t)*y7[2]+pow(t,3)*y7[3];
        x8t[i] = pow(1-t,3)*x8[0]+3*t*pow(1-t,2)*x8[1]+3*pow(t,2)*(1-t)*x8[2]+pow(t,3)*x8[3];
        y8t[i] = pow(1-t,3)*y8[0]+3*t*pow(1-t,2)*y8[1]+3*pow(t,2)*(1-t)*y8[2]+pow(t,3)*y8[3];
        x9t[i] = pow(1-t,3)*x9[0]+3*t*pow(1-t,2)*x9[1]+3*pow(t,2)*(1-t)*x9[2]+pow(t,3)*x9[3];
        y9t[i] = pow(1-t,3)*y9[0]+3*t*pow(1-t,2)*y9[1]+3*pow(t,2)*(1-t)*y9[2]+pow(t,3)*y9[3];
        x10t[i] = pow(1-t,3)*x10[0]+3*t*pow(1-t,2)*x10[1]+3*pow(t,2)*(1-t)*x10[2]+pow(t,3)*x10[3];
        y10t[i] = pow(1-t,3)*y10[0]+3*t*pow(1-t,2)*y10[1]+3*pow(t,2)*(1-t)*y10[2]+pow(t,3)*y10[3];
        x11t[i] = pow(1-t,3)*x11[0]+3*t*pow(1-t,2)*x11[1]+3*pow(t,2)*(1-t)*x11[2]+pow(t,3)*x11[3];
        y11t[i] = pow(1-t,3)*y11[0]+3*t*pow(1-t,2)*y11[1]+3*pow(t,2)*(1-t)*y11[2]+pow(t,3)*y11[3];
        x12t[i] = pow(1-t,3)*x12[0]+3*t*pow(1-t,2)*x12[1]+3*pow(t,2)*(1-t)*x12[2]+pow(t,3)*x12[3];
        y12t[i] = pow(1-t,3)*y12[0]+3*t*pow(1-t,2)*y12[1]+3*pow(t,2)*(1-t)*y12[2]+pow(t,3)*y12[3];
        x13t[i] = pow(1-t,3)*x13[0]+3*t*pow(1-t,2)*x13[1]+3*pow(t,2)*(1-t)*x13[2]+pow(t,3)*x13[3];
        y13t[i] = pow(1-t,3)*y13[0]+3*t*pow(1-t,2)*y13[1]+3*pow(t,2)*(1-t)*y13[2]+pow(t,3)*y13[3];
        x14t[i] = pow(1-t,3)*x14[0]+3*t*pow(1-t,2)*x14[1]+3*pow(t,2)*(1-t)*x14[2]+pow(t,3)*x14[3];
        y14t[i] = pow(1-t,3)*y14[0]+3*t*pow(1-t,2)*y14[1]+3*pow(t,2)*(1-t)*y14[2]+pow(t,3)*y14[3];

        c++;
    }

    glColor3f(0,0,0);
    glPointSize(4);
    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(xt[i],y1t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x2t[i],y2t[i]);
    }
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(410+xa, 275);
    glVertex2f(435+xa, 285);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(435+xa, 285);
    glVertex2f(422.5+xa, 275);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(422.5+xa, 275);
    glVertex2f(435+xa, 265);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(435+xa, 265);
    glVertex2f(410+xa, 270);
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x3t[i],y3t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x4t[i],y4t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x5t[i],y5t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x6t[i],y6t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x7t[i],y7t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x8t[i],y8t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x9t[i],y9t[i]);
    }
    glEnd();

    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(250+xa, 575);
    glVertex2f(275+xa, 585);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(275+xa, 585);
    glVertex2f(262.5+xa, 575);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(262.5+xa, 575);
    glVertex2f(275+xa, 565);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(275+xa, 565);
    glVertex2f(250+xa, 570);
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x10t[i],y10t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x11t[i],y11t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x12t[i],y12t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x13t[i],y13t[i]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for(i=0;i<100;i++)
    {
        glVertex2i(x14t[i],y14t[i]);
    }
    glEnd();
    Sprint(10, 10, "Nikita Juneja R110218098");
    glFlush();
}


void mouse(int button, int state, int x, int y)
{
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
//    {
//        AniFlag = 1;
//    }
//    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//    {
//        AniFlag = 0;
//    }
//    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{

    if (key == ESC)
    {
        exit(0);
    }
}
void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,750,0,750);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.529, 0.808, 0.98, 0);

}
void reshape(int w, int h)
{
        glViewport(0,0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if(w<=h)
            gluOrtho2D(0, maxwidth, 0, maxheight*(float)h/(float)w);
        else
            gluOrtho2D(0, maxwidth*(float)w/(float)h, 0, maxheight);
        glMatrixMode(GL_MODELVIEW);
}
void special(int key, int x, int y){
    if(key == GLUT_KEY_LEFT)
        AniFlag = 1;
    if(key == GLUT_KEY_RIGHT)
        AniFlag = 0;
    glutPostRedisplay();
}

int main(int argC,char *argV[])
{
    glutInit(&argC,argV);
    glutInitWindowSize(maxwidth,maxheight);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("LAB 10: Bezier Curve");
    MyInit();
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutReshapeFunc(reshape);
    glutIdleFunc(Animate);
    glutSpecialFunc(special);


    glutMainLoop();
    return 0;
}


