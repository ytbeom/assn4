//http://junpp.egloos.com/viewer/2410743
//헤더파일, 소스파일 분리작업 거침

#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

#ifndef OBJLOADER_H
#define OBJLOADER_H

#define Debug(x){MessageBox(NULL, x, "Debug:", MB_OK);}


// Define targa header.
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)

struct vertex
{
	float x, y, z;
	unsigned int index;	
};
typedef vertex normal;
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

struct material
{	
	char name[32];
	int illum;
	char map_Kd[32];
	float Ni;
	float Kd[3];
	float Ka[3];
	float Tf[3];
	unsigned int texture;
};

class model
{
private:
	int faces;
	int coords;
	int normals;
	bool loaded;
	char mtllib[256];
	char filename[256];
	char directory[256];
	unsigned int vindex;
	unsigned int tindex;
	unsigned int nindex;
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

	struct mnode
	{
		material data;
		mnode * next;
	};
	struct fnode
	{
		face data;
		mnode * mat;
		fnode * next;
	};

	vnode * vfirst;
	vnode * vcurrent;
	tnode * tfirst;
	tnode * tcurrent;
	vnode * nfirst;
	vnode * ncurrent;
	fnode * ffirst;
	fnode * fcurrent;
	mnode * mfirst;
	mnode * mcurrent;
	void skipComment(FILE *);

	bool loadVertex(FILE *);
	bool loadTexCoord(FILE *);
	bool loadNormal(FILE *);
	bool loadFace(FILE *);
	bool loadMaterialLib(FILE *);
	void loadMaterials(FILE *);
//	void loadBmpTexture(char* fileName, GLuint* texture);
//	void loadTGAtexture(char* fileName, GLuint* texture);
	void useMaterial(FILE *);

/*
	AUX_RGBImageRec *LoadBMPFile(char *filename)
	{
		FILE *hFile = NULL;

		if(!filename) return NULL;

		hFile = fopen(filename, "r");

		if(hFile) {
			fclose(hFile);
			return auxDIBImageLoad(filename);
		}

		return NULL;
	}

*/

public:
	bool Load(char * objfile, char * mtlname);
	model()
	{
		vfirst=vcurrent= NULL;
		tfirst=tcurrent= NULL;
		nfirst=ncurrent= NULL;
		ffirst=fcurrent= NULL;
		mfirst=mcurrent= NULL;
		vindex=tindex=nindex= 1;
	}
	void draw();
	float Y(float, float){return 0.0;}
	bool Collide(float, float, float,float, float, float){return false;}
};

#endif OBJLOADER_H