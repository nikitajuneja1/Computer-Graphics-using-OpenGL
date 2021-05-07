#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include<stdio.h>
#include <algorithm>
#include <functional>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define Size 800
using namespace std;
char buffer[100];

typedef float Color[3];
struct Point
{
	int x, y;
};
Point p1, p2, p3, p4;
Point p5, p6, p7, p8;

void Sprint( int x, int y, char *st)
{
    int l,ii;
    l=strlen(st);
    glColor3f(0, 0, 0);
    glRasterPos2i( x, y);
    for( ii=0; ii<l; ii++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[ii]);
    }
}
void printCordinates(float X, float Y)
{
    gcvt(X,3,buffer);
    char str[20]={"("};
    strcat(str, buffer);
    strcat(str, ",");
    gcvt(Y,3,buffer);
    strcat(str, buffer);
    strcat(str, ")");
    Sprint(X, Y, str);
}
typedef struct IntersectionPoint
{
	int pointFlag;
	int index0, index1;
	Point p;
	bool inFlag;
	int dis;
}IP;
void points(int a, int b)
{
glPointSize(5);
glColor3f(0,0,0);
glBegin(GL_POINTS);
glVertex2f(a,b);
glEnd();
}
class Pg
{
public:
	vector<Point> pts;
	Pg(void);
	~Pg(void);
	void drawPgLine(Color c);
};
Pg::Pg(void)
{
    cout<<"Constructor called\n";
}
Pg::~Pg(void)
{
    cout<<"Destructor called\n";
}
void Pg::drawPgLine(Color c)
{
	glColor3fv(c);
	glLineWidth(2.0);
	glBegin(GL_POLYGON);
	int size = pts.size();
	for (int i = 0; i < size; i++){
		glVertex2i(pts[i].x, pts[i].y);
		//printCordinates(pts[i].x, pts[i].y);
	}
	glEnd();

}

