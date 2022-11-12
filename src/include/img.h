#pragma once

#include "matrix.h"
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <GL/glut.h>
typedef struct {
	Matrix* img_data;
	int label;
}Img;
struct dataset_info{
    int total_num_of_files;
}ds_info;
struct input_info{
    int width,height,kind;
}info;


Img** csv_to_imgs(char* file_string, int number_of_imgs);
Img** bin_to_imgs(char* file_string);
void img_print(Img* img);
void img_free(Img *img);
void imgs_free(Img **imgs, int n);
double rgb2gray_pixel(int r, int g, int b);

