#include "include/matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <stdint.h>
#define MAXCHAR 100




Matrix* matrix_create(int row, int col) {
	Matrix *matrix = malloc(sizeof(Matrix));
	matrix->rows = row;
	matrix->cols = col;
	matrix->entries = malloc(row * sizeof(double*));
	for (int i = 0; i < row; i++) {
		matrix->entries[i] = malloc(col * sizeof(double));
	}
	return matrix;
}



void matrix_fill(Matrix *m, int n) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->entries[i][j] = n;
		}
	}
}

void matrix_free(Matrix *m) {
	for (int i = 0; i < m->rows; i++) {
		free(m->entries[i]);
	}
	free(m);
	m = NULL;
}

void matrix_print(Matrix* m) {
	printf("Rows: %d Columns: %d\n", m->rows, m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			printf("%1.3f ", m->entries[i][j]);
		}
		printf("\n");
	}
}

void matrix_size(Matrix* m) {
	printf("Rows: %d Columns: %d\n", m->rows, m->cols);
}

Matrix* matrix_copy(Matrix* m) {
	Matrix* mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			mat->entries[i][j] = m->entries[i][j];
		}
	}
	return mat;
}


void matrix_save(Matrix* m, char* file_string) {
	FILE* file = fopen(file_string, "w");
	//fprintf(file, "%d\n", m->rows);
	//fprintf(file, "%d\n", m->cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fprintf(file, "%.6f ", m->entries[i][j]);
		}
		if(i!=m->rows-1)fprintf(file, ",");
	}
	printf("Successfully saved matrix to %s\n", file_string);
	fclose(file);
}


void matrix_save_bin(Matrix* m,char *filesting) {
	char buffer[100];
	sprintf(buffer,"%s",filesting);
	FILE* file = fopen(buffer, "wb");
	fwrite(&m->rows,sizeof(int),1,file);
	fwrite(&m->cols,sizeof(int),1,file);
	for(int i=0; i<m->rows;i++){
		for(int j=0;j<m->cols;j++){
			fwrite(&m->entries[i][j],sizeof(double),1,file);
		}
	}

	fwrite(&m,sizeof(m->entries)*sizeof(double),1,file);
	printf("Successfully saved matrix to %s\n", buffer);
	fclose(file);
}




Matrix* matrix_load(char* file_string) {
	FILE* file = fopen(file_string, "r");
	char entry[MAXCHAR]; 
	fgets(entry, MAXCHAR, file);
	int rows = atoi(entry);
	fgets(entry, MAXCHAR, file);
	int cols = atoi(entry);
	Matrix* m = matrix_create(rows, cols);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			fgets(entry, MAXCHAR, file);
			m->entries[i][j] = strtod(entry, NULL);
		}
	}
	printf("Sucessfully loaded matrix from %s\n", file_string);
	fclose(file);
	return m;
}





Matrix* matrix_load_bin(char* file_string) {
	FILE* file = fopen(file_string, "rb");
	int rows;
	fread(&rows,sizeof(int),1,file);
	int cols;
	fread(&cols,sizeof(int),1,file);
	Matrix* m = matrix_create(rows, cols);
	m->rows=rows;
	m->cols=cols;
	double inp;
	for(int i=0; i<rows;i++){
		for(int j=0;j<cols;j++){
			fread(&inp,sizeof(double),1,file);
			m->entries[i][j]=inp;
		}
	}
	//fread(&m->entries,sizeof(m->entries),1,file);
	printf("Sucessfully loaded matrix from %s\n", file_string);
	fclose(file);
	return m;
}

double uniform_distribution(double low, double high) {
	double difference = high - low; // The difference between the two
	int scale = 10000;
	int scaled_difference = (int)(difference * scale);
	return low + (1.0 * (rand() % scaled_difference) / scale);
}

void matrix_randomize(Matrix* m, int n) {
	// Pulling from a random distribution of 
	// Min: -1 / sqrt(n)
	// Max: 1 / sqrt(n)
	double min = -1.0 / sqrt(n);
	double max = 1.0 / sqrt(n);
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			m->entries[i][j] = uniform_distribution(min, max);
		}
	}
}

