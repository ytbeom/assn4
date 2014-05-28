#include <windows.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "main.h"
#include "ObjLoader.h"

#ifndef ROCK_H
#define ROCK_H

using namespace std;

class Rock{
public:
	vector<int> RockList;
	vector<int>::iterator pointer;
	int NumofRock;
	model rockmodel;

	Rock(int jumplength);
	void init(int jumplength, float mapsize, int stage);
	void display_rock(int shadingmode);
};


#endif ROCK_H