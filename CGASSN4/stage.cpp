#include "stage.h"

Background::Background(){
	season = 1;
	int i;
	// 배경 날림의 위치 초기화
	for (i = 0; i < mapsize/10; i++) {
		int x = rand()%((int)mapsize+200)-100;
		int y = rand()%100+10;
		BackgroundX.push_back(x);
		BackgroundY.push_back(y);
	}
	// 배경 데코에 쓸 것
	for (i = 0; i < 200; i++) {
		int d = (rand()+i)%(100);
		dec[i] = d;
	}
}
void Background::init(float _mapsize, float _bottom, int _season){
	mapsize = _mapsize;
	bottom = _bottom;
	season = _season;
	for (int i = 0; i < 200; i++) {
		int d = (rand())%((int)mapsize);
		dec[i] = d;
		//printf("%d\n",d);
	}
}
void Background::draw(int BackgroundChange){
	
	//하늘 바탕?
	//glColor3f(0.529,0.807,0.980);
	//glRectf(-mapsize,10,mapsize+200,100);
	

		// 게임 화면 바닥
		if(season==1)
			glColor3f(0,0.6,0);
		else if(season==2)
			glColor3f(0,0.4,0);
		else if(season==3)
			glColor3f(0.4,0.2,0);
		else if(season==4)
			glColor3f(1.0,1.0,1.0);
		//glRectf(-mapsize,0,mapsize+200,bottom-10);
		glPushMatrix();
		glScalef(1,bottom/mapsize,50/mapsize);
		glTranslatef(mapsize/2,0,-25);
		glutSolidCube(mapsize);
		glPopMatrix();
		if(season==1||season==3){
			int i;
			int k=0;
			for(i=0;i<mapsize+200;i++){
				k++;
				if(k>190)
					k=0;
				int temp2 = dec[k]%2;
				int temp3 = dec[k]%3;
				int temp7 = dec[k]%7;
				for(int j=0;j<(temp7*k)%5;j++){
					float tempY = bottom-10-j*(float)(temp7/6);
					glPushMatrix();
					glTranslatef(i-50,tempY,0);
					glRotatef(dec[k]%360,0,0,1);
					if(season==1){
						if((temp2+j)%2)
							glColor3f(1.0,0.4,0.4);
						else
							glColor3f(1.0,1.0,0);
						int fsize = 1;
						glRectf(0,0,fsize,fsize);
					}
					else{
						if((temp2+j)%2)
							drawMaple();
						else
							drawGinkgo();
					}
					glPopMatrix();
				}
			}
		}
		if(season!=2){
			// 꽃잎 그리기
			if (BackgroundChange < 9) {
				for (unsigned int i = 0; i < BackgroundX.size(); i++) {
					drawFlying(season,BackgroundX[i],BackgroundY[i]);
				}
			}
			else { // 꽃잎 위치 update
				BackgroundX.clear();
				BackgroundY.clear();
				for (int i = 0; i < mapsize/10; i++) {
					int x = rand()%((int)mapsize+200)-100;
					int y = rand()%100+10;
					BackgroundX.push_back(x);
					BackgroundY.push_back(y);
				}		
			}
		}
	// 시작 위치에 노란색 깃발 표시
	glPushMatrix();
	glTranslatef(-10,0,0);
	drawFlag();
	glPopMatrix();


	// 끝나는 위치에 노란색 깃발 표시
	glPushMatrix();
	glTranslatef(mapsize,0,0);
	drawFlag();
	glPopMatrix();

}

void Background::drawFlying(int season, float X, float Y){
	glPushMatrix();
	glTranslatef(X,Y,0);
	if(season==3){
		int color;
		color = (int)X%2;
		if(color==0){//단풍
			glPushMatrix();
			glRotatef(((int)X*10)%360,0,0,1);
			drawMaple();
			glPopMatrix();
		}
		else{//은행
			glPushMatrix();
			glRotatef(((int)X*10)%360,0,0,1);
			drawGinkgo();
			glPopMatrix();	
		}
	}
	else{
		if(season==1)
			glColor3f(1.0,0.4,0.4);
		int fsize = 1;
		glRectf(0,0,fsize,fsize);
	}
	glPopMatrix();
}

