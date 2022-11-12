#include "include/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <include/nn.h>
#include "include/worker.h"
#include "include/img.h"
#include "include/ops.h"
//#include <GL/glut.h>



int main(int argc, char **argv)
{
    Img** imgs = bin_to_imgs("data/train.bin");
    Worker *worker_a=worker_create(784,300,10,0.236);
    Worker *worker_b=worker_create(10,300,784,0.236);
    worker_make(worker_b,imgs,1000);
    //worker_train(worker_a,imgs,60000);
    imgs_free(imgs,60000);
    imgs = bin_to_imgs("data/test.bin");
    matrix_size(worker_a->net->hidden_weights);
    //worker_predict(worker_a,imgs,10000);
    worker_show(worker_b,imgs,20);
    imgs_free(imgs,10000);
    network_free(worker_a->net);
}
