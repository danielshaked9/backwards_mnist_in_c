#include "include/nn.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/ops.h"
#include "include/activations.h"
#include <time.h>
#include "include/img.h"
#include "include/worker.h"

#define MAXCHAR 1000

// 784, 300, 10
NeuralNetwork* network_create(int input, int hidden, int output, double lr) {
	NeuralNetwork* net = malloc(sizeof(NeuralNetwork));
	net->input = input;
	net->hidden = hidden;
	net->output = output;
	net->learning_rate = lr;
	Matrix* hidden_weights = matrix_create(hidden, input);
	Matrix* output_weights = matrix_create(output, hidden);
	Matrix* last_output = matrix_create(output, 1);
	matrix_randomize(hidden_weights, hidden);
	matrix_randomize(output_weights, output);
	net->hidden_weights = hidden_weights;
	net->output_weights = output_weights;
	net->last_output = last_output;
	return net;
}



void network_train(NeuralNetwork* net, Matrix* input, Matrix* output) {
	// Feed forward
	Matrix* hidden_inputs	= dot(net->hidden_weights, input); // in_a: 1x784 hiddn_a: 784x1000       in_b: 1x10 hiddn_b: 10x1000  
	Matrix* hidden_outputs = apply(sigmoid, hidden_inputs);  
	Matrix* final_inputs = dot(net->output_weights, hidden_outputs); // 1x1000 outw_a: 1000x10 , 1x1000 outw_b: 1000x784
	Matrix* final_outputs = apply(sigmoid, final_inputs);



	// Find errors
	Matrix* output_errors = subtract(output, final_outputs);
	Matrix* hidden_errors = dot(transpose(net->output_weights), output_errors);

	// Backpropogate

	//Change net->output_weights
	Matrix* sigmoid_primed_mat = sigmoidPrime(final_outputs);
	Matrix* multiplied_mat = multiply(output_errors, sigmoid_primed_mat);
	Matrix* transposed_mat = transpose(hidden_outputs);
	Matrix* dot_mat = dot(multiplied_mat, transposed_mat);
	Matrix* scaled_mat = scale(net->learning_rate, dot_mat);
	Matrix* added_mat = add(net->output_weights, scaled_mat);
	matrix_free(net->output_weights); // Free the old weights before replacing
	net->output_weights = added_mat;


	matrix_free(sigmoid_primed_mat);
	matrix_free(multiplied_mat);
	matrix_free(transposed_mat);
	matrix_free(dot_mat);
	matrix_free(scaled_mat);

	//Change net->hidden_weights

	sigmoid_primed_mat = sigmoidPrime(hidden_outputs);
	multiplied_mat = multiply(hidden_errors, sigmoid_primed_mat);
	transposed_mat = transpose(input);
	dot_mat = dot(multiplied_mat, transposed_mat);
	scaled_mat = scale(net->learning_rate, dot_mat);
	added_mat = add(net->hidden_weights, scaled_mat);
	matrix_free(net->hidden_weights); // Free the old hidden_weights before replacement
	net->hidden_weights = added_mat; 


	matrix_free(sigmoid_primed_mat);
	matrix_free(multiplied_mat);
	matrix_free(transposed_mat);
	matrix_free(dot_mat);
	matrix_free(scaled_mat);

	// Free matrices
	matrix_free(hidden_inputs);
	matrix_free(hidden_outputs);
	matrix_free(final_inputs);
	matrix_free(final_outputs);
	matrix_free(output_errors);
	matrix_free(hidden_errors);

}



Matrix* network_predict(NeuralNetwork* net, Matrix* input_data) {
	Matrix* hidden_inputs	= dot(net->hidden_weights, input_data);
	Matrix* hidden_outputs = apply(sigmoid, hidden_inputs);
	Matrix* final_inputs = dot(net->output_weights, hidden_outputs);
	Matrix* final_outputs = apply(sigmoid, final_inputs);
	Matrix* result = softmax(final_outputs);
	return result;
}

void network_save(NeuralNetwork* net, char* file_string) {
	mkdir(file_string, 0777);
	// Write the descriptor file
	chdir(file_string);
	FILE* descriptor = fopen("descriptor", "w");
	fprintf(descriptor, "%d\n", net->input);
	fprintf(descriptor, "%d\n", net->hidden);
	fprintf(descriptor, "%d\n", net->output);
	fclose(descriptor);
	matrix_save(net->hidden_weights, "hidden");
	matrix_save(net->output_weights, "output");
	printf("Successfully written to '%s'\n", file_string);
	chdir(".."); // Go back to the orignal directory
}

void network_save_bin(NeuralNetwork* net, char* file_string) {
	mkdir(file_string, 0777);
	// Write the descriptor file
	chdir(file_string);
	FILE* descriptor = fopen("descriptor", "wb");

	fprintf(descriptor, "%d\n", net->input);
	fprintf(descriptor, "%d\n", net->hidden);
	fprintf(descriptor, "%d\n", net->output);
	fclose(descriptor);

	matrix_save_bin(net->hidden_weights, "hidden.bin");
	matrix_save_bin(net->output_weights, "output.bin");
	printf("Successfully written to '%s'\n", file_string);
	chdir(".."); // Go back to the orignal directory
}

NeuralNetwork* network_load(char* file_string) {
	NeuralNetwork* net = malloc(sizeof(NeuralNetwork));
	char entry[MAXCHAR];
	chdir(file_string);

	FILE* descriptor = fopen("descriptor", "r");
	fgets(entry, MAXCHAR, descriptor);
	net->input = atoi(entry);
	fgets(entry, MAXCHAR, descriptor);
	net->hidden = atoi(entry);
	fgets(entry, MAXCHAR, descriptor);
	net->output = atoi(entry);
	fclose(descriptor);
	net->hidden_weights = matrix_load("hidden");
	net->output_weights = matrix_load("output");
	printf("Successfully loaded network from '%s'\n", file_string);
	chdir("-"); // Go back to the original directory
	return net;
}

NeuralNetwork* network_load_bin(char* file_string) {
	NeuralNetwork* net = malloc(sizeof(NeuralNetwork));
	char entry[MAXCHAR];
	chdir(file_string);

	FILE* descriptor = fopen("descriptor", "r");
	fgets(entry, MAXCHAR, descriptor);
	net->input = atoi(entry);
	fgets(entry, MAXCHAR, descriptor);
	net->hidden = atoi(entry);
	fgets(entry, MAXCHAR, descriptor);
	net->output = atoi(entry);
	fclose(descriptor);

	net->hidden_weights=matrix_load_bin("hidden.bin");
	net->output_weights=matrix_load_bin("output.bin");
	printf("Successfully loaded network from '%s'\n", file_string);
	chdir(".."); // Go back to the original directory
	return net;
}

void network_print(NeuralNetwork* net) {
	printf("# of Inputs: %d\n", net->input);
	printf("# of Hidden: %d\n", net->hidden);
	printf("# of Output: %d\n", net->output);
	printf("Hidden Weights: \n");
	matrix_print(net->hidden_weights);
	printf("Output Weights: \n");
	matrix_print(net->output_weights);
}

void network_free(NeuralNetwork *net) {
	matrix_free(net->hidden_weights);
	matrix_free(net->output_weights);
	free(net);
	net = NULL;
}