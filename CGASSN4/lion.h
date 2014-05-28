#ifndef lion_H
#define lion_H

#include <iostream>
#include <windows.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <gl/freeglut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <math.h>

#define PI 3.1415926535
#define g 9.80665

class Lion{
public:
	float x;
	float y;
	float size;
	int c_state; // 다리가 너무 빨리 움직이는 것을 막기 위한 counter
	int state; // 다리의 상태 (0~7)
	int jump_state; // 점프하면 1, 아니면 0
	float velocity;
	float thigh_angle_list[8];
	float knee_angle_list[8];

	// lion texture mapping을 위한 GLUquadricObj 객체들 선언
	GLUquadricObj *quadric_lion;


	Lion();
	//void drawLeg();
	void drawLion(GLuint lion_1_texture, GLuint lion_2_texture);
	void drawDeath(Lion my_lion, int viewmode);
	void drawClear(Lion my_lion, int viewmode);

	// assignment2 functions
	void drawTorso(GLuint lion_1_texture, GLuint lion_2_texture);
	void drawHead();
	void drawHead(GLuint lion_1_texture, GLuint lion_2_texture);
	void drawTail(GLuint lion_1_texture, GLuint lion_2_texture);
	void drawUpperLeg(GLuint lion_1_texture, GLuint lion_2_texture);
	void drawLowerLeg(GLuint lion_1_texture, GLuint lion_2_texture);
	int IsCollisionPot(float x, float y, float radius);
	int IsCollisionLoop(float x, float y, float radius);
};

#endif