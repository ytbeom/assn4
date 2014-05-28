#include "fireloop.h"
#include "lion.h"

Fireloop::Fireloop(int jumplength){
	top = 100.0;
	RadiusofLoop = 30.0;
	WidthofLoop = 8.0;
	// 불고리 개수/위치 설정 (게임 map 밖에 있어도 됨)
	NumofLoop = rand()%1000+500; // 500에서 1000개 사이의 Loop 생성

}

void Fireloop::init(int _jumplength, float _mapsize, int stage){
	jumplength = _jumplength;
	LoopList.clear();
	NumofLoop = rand()%1000+500;// 0~2*jumplength 사이의 위치에 첫 Loop 생성
//	printf("num of loop : %d",NumofLoop);
	LoopList.push_back(rand()%(2*jumplength+1)+jumplength);
	for (int i=0; i<NumofLoop-1; i++) {
		// 앞 고리와 jumplength~3*jumplength 의 간격을 갖는 고리를 생성
		LoopList.push_back(LoopList[i]+((rand()%(7-stage))*jumplength));
	}
	mapsize = _mapsize;
}

void Fireloop::display_3d_fireloop(float lion_x, int translateLoop, int shademode) {
	for (int i=0; i < NumofLoop; i++) {
		if(0<LoopList[i]+translateLoop && LoopList[i]+translateLoop<mapsize) {
			glColor3f(1.0, 0.0, 0.0);
			glPushMatrix();
			glTranslatef(LoopList[i],70,0);
			glRotatef(90,0.0,1.0,0.0);
			if(shademode==0)
				glutWireTorus(3, 27, 20, 20);
			else
				glutSolidTorus(3, 27, 20, 20);
			glPopMatrix();
		}
	}
}

/*
void Fireloop::display_fireloop_front(int toggle,float lion_x,int translateLoop) {
	// 고리의 앞부분을 그리는 부분, 사자보다 먼저 그려져야 함
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
	// 고리의 뒷부분을 그리는 부분, 사자보다 나중에 그려져야 함
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