int matrix_argmax(Matrix* m) {
	// Expects a Mx1 matrix
	double max_score = 0;
	int max_idx = 0;
	for (int i = 0; i < m->rows; i++) {
		if (m->entries[i][0] > max_score) {
			max_score = m->entries[i][0];
			max_idx = i;
		}
	}
	return max_idx;
}

Matrix* matrix_flatten(Matrix* m, int axis) {
	// Axis = 0 -> Column Vector, Axis = 1 -> Row Vector
	Matrix* mat;
	if (axis == 0) {
		mat = matrix_create(m->rows * m->cols, 1);
	} else if (axis == 1) {
		mat = matrix_create(1, m->rows * m->cols);
	} else {
		printf("Argument to matrix_flatten must be 0 or 1");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (axis == 0) mat->entries[i * m->cols + j][0] = m->entries[i][j];
			else if (axis == 1) mat->entries[0][i * m->cols + j] = m->entries[i][j];
		}
	}
	return mat;
}

void matrix_unflatten_print(Matrix* m, int rows, int cols) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <cols; j++) {
			printf("%f ",m->entries[i+j][0]);
		}
		printf("\n");
	}
}



double pix (double value, double max)
{	int count=0;
    while(max<256.0){
		max*=1.01;
		++count;;
	}
	for(int i=0;i<count;i++){
		value*=1.01;
		//printf("%lf\n",value);

	}
    return (value);
}

Matrix* matrix_unflatten(Matrix* m, int rows, int cols) {
	Matrix* m_ret=matrix_create(rows,cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <cols; j++) {
			m_ret->entries[i][j] = m->entries[i+j][0];
		}
	}
	return m_ret;
}


pixel_t* pixel_at(bitmap_t* bitmap, int x, int y){
    return bitmap->pixels + bitmap->width * y + x;
}




int matrix_to_png(char *path,Matrix* m,double max){


    bitmap_t fruit;
    int x;
    int y;
    int status;

    status = 0;

    /* Create an image. */

    fruit.width = m->cols;
    fruit.height = m->rows;

    fruit.pixels = calloc (fruit.width * fruit.height, sizeof (pixel_t));

    if (! fruit.pixels) {
	return -1;
    }

    for (y = 0; y < fruit.height; y++) {
        for (x = 0; x < fruit.width; x++) {
            pixel_t * pixel = pixel_at (& fruit, x, y);
            pixel->val = m->entries[x][y]; 
        }
    }
	bitmap_t *bitmap=&fruit;


    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    x=0;
	y=0;
    png_byte ** row_pointers = NULL;
    /* "status" contains the return value of this function. At first
       it is set to a value which means 'failure'. When the routine
       has finished its work, it is set to a value which means
       'success'. */
    status = -1;
    /* The following number is set by trial and error only. I cannot
       see where it it is documented in the libpng manual.
    */
    int pixel_size = 3;
    int depth = 8;
    
    fp = fopen (path, "wb");
    if (! fp) {
        goto fopen_failed;
    }

    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }
    
    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }
    
    /* Set up error handling. */

    if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }
    
    /* Set image attributes. */

    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->width,
                  bitmap->height,
                  depth,
                  PNG_COLOR_TYPE_GRAY,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);
    
    /* Initialize rows of PNG. */

    row_pointers = png_malloc (png_ptr, bitmap->height * sizeof (png_byte *));
    for (y = 0; y < bitmap->height; y++) {
        png_byte *row = 
            png_malloc (png_ptr, sizeof (uint8_t) * bitmap->width * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->width; x++) {
            pixel_t * pixel = pixel_at (bitmap, x, y);
			printf("%lf\n",pixel->val);
            *row++ =pixel->val;

        }
    }
    
    /* Write the image data to "fp". */

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    /* The routine has successfully written the file, so we set
       "status" to a value which indicates success. */

    status = 0;
    
    for (y = 0; y < bitmap->height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);
    
 png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);
 png_create_write_struct_failed:
    fclose (fp);
 fopen_failed:
    return status;
}
