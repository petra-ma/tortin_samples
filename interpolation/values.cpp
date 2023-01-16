#include<iostream>
#include"values.h"

real getY(int indexes[], real y[], int size[], int dimX){

	int index = 0;
	int factor = 1;

	for (int i=dimX-1;i>=0;i--){
		index += indexes[i]*factor;
		factor *= size[i];
		if(indexes[i]>=size[i] || indexes[i]<0)
			return NAN1;
	}

	return y[index];
}

int getYindex(int indexes[], real y[], int size[], int dimX){

	int index = 0;
	int factor = 1;

	for (int i=dimX-1;i>=0;i--){
		index += indexes[i]*factor;
		factor *= size[i];
		if(indexes[i]>=size[i] || indexes[i]<0)
			return -1;
	}

	return index;
}

int findIndex(int j, real query[], int size[], real *axes[]){

	for (int i=1;i<=size[j]-1;i++)
		if (axes[j][i] >= query[j]) 
			return i-1;

	return 0;
}

real* getY(int i1, int i2, real y[], int size[]){

	if(i1<0 || i2<0 || i1>=size[0] || i2>=size[1])
		return NULL;

	return &y[i1+size[0]*i2];
}

real* getValue(real axes[], int size, int index){

	if (index < 0) return NULL;
	if (index >= size) return NULL;

	return axes+index;
}

real getYNG(int i1, int i2, real y[], int size[]){

	if(i1<0 || i2<0 || i1>=size[0] || i2>=size[1])
		return NAN1;

	return y[i1+size[0]*i2];
}

real getValueNG(real axes[], int size, int index){

	if (index < 0) return NAN1;
	if (index >= size) return NAN1;

	return axes[index];
}