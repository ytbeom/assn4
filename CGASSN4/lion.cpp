#include "lion.h"

extern float WidthofLoop;
extern float mapsize;

Lion::Lion() {
	x = 0; 
	y = 0; 
	size = 1; 
	state = 0; 
	c_state = 0; 
	jump_state = 0;
	// angle list initialize
	thigh_angle_list[0] = -60.0;
	thigh_angle_list[1] = -30.0;
	thigh_angle_list[2] = 0.0;
	thigh_angle_list[3] = 50.0;
	thigh_angle_list[4] = 50.0;
	thigh_angle_list[5] = 20.0;
	thigh_angle_list[6] = 0;
	thigh_angle_list[7] = -30.0;
	// knee list initialize
	knee_angle_list[0] = -60.0;
	knee_angle_list[1] = -45.0;
	knee_angle_list[2] = 0.0;
	knee_angle_list[3] = 0.0;
	knee_angle_list[4] = 0.0;
	knee_angle_list[5] = 0.0;
	knee_angle_list[6] = 0.0;
	knee_angle_list[7] = -45.0;

	quadric_lion = gluNewQuadric();
}

int Lion::IsCollisionPot(float _x, float _y, float _radius){
	if(_x-_radius < x+0.2*size && _x+_radius > x-0.8*size) {
		if(y-0.7*size < _y)
			return true;
	}
	return false;
}

int Lion::IsCollisionLoop(float _x, float _y, float _radius){
	if(_x < x+0.3*size && x-0.7*size < _x){
		if(!(y-0.7*size>_y-_radius&&y+0.5*size<_y+_radius))
			return true;
	}
	return false;
}

void Lion::drawDeath(Lion my_lion, int viewmode){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	char string[] ="GAME OVER";
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(my_lion.x,50);
	int len = 9;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string[i]);
}

void Lion::drawClear(Lion my_lion, int viewmode){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	char string[] ="STAGE CLEAR";
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(my_lion.x+15,50);

	int len = 11;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string[i]);
}

/*
void Lion::drawLeg(){
	
}
*/

