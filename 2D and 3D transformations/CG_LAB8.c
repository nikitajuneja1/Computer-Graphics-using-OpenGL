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
#define ox 400.0
#define oy 400.0

char buffer[100];

int subMenu, subMenu2, subMenu3, subMenu4, subMenu5, subMenu6;
int numberOfPoints;
int numberOfClicks;
int count = 0;
int choice2;
int scaleChoice, rotationChoice, translationChoice, shearingChoice;
float arr[20][2];
int mode = 0;

int gx1 = 0, gx2 = 0, gy1 = 0, gy2 = 0; // global variables to store the points
int lineCount = 0;

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
    glColor3f(0, 0, 1);
    glRasterPos2i( x, y);
    for( ii=0; ii<l; ii++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[ii]);
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
void points(int x, int y) // to draw a point
{
    glColor3f(0, 0, 0);
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
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
    drawLine(-400,0, 400, 0, 0, 0, 0);
    drawLine(0,-400, 0, 400, 0, 0, 0);
    printCordinates(0, 0);
}

void drawPolygon(float (*arr)[2], int n, float R, float G, float B)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 119, 182);
    glBegin(GL_POLYGON);
    int i;
    for (i = 0; i < n; i++){
        glVertex2f(arr[i][0], arr[i][1]);
    }
    glEnd();
    for(i=0; i<n; i++){
        printCordinates(arr[i][0], arr[i][1]);
    }
    // glFlush();
    Sprint1(175, -20, "X-axis");
    Sprint1(-70, 150, "Y-axis");
    Sprint1(-400, 10, "(-400,0)");
    Sprint1(330, 10, "(400,0)");
    Sprint1(0, 380, "(0,400)");
    Sprint1(0, -390, "(0,-400)");
    Sprint(390,-5,">");
    Sprint(-400,-5,"<");
    Sprint(-5,385,"^");
    Sprint(-6,-400,"v");
    drawCoordinates();
    Sprint(120, -385, "Nikita Juneja R110218098");
    glFlush();
}


