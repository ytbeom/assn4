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

void Lion::drawLeg(){
	
}

void Lion::drawLion(){


	// assignment2 drawLion function

	// ������ Torso�� ������, ��ġ�� ���� ������ �ٸ��� �����׸�

	if (jump_state == 0) {
		// ���� �޴ٸ�
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.3*size,-0.25*size,-0.1*size);
		glRotatef(thigh_angle_list[state],0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[state%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();	

		// ���� �����ٸ�
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.3*size,-0.25*size,0.1*size);
		glRotatef(thigh_angle_list[state],0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[state%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// ���� �޴ٸ�
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.9*size,-0.25*size,-0.1*size);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// ���� �����ٸ�
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.9*size,-0.25*size,0.1*size);
		glRotatef(thigh_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(knee_angle_list[(state+4)%8],0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();
	}
	else {
		// ���� �޴ٸ�
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.3*size,-0.25*size,-0.1*size);
		glRotatef(60,0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(0,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();	

		// ���� �����ٸ�
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.3*size,-0.25*size,0.1*size);
		glRotatef(60,0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(0,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// ���� �޴ٸ�
		glColor3f(1.0,0.9,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.9*size,-0.25*size,-0.1*size);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();

		// ���� �����ٸ�
		glColor3f(1.0,1.0,0.0);
		glPushMatrix();
		// Torso�� ���������� ���� �ٸ��� ������� ��ġ�� ��ȯ
		glTranslatef(-0.9*size,-0.25*size,0.1*size);
		glRotatef(-45,0.0,0.0,1.0);
		drawUpperLeg();
		// ���� �ٸ��� �Ʒ��� �ٸ��� ������� ��ġ ��ȯ
		glTranslatef(0,-0.12*size,0);
		glRotatef(-45,0.0,0.0,1.0);
		drawLowerLeg();
		glPopMatrix();
	}
	
	glPushMatrix();
	glRotatef(90,0,1,0);
	glScalef(4,4,4);
	drawHead();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.5,-1.5,0);
	glRotatef(270,0,1,0);
	glRotatef(90,0,0,1);
	glScalef(8,8,8);
	drawTorso();
	glPopMatrix();

	
	


}

// ���� ��ǥ�� (0,0)���� �� ������ �׸�
void Lion::drawTorso() {
	glColor3f(1.0,1.0,0.0);
	
	glutWireCylinder(0.5,2,20,20);
	
	glPushMatrix();
	glRotatef(180,0,1,0);
	glutWireCone(0.5,0.5,10,10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1,1,0.4);
	glutWireSphere(0.5,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
	glScalef(1,1,0.4);
	glutWireSphere(0.5,20,20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
	glRotatef(45,0,1,0);
	glutWireCylinder(0.05,2,10,10);
	
	glPushMatrix();
	glColor3f(1.0,0.5,0.0);
	glTranslatef(0,0,2);
	glutWireSphere(0.1,10,10);
	glPopMatrix();
	
	glPopMatrix();
	
}

// ���� ��ǥ�� (0,0)���� �� �Ӹ��� �׸�
void Lion::drawHead() {
	//head
	glPushMatrix();
	glColor3f(1.0,1.0,0.0);
	glutWireSphere(1,20,20);
	glPopMatrix();
	
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

// (x-0.93*size, y-0.09*size)�� ���ο� ���� �������� ������ �׸�
void Lion::drawTail() {
}

void Lion::drawUpperLeg() {
	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(5,5,5);
	glutSolidCylinder(0.2,0.5,10,10);
	glutSolidSphere(0.2,20,20);
	glPopMatrix();
}

void Lion::drawLowerLeg() {
	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(5,5,5);
	glutSolidCylinder(0.2,0.5,10,10);
	glutSolidSphere(0.2,20,20);
	glPopMatrix();
}