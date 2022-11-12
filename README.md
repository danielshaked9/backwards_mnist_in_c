# backwards_mnist_in_c
wrritten on linux system


1.clone into project
2.tar -xvf train_png.tar.xz
3.tar -xvf test_png.tar.xz
4.mkdir data
5.python png_folder_to_bin.py 
6.make
7.make run
8. to view the result run display_img.py

for regular training and predicting use worker_train() and worker_predict() function
for generating images from labels use worker_make() and worker_show() and than use python file to see the outputs


