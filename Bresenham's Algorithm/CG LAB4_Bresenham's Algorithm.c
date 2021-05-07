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
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(a,b);
    glEnd();
}
void linepoints(int a, int b){
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex2f(a,b);
    glEnd();
}
void bresenhamAlgorithm(int x, int y, int xx, int yy){

    float dx, dy;
    dx = xx-x;
    dy = yy-y;
    slope = (float)dy/dx;
    //for debugging purposes
    printf("%f %f %f \n", dx, dy, slope);
    int P;
    P = 2*dy - dx;
    if(x>xx){
        // swapping the coordinates since they are drawn upside down
        x = x+xx;
        xx = x-xx;
        x = x-xx;
        
        y = y+yy;
        yy = y-yy;
        y = y-yy;
        
        dx = -dx;
        dy = -dy;
    }
    if(slope<=1 && slope>=0){
    while(x<=xx){
        x = x+1;
        if(P>0){
            y = y+1;
            linepoints(x,y);
            P = P + 2*dy - 2*dx;
        }
        else{
            linepoints(x,y);
            P = P + 2*dy;
        }
        }
    }
    else if(slope>1){
        dx = dx + dy;
        dy = dx - dy;
        dx = dx - dy;
        P = 2*dx - dy;
        while(y<=yy){
            if(P>0){
                x = x+1;
                y = y+1;
                linepoints(x,y);
                P = P + 2*dy - 2*dx;
            }
            else{
                x = x;
                y = y+1;
                linepoints(x,y);
                P = P + 2*dy;
            }
        }
    }
    else if(slope<0 && slope>-1){
        P = 2*dx - dy;
        while(x<=xx){
            if(P<0){
                x = x+1;
                y = y;
                linepoints(x,y);
                P = P-2*dy;
            }
            else{
                x = x+1;
                y = y-1;
                linepoints(x,y);
                P = P- 2*dy -2*dx;
            }
        }
    }
    else if(slope<-1){
        P = 2*dx+dy;
        while (x<=xx) {
            if(P>0){
                x = x+1;
                y = y-1;
                linepoints(x,y);
                P = P+ 2*dy +2*dx;
            }
            else{
                y = y-1;
                linepoints(x,y);
                P = P+2*dx;
            }
        }
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
            x1 = mousex;
            yy = 480-mousey;
            points(x1, yy);
            //for debugging purposes
            printf("x0=%d \n",x0);
            printf("y0=%d \n",y);
            printf("x1=%d \n",x1);
            printf("y1=%d \n",yy);
            glColor3f(1,0,0);
            bresenhamAlgorithm(x0, y, x1, yy);
        }
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
         printf("slope: %f \n", slope);
        if(slope<=1 && slope>=0){
            glColor3f(0, 1,0);
        }
        else if(slope>1){
            glColor3f(0, 0, 1);
        }
        else if(slope<0 && slope>-1){
            glColor3f(0.5, 0.5, 0);
        }
        else{
            glColor3f(2.5, 0.20, 1.47);
        }
        bresenhamAlgorithm(x0, y, x1, yy);
    }
    glutPostRedisplay();
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    Sprint(10, 10, "Nikita Juneja R110218098");
    Sprint(475, 400, "Slope= ");
    glColor3d(1,1,1);
    glBegin(GL_POLYGON);
    glVertex2i(540,400);
    glVertex2i(640,400);
    glVertex2i(640,460);
    glVertex2i(540,460);
    glEnd();
    glColor3d(0,0,0);
    char buf[100]={"\0"};
    sprintf(buf,"%f", slope);
    for( int j=0; j<strlen(buf); j++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buf[j]);
    }
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
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Exp-4: Bresenham's Algorithm");
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}