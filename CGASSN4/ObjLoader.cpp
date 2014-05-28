#include "ObjLoader.h"

// 필요한 코드만 남기고 전체 수정
// 수정시 참고한 사이트
// http://blog.naver.com/PostView.nhn?blogId=bluefallsky&logNo=140119335319
// http://3dapi.com/et01_opengl/

void model::draw()
{
	if(loaded)
	{
		fnode * fcursor = ffirst;
		int nCnt = 0;
		glBegin(GL_TRIANGLES);
		while(fcursor != NULL)
		{
			nCnt++;
			//glColor3f(150.0/255, 75.0/255, 0);
			glColor3f(1,1,1);
			glTexCoord2f(fcursor->data.u[0], fcursor->data.v[0]);
			glVertex3f(fcursor->data.x[0], fcursor->data.y[0], fcursor->data.z[0]);

			glTexCoord2f(fcursor->data.u[1], fcursor->data.v[1]);
			glVertex3f(fcursor->data.x[1], fcursor->data.y[1], fcursor->data.z[1]);

			glTexCoord2f(fcursor->data.u[2], fcursor->data.v[2]);
			glVertex3f(fcursor->data.x[2], fcursor->data.y[2], fcursor->data.z[2]);
			fcursor = fcursor->next;
		}
		glEnd();
	}
}

bool model::Load(char * objfile, char * mtlname)
{
	char buffer[256];
	strcpy(filename, objfile);
	FILE * file = fopen(filename, "r");

	if(file == NULL)
	{
		//MessageBox(NULL, objfile, "Model file not found:", MB_OK);
		return false;
	}
	while(fscanf(file, "%s", buffer) != EOF)
	{
		if(!strcmp("#", buffer))
			continue;
		if(!strcmp("mtllib", buffer))
			continue;
		if(!strcmp("v", buffer))loadVertex(file);
		if(!strcmp("vt", buffer))loadTexCoord(file);
		if(!strcmp("f", buffer))loadFace(file);
		if(!strcmp("s", buffer));
			continue; 
		if(!strcmp("usemtl", buffer));
			continue;
	}
	fclose(file);
	loaded = true;
	return true;
}

bool model::loadVertex(FILE * file)
{
	vnode * temp = new vnode();
	fscanf(file, "%f %f %f", &temp->data.x, &temp->data.y, &temp->data.z);
	temp->data.index = vindex;
	if(vfirst == NULL)
	{
		vfirst = temp;
		vcurrent = temp;
		vfirst->next = NULL;
	}
	else
	{
		vcurrent->next = temp;
		vcurrent = vcurrent->next;
		vcurrent->next = NULL;
	}
	vindex++;
	return true;
}

bool model::loadTexCoord(FILE * file)
{
	tnode * temp = new tnode();
	fscanf(file, "%f %f", &temp->data.u, &temp->data.v);
	temp->data.index = tindex;
	temp->next = NULL;
	if(tfirst == NULL)
	{
		tfirst = temp;
		tcurrent = temp;
	}
	else
	{
		tcurrent->next = temp;
		tcurrent = tcurrent->next;
	}
	tindex++;
	return true;
}

bool model::loadFace(FILE * file)
{
	fnode * temp = new fnode();
	vnode * vcursor = vfirst;
	tnode * tcursor = tfirst;
	unsigned int v_index[3], t_index[3];
	for(int i = 0; i < 3; i++)
	{
		vcursor = vfirst;
		tcursor = tfirst;
		fscanf(file, "%i/%i", &v_index[i], &t_index[i]);

		for(int v = 1; v != v_index[i]; v++)
			vcursor = vcursor->next;
		temp->data.x[i] = vcursor->data.x;
		temp->data.y[i] = vcursor->data.y;
		temp->data.z[i] = vcursor->data.z;

		for(int k = 1; k != t_index[i]; k++)
			tcursor = tcursor->next;
		temp->data.u[i] = tcursor->data.u;
		temp->data.v[i] = tcursor->data.v;
	}

	temp->next = NULL;
	if(ffirst == NULL)
	{
		ffirst = temp;
		fcurrent = temp;
		ffirst->next = NULL;
	}
	else
	{
		fcurrent->next = temp;
		fcurrent = fcurrent->next;
		fcurrent->next = NULL;
	}
	faces++;
	return true;
}