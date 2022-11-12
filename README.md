# backwards_mnist_in_c
written on linux system

clone into project

tar -xvf train_png.tar.xz 

tar -xvf test_png.tar.xz 

mkdir data 

mkdir results

python png_folder_to_bin.py 

make

make run


to view the result run display_img.py

for regular training and predicting use worker_train() and worker_predict() function
for generating images from labels use worker_make() and worker_show() and than use python file to see the outputs

examples of outputs:
generated from label input 0:
![res00 csvres](https://user-images.githubusercontent.com/70443184/201462784-33502031-ca29-47f7-b84f-d42097242fdb.png)
from 3:
![res5-label3 csvres](https://user-images.githubusercontent.com/70443184/201462812-49c6a0d0-2b0d-4cbc-ac7d-9f94bd6ce1a1.png)
from 7:
![res11-label7 csvres](https://user-images.githubusercontent.com/70443184/201462814-abab5751-6a16-49df-9fe4-69631aec327a.png)
from 2:
![res182 csvres](https://user-images.githubusercontent.com/70443184/201462834-79c9f89c-6d0c-4488-8261-b64f34eb3ad0.png)
from 9:
![res159 csvres](https://user-images.githubusercontent.com/70443184/201462847-280690c9-6ed8-4d74-b0fc-21eaf9ec570d.png)





