#include<iostream>
#include"values.h"
#include<cmath>
#include<math.h>

using namespace std;

bool isnan1(real nan){

	if(nan != nan)
		return true;

	return false;
}

real linear(real x1,real x2, real y1, real y2, real query){

	if (isnan1(y2)) return y1;
	return y1 + (y2-y1)*(query-x1)/(x2-x1);
}

real quadraticRight(real x0, real x1, real x2, real y0, real y1, real y2, real query){

	real x1d = (y2-y0)/(x2-x0);
	real dx = x2-x1;
	real b = (y2 - x1d*dx - y1)/(dx*dx);
	real q = query - x1;
	real result = b*q*q + x1d*q + y1;

	return result;
}

real quadraticLeft(real x1, real x2, real x3, real y1, real y2, real y3, real query){
	return quadraticRight(-x3,-x2,-x1,y3,y2,y1,-query);
}

real quadraticLeft_depl(real x1, real x2, real x3, real y1, real y2, real y3, real query){

	real a = ((y3-y1)*(x2-x1)+(y1-y2)*(x3-x1))/((x3-x1)*(x1*x1-x2*x2)+(x3*x3-x1*x1)*(x2-x1));
	real b = (y2+a*(x1*x1-x2*x2)-y1)/(x2-x1);
	real c = y1 - a*x1*x1 - b*x1;
	return a*query*query+b*query + c;
}

real computeDerivation(real x0, real x1, real x2, real y0, real y1, real y2){

	real d = (y2-y0)/(x2-x0);
	if(d<0)
		return -computeDerivation(x0, x1, x2, -y0, -y1, -y2);
	if((y1-y0)*(y1-y2)>=0)
		return 0;

	real d1 = (y1-y0)/(x1-x0);
	real d2 = (y2-y1)/(x2-x1);
	if(d1<d)
		d = d1;
	if(d2<d)
		d = d2;
	return d;
}

real cubicSpline(real x0, real x1, real x2, real x3, real y0, real y1, real y2, real y3, real query){

	real x1d = computeDerivation(x0, x1, x2, y0, y1, y2);
	real x2d = computeDerivation(x1, x2, x3, y1, y2, y3);
	real dx = x2-x1;
	real a = (dx*x2d - 2*y2 + x1d*dx + 2*y1)/(dx*dx*dx);
	real b = (y2 - a*dx*dx*dx - x1d*dx - y1)/(dx*dx);
	real q = query - x1;
	return a*q*q*q + b*q*q + x1d*q + y1;
}

void spline(real *x0, real *x1, real *x2, real *x3, real *y0, real *y1, real *y2, real *y3, real query, real *&result){

	if (y1 == NULL) result = NULL;
	else if (y0 == NULL && y3 == NULL) *result = linear(*x1,*x2,*y1,*y2,query);
	else if (y0 == NULL) *result = quadraticLeft(*x1, *x2, *x3, *y1, *y2, *y3, query);
	else if (y3 == NULL) *result = quadraticRight(*x0, *x1, *x2, *y0, *y1, *y2, query);
	else *result = cubicSpline(*x0, *x1, *x2, *x3, *y0, *y1, *y2, *y3, query);
}

real splineNG(real x[], real y[], real query){
	
	if (isnan1(y[1])) return NAN1;
	else if (isnan1(y[0]) && isnan1(y[2])) return y[1];
	else if (isnan1(y[0]) && isnan1(y[3])) return linear(x[1],x[2],y[1],y[2],query);
	else if (isnan1(y[0])) return quadraticLeft(x[1], x[2], x[3], y[1], y[2], y[3], query);
	else if (isnan1(y[3])) return quadraticRight(x[0], x[1], x[2], y[0], y[1], y[2], query);
	else return cubicSpline(x[0], x[1], x[2], x[3], y[0], y[1], y[2], y[3], query);
}

real splineNG_depl(real x[], real y[], real query){
	
	if (isnan1(y[1])) return NAN1;
	else if (isnan1(y[0]) && isnan1(y[2])) return y[1];
	else if (isnan1(y[0]) && isnan1(y[3])) return linear(x[1],x[2],y[1],y[2],query);
	else if (isnan1(y[0])) return quadraticLeft_depl(x[1], x[2], x[3], y[1], y[2], y[3], query);
	else if (isnan1(y[3])) return quadraticRight(x[0], x[1], x[2], y[0], y[1], y[2], query);
	else return cubicSpline(x[0], x[1], x[2], x[3], y[0], y[1], y[2], y[3], query);
}