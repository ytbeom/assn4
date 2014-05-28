// http://junpp.egloos.com/viewer/2410743
// 헤더파일, 소스파일 분리작업 거침

#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <vector>
#include <math.h>

#ifndef OBJLOADER_H
#define OBJLOADER_H

struct vertex
{
	float x, y, z;
	unsigned int index;	
};

struct texcoord
{
	float u, v;
	unsigned int index;
};

struct face
{
	float x[3], y[3], z[3];		//vertices
	float u[3], v[3];			//text coords
	int v1_index, v2_index, v3_index;		//vertex indexes
};

class model
{
private:
	int faces;
	int coords;
	bool loaded;
	char filename[256];
	unsigned int vindex;
	unsigned int tindex;
	
	struct vnode
	{
		vertex data;
		vnode * next;
	};
	struct tnode
	{
		texcoord data;
		tnode * next;
	};
	struct fnode
	{
		face data;
		fnode * next;
	};
	struct vertexnormal
	{
		int facenum;
		std::vector<fnode> facelist;
		// normal vector의 성분들
		float n_x;
		float n_y;
		float n_z;
	};
	vnode * vfirst;
	vnode * vcurrent;
	tnode * tfirst;
	tnode * tcurrent;
	fnode * ffirst;
	fnode * fcurrent;
	vertexnormal vertexnormallist[98];
	
	bool loadVertex(FILE *);
	bool loadTexCoord(FILE *);
	bool loadFace(FILE *);
	
public:
	bool Load(char * objfile, char * mtlname);
	model()
	{
		vfirst=vcurrent= NULL;
		tfirst=tcurrent= NULL;
		ffirst=fcurrent= NULL;
		vindex=tindex=1;
		for (int i=0; i<98; i++)
			vertexnormallist[i].facenum = 0;
	}
	void draw(int shadingmode, float rockscale);
	float Y(float, float){return 0.0;}
	bool Collide(float, float, float,float, float, float){return false;}
	void cal_VertexNormal();
};

#endif OBJLOADER_H