void Lion::drawLion(GLuint lion_1_texture, GLuint lion_2_texture){
	// assignment2 drawLion function
	// 시작은 Torso의 기준점, 겹치는 문제 때문에 다리를 먼저그림

	// Quadric 객체들의 속성 결정, shading mode에 따라 GLU_LINE인지 GLU_FILL인지 결정해야 함
	gluQuadricDrawStyle(quadric_lion, GLU_FILL);
	gluQuadricTexture(quadric_lion, GL_TRUE);

	glEnable (GL_TEXTURE_2D);
	glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	if (jump_state == 0) {
		// 앞쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.3*size,-0.25*size,-0.1*size);
		glRotatef(thigh_angle_list[state],0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[state%8],0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();
		glPopMatrix();	

		// 앞쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.3*size,-0.25*size,0.1*size);
		glRotatef(thigh_angle_list[state],0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[state%8],0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();
		glPopMatrix();

		// 뒷쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.25*size,-0.1*size);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();
		glPopMatrix();

		// 뒷쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.25*size,0.1*size);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();
		glPopMatrix();
	}
	else {
		// 앞쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.3*size,-0.25*size,-0.1*size);
		glRotatef(60,0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(0,0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();	
		glPopMatrix();

		// 앞쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.3*size,-0.25*size,0.1*size);
		glRotatef(60,0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(0,0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();
		glPopMatrix();

		// 뒷쪽 왼다리
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.25*size,-0.1*size);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();
		glPopMatrix();

		// 뒷쪽 오른다리
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso의 기준점에서 앞쪽 다리의 상대적인 위치로 변환
		glTranslatef(-0.9*size,-0.25*size,0.1*size);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg(lion_1_texture, lion_2_texture);
		glPushMatrix();
		// 위쪽 다리와 아랫쪽 다리의 상대적인 위치 변환
		glTranslatef(0,-0.12*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg(lion_1_texture, lion_2_texture);
		glPopMatrix();
		glPopMatrix();
	}
	
	glPushMatrix();
	glRotatef(90,0,1,0);
	glScalef(4,4,4);
	drawHead(lion_1_texture, lion_2_texture);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5,-1.5,0);
	glRotatef(270,0,1,0);
	glRotatef(90,0,0,1);
	glScalef(8,8,8);
	drawTorso(lion_1_texture, lion_2_texture);
	glPopMatrix();
}

// 시작 좌표를 (0,0)으로 해 몸통을 그림
void Lion::drawTorso(GLuint lion_1_texture, GLuint lion_2_texture) {
	glBindTexture(GL_TEXTURE_2D, lion_2_texture);

	glColor3f(1.0,1.0,0.0);

	// main body
	//glutWireCylinder(0.5,2,20,20);
	gluCylinder(quadric_lion, 0.5, 0.5, 2, 20, 20);

	glPushMatrix();
	glRotatef(180,0,1,0);
	//glutWireCone(0.5,0.5,10,10);
	gluCylinder(quadric_lion, 0.5, 0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1,1,0.4);
	//glutWireSphere(0.5,20,20);
	gluSphere(quadric_lion, 0.5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
	glScalef(1,1,0.4);
	//glutWireSphere(0.5,20,20);
	gluSphere(quadric_lion, 0.5, 20, 20);
	glPopMatrix();

	// tail part
	glPushMatrix();
	glTranslatef(0,0,2);
	glRotatef(45,0,1,0);
	//glutWireCylinder(0.05,2,10,10);
	gluCylinder(quadric_lion, 0.05, 0.05, 2, 10, 10);
	
	glBindTexture(GL_TEXTURE_2D, lion_1_texture);
	glPushMatrix();
	glColor3f(1.0,0.5,0.0);
	glTranslatef(0,0,2);
	//glutWireSphere(0.1,10,10);
	gluSphere(quadric_lion, 0.1, 10, 10);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

// 시작 좌표를 (0,0)으로 해 머리를 그림
void Lion::drawHead(GLuint lion_1_texture, GLuint lion_2_texture) {
	//head
	glBindTexture(GL_TEXTURE_2D, lion_2_texture);

	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	//glutWireSphere(1,20,20);
	gluSphere(quadric_lion, 1, 20, 20);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// eye part
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(-0.4,0.01,0.88);
	glutSolidSphere(0.07,10,10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0.4,0.01,0.88);
	glutSolidSphere(0.07,10,10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0,-0.25,0.9375);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();

	// nose part
	glBindTexture(GL_TEXTURE_2D, lion_2_texture);
	
	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(-0.2,-0.4,0.8);
	//glutWireSphere(0.2,10,10);
	gluSphere(quadric_lion, 0.2, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(0.2,-0.4,0.8);
	//glutWireSphere(0.2,10,10);
	gluSphere(quadric_lion, 0.2, 10, 10);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
		
	// mane part
	glBindTexture(GL_TEXTURE_2D, lion_1_texture);

	glPushMatrix();
	glTranslatef(cos(0.0)*1.7,sin(0.0)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI/2)*1.7,sin(PI/2)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI)*1.7,sin(PI)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*3/2)*1.7,sin(PI*3/2)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI/4)*1.7,sin(PI/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*3/4)*1.7,sin(PI*3/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*5/4)*1.7,sin(PI*5/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*7/4)*1.7,sin(PI*7/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	//glutWireSphere(0.7,20,20);
	gluSphere(quadric_lion, 0.7, 20, 20);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);
	//head end
}

// 시작 좌표를 (0,0)으로 해 머리를 그림
void Lion::drawHead() {
	//head
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glutWireSphere(1,20,20);
	glPopMatrix();
	
	// eye part
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(-0.4,0.01,0.88);
	glutSolidSphere(0.07,10,10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0.4,0.01,0.88);
	glutSolidSphere(0.07,10,10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(0,-0.25,0.9375);
	glutSolidSphere(0.05,10,10);
	glPopMatrix();

	// nose part
	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(-0.2,-0.4,0.8);
	glutWireSphere(0.2,10,10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,1,0);
	glTranslatef(0.2,-0.4,0.8);
	glutWireSphere(0.2,10,10);
	glPopMatrix();
		
	// mane part
	glPushMatrix();
	glTranslatef(cos(0.0)*1.7,sin(0.0)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI/2)*1.7,sin(PI/2)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI)*1.7,sin(PI)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*3/2)*1.7,sin(PI*3/2)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI/4)*1.7,sin(PI/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*3/4)*1.7,sin(PI*3/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*5/4)*1.7,sin(PI*5/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cos(PI*7/4)*1.7,sin(PI*7/4)*1.7,0);
	glColor3f(1.0,0.5,0.0);
	glutWireSphere(0.7,20,20);
	glPopMatrix();
	//head end
}

// (x-0.93*size, y-0.09*size)을 새로운 원점 기준으로 꼬리를 그림
void Lion::drawTail(GLuint lion_1_texture, GLuint lion_2_texture) {
}

void Lion::drawUpperLeg(GLuint lion_1_texture, GLuint lion_2_texture) {
	glBindTexture(GL_TEXTURE_2D, lion_2_texture);

	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(5,5,5);
	//glutSolidCylinder(0.2,0.5,10,10);
	//glutSolidSphere(0.2,20,20);
	gluCylinder(quadric_lion, 0.2, 0.2, 0.5, 10, 10);
	gluSphere(quadric_lion, 0.2, 20, 20);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Lion::drawLowerLeg(GLuint lion_1_texture, GLuint lion_2_texture) {
	glBindTexture(GL_TEXTURE_2D, lion_2_texture);

	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(5,5,5);
	//glutSolidCylinder(0.2,0.5,10,10);
	//glutSolidSphere(0.2,20,20);
	gluCylinder(quadric_lion, 0.2, 0.2, 0.5, 10, 10);
	gluSphere(quadric_lion, 0.2, 20, 20);
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, 0);
}