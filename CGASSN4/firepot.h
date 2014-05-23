#include <windows.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "main.h"

#ifndef FIREPOT_H
#define FIREPOT_H

using namespace std;

class Firepot{
public:

	vector<int> PotList;
	vector<int>::iterator pointer;
	int NumofPot;
	int jumplength;
	float BottomofPot;
	float HeightofPot;
	float RadiusofPot;
	float HeightofFire;
	float RadiusofFire;
	float RadiusofShadow;
	float RadiusofBigFire;
	float TopofFire;
	float WidthofTriangle;

	Firepot(int jumplength);
	void init(int jumplength, float mapsize, int stage);
	void display_firepot(int toggle);
	void drawSidefire();
	void drawCenterfire();
	void drawLittlefire();



};


#endif FIREPOT_H