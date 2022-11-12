#include "include/img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 10000

Img** csv_to_imgs(char* file_string, int number_of_imgs) {
	FILE *fp;
	Img** imgs = malloc(number_of_imgs * sizeof(Img*));
	char row[MAXCHAR];
	fp = fopen(file_string, "r");

	// Read the first line 
	fgets(row, MAXCHAR, fp);
	int i = 0;
	while (feof(fp) != 1 && i < number_of_imgs) {
		imgs[i] = malloc(sizeof(Img));

		int j = 0;
		fgets(row, MAXCHAR, fp);
		char* token = strtok(row, ",");
		imgs[i]->img_data = matrix_create(28, 28);
		while (token != NULL) {
			if (j == 0) {
				imgs[i]->label = atoi(token);
			} else {
				imgs[i]->img_data->entries[(j-1) / 28][(j-1) % 28] = atoi(token) / 256.0;
			}
			token = strtok(NULL, ",");
			j++;
		}
		i++;
	}
	fclose(fp);
	return imgs;
}


double rgb2gray_pixel(int r, int g, int b){
    return ((0.2126*r) + (0.7152*g) + (0.0722 * b))/256.000000;

}


Img** bin_to_imgs(char* file_string) {
	FILE *fp;

	
	char row[MAXCHAR];
	fp = fopen(file_string, "rb");
	fread(&ds_info,sizeof(ds_info),1,fp);
	Img** imgs = malloc(ds_info.total_num_of_files * sizeof(Img*));
	
	double num;
	int i = 0;
	while (i < ds_info.total_num_of_files) {
		imgs[i] = malloc(sizeof(Img));
		fread(&info,sizeof(info),1,fp);
		imgs[i]->img_data = matrix_create(info.height, info.width);
		imgs[i]->label=info.kind;
        for(int k=0;k<info.height;k++){
            for(int j=0;j<info.width;j++){
				fread(&num,sizeof(double),1,fp);
				imgs[i]->img_data->entries[k][j]=num / 256.0;
				
                //printf("(%d,%d,%d) ", pixel.red,pixel.green,pixel.blue);
            }
            //printf("\n");
        }
		i++;
	}
	fclose(fp);
	printf("%d images loaded\n",ds_info.total_num_of_files);
	return imgs;
}

void img_print(Img* img) {
	matrix_print(img->img_data);
	printf("Img Label: %d\n", img->label);
}

void img_free(Img* img) {
	matrix_free(img->img_data);
	free(img);
	img = NULL;
}

void imgs_free(Img** imgs, int n) {
	for (int i = 0; i < n; i++) {
		img_free(imgs[i]);
	}
}