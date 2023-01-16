#pragma once
#define real double

real linear(real x1,real x2, real y1, real y2, real query);
real quadraticRight(real x0, real x1, real x2, real y0, real y1, real y2, real query);
real quadraticLeft(real x1, real x2, real x3, real y1, real y2, real y3, real query);
real cubicSpline(real x0, real x1, real x2, real x3, real y0, real y1, real y2, real y3, real query);
void spline(real *x0, real *x1, real *x2, real *x3, real *y0, real *y1, real *y2, real *y3, real query, real *&result);
real splineNG(real x[], real y[], real query);
real splineNG_depl(real x[], real y[], real query);