#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define ESC 27
#define SPACE 32

int i=1,j=1;
int numberOfClicks = 0;
int numberOfClicksR = 0;
int x0, y, xx, yy;
double p[4],q[4];
int xmin = 0, ymin = 0, xmax = 0, ymax = 0;
char buffer[100];
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
void Sprint1( int x, int y, char *st)
{
    int l,ii;
    l=strlen(st);
    glColor3f(0, 0, 0);
    glRasterPos2i( x, y);
    for( ii=0; ii<l; ii++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, st[ii]);
    }
}
void printCordinates(float X, float Y)
{
    gcvt(X,4,buffer);
    char str[20]={"( "};
    strcat(str, buffer);
    strcat(str, ", ");
    gcvt(Y,5,buffer);
    strcat(str, buffer);
    strcat(str, " )");
    Sprint1(X, Y, str);
}

void points(int a, int b){
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(a,b);
    glEnd();
}

void line(int p, int q, int r, int s){
    glPointSize(5);
    glBegin(GL_LINES);
    glVertex2f(p,q);
    glVertex2f(r,s);
    glEnd();
}
void createRectangle(){
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}
void liangBarsky(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1,i, xx1,xx2,yy1,yy2;
    float t1,t2,p[4],q[4],temp;
    p[0]=-dx;
    q[0]=x1-xmin;
    p[1]=dx;
    q[1]=xmax-x1;
    p[2]=-dy;
    q[2]=y1-ymin;
    p[3]=dy;
    q[3]=ymax-y1;
    glColor3f(0,0,1);
    for(i=0;i<4;i++)
    {
        if(p[i]==0)
        {
            printf("line is parallel");
            if(q[i]>=0)
            {
                if(i<2)
                {
                    if(y1<ymin)
                    {
                        y1=ymin;
                    }
                    
                    if(y2>ymax)
                    {
                        y2=ymax;
                    }
                    
                    line(x1,y1,x2,y2);
                }
                
                if(i>1)
                {
                    if(x1<xmin)
                    {
                        x1=xmin;
                    }
                    
                    if(x2>xmax)
                    {
                        x2=xmax;
                    }
                    
                    line(x1,y1,x2,y2);
                }
            }
        }
    }
    
    t1=0;
    t2=1;
    
    for(i=0;i<4;i++)
    {
        temp=q[i]/p[i];
        
        if(p[i]<0)
        {
            if(t1<=temp)
                t1=temp;
        }
        else
        {
            if(t2>temp)
                t2=temp;
        }
    }
    
    if(t1<t2)
    {
        xx1 = x1 + t1 * p[1];
        xx2 = x1 + t2 * p[1];
        yy1 = y1 + t1 * p[3];
        yy2 = y1 + t2 * p[3];
        line(xx1,yy1,xx2,yy2);
        printCordinates(xx1, yy1-10);
        printCordinates(xx2, yy2-10);
    }
}

void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        numberOfClicks++;
        if(numberOfClicks%2==1){
            x0 = mousex;
            y = 480-mousey;
            points(x0, y);
        }
        if(numberOfClicks%2==0){
            xx = mousex;
            yy = 480-mousey;
            points(xx, yy);
            //for debugging purposes
            printf("x0=%d \n",x0);
            printf("y0=%d \n",y);
            printf("x1=%d \n",xx);
            printf("y1=%d \n",yy);
            glColor3f(1,0,0);
            line(x0, y, xx, yy);
            liangBarsky(x0, y, xx, yy);
        }
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
        if(numberOfClicksR==0){
            glColor3f(0,0,0);
            xmin =100;
            xmax = 300;
            ymin = 100;
            ymax = 300;
            createRectangle();
            
        }
        if(numberOfClicksR!=0){
            glClear(GL_COLOR_BUFFER_BIT);
            xmin += 20;
//            ymin+=50;
            xmax+=20;
//            ymax+=50;
            createRectangle();
            
        }
        numberOfClicksR++;
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
    if(key==ESC){
        exit(0);
    }
    if(key==SPACE){
        glClear(GL_COLOR_BUFFER_BIT);
        ymin+=20;
        ymax+=20;
        createRectangle();
    }
    glutPostRedisplay();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Viva: Clipping Algorithm");
    
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}
