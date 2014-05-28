#include <time.h>
#include <stdlib.h>
#include "lion.h"
#include "firepot.h"
#include "fireloop.h"
#include "stage.h"
#include "rock.h"
#include "BitmapLoader.h"

float mapsize;
float bottom = 20.0;
int jumplength = 80; // 사자가 1회 점프할 때 움직이는 거리
int xposition = 0.0;
int BackgroundChange = 0;
int translateLoop;
int stage=1;
int start=0;
int startfresh;
int viewmode = 5; // 1: 1st person view, 2: 3rd person view, 3: top view, 4: side view 5: assignment 1,2 view
int lightsource = 0;
int shadingmode = 0;

Lion my_lion;
Background my_bg;
//Firepot my_pot(jumplength);
Rock my_rock(jumplength);
Fireloop my_loop(jumplength);

GLubyte *rock; // 데이터를 가리킬 포인터 (바위 표면을 의미)
BITMAPINFO *rock_info; // 비트맵 헤더 저장할 변수
GLuint rock_texture; // 바위 표면 texture

GLubyte *lion_1; // 데이터를 가리킬 포인터 (사자의 어두운 색 부분을 의미)
BITMAPINFO *lion_1_info; // 비트맵 헤더 저장할 변수
GLuint lion_1_texture; // 사자 texture

GLubyte *lion_2; // 데이터를 가리킬 포인터 (사자의 밝은 색 부분을 의미)
BITMAPINFO *lion_2_info; // 비트맵 헤더 저장할 변수
GLuint lion_2_texture; // 사자 texture

