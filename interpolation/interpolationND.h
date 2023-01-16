#pragma once
#include"values.h"

real cubicND(int n, int index[], real query[], real y[], int size[], real *axes[], int dimX);
real cubicND2(int n, int index[], real query[], real y[], int size[], real *axes[], int indexArray[], int dimX);
real cubicNDinit(int n, int index[], real query[], real y[], int size[], real *axes[], int indexArray[], int dimX);
real linearND(int n, int index[], real query[], real y[], int size[], real *axes[], int dimX);
real splineNG(real x0, real x1, real x2, real x3, real y0, real y1, real y2, real y3, real query);