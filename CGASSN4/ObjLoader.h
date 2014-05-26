// http://junpp.egloos.com/viewer/2410743
// 헤더파일, 소스파일 분리작업 거침

#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

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
	float a[3], b[3], c[3];		//normals
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
	vnode * vfirst;
	vnode * vcurrent;
	tnode * tfirst;
	tnode * tcurrent;
	fnode * ffirst;
	fnode * fcurrent;
	
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
	}
	void draw();
	float Y(float, float){return 0.0;}
	bool Collide(float, float, float,float, float, float){return false;}
};

#endif OBJLOADER_H