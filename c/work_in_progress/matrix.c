#include "engine.h"

/////////////////////////////
//basic matrix manipulation//
/////////////////////////////

/*random snippet
	
	T
	|\
	| \
	|  \ M
	|  /
	| /
	|/
	B
	
	y: By -> Ty
	x0 is on BT
	x1 is on BM or on MT
	(x0,y) -> (x1,y)

	x0: Bx -> Tx; x0 += (Tx - Bx)/(Ty - By)
	x1: Bx -> Mx; x1 += (Mx - Bx)/(My - By)
	x1: Mx -> Tx; x1 += (Tx - Mx)/(Ty - My)
	
	z_buffering
	maintain a 2d array of z-values
	that corresponds to our 2d array of pixels (screen)
	when we plot pixels, check the new z-value against what is currently in the z-buffer
*/

int * mx_toint(struct Matrix mx, int *result, int row){
	int i;
	for(i = 0;i < mx.col;i++){
		result[i] = mx_get(mx, row, i + 1);
	}
	return result;	
}


void mx_print(struct Matrix mx){
	int i;
	for(i = 0; i < mx.col; i++){
		printf("[%f] ",mx.x[i]);
	}
	printf("\n");
	for(i = 0; i < mx.col; i++){
		printf("[%f] ",mx.y[i]);
	}
	printf("\n");
	for(i = 0; i < mx.col; i++){
		printf("[%f] ",mx.z[i]);
	}
	printf("\n");
	for(i = 0; i < mx.col; i++){
		//printf("[%f] ",mx.one[i]);
	}
	printf("\n");
}



//init default 4 row point matrix
struct Matrix mx_init(struct Matrix mx, int col){

	mx.col = col;
	mx.type = 'a';

	mx.x = malloc (col * sizeof(double));
	mx.y = malloc (col * sizeof(double));
	mx.z = malloc (col * sizeof(double));
	//mx.one = malloc (col * sizeof(double));

	int i;
	for(i = 0; i < col; i++){
		mx.x[i] = INIT_VALUE; 
		mx.y[i] = INIT_VALUE; 
		mx.z[i] = INIT_VALUE; 
		//mx.one[i] = 1; 
	}

	return mx;
}

struct Matrix mx_init_e(struct Matrix mx, int col){

	mx.col = col;
	mx.type = 'b';
	mx.edge_num = 0;

	mx.x = malloc (col * sizeof(double));
	mx.y = malloc (col * sizeof(double));
	mx.z = malloc (col * sizeof(double));
	//mx.one = malloc (col * sizeof(double));

	int i;
	for(i = 0; i < col; i++){
		mx.x[i] = INIT_VALUE; 
		mx.y[i] = INIT_VALUE; 
		mx.z[i] = INIT_VALUE; 
		//mx.one[i] = 1; 
	}

	return mx;
}

struct Matrix mx_addmatrix(struct Matrix src, struct Matrix dst){
	if(src.type == 'a' && dst.type == 'a'){
		int lim = dst.col + src.col;
		int size = lim * sizeof(double);
		dst.x = realloc(dst.x, size);
		dst.y = realloc(dst.y, size);
		dst.z = realloc(dst.z, size);
		int i;
		int j = 0;
		for(i = dst.col; i < lim; i++){
			dst.x[i] = src.x[j];
			dst.y[i] = src.y[j];
			dst.z[i] = src.z[j];
			j++;
		}
		
		dst.col = lim;
		return dst;
	}else{
		printf("Error: mx_addmatrix, inconsistent matrix type or matrix type not supported\n");

	}
}
//actual math input
double mx_get(struct Matrix mx, int row, int col){
 	if(row == 0 || col == 0){
 		printf("Error: mx_get array start with 1\n");
 	}else if(row == 1){
 		return mx.x[col - 1];
 	}else if(row == 2){
 		return mx.y[col - 1];
 	}else if(row == 3){
 		return mx.z[col - 1];
 	}else if(row == 4){
		//return mx.one[col - 1];
 	}else{
 		printf("Err: mx_get, invalid row_num, returning 0\n");
 		return 0;
 	}
 }

struct Matrix mx_set(struct Matrix mx, int row, int col, double val){
 	if(row == 0 || col == 0){
 		printf("Error: mx_set array start with 1\n");
 	}else if(row == 1){
 		mx.x[col - 1] = val;
 	}else if(row == 2){
 		mx.y[col - 1] = val;
 	}else if(row == 3){
 		mx.z[col - 1] = val;
 	}else if(row == 4){
		printf("Warning: mx_set, modifying constant row\n");
		//mx.one[col - 1] = val;	
 	}else{
 		printf("Err: mx_row, invalid row_num, returning original matrix\n");
 		return mx;
 	}
 	return mx;
 }

 void mx_free(struct Matrix mx){
 	if(mx.type == 'a'){
 		if(mx.col != 0){
 			free(mx.x);
 			free(mx.y);
 			free(mx.z);
 		}
 	}
 }


struct Matrix mx_copy(struct Matrix src, struct Matrix dst){
	if(src.type == 'b'){
		dst = mx_init_e(dst,src.col);
		int i;
		for(i = 0; i < src.col;i ++){
			dst.x[i] = src.x[i];
			dst.y[i] = src.y[i];
			dst.z[i] = src.z[i];

			i++;

			dst.x[i] = src.x[i];
			dst.y[i] = src.y[i];
			dst.z[i] = src.z[i];

			dst.edge_num ++;
		}
	}
	return dst;
}

void mx_export(struct Matrix mx, int color[]){
	if(mx.type == 'a'){

	}else if(mx.type == 'b'){
		drawLine(mx,color);
	}else if(mx.type == 'c'){
		drawLine(mx,color);
	}
}

