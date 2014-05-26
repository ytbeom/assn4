#include "rock.h"
#include "BitmapLoader.h"

Rock::Rock(int jumplength){
	RockList.push_back((rand()%2+1)*jumplength*2); 
}

void Rock::init(int _jumplength, float mapsize, int stage){
	// ���� ����/��ġ ���� (���� map �ȿ� �ְԲ�)
	rockmodel.Load("tri_rock.obj","tri_rock.mtl");
	RockList.clear();
	RockList.push_back((rand()%2+1)*_jumplength*2);
	for (int i=0; i<(mapsize/_jumplength); i++) {
		 // �� ������ 1*jumplength~2*jumplength �� ������ ���� �׾Ƹ��� ����
		int position = RockList[i]+((rand()%(6-stage)+1)*_jumplength*2);
		if (position < mapsize*2)
			RockList.push_back(position);
		else
			break;
	}
	NumofRock = RockList.size();
}

void Rock::display_rock() {
	// ������ �׸��� �κ�
	for (int i = 0; i < NumofRock; i++) {
		glPushMatrix();
		glTranslatef(RockList[i]/2,15,6);
		glScalef(6.0,6.0,6.0);
		rockmodel.draw();
		glPopMatrix();
	}
}