bool isPointInsidePg(Point p, Pg& py)
{
	int cnt = 0, size = py.pts.size();
	for (int i = 0; i < size; i++) {
		Point p1 = py.pts[i];
		Point p2 = py.pts[(i + 1) % size];
		if (p1.y == p2.y) continue;
		if (p.y < min(p1.y, p2.y)) continue;
		if (p.y >= max(p1.y, p2.y)) continue;
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		if (x > p.x) cnt++;
	}
	return (cnt % 2 == 1);
}
int cross(Point& p0, Point& p1, Point& p2)
{
	return ((p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y));
}
bool onSegment(Point& p0, Point& p1, Point& p2)
{
	int minx = min(p0.x, p1.x), maxx = max(p0.x, p1.x);
	int miny = min(p0.y, p1.y), maxy = max(p0.y, p1.y);
	if (p2.x >= minx && p2.x <= maxx && p2.y >= miny && p2.y <= maxy) return true;
	return false;
}
bool segmentsIntersect(Point& p1, Point& p2, Point& p3, Point& p4)
{
	int d1 = cross(p3, p4, p1);
	int d2 = cross(p3, p4, p2);
	int d3 = cross(p1, p2, p3);
	int d4 = cross(p1, p2, p4);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
		return true;
	if (d1 == 0 && onSegment(p3, p4, p1)) return true;
	if (d2 == 0 && onSegment(p3, p4, p2)) return true;
	if (d3 == 0 && onSegment(p1, p2, p3)) return true;
	if (d4 == 0 && onSegment(p1, p2, p4)) return true;
	return false;
}
Point getintersectPoint(Point p1, Point p2, Point p3, Point p4)
{
	Point p;
	int b1 = (p2.y - p1.y) * p1.x + (p1.x - p2.x) * p1.y;
	int b2 = (p4.y - p3.y) * p3.x + (p3.x - p4.x) * p3.y;
	int D = (p2.x - p1.x) * (p4.y - p3.y) - (p4.x - p3.x) * (p2.y - p1.y);
	int D1 = b2 * (p2.x - p1.x) - b1 * (p4.x - p3.x);
	int D2 = b2 * (p2.y - p1.y) - b1 * (p4.y - p3.y);
	p.x = D1 / D;
	p.y = D2 / D;
	return p;
}
void generateIntersectPoints(Pg& pyclip, Pg& py, list<IP>& iplist)
{
	int clipSize = pyclip.pts.size(), pySize = py.pts.size();

	for (int i = 0; i < clipSize; i++) {
		Point p1 = pyclip.pts[i];
		Point p2 = pyclip.pts[(i + 1) % clipSize];
		for (int j = 0; j < pySize; j++) {
			Point p3 = py.pts[j];
			Point p4 = py.pts[(j + 1) % pySize];
			if (segmentsIntersect(p1, p2, p3, p4)) {
				IP ip;
				ip.index0 = j;
				ip.index1 = i;
				ip.p = getintersectPoint(p1, p2, p3, p4);
				iplist.push_back(ip);
			}
		}
	}
}
int getDistance(Point& p1, Point& p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
bool distanceComparator(IP& ip1, IP& ip2) {
	return ip1.dis < ip2.dis;
}
void generateList(Pg& py, list<IP>& iplist, list<IP>& comlist, int index) {
	int size = py.pts.size();
	list<IP>::iterator it;

	for (int i = 0; i < size; i++) {
		Point p1 = py.pts[i];
		IP ip;
		ip.pointFlag = 0;
		ip.p = p1;
		comlist.push_back(ip);
		list<IP> oneSeg;
		for (it = iplist.begin(); it != iplist.end(); it++) {
			if ((index == 0 && i == it->index0) ||
				(index == 1 && i == it->index1)) {
				it->dis = getDistance(it->p, p1);
				it->pointFlag = 1;
				oneSeg.push_back(*it);
			}
		}
		oneSeg.sort(distanceComparator);
		for (it = oneSeg.begin(); it != oneSeg.end(); it++)
			comlist.push_back(*it);
	}
}
void getPgPointInOut(list<IP>& Pglist, Pg& pyclip) {
	bool inFlag;
	list<IP>::iterator it;
	for (it = Pglist.begin(); it != Pglist.end(); it++) {
		if (it->pointFlag == 0) {
			if (isPointInsidePg(it->p, pyclip))
				inFlag = true;
			else inFlag = false;
		}
		else {
			inFlag = !inFlag;
			it->inFlag = inFlag;
		}
	}
}
bool operator==(Point& p1, Point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}
void getClipPointInOut(list<IP>& cliplist, list<IP>& Pglist) {
	list<IP>::iterator it, it1;
	for (it = cliplist.begin(); it != cliplist.end(); it++) {
		if (it->pointFlag == 0) continue;
		for (it1 = Pglist.begin(); it1 != Pglist.end(); it1++) {
			if (it1->pointFlag == 0) continue;
			if (it->p == it1->p) it->inFlag = it1->inFlag;
		}
	}
}
void generateClipArea(list<IP>& Pglist, list<IP>& cliplist) {
	list<IP>::iterator it, it1;
	Pg py;
	Color c = { 0.0, 1.0, 0.0 };

	for (it = Pglist.begin(); it != Pglist.end(); it++)
		if (it->pointFlag == 1 && it->inFlag) break;
	py.pts.clear();

	while (true) {

		if (it == Pglist.end()) break;
		py.pts.push_back(it->p);
		for (; it != Pglist.end(); it++) {
			if (it->pointFlag == 1 && !it->inFlag) break;
			py.pts.push_back(it->p);
		}
		for (it1 = cliplist.begin(); it1 != cliplist.end(); it1++)
			if (it1->p == it->p) break;

		for (; it1 != cliplist.end(); it1++) {
			if (it1->pointFlag == 1 && it1->inFlag) break;
			py.pts.push_back(it1->p);
		}
		if (py.pts[0] == it1->p) {
			py.drawPgLine(c);
			for (int i = 0; i < py.pts.size(); i++){

		points(py.pts[i].x, py.pts[i].y);
	}
			py.pts.clear();
			for (; it != Pglist.end(); it++)
				if (it->pointFlag == 1 && it->inFlag) break;
			continue;
		}
		for (; it != Pglist.end(); it++)
			if (it->p == it1->p) break;
	}
}

void weilerAtherton(Pg& pyclip, Pg& py) {
	list<IP> iplist, Pglist, cliplist;
	generateIntersectPoints(pyclip, py, iplist);

	generateList(py, iplist, Pglist, 0);
	generateList(pyclip, iplist, cliplist, 1);

	getPgPointInOut(Pglist, pyclip);

	getClipPointInOut(cliplist, Pglist);

	generateClipArea(Pglist, cliplist);



}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Size - 1, 0.0, Size - 1);
}