void tranformation(float arr[][2], int n, float matrix[][3])
{
    int p, i, j, k;
    for (p = 0; p < n; p++)
    {
        float tar[][1] = {{0}, {0}, {0}};
        float ar[][1] = {{arr[p][0]}, {arr[p][1]}, {1}};
        for (i = 0; i < 3; i++)
        {
            for (k = 0; k < 1; k++)
            {
                for (j = 0; j < 3; j++)
                    tar[i][k] += matrix[i][j] * ar[j][k];
            }
        }
        arr[p][0] = tar[0][0];
        arr[p][1] = tar[1][0];
    }
    drawPolygon(arr, numberOfPoints, 1.0, 0.5, 0.5);
}
void mouse(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    GLint wh = 800;
    int x = xMouse - ox;
    int y = wh - yMouse - oy;
    int x0,y0;
    if (button == GLUT_LEFT_BUTTON && action == GLUT_UP && count != -1 && mode == 0)
    {
        count++;
        points(x, y);
        arr[count - 1][0] = x;
        arr[count - 1][1] = y;

    }
    else if (button == GLUT_LEFT_BUTTON && action == GLUT_UP && mode == 1)
    {
        numberOfClicks++;
        if (numberOfClicks%2==1)
        {
            gx1 = xMouse-ox;
            gy1 = wh - yMouse - oy;
            points(gx1, gy1);
            printf("%d %d \n", gx1,gy1);
            printCordinates(x, y);
            
        }
        else if(numberOfClicks%2==0)
        {
            gx2 = xMouse-ox;
            gy2 = wh - yMouse - oy;
            points(gx2, gy2);
            printf("%d %d \n", gx2,gy2);
            printCordinates(x, y);
            drawLine(gx1, gy1, gx2, gy2, 1, 0, 0);
            mode = 0;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && action == GLUT_UP && count != -1 && mode == 0)
    {
        count++;
        points(x, y);
        arr[count - 1][0] = x;
        arr[count - 1][1] = y;
        numberOfPoints = count;
        drawPolygon(arr, numberOfPoints, 1.0, 0.5, 0.5);
        count = -1;
        mode = 1;
    }
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//multiply the current matrix by identity matrix
    gluOrtho2D(-400.0, 400.0, -400.0, 400);
    glColor3f(0, 0, 0);
    Sprint(120, -385, "Nikita Juneja R110218098");
    printCordinates(0, 0);
    Sprint1(-400, 10, "(-400,0)");
    Sprint1(330, 10, "(400,0)");
    Sprint1(0, 380, "(0,400)");
    Sprint1(0, -390, "(0,-400)");
    Sprint1(175, -20, "X-axis");
    Sprint1(-70, 150, "Y-axis");
    Sprint(390,-5,">");
    Sprint(-400,-5,"<");
    Sprint(-5,385,"^");
    Sprint(-6,-400,"v");
    drawCoordinates();
    

}
void menuHandler(int choice)
{
    switch (choice)
    {
        default:
            printf("\nWrong Input");
    }
}
int shearing()
{
    float a, b;
    if (shearingChoice == 1)
    {
        a = 0, b = 1;
    }
    else if (shearingChoice == 2)
    {
        a = 1, b = 0;
    }
    float matrix[][3] = {{1, a, 0}, {b, 1, 0}, {0, 0, 1}};
    tranformation(arr, numberOfPoints, matrix);
}
int translation()
{
    float tx, ty;
    if (translationChoice == 1)
    {
        ty = 0;
        tx = 200;
    }
    else if (translationChoice == 2)
    {
        tx = 0;
        ty = 200;
    }
    float matrix[][3] = {{1, 0, tx}, {0, 1, ty}, {0, 0, 1}};
    tranformation(arr, numberOfPoints, matrix);
}
int rotation()
{
    double theta;
    if (rotationChoice == 1)
    {
        theta = -45;
    }
    else if (rotationChoice == 2)
    {
        theta = 45;
    }
    theta *= (3.1415926 / 180); //converting degree into radians
    float sine = sin(theta);
    float cosine = cos(theta);
    float matrix[][3] = {{cosine, -sine, 0}, {sine, cosine, 0}, {0, 0, 1}};
    tranformation(arr, numberOfPoints, matrix);
}
int scaling()
{
    float sx, sy;
    if (scaleChoice == 1)
        sx = sy = 1.5;
    else if (scaleChoice == 2)
        sx = sy = 0.5;
    float matrix[][3] = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};
    tranformation(arr, numberOfPoints, matrix);
}
int reflection()
{
    float x = 1, y = 1;
    if (choice2 == 1)
        y = -1;
    else if (choice2 == 2)
        x = -1;
    else
    {
        printf("\nWrong Input");
        return 0;
    }
    float matrix[][3] = {{x, 0, 0}, {0, y, 0}, {0, 0, 1}};
    tranformation(arr, numberOfPoints, matrix);
}
int arbitraryReflection(int choice)
{
    if (choice == 1)
    {
        mode = 1; //to draw line
    }
    else if (choice == 2)
    {
        mode = 0; //to draw polygon
        float m = (gy2 - gy1) / (gx2 - gx1);
        float c = gy1 - m * gx1;
        float a = (1+m*m),b = 1-m*m, d= 2*m;
        float matrix[][3] = {{b/a, d/a, -d*c/a}, {d/a, -b/a,  2*c/a}, {0, 0, 1}};
        drawLine(gx1,gy1,gx2,gy2,1,0,0);
        tranformation(arr, numberOfPoints, matrix);
    }
}
void subMenu1Handler(int choice)
{
    choice2 = choice;
    reflection();
}
void subMenu2Handler(int choice)
{
    scaleChoice = choice;
    scaling();
}
void subMenu3Handler(int choice)
{
    rotationChoice = choice;
    rotation();
}
void subMenu4Handler(int choice)
{
    translationChoice = choice;
    translation();
}
void subMenu5Handler(int choice)
{
    shearingChoice = choice;
    shearing();
}
void subMenu6Handler(int choice)
{
    arbitraryReflection(choice);
}
void Menu()
{
    glutCreateMenu(menuHandler);
    glutAddSubMenu("Reflection", subMenu);
    glutAddSubMenu("Rotation", subMenu3);
    glutAddSubMenu("Translation", subMenu4);
    glutAddSubMenu("Scaling", subMenu2);
    glutAddSubMenu("Shearing", subMenu5);
    glutAddSubMenu("Arbitrary Line", subMenu6);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}
void keyboard(unsigned char key, int mousex, int mousey){
    if(key==ESC){
        exit(0);
    }
    if(key==SPACE){
        glClear(GL_COLOR_BUFFER_BIT);

    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Nikita Juneja - Extended 2D Tranformations");

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    subMenu = glutCreateMenu(subMenu1Handler);
    glutAddMenuEntry("Reflection about X axis", 1);
    glutAddMenuEntry("Reflection about Y axis", 2);
    subMenu2 = glutCreateMenu(subMenu2Handler);
    glutAddMenuEntry("Scale up", 1);
    glutAddMenuEntry("Scale down", 2);
    subMenu3 = glutCreateMenu(subMenu3Handler);
    glutAddMenuEntry("Clockwise Direction", 1);
    glutAddMenuEntry("Anti - Clockwise Direction", 2);
    subMenu4 = glutCreateMenu(subMenu4Handler);
    glutAddMenuEntry("Translation in X Axis", 1);
    glutAddMenuEntry("Translation in Y Axis", 2);
    subMenu5 = glutCreateMenu(subMenu5Handler);
    glutAddMenuEntry("Shearing in X Axis", 1);
    glutAddMenuEntry("Shearing in Y Axis", 2);
    subMenu6 = glutCreateMenu(subMenu6Handler);
    glutAddMenuEntry("Draw line", 1);
    glutAddMenuEntry("Reflection about Arbitrary Line", 2);
    Menu();

    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
