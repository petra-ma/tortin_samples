#include"interpolation1D.h"
#include"values.h"

int pow2(int exp){
	int result=1;
	for(int i=0; i<exp; i++)
		result*=2;
	return result;
}

real linearRecursion(int n, real array[], int index[], real query[], real *axes[], int dimX){
	if(n==0)
		return array[0];

	int pow = pow2(n-1);
	real* aux = new real[pow];
	for(int i=0; i<pow; i++){
		aux[i] = linear(axes[dimX-n][index[dimX-n]],axes[dimX-n][index[dimX-n]+1],array[i*2],array[i*2+1],query[dimX-n]);
	}
	real result = linearRecursion(n-1, aux, index, query, axes, dimX);
	delete[] aux;
	return result;
}

real linearND(int n, int index[], real query[], real y[], int size[], real *axes[], int dimX){
	int pow = pow2(n);
	real* aux = new real[pow];
	int* indexes = new int[n];

	for (int c=0; c<pow; c++){
		for (int i = 0; i < n; i++){
			indexes[i] = index[i] + (c>>i) % 2;
		}
		aux[c] = getY(indexes, y, size, dimX);
	}

	real res = linearRecursion(n, aux, index, query, axes, dimX);
	delete[] aux;
	delete[] indexes;
	return res;
}
