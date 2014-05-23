

#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lion.h"


#include <gl/freeglut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#ifndef stage_H
#define stage_H

#define PI 3.1415926535
#define g 9.80665

using namespace std;
class Stage{
public:
	int season;

	Stage(){season = 0;}

	void drawBackground();

};

class Background{
public:
	int season;
	float mapsize;
	float bottom;
	vector<int> BackgroundX;
	vector<int>::iterator pointerX;
	vector<int> BackgroundY;
	vector<int>::iterator pointerY;
	int dec[200];

	Background();
	void init(float mapsize, float bottom, int season);
	void draw(int BackgroundChange);
	void drawFlying(int season, float X, float Y);
	void info(float lion_x, int viewmode);
	void drawMaple();
	void drawGinkgo();
	void drawFlag();
	void tutorial();
	void start(Lion my_lion);

};


#endif