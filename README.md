# backwards_mnist_in_c
wrritten on linux system


clone into project

tar -xvf train_png.tar.xz \n
tar -xvf test_png.tar.xz \n
mkdir data \n
python png_folder_to_bin.py \n
make\n
make run\n


to view the result run display_img.py

for regular training and predicting use worker_train() and worker_predict() function
for generating images from labels use worker_make() and worker_show() and than use python file to see the outputs


