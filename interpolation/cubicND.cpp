#include"values.h"
#include"interpolation1D.h"

int pow4(int exp){
	int result=1;
	for(int i=0; i<exp; i++)
		result*=4;
	return result;
}

real cubicRecursion(int n, real valuesY[], int index[], real query[], int size[], real *axes[], int dimX){
	if(n==0)
		return valuesY[0];

	int pow = pow4(n-1);
	real* aux = new real[pow];
	for(int i=0; i<pow; i++){
		real valX[4], valY[4];
		for(int k=0; k<4; k++){
			valX[k]=getValueNG(axes[dimX-n],size[dimX-n],index[dimX-n]+k-1);
			valY[k]=valuesY[i*4+k];
		}
		if(n == 1)
			aux[i] = splineNG_depl(valX, valY, query[dimX-n]);
		else aux[i] = splineNG(valX, valY, query[dimX-n]);
	}
	real result = cubicRecursion(n-1, aux, index, query, size, axes, dimX);
	delete[] aux;
	return result;
}

real cubicNDinit(int n, int index[], real query[], real y[], int size[], real *axes[], int indexArray[], int dimX){

	int pow = pow4(n);
	int* coordinatesX = new int[n];

	for (int c = 0; c < pow; c++){
		for (int i = 0; i < n; i++){
			coordinatesX[i] = index[i] + (c >> (2 * i)) % 4 - 1;
		}
		indexArray[c] = getYindex(coordinatesX, y, size, dimX);
	}

	delete[] coordinatesX;
	return 0;
}

real cubicND(int n, int index[], real query[], real y[], int size[], real *axes[], int dimX){

	int pow = pow4(n);
	int* coordinatesX = new int[n];

	real* valuesY = new real[pow];

	for (int c = 0; c < pow; c++){
		for (int i = 0; i < n; i++){
			coordinatesX[i] = index[i] + (c >> (2*i)) % 4 - 1;
		}
		int index = getYindex(coordinatesX, y, size, dimX);
		real value = NAN1;
		if (index != -1)
			value = y[index];
		valuesY[c] = value;
	}

	real res = cubicRecursion(n, valuesY, index, query, size, axes, dimX);
    delete[] valuesY;
    delete[] coordinatesX;
	return res;
}

real cubicND2(int n, int index[], real query[], real y[], int size[], real *axes[], int indexArray[], int dimX){

	int pow = pow4(n);

	real* valuesY = new real[pow];

    for (int c = 0; c < pow; c++){
        real value = NAN1;
        if (indexArray[c] != -1)
            value = y[indexArray[c]];
        valuesY[c] = value;
    }

	real res = cubicRecursion(n, valuesY, index, query, size, axes, dimX);
	delete[] valuesY;
	return res;
}