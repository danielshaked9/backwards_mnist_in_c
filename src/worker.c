#include <stdio.h>
#include <stdlib.h>
#include "include/worker.h"
#include "include/img.h"
#include "include/ops.h"
#include "include/activations.h"




Worker* worker_create(int input, int hidden, int output, double lr){
    Worker* worker=malloc(sizeof(Worker));
    worker->net=network_create(input,hidden,output,lr);
    return worker;
}



void* worker_talk(Worker* a, Worker *b){
    printf("worker talk\n");
    b->net->output_weights= dot(transpose(a->net->hidden_weights), transpose(b->net->output_weights));
    printf("worker talk\n");
    Matrix* hidden_hidden_weights= dot(b->net->output_weights,transpose(a->net->hidden_weights) ); // 784x784
    printf("worker talk\n");

    matrix_free(hidden_hidden_weights);
    //matrix_free(final_final_inputs);
}


Matrix* worker_gen_output(int label,int output_size){
    Matrix* output=matrix_create(output_size,1);
    output->entries[label][0] = 1;
    return output;
}
void worker_train(Worker* a, Img **imgs,int batch_size){
    int i=0;


    for (i = 0; i < batch_size; i++) {
        Img* cur_img = imgs[i];
        Matrix* img_data = matrix_flatten(cur_img->img_data, 0); // 0 = flatten to column vector
        Matrix* output = matrix_create(10, 1);
        output->entries[cur_img->label][0] = 1;
        network_train(a->net,img_data,output);
        matrix_free(output);
        matrix_free(img_data);
        fflush(stdout);
        if(i%100==0) printf("\r%d",i);
	}
    printf("worker train complete\n");
    network_save_bin(a->net,"bin");
}

void worker_make(Worker* a, Img **imgs,int batch_size){
    int i=0;

    for (i = 0; i < batch_size; i++) {
        Img* cur_img = imgs[i];

        Matrix* img_data = matrix_flatten(cur_img->img_data, 0); // 0 = flatten to column vector
        Matrix* output = matrix_create(10, 1);
        output->entries[cur_img->label][0] = 1;
        network_train(a->net,output,img_data);
        matrix_free(output);
        matrix_free(img_data);
        fflush(stdout);
        if(i%100==0) printf("\r%d",i);
	}
    printf("worker make complete\n");
    network_save_bin(a->net,"bin");

    network_free(a->net);
}
void worker_talk_batch_imgs(Worker* a, Worker* b, Img **imgs, int batch_size) {
    int i=0;
	for (i = 0; i < batch_size; i++) {
		Img* cur_img = imgs[i];

		Matrix* img_data = matrix_flatten(cur_img->img_data, 0); // 0 = flatten to column vector
		Matrix* output = matrix_create(10, 1);
		output->entries[cur_img->label][0] = 1;
		matrix_free(output);
		matrix_free(img_data);

        fflush(stdout);
        if(i%100==0) printf("\r%d",i);
	}


}
void worker_predict(Worker* a, Img** imgs,int num_of_batch_imgs){
    int i=0;
    int n=0;
    a->net=network_load_bin("bin");

    for(i=0;i<num_of_batch_imgs;i++){
        
        Img* cur_img = imgs[i];
        Matrix* img_data = matrix_flatten(cur_img->img_data, 0); // 0 = flatten to column vector
        Matrix* output = matrix_create(10, 1);
        output->entries[cur_img->label][0] = 1;
        Matrix* prediction = network_predict(a->net, img_data);
        if (matrix_argmax(prediction) == cur_img->label){
            ++n;
            printf("label: %d prediction: %d score: %lf\n",cur_img->label,matrix_argmax(prediction),(double)n/num_of_batch_imgs);
        }
    }
    
}

void worker_show(Worker* a, Img** imgs,int num_of_batch_imgs){
    int i=0;
    int n=0;
    a->net=network_load_bin("bin");
    char buffer[100];
    for(i=0;i<num_of_batch_imgs;i++){
        
        Img* cur_img = imgs[i];
        //Matrix* img_data = matrix_flatten(cur_img->img_data, 0); // 0 = flatten to column vector
        Matrix* output = matrix_create(10, 1);
        output->entries[cur_img->label][0] = 1;
        //img_data=scale(256,cur_img->img_data);
        sprintf(buffer,"results/res%d-label_%d.csv",i,cur_img->label);
        Matrix* prediction =network_predict(a->net, output);
        double max=prediction->entries[matrix_argmax(prediction)][0];
        matrix_save(prediction,buffer);
        matrix_free(prediction);
    }

}