void init(void)
{
	my_lion.x = 0;
	my_lion.y = bottom;
	my_lion.size = 20;
	my_lion.c_state = 0;
	my_lion.state = 2;
	my_lion.jump_state = 0;
	translateLoop=0;
	startfresh=0;

	srand((unsigned int)time(NULL));
	
	// 1000에서 2000 사이의 mapsize 생성
	mapsize = rand()%1000+1000;
//	mapsize = 200;
	my_bg.init(mapsize,bottom,stage);
	//my_pot.init(jumplength,mapsize,stage);
	my_rock.init(jumplength,mapsize,stage);
	my_loop.init(jumplength,mapsize,stage);

	glGenTextures (1, &rock_texture); 
	glBindTexture(GL_TEXTURE_2D, rock_texture);
	rock=LoadDIBitmap("Rock-Texture-Surface.bmp",&rock_info);
	glTexImage2D ( GL_TEXTURE_2D, 0, 3, 2592, 1944, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, rock);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &lion_1_texture); 
	glBindTexture(GL_TEXTURE_2D, lion_1_texture);
	lion_1 = LoadDIBitmap("lion_texture_1.bmp",&lion_1_info);
	glTexImage2D ( GL_TEXTURE_2D, 0, 3, 161, 88, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, lion_1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenTextures(1, &lion_2_texture); 
	glBindTexture(GL_TEXTURE_2D, lion_2_texture);
	lion_2 = LoadDIBitmap("lion_texture_2.bmp", &lion_2_info);
	glTexImage2D ( GL_TEXTURE_2D, 0, 3, 145, 110, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, lion_2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}

int collision(){
	/*
	for(int i = 0; i < my_rock.NumofRock; i++){
		if(my_lion.IsCollisionPot(my_rock.RockList[i]/2, 15.0+2.4971*6.0, 3.18344*3))
			return true;
	}
	
	for(int i = 0; i < my_loop.NumofLoop; i++){
		if(my_lion.IsCollisionLoop(my_loop.LoopList[i]+translateLoop, my_loop.top - my_loop.RadiusofLoop, my_loop.RadiusofLoop))
			return true;
	}
	*/
	return false;
}

// 시간이 지나면 속도가 자동으로 0이 되게끔 하는 함수
void Stop(int value){
	int keep;
	if(my_lion.y!=bottom)
		keep=0;
	else{
		if(my_lion.velocity<0.005 && my_lion.velocity>-0.005){
			my_lion.velocity=0;
			//my_lion.state=2;
			keep=0;
		}
		else if(my_lion.velocity>0){
			keep=1;
			my_lion.velocity -= 0.005;
		}
		else{
			keep=1;
			my_lion.velocity += 0.005;
		}
	}
	if(keep)
		glutTimerFunc(100, Stop, 1);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if (BackgroundChange < 9) 
		BackgroundChange++;
	else
		BackgroundChange=0;
	if (start==0)
		my_bg.start(my_lion);
	else if(start==1)
		my_bg.tutorial();
	else{
	if (!collision() && my_lion.x > mapsize && my_bg.season<4) {
		my_lion.drawClear(my_lion, viewmode);
		glFlush();
		glutSwapBuffers();
		Sleep(2000);
		stage++;
		init();
		//exit(1);
	}
	else if (!collision() && my_lion.x > mapsize && my_bg.season==4) {
		my_lion.drawClear(my_lion, viewmode);
		glFlush();
		glutSwapBuffers();
		Sleep(2000);
		exit(1);
	}
	else if(!collision()) {
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);


		GLfloat lightposition [] = {mapsize/2, 200, 0, 0};
		GLfloat lightposition2 [] = {0, 50, 0, 0};
		GLfloat ambient [] = {1, 0, 0, 1};
		GLfloat ambient2 [] = {1, 0, 0, 1};
		GLfloat diffuse [] = {1, 1, 0, 1};
		GLfloat diffuse2 [] = {1, 1, 0, 1};

		switch(lightsource){
		case 0:
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			glLightfv(GL_LIGHT0, GL_POSITION, lightposition);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT1, GL_POSITION, lightposition2);
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
			break;
		case 1:
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			glLightfv(GL_LIGHT2, GL_POSITION, lightposition);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT3, GL_POSITION, lightposition2);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse2);
			break;
		}

		switch(shadingmode){
		case 0:
			glDisable(GL_LIGHTING);
			break;
		case 1:
			//glLightModel(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
			glShadeModel(GL_FLAT);
			break;
		case 2:
			glShadeModel(GL_SMOOTH);
			break;
		case 3:
			break;
		}
			

		my_bg.draw(BackgroundChange);
		my_bg.info(my_lion.x, viewmode);
		startfresh=1;
		bool right = ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000);
		bool left = ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000);
		if(right) {
			if (my_lion.y==bottom) {
				my_lion.x += 1;
				my_lion.velocity += 0.05;

				if(my_lion.velocity<0)
					my_lion.velocity=0;

				// state change
				if (my_lion.c_state == 3) {
					my_lion.state = (my_lion.state+1)%8;
					my_lion.c_state = 0;
				}
				else 
					my_lion.c_state++;

				glutTimerFunc(100, Stop, 1);
			}	
		}
		if (left) {
			if(my_lion.y==bottom){
				my_lion.x -= 1;
				my_lion.velocity -= 0.05;
				if(my_lion.velocity>0)
					my_lion.velocity=0;
				// state change
				if (my_lion.c_state == 3) {
					my_lion.state = (my_lion.state+1)%8;
					my_lion.c_state = 0;
				}
				else 
					my_lion.c_state++;
				glutTimerFunc(100, Stop, 1);
			}
		}
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		switch(viewmode) {
		case 1:
			gluPerspective(60,2,10,1000);
			gluLookAt(my_lion.x,my_lion.y,0,my_lion.x+500,my_lion.y,0,0,1,0);
			break;
		case 2:
			gluPerspective(60,2,10,1000);
			gluLookAt(my_lion.x-100,60,0,my_lion.x+500,50,0,0,1,0);
			break;
		case 3:
			glRotatef(90,-1,0,0);
			glOrtho(-50, 50+mapsize, 0, 100, -mapsize/4, -mapsize/4+50+mapsize/2);
			break;
		case 4:
			glOrtho(-50, 50+mapsize, -mapsize/4, -mapsize/4+50+mapsize/2, -50, 50);
			break;
		case 5:
			glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
			break;
		}
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();	
		glutPostRedisplay();

		//translate Loop and draw 3D fireloop
		glPushMatrix();
		glTranslatef(translateLoop,0,0);
		my_loop.display_3d_fireloop(my_lion.x, translateLoop);
		glPopMatrix();

		//draw lion
		glPushMatrix();
		glTranslatef(my_lion.x,my_lion.y,0);
		my_lion.drawLion(lion_1_texture, lion_2_texture);
		glPopMatrix();

		// draw rock
		glEnable (GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, rock_texture);
		glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glPushMatrix();
		my_rock.display_rock();
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CCW);  
		glEnable(GL_CULL_FACE);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFlush();
		glutSwapBuffers();
	}
	
	else {
		my_lion.drawDeath(my_lion, viewmode);
		glFlush();
		glutSwapBuffers();
		Sleep(2000);
		exit(1);
	}
	}
}

