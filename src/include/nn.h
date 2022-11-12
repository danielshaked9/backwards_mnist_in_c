#pragma once

#include "matrix.h"





typedef struct {
	int input;
	int hidden;
	int output;
	double learning_rate;
	Matrix* hidden_weights;
	Matrix* output_weights;
	Matrix* last_output;
} NeuralNetwork;



NeuralNetwork* network_create(int input, int hidden, int output, double lr);

void network_train(NeuralNetwork* net, Matrix* input_data, Matrix* output_data);

Matrix* network_predict(NeuralNetwork* net, Matrix* input_data);

void network_save(NeuralNetwork* net, char* file_string);
void network_save_bin(NeuralNetwork* net, char* file_string);

NeuralNetwork* network_load(char* file_string);
NeuralNetwork* network_load_bin(char* file_string);


void network_print(NeuralNetwork* net);

void network_free(NeuralNetwork* net);



/*
void network_train_from_bin(NeuralNetwork* net, char* file_string);
double network_predict_imgs_from_bin(NeuralNetwork* net, char* file_string);
*/