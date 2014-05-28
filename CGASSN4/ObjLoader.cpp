#include "ObjLoader.h"

// 필요한 코드만 남기고 전체 수정
// 수정시 참고한 사이트
// http://blog.naver.com/PostView.nhn?blogId=bluefallsky&logNo=140119335319
// http://3dapi.com/et01_opengl/

void model::draw(int shadingmode, float rockscale)
{
	if(loaded)
	{
		fnode * fcursor = ffirst;
		int nCnt = 0;
		if (shadingmode == 0)
			glBegin(GL_LINE_LOOP);
		else
			glBegin(GL_TRIANGLES);
		while(fcursor != NULL)
		{
			nCnt++;
			//glColor3f(150.0/255, 75.0/255, 0);
			glColor3f(1,1,1);
			glTexCoord2f(fcursor->data.u[0], fcursor->data.v[0]);
			glVertex3f(fcursor->data.x[0]+(vertexnormallist[fcursor->data.v1_index].n_x)*rockscale,
				fcursor->data.y[0]+(vertexnormallist[fcursor->data.v1_index].n_y)*rockscale, 
				fcursor->data.z[0]+(vertexnormallist[fcursor->data.v1_index].n_z)*rockscale);

			glTexCoord2f(fcursor->data.u[1], fcursor->data.v[1]);
			glVertex3f(fcursor->data.x[1]+(vertexnormallist[fcursor->data.v2_index].n_x)*rockscale,
				fcursor->data.y[1]+(vertexnormallist[fcursor->data.v2_index].n_y)*rockscale, 
				fcursor->data.z[1]+(vertexnormallist[fcursor->data.v2_index].n_z)*rockscale);

			glTexCoord2f(fcursor->data.u[2], fcursor->data.v[2]);
			glVertex3f(fcursor->data.x[2]+(vertexnormallist[fcursor->data.v3_index].n_x)*rockscale,
				fcursor->data.y[2]+(vertexnormallist[fcursor->data.v3_index].n_y)*rockscale, 
				fcursor->data.z[2]+(vertexnormallist[fcursor->data.v3_index].n_z)*rockscale);
			fcursor = fcursor->next;;
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
	//data loading이 끝난 후, vertex normal vector를 계산한다
	cal_VertexNormal();
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

	temp->data.v1_index = v_index[0]-1;
	temp->data.v2_index = v_index[1]-1;
	temp->data.v3_index = v_index[2]-1;
	vertexnormallist[v_index[0]-1].facenum++;
	vertexnormallist[v_index[0]-1].facelist.push_back(*temp);

	vertexnormallist[v_index[1]-1].facenum++;
	vertexnormallist[v_index[1]-1].facelist.push_back(*temp);

	vertexnormallist[v_index[2]-1].facenum++;
	vertexnormallist[v_index[2]-1].facelist.push_back(*temp);

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

void model::cal_VertexNormal() {
	for (int i=0; i<98; i++) {
		vertexnormallist[i].n_x = 0;
		vertexnormallist[i].n_y = 0;
		vertexnormallist[i].n_z = 0;
		for (int j=0; j<vertexnormallist[i].facenum; j++) {
			float v1_x = vertexnormallist[i].facelist[j].data.x[1]-vertexnormallist[i].facelist[j].data.x[0];
			float v1_y = vertexnormallist[i].facelist[j].data.y[1]-vertexnormallist[i].facelist[j].data.y[0];
			float v1_z = vertexnormallist[i].facelist[j].data.z[1]-vertexnormallist[i].facelist[j].data.z[0];
			float v2_x = vertexnormallist[i].facelist[j].data.x[2]-vertexnormallist[i].facelist[j].data.x[1];
			float v2_y = vertexnormallist[i].facelist[j].data.y[2]-vertexnormallist[i].facelist[j].data.y[1];
			float v2_z = vertexnormallist[i].facelist[j].data.z[2]-vertexnormallist[i].facelist[j].data.z[1];
			
			// 현재 관찰하고 있는 면의 normal vector 성분
			float f_nx = v1_y*v2_z - v1_z*v2_y;
			float f_ny = v1_z*v2_x - v1_x*v2_z;
			float f_nz = v1_x*v2_y - v1_y*v2_z;
			float vectorsize = sqrt((f_nx)*(f_nx)+(f_ny)*(f_ny)+(f_nz)*(f_nz));
			f_nx = f_nx/vectorsize;
			f_ny = f_ny/vectorsize;
			f_nz = f_nz/vectorsize;

			//계산한 현재 관찰 면의 normal vector 성분을 vertex normal vector 성분에 더한다
			vertexnormallist[i].n_x += f_nx;
			vertexnormallist[i].n_y += f_ny;
			vertexnormallist[i].n_z += f_nz;
		}
		// 각 면에 대한 계산 값이 모두 더해지면, 그 합을 인접한 face의 수로 나눈다
		vertexnormallist[i].n_x = vertexnormallist[i].n_x/vertexnormallist[i].facenum;
		vertexnormallist[i].n_y = vertexnormallist[i].n_y/vertexnormallist[i].facenum;
		vertexnormallist[i].n_z = vertexnormallist[i].n_z/vertexnormallist[i].facenum;
	}
}