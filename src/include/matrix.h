
#pragma once
typedef struct {
	int rows;
	int cols;
	double** entries;

} Matrix;


/* A coloured pixel. */

typedef struct
{
    double val;

}
pixel_t;

/* A picture. */
    
typedef struct
{
    pixel_t *pixels;
    int width;
    int height;
}
bitmap_t;


Matrix* matrix_create(int row, int col);
void matrix_fill(Matrix *m, int n);
void matrix_free(Matrix *m);
void matrix_print(Matrix *m);
void matrix_size(Matrix *m);
Matrix* matrix_copy(Matrix *m);
void matrix_save(Matrix* m, char* file_string);
Matrix* matrix_load(char* file_string);
void matrix_randomize(Matrix* m, int n);
int matrix_argmax(Matrix* m);
Matrix* matrix_flatten(Matrix* m, int axis);
Matrix* matrix_load_bin(char* file_string);
void matrix_save_bin(Matrix* m,char* file_string);
void matrix_unflatten_print(Matrix* m, int rows, int cols);

pixel_t* pixel_at (bitmap_t * bitmap, int x, int y);
Matrix* matrix_unflatten(Matrix* m, int rows, int cols);
double pix (double value, double max);
int matrix_to_png(char *path,Matrix* m,double max);