void Background::info(float lion_x, int viewmode){
	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	char string[] ="STAGE : ";
	glColor3f(0,0,0.5);
	switch (viewmode) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		glRasterPos3f(0.9*mapsize,0,-0.2*mapsize);
		break;
	case 4:
		glRasterPos3f(0.9*mapsize, 0.2*mapsize,0);
		break;
	case 5:
		glPushMatrix();
		glTranslatef(lion_x,0,0);
		glRasterPos2f(120,90);
		break;
	}
	int len = 8;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string[i]);
	char print_stage;
	print_stage=season+48;
	glutBitmapCharacter(font,print_stage);


	glColor3f(1,0,0);
	
	int now=lion_x;	
	switch (viewmode) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		
		glBegin(GL_POLYGON);
		glVertex3f(0.9*mapsize,0,-0.2*mapsize+50);
		if(lion_x<0)
			now=0;
		for( float angle = 0;angle<((now/mapsize)*2)*PI;angle+=0.1){
			float x = 0.9*mapsize+20*cos(angle);
			float y = -0.2*mapsize+50-20*sin(angle);
			glVertex3f(x,0,y);
		}
		glEnd();
		break;
	case 4:
		glBegin(GL_POLYGON);
		glVertex3f(0.9*mapsize, 0.2*mapsize-50,0);
		if(lion_x<0)
			now=0;
		for( float angle = 0;angle<((now/mapsize)*2)*PI;angle+=0.1){
			float x = 0.9*mapsize+20*cos(angle);
			float y = 0.2*mapsize-50+20*sin(angle);
			glVertex3f(x,y,0);
		}
		glEnd();
		break;
	case 5:
		glBegin(GL_POLYGON);
		glVertex2f(145, 91);
		if(lion_x<0)
			now=0;
		for( float angle = 0;angle<((now/mapsize)*2)*PI;angle+=0.1){
			float x = 145+2*cos(angle);
			float y = 91+2*sin(angle);
			glVertex2f(x,y);
		}
		glEnd();
		glPopMatrix();
		break;
	}
	
}

void Background::drawMaple(){
		glColor3f(1,0,0);
		glBegin(GL_TRIANGLES);
		glVertex2f(0.5,-0.2);
		glVertex2f(-2.5,0.5);
		glVertex2f(0.5,1.2);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(0,1);
		glVertex2f(1.5,2.5);
		glVertex2f(1,0.5);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(0,0);
		glVertex2f(1.5,-1.5);
		glVertex2f(1,0.5);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(0,0);
		glVertex2f(-1.2,2.5);
		glVertex2f(1,1);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(0,1);
		glVertex2f(-1.2,-1.5);
		glVertex2f(1,0);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(1, 0);
		glVertex2f(1, 1);
		glVertex2f(0, 1);
		glEnd();
		glRectf(1,0.4,1.5,0.6);
		
}
void Background::drawGinkgo(){
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	for( float angle = (2.0/3.0)*PI;angle<(4.0/3.0)*PI;angle+=0.1){
		float x = 2*cos(angle);
		float y = 2*sin(angle);
		glVertex2f(x,y);
	}
	glEnd();
	glRectf(0,-0.1,1,0.1);
}

void Background::drawFlag(){
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 6);
	glVertex2f(0, 46);
	glVertex2f(20, 36);
	glVertex2f(0, 30);
	glEnd();
	glLineWidth(1);
}

void Background::tutorial(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200, 0, 100, -50, 50);
	
	char string[] ="GAME TUTORIAL";
	char string2[] = "mode selection";
	char string3[] = "1: 1st person view";
	char string4[] = "2: 3rd person view";
	char string5[] = "3: top view       ";
	char string6[] = "4: side view      ";
	char string7[] = "5: zoom view      ";
	char string8[] = "move";
	char string9[] = "LEFT, RIGHT KEY: go forward, backward";
	char string10[] = "UP KEY: jump";
	char string11[] = "Press Enter to start...";
	glColor3f(1.0,1.0,1.0);

	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	glRasterPos2f(80,80);
	int len = 13;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string[i]);

	glRasterPos2f(20,60);
	len = 14;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string2[i]);

	glRasterPos2f(15,50);
	len = 18;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string3[i]);
	glRasterPos2f(15,45);
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string4[i]);
	glRasterPos2f(15,40);
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string5[i]);
	glRasterPos2f(15,35);
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string6[i]);
	glRasterPos2f(15,30);
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string7[i]);


	glRasterPos2f(100,60);
	len = 4;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string8[i]);
	glRasterPos2f(100,50);
	len = 37;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string9[i]);
	glRasterPos2f(100,45);
	len = 13;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string10[i]);

	glRasterPos2f(150,10);
	len = 23;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string11[i]);


	glFlush();
	glutSwapBuffers();

}

void Background::start(Lion my_lion){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200, 0, 100, -50, 50);

	glPushMatrix();
	glTranslatef(100,50,0);
	glScalef(10,10,10);
	my_lion.drawHead();
	glPopMatrix();

	void *font = GLUT_BITMAP_TIMES_ROMAN_24;
	char string11[] = "Press Enter to start...";
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(150,10);
	int len = 23;
	for(int i=0;i<len;i++)
		glutBitmapCharacter(font,string11[i]);


	glFlush();
	glutSwapBuffers();
};