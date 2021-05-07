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

#define PI 3.14159265358
#define DRAWPOLYGON 0
#define TRANSLATE 1
#define ROTATE 2
#define SCALE 3
#define REFLECT 4
#define SHEARING 5
char buffer[100];
int tran_x,tran_y;
int tran_z = 0;
int _xtmp,_ytmp;
int mode=DRAWPOLYGON;
int subMenu1, subMenu2, subMenu3, subMenu4, subMenu5;

int scaleChoice, rotationChoice, translationChoice, shearingChoice, reflectionChoice;
typedef GLfloat Matrix4x4[4][4];
Matrix4x4 theMatrix;
float ptsFin[8][3];
float cx=0, cy=0, cz=0;
int arbx = 0, arby = 0, arbz = 0;
void DrawPolygon();

void SetIdentity(Matrix4x4 m){
    int i, j;
    for (i=0; i<4; i++)
        for (j=0; j<4; j++)
            m[i][j] = (i == j);
}

void init(){
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glOrtho(-454.0, 454.0, -300.0, 300.0, -400.0, 400.0);
    glEnable(GL_DEPTH_TEST);
    gluLookAt(2, 3, 4, 0, 0, 0, 0, 100, 0);
    SetIdentity(theMatrix);
}

void MultiplyMat(Matrix4x4 a , Matrix4x4 b)
{
    int i,j;
    Matrix4x4 tmp;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            tmp[i][j]=a[i][0]*b[0][j]+a[i][1]*b[1][j]+a[i][2]*b[2][j]+a[i][3]*b[3][j];
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            theMatrix[i][j] = tmp[i][j];
}


