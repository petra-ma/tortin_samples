#pragma once
#include<limits>
#include<iostream>

#define NAN1 std::numeric_limits<real>::quiet_NaN()
#define real double

real getY(int indexes[], real y[], int size[], int dimX);
int getYindex(int indexes[], real y[], int size[], int dimX);
int findIndex(int j, real query[], int size[], real *axes[]);
real* getY(int i1, int i2, real y[], int size[]);
real* getValue(real axes[], int size, int index);
real getValueNG(real axes[], int size, int index);