void GenerateRandomSimplePg(Pg &G, int M)
{
	Point P;
	G.pts.clear();
	for (int i = 0; i < M; ++i)
	{
		bool flag;
		do
		{
			P.x = rand() % Size;
			P.y = rand() % Size;
			flag = true;
			for (int j = 1; j < i - 1; ++j)
				if (segmentsIntersect(G.pts[j - 1], G.pts[j], G.pts[i - 1], P))
				{
					flag = false;
					break;
				}
			if (flag && i == M - 1)
			{
				for (int j = 2; j < i; ++j)
					if (segmentsIntersect(G.pts[j - 1], G.pts[j], P, G.pts[0]))
					{
						flag = false;
						break;
					}
			}
		} while (!flag);
		G.pts.push_back(P);
	}
}

void KeyboardAction(unsigned char key, int x, int y)
{

    if(key==27)
	exit(0);
}
int rclick=0,lclick=0;


void mouse(int button, int state, int mousex, int mousey)
{
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        p1.x = mousex+200, p1.y = 800-mousey+200;
	    p2.x = mousex+200, p2.y = 800-mousey-200;
    	p3.x = mousex-200, p3.y = 800-mousey-200;
	    p4.x = mousex-200, p4.y = 800-mousey+200;
        rclick++;



    }
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(lclick==0){
            p5.x = mousex, p5.y = 800-mousey;
        }
        if(lclick==1){
            p6.x = mousex, p6.y = 800-mousey;
        }
        if(lclick==2){
            p7.x = mousex, p7.y = 800-mousey;
        }
        if(lclick==3){
            p8.x = mousex, p8.y = 800-mousey;
        }
        lclick++;
        //glutPostRedisplay();

    }


}




void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_POINT_SMOOTH);

Pg pyclip, py;
	//GenerateRandomSimplePg(pyclip, 4);
	//GenerateRandomSimplePg(py, 4);


    if(lclick==4){
	py.pts.push_back(p5);
	py.pts.push_back(p6);
	py.pts.push_back(p7);
	py.pts.push_back(p8);
    lclick=0;
    }
if(rclick){
	pyclip.pts.push_back(p1);
	pyclip.pts.push_back(p2);
	pyclip.pts.push_back(p3);
	pyclip.pts.push_back(p4);

    }
	Color a = { 0.0, 0.0, 1.0 };
	Color b = { 1.0, 0.0, 0.0 };
	py.drawPgLine(a);
	pyclip.drawPgLine(b);
	weilerAtherton(pyclip, py);
	for (int i = 0; i < py.pts.size(); i++){

		printCordinates(py.pts[i].x, py.pts[i].y);
	}

	for (int i = 0; i < py.pts.size(); i++){

		printCordinates(pyclip.pts[i].x, pyclip.pts[i].y);
	}

	glColor3f (0,0,0);
 glRasterPos2f(500,80);
 char *string2 = "Nikita Juneja 500067046";
 while(*string2)
 {
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string2++);
 }
 glRasterPos2f(240,740);
 char *string3 = "Weiler-Atherton Polygon Clipping";
 while(*string3)
 {
 glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string3++);
 }

	glFlush();
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,800 );

	glutCreateWindow("Lab 7: Weiler-Artherton Polygon Clipping Algorithm");

	glutKeyboardFunc(KeyboardAction);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 0;
}
