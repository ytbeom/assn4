#include "fireloop.h"
#include "lion.h"

Fireloop::Fireloop(int jumplength){
	top = 100.0;
	RadiusofLoop = 30.0;
	WidthofLoop = 8.0;
	// �Ұ� ����/��ġ ���� (���� map �ۿ� �־ ��)
	NumofLoop = rand()%1000+500; // 500���� 1000�� ������ Loop ����

}

void Fireloop::init(int _jumplength, float _mapsize, int stage){
	jumplength = _jumplength;
	LoopList.clear();
	NumofLoop = rand()%1000+500;// 0~2*jumplength ������ ��ġ�� ù Loop ����
//	printf("num of loop : %d",NumofLoop);
	LoopList.push_back(rand()%(2*jumplength+1)+jumplength);
	for (int i=0; i<NumofLoop-1; i++) {
		// �� ���� jumplength~3*jumplength �� ������ ���� ���� ����
		LoopList.push_back(LoopList[i]+((rand()%(7-stage))*jumplength));
	}
	mapsize = _mapsize;
}

void Fireloop::display_3d_fireloop(float lion_x, int translateLoop) {
	for (int i=0; i < NumofLoop; i++) {
		if(0<LoopList[i]+translateLoop && LoopList[i]+translateLoop<mapsize) {
			glColor3f(1.0, 0.0, 0.0);
			glPushMatrix();
			glTranslatef(LoopList[i],70,0);
			glRotatef(90,0.0,1.0,0.0);
			glutWireTorus(3, 27, 20, 20);
			glPopMatrix();
		}
	}
}

/*
void Fireloop::display_fireloop_front(int toggle,float lion_x,int translateLoop) {
	// ���� �պκ��� �׸��� �κ�, ���ں��� ���� �׷����� ��
		//printf(" translate Loop : %d\n",translateLoop);
	for (int i = 0; i < NumofLoop; i++) {
		
		if(lion_x-100<LoopList[i]+translateLoop&&LoopList[i]+translateLoop<lion_x+1000){
			glColor3f(1.0, 0.0, 0.0);
			for (float angle = (-1.0/2.0)*PI; angle > (-3.0/2.0)*PI; angle -= 0.1) {
				float x = WidthofLoop * cos(angle);
				float y = top - RadiusofLoop + RadiusofLoop * sin(angle);
				glPushMatrix();
				glTranslatef(LoopList[i],0,0);
				glTranslatef(rand()%2,0,0);
				glBegin(GL_POLYGON);
				glVertex2f(x-1,y+2);
				glVertex2f(x-2,y);
				glVertex2f(x-1,y-2);
				glVertex2f(x+1,y-2);
				glVertex2f(x+2,y);
				glVertex2f(x+1,y+2);
				glEnd();
				glPopMatrix();
				}
			glColor3f(1.0, 0.7, 0.0);
			for (float angle = (-1.0/2.0)*PI; angle > (-3.0/2.0)*PI; angle -= 0.1) {
				float x = WidthofLoop * cos(angle);
				float y = top - RadiusofLoop + RadiusofLoop * sin(angle);
				glPushMatrix();
				glTranslatef(LoopList[i],0,0);
				glTranslatef(rand()%2,0,0);
				glBegin(GL_POLYGON);
				glVertex2f(x-0.5,y+2);
				glVertex2f(x-1,y);
				glVertex2f(x-0.5,y-2);
				glVertex2f(x+0.5,y-2);
				glVertex2f(x+1,y);
				glVertex2f(x+0.5,y+2);
				glEnd();
				glPopMatrix();
				}
			glColor3f(1.0, 0.5, 0.0);
			for (float angle = (-1.0/2.0)*PI; angle > (-3.0/2.0)*PI; angle -= 0.1) {
				float x = WidthofLoop * cos(angle);
				float y = top - RadiusofLoop + RadiusofLoop * sin(angle);
				glPushMatrix();
				glTranslatef(LoopList[i],0,0);
				glTranslatef(rand()%2,0,0);
				glBegin(GL_POLYGON);
				glVertex2f(x-0.2,y+2);
				glVertex2f(x-0.3,y);
				glVertex2f(x-0.2,y-2);
				glVertex2f(x+0.2,y-2);
				glVertex2f(x+0.3,y);
				glVertex2f(x+0.2,y+2);
				glEnd();
				glPopMatrix();
				}
		}
	}
			

	
}

void Fireloop::display_fireloop_back(int toggle,float lion_x,int translateLoop) {
	// ���� �޺κ��� �׸��� �κ�, ���ں��� ���߿� �׷����� ��
	for (int i = 0; i < NumofLoop; i++) {
		if(lion_x-100<LoopList[i]+translateLoop&&LoopList[i]+translateLoop<lion_x+1000){
			glColor3f(1.0, 0.0, 0.0);
			for (float angle = (-1.0/2.0)*PI; angle < (1.0/2.0)*PI; angle += 0.1) {
				float x = WidthofLoop * cos(angle);
				float y = top - RadiusofLoop + RadiusofLoop * sin(angle);
				glPushMatrix();
				glTranslatef(LoopList[i],0,0);
				glTranslatef(rand()%2,0,0);
				glBegin(GL_POLYGON);
				glVertex2f(x-1,y+2);
				glVertex2f(x-2,y);
				glVertex2f(x-1,y-2);
				glVertex2f(x+1,y-2);
				glVertex2f(x+2,y);
				glVertex2f(x+1,y+2);
				glEnd();
				glPopMatrix();
			}
			glColor3f(1.0, 0.7, 0.0);
			for (float angle = (-1.0/2.0)*PI; angle < (1.0/2.0)*PI; angle += 0.1) {
				float x = WidthofLoop * cos(angle);
				float y = top - RadiusofLoop + RadiusofLoop * sin(angle);
				glPushMatrix();
				glTranslatef(LoopList[i],0,0);
				glTranslatef(rand()%2,0,0);
				glBegin(GL_POLYGON);
				glVertex2f(x-0.5,y+2);
				glVertex2f(x-1,y);
				glVertex2f(x-0.5,y-2);
				glVertex2f(x+0.5,y-2);
				glVertex2f(x+1,y);
				glVertex2f(x+0.5,y+2);
				glEnd();
				glPopMatrix();
			}

			glColor3f(1.0, 0.5, 0.0);
			for (float angle = (-1.0/2.0)*PI; angle < (1.0/2.0)*PI; angle += 0.1) {
				float x = WidthofLoop * cos(angle);
				float y = top - RadiusofLoop + RadiusofLoop * sin(angle);
				glPushMatrix();
				glTranslatef(LoopList[i],0,0);
				glTranslatef(rand()%2,0,0);
				glBegin(GL_POLYGON);
				glVertex2f(x-0.2,y+2);
				glVertex2f(x-0.3,y);
				glVertex2f(x-0.2,y-2);
				glVertex2f(x+0.2,y-2);
				glVertex2f(x+0.3,y);
				glVertex2f(x+0.2,y+2);
				glEnd();
				glPopMatrix();
			}

		}
	}
	
}
*/