void Sprint1(float x, float y, float z, char *str) {
    glRasterPos2f(x, y);

    for (char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}
void printCordinates(float X, float Y, float Z)
{
    gcvt(X,4,buffer);
    char str[30]={"( "};
    strcat(str, buffer);
    strcat(str, ", ");
    gcvt(Y,5,buffer);
    strcat(str, buffer);
    strcat(str, ", ");
    gcvt(Z,6,buffer);
    strcat(str, buffer);
    strcat(str, " )");
    Sprint1(X, Y,Z,str);
}

void Sprint(float x, float y, float z, char *str) {
    glRasterPos3f(x, y, z);
    glColor3f(0,0,1);
    for (char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void translation(int tx, int ty, int tz)
{
    Matrix4x4 m;
    SetIdentity(m);
    m[0][3] = tx;
    m[1][3] = ty;
    m[2][3] = tz;
    MultiplyMat(m, theMatrix);
}

void rotationX(int x, int y, int z, float theta){
    float tx = cx, ty=cy, tz=cz;
    theta=theta/180*PI;
    Matrix4x4 matRot;
    SetIdentity(matRot);

    matRot[1][1]=cos(theta);
    matRot[1][2]=sin(theta);
    matRot[1][3]=y*(1-cos(theta))-z*sin(theta);
    matRot[2][1]=-sin(theta);
    matRot[2][2]=cos(theta);
    matRot[2][3]=z*(1-cos(theta))+y*sin(theta);
    cy = ty*cos(theta)+tz*sin(theta)+ matRot[1][3];
    cz = -ty*sin(theta)+tz*cos(theta)+ matRot[2][3];

    MultiplyMat(matRot,theMatrix);
}

void rotationY(int x, int y, int z, float theta){
    float tx = cx, ty=cy, tz=cz;
    theta=theta/180*PI;
    Matrix4x4 matRot;
    SetIdentity(matRot);

    matRot[0][0]=cos(theta);
    matRot[0][2]=-sin(theta);
    matRot[0][3]=x*(1-cos(theta))+z*sin(theta);
    matRot[2][0]=sin(theta);
    matRot[2][2]=cos(theta);
    matRot[2][3]=z*(1-cos(theta))-x*sin(theta);
    cz = tx*sin(theta)+tz*cos(theta)+ matRot[2][3];
    cx = tx*cos(theta)-tz*sin(theta)+ matRot[0][3];

    MultiplyMat(matRot,theMatrix);
}

void rotationZ(int x, int y, int z, float theta){
    float tx = cx, ty=cy, tz=cz;
    theta=theta/180*PI;
    Matrix4x4 matRot;
    SetIdentity(matRot);

    matRot[0][0]=cos(theta);
    matRot[0][1]=sin(theta);
    matRot[0][3]=x*(1-cos(theta))-y*sin(theta);
    matRot[1][0]=-sin(theta);
    matRot[1][1]=cos(theta);
    matRot[1][3]=y*(1-cos(theta))+x*sin(theta);
    cx = tx*cos(theta)+ty*sin(theta)+ matRot[0][3];
    cy = -tx*sin(theta)+ty*cos(theta)+ matRot[1][3];

    MultiplyMat(matRot,theMatrix);
}

void scaling(GLfloat sx,GLfloat sy, GLfloat sz,int x,int y, int z)
{
    Matrix4x4 m;
    SetIdentity(m);
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    
    MultiplyMat(m , theMatrix);
}

void reflection(int x)
{
    if(x==120)
    {
        Matrix4x4 matrefl={{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,0,0,1}};
        MultiplyMat(matrefl,theMatrix);
    }
    if(x==121)
    {
        Matrix4x4 matrefl={{-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
        MultiplyMat(matrefl,theMatrix);
    }
    if(x==122)
    {
        Matrix4x4 matrefl={{1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,0,1}};
        MultiplyMat(matrefl,theMatrix);
    }
}

void Shearing(GLfloat sx,GLfloat sy, GLfloat sz)
{
    Matrix4x4 matShear ={{1,sy,sz,0},{sx,1,sz,0},{sx,sy,1,0},{0,0,0,1}};
    MultiplyMat(matShear,theMatrix);
}

void transformedPoints(){
    int i,k;
    float ptsIni[8][3];
    for(k=0 ; k<8 ; k++)
        for (i=0 ; i<3 ; i++)
            ptsIni[k][i]=ptsFin[k][i];
    for(k=0 ; k<8 ; k++)
        for (i=0 ; i<3 ; i++)
            ptsFin[k][i] = theMatrix[i][0]*ptsIni[k][0] + theMatrix[i][1]*ptsIni[k][1]
            + theMatrix[i][2]*ptsIni[k][2] + theMatrix[i][3];
    if(mode != ROTATE){
        for(i=0; i<3; i++)
        {
            if(i==0)
                cx = theMatrix[i][0]*cx + theMatrix[i][1]*cy + theMatrix[i][2]*cz + theMatrix[i][3];
            if(i==1)
                cy = theMatrix[i][0]*cx + theMatrix[i][1]*cy + theMatrix[i][2]*cz + theMatrix[i][3];
            if(i==2)
                cz = theMatrix[i][0]*cx + theMatrix[i][1]*cy + theMatrix[i][2]*cz + theMatrix[i][3];
        }
    }
    glutPostRedisplay();
    SetIdentity(theMatrix);
}

void DrawPolygon(float a[8][3])
{
    int i;
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(a[0][0],a[0][1],a[0][2]);
    glVertex3f(a[1][0],a[1][1],a[1][2]);
    glVertex3f(a[2][0],a[2][1],a[2][2]);
    glVertex3f(a[3][0],a[3][1],a[3][2]);
    glEnd();
    i=0;
    glColor3f (0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
    glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
    glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
    glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
    glEnd();
    glColor3f (0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(a[0][0],a[0][1],a[0][2]);
    glVertex3f(a[3][0],a[3][1],a[3][2]);
    glVertex3f(a[7][0],a[7][1],a[7][2]);
    glVertex3f(a[4][0],a[4][1],a[4][2]);
    glEnd();
    i=1;
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
    glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
    glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
    glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
    glEnd();
    i=2;
    glColor3f (0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3s(a[0+i][0],a[0+i][1],a[0+i][2]);
    glVertex3s(a[1+i][0],a[1+i][1],a[1+i][2]);
    glVertex3s(a[5+i][0],a[5+i][1],a[5+i][2]);
    glVertex3s(a[4+i][0],a[4+i][1],a[4+i][2]);
    glEnd();
    i=4;
    glColor3f (1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex3f(a[0+i][0],a[0+i][1],a[0+i][2]);
    glVertex3f(a[1+i][0],a[1+i][1],a[1+i][2]);
    glVertex3f(a[2+i][0],a[2+i][1],a[2+i][2]);
    glVertex3f(a[3+i][0],a[3+i][1],a[3+i][2]);
    glEnd();
    
}


void drawTetrahedron()
{
    float random[8][4]={{-30,0,30},{0,0,0},{30,0,30},{0,60,0},
        {-30,0,-30},{0,0,0},{30,0,-30},{0,60,0}};
    for(int i=0;i<8;i++)
        for(int j=0;j<4;j++)
            ptsFin[i][j]=random[i][j];
}

void erasePolygon()
{
    for(int i = 0; i<8; i++)
        for(int j = 0; j<3; j++)
            ptsFin[i][j] = 0;
}

int sub=10;

void keyboard(unsigned char key,int x,int y){}

void Display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(2);
    glColor3f (0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-454 ,0);
    glVertex2f( 454 ,0);
    glVertex2f(0 ,-300);
    glVertex2f(0 , 300);
    glVertex3f(0,0,-400);
    glVertex3f(0,0,400);
    glEnd();
    glColor3f(0,0,1);
    printCordinates(0, 0, 0);
    glColor3f(0,0,1);
    Sprint(-350,10,0,"X-axis");
    Sprint(340,0,0,"X-axis");
    Sprint(0,-250,0,"Y-axis");
    Sprint(0,250,0,"Y-axis");
    Sprint(10,0,-350,"Z-axis");
    Sprint(10,0,340,"Z-axis");
    glPointSize(10);

    DrawPolygon(ptsFin);
    
    glColor3f(0,0,0);
//    printCordinates(cx,cy, cz);
    Sprint1(360,-170, 0, "Nikita Juneja");
    Sprint1(370,-200, 0,"R110218098");
    Sprint1(-484,0,0,"(-400,0,0)");
    Sprint1(400,0,0,"(400,0,0)");
    Sprint1(0,300,0, "(0,300,0)");
    Sprint1(0,-300,0, "(0,-300,0)");
    Sprint1(200,300,400, "(0,0,400)");
    Sprint1(-200,-320,-400, "(0,0,-400)");
    glFlush();
}

void Menu(int id){
    if(id==0){
        drawTetrahedron();
//        DrawPolygon(ptsFin);
        mode=0;
    }
    
    glutPostRedisplay();
}
void subMenu1Handler(int choice){
    reflectionChoice = choice;
    mode = 4;
    
    glutPostRedisplay();
}
void subMenu2Handler(int choice){
    scaleChoice = choice;
    mode = 3;
    glutPostRedisplay();
}
void subMenu3Handler(int choice){
    rotationChoice = choice;
    mode=2;
    glutPostRedisplay();
}
void subMenu4Handler(int choice){
    translationChoice = choice;
    mode=1;
    glutPostRedisplay();
}
void subMenu5Handler(int choice){
    shearingChoice = choice;
    mode=5;
    glutPostRedisplay();
}

void mymouse(int button,int state,int x,int y, int z){
    int ssz = 1;
    float tx,ty,tz,theta;
    if (state == GLUT_UP){
        switch(mode)
        {
            case DRAWPOLYGON:

                if(button==GLUT_LEFT_BUTTON){
                    cx = 0, cy = 0, cz = 0;
                    printCordinates(x, y,z);
                    erasePolygon();
                }
                glutPostRedisplay();
                break;
                
            case TRANSLATE:
                if(translationChoice==1){
                    if(button==GLUT_MIDDLE_BUTTON){
                        translation(-sub,0,0);
                        transformedPoints();
                    }
                    if(button==GLUT_LEFT_BUTTON){
                        translation(sub,0,0);
                        transformedPoints();
                    }
                }
       
                if(translationChoice==2){
                    if(button==GLUT_MIDDLE_BUTTON){
                        translation(0,sub,0);
                        transformedPoints();
                    }
                    if(button==GLUT_LEFT_BUTTON){
                        translation(0,-sub,0);
                        transformedPoints();
                    }
                }
                if(translationChoice==3){
                    if(button==GLUT_MIDDLE_BUTTON){
                        translation(0,0,sub);
                        transformedPoints();
                    }
                    if(button==GLUT_LEFT_BUTTON){
                        translation(0,0,-sub);
                        transformedPoints();
                    }
                }
                glutPostRedisplay();
                break;

            case SCALE:
                if(button==GLUT_MIDDLE_BUTTON)
                {
                    scaling(0.5,0.5,0.5,arbx, arby, arbz);
                    transformedPoints();
                }
                if(button==GLUT_LEFT_BUTTON)
                {
                    scaling(1.5,1.5,1.5,arbx, arby, arbz);
                    transformedPoints();
                }

                glutPostRedisplay();
                break;
            case ROTATE:
                if(rotationChoice==1){
                    if(button==GLUT_LEFT_BUTTON)
                    rotationX(arbx, arby, arbz, 20);
                    
                    if(button==GLUT_MIDDLE_BUTTON)
                        rotationX(arbx, arby, arbz, -20);
                }
                if(rotationChoice==2){
                     if(button==GLUT_LEFT_BUTTON)
                     rotationY(arbx, arby, arbz, 20);
                    
                    if(button==GLUT_MIDDLE_BUTTON)
                        rotationY(arbx, arby, arbz, -20);
                }
                if(rotationChoice==3){
                    if(button==GLUT_LEFT_BUTTON)
                    rotationZ(arbx, arby, arbz, 20);
                    
                    if(button==GLUT_MIDDLE_BUTTON)
                        rotationZ(arbx, arby, arbz, -20);
                }
                
                transformedPoints();
                break;

            case REFLECT:
                if(reflectionChoice==1){
                    if(button==GLUT_LEFT_BUTTON)
                        reflection(120);
                }
                if(reflectionChoice==2){
                    if(button==GLUT_LEFT_BUTTON)
                        reflection(121);
                }
                if(reflectionChoice==3){
                    if(button==GLUT_LEFT_BUTTON)
                        reflection(122);
                }

                transformedPoints();
                break;

            case SHEARING:
                if(shearingChoice==1){
                    if(button==GLUT_MIDDLE_BUTTON)
                    {
                        float ssx = 0.1, ssy = 0, ssz = 0;
                        Shearing(ssx,ssy,ssz);
                    }
                    if(button==GLUT_LEFT_BUTTON)
                    {
                        float ssx = -0.1, ssy = 0, ssz=0;
                        Shearing(ssx,ssy,ssz);
                    }
                }
                if(shearingChoice==2){
                    if(button==GLUT_MIDDLE_BUTTON)
                    {
                        float ssx = 0, ssy = -0.1, ssz=0;
                        Shearing(ssx,ssy,ssz);
                    }
                    if(button==GLUT_LEFT_BUTTON)
                    {
                        float ssx = 0, ssy = 0.1, ssz=0;
                        Shearing(ssx,ssy,ssz);
                    }
                }
                if(shearingChoice==3){
                    if(button==GLUT_MIDDLE_BUTTON)
                    {
                        float ssx = 0, ssy = 0, ssz=0.1;
                        Shearing(ssx,ssy,ssz);
                    }
                    if(button==GLUT_LEFT_BUTTON)
                    {
                        float ssx = 0, ssy = 0, ssz=-0.1;
                        Shearing(ssx,ssy,ssz);
                    }
                }
                
                
                transformedPoints();
                break;
    }
    }
}
    

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1000, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Nikita Juneja: 3-D Transformations");
    init();
    
    subMenu1 = glutCreateMenu(subMenu1Handler);
    glutAddMenuEntry("Reflection about X axis", 1);
    glutAddMenuEntry("Reflection about Y axis", 2);
    glutAddMenuEntry("Reflection about Z axis", 3);
    subMenu2 = glutCreateMenu(subMenu2Handler);
    glutAddMenuEntry("Scale up", 1);
    glutAddMenuEntry("Scale down", 2);
    subMenu3 = glutCreateMenu(subMenu3Handler);
    glutAddMenuEntry("About X axis", 1);
    glutAddMenuEntry("About Y axis", 2);
    glutAddMenuEntry("About Z axis", 3);
    subMenu4 = glutCreateMenu(subMenu4Handler);
    glutAddMenuEntry("Translation in X Axis", 1);
    glutAddMenuEntry("Translation in Y Axis", 2);
    glutAddMenuEntry("Translation in Z Axis", 3);
    subMenu5 = glutCreateMenu(subMenu5Handler);
    glutAddMenuEntry("Shearing in X Axis", 1);
    glutAddMenuEntry("Shearing in Y Axis", 2);
    glutAddMenuEntry("Shearing in Z Axis", 3);

    int id=glutCreateMenu(Menu);
    glutAddMenuEntry("Draw Tetrahedron",0);
    glutAddSubMenu("Reflection", subMenu1);
    glutAddSubMenu("Scaling", subMenu2);
    glutAddSubMenu("Rotation", subMenu3);
    glutAddSubMenu("Translation", subMenu4);
    glutAddSubMenu("Shearing", subMenu5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMouseFunc(mymouse);
    glutDisplayFunc(Display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