float jump_initX = 0;
float jump_upX = 0;
void Jump(int jump_direction){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int keep = 1;
	float print_x;

	//jump forward
	if(jump_direction == 1){
		my_lion.jump_state=1;
		print_x = my_lion.x-jump_initX;
		my_lion.x += 1;
	}
	//jumb backward
	else if(jump_direction == -1){
		my_lion.jump_state=1;
		print_x = jump_initX-my_lion.x;
		my_lion.x -= 1;
	}
	//jump up
	else{
		my_lion.jump_state=1;
		if(jump_upX<81)
			jump_upX+=1;
		print_x = jump_upX;
	}
	switch(viewmode) {
	case 1:
		gluPerspective(60,2,10,1000);
		gluLookAt(my_lion.x,my_lion.y,0,my_lion.x+500,my_lion.y,0,0,1,0);
		break;
	case 2:
		gluPerspective(60,2,10,1000);
		gluLookAt(my_lion.x-100,60,0,my_lion.x+500,50,0,0,1,0);
		break;
	case 3:
		glRotatef(90,-1,0,0);
		glOrtho(-50, 50+mapsize, 0, 100, -mapsize/4, -mapsize/4+50+mapsize/2);
		break;
	case 4:
		glOrtho(-50, 50+mapsize, -mapsize/4, -mapsize/4+50+mapsize/2, -50, 50);
		break;
	case 5:
		glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
		break;
	}
	
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();	
	glutPostRedisplay();

	my_lion.y = bottom + 60 - 0.066*(print_x-30)*(print_x-30);

	if (my_lion.y<bottom) {
		keep=0;
		my_lion.state=2;
		my_lion.jump_state = 0;
		my_lion.y=bottom;
		jump_upX=0;
		glutTimerFunc(1, Stop, 1);
	}
	if(keep)
		glutTimerFunc(700/60, Jump, jump_direction);
}

void specialkeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if(my_lion.y==bottom&&startfresh==1) {
			jump_initX = my_lion.x;
			bool right = ((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000);
			bool left = ((GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000);
			if (right)
				glutTimerFunc(700/60,Jump,1);
			else if (left)
				glutTimerFunc(700/60,Jump,-1);
			else
				glutTimerFunc(700/60,Jump,0);
		}
		break;
	}

}

void keyboard(unsigned char key, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (key) {
	case '1':
		viewmode = 1;
		gluPerspective(60,2,10,1000);
		gluLookAt(my_lion.x,my_lion.y,0,my_lion.x+500,my_lion.y,0,0,1,0);
		break;
	case '2':
		viewmode = 2;
		gluPerspective(60,2,10,1000);
		gluLookAt(my_lion.x-100,60,0,my_lion.x+500,50,0,0,1,0);
		break;
	case '3':
		viewmode = 3;
		glRotatef(90,-1,0,0);
		glOrtho(-50, 50+mapsize, 0, 100, -mapsize/4, -mapsize/4+50+mapsize/2);
		break;
	case '4':
		viewmode = 4;
		glOrtho(-50, 50+mapsize, -mapsize/4, -mapsize/4+50+mapsize/2, -50, 50);
		break;
	case '5':
		viewmode = 5;
		glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
		break;
	case 13:
		start++;
		break;
	case 'q':
		shadingmode = 0;
		break;
	case 'w':
		shadingmode = 1;
		break;
	case 'e':
		shadingmode = 2;
		break;
	case 'r':
		shadingmode = 3;
		break;
	case 'a':
		lightsource = 0;
		break;
	case 's':
		lightsource = 1 ;
		break;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	// TODO
	// gluOrtho2D update
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50+my_lion.x, 150+my_lion.x, 0, 100, -50, 50);
}

void moveObjects(int) {
	if(stage<3)
		translateLoop-=1;
	else
		translateLoop-=(float)stage/2+(float)(stage%2)/2;
	glutPostRedisplay();
	glutTimerFunc(2000/60,moveObjects,1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Circus Charlie");
	init();

	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);

	glutTimerFunc(2000/60,moveObjects,1);
	glutMainLoop();
}
