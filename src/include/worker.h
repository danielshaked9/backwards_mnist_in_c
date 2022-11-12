//#include "nn.h"
#include "matrix.h"
#include "img.h"
#include "nn.h"
typedef struct _Worker{
    NeuralNetwork* net;
    struct _Worker *worker;
}Worker;

Worker* worker_create(int input, int hidden, int output, double lr);
void* worker_talk(Worker* a, Worker *b);
Matrix* worker_gen_output(int label,int output_size);
void worker_talk_batch_imgs(Worker* a, Worker* b, Img** imgs, int batch_size);
void worker_predict(Worker* a, Img** imgs,int num_of_batch_imgs);
void worker_train(Worker* a, Img **imgs,int batch_size);
void worker_make(Worker* a, Img **imgs,int batch_size);
void worker_show(Worker* a, Img** imgs,int num_of_batch_imgs);
