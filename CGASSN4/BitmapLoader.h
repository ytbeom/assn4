#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

GLubyte * LoadDIBitmap (const char *filename, BITMAPINFO **info);

#endif BITMAPLOADER_H