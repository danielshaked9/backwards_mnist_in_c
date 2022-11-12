import glob
import os
from PIL import Image
import numpy as np


import struct
#print(gen_random_string())
def search_digit(stringinp):
    num = ""
    for c in stringinp:
        if c.isdigit():
            return c
path = "test_png"
# search text files starting with the word "sales"
pattern = path + "*.png"

# List of the files that match the pattern
result = glob.glob(pattern)




output_file = "test.bin"
out_file = open(output_file,"wb")

count = 0
for file_name in result:
    count = count + 1

ds_info=count
with open(output_file, 'wb') as file:
    file.write(struct.pack('i',count))
    count=0

    for file_name in result:
        kind=int(search_digit(file_name))
        im_frame = Image.open(file_name)
        width=int(im_frame.size[0])
        height=int(im_frame.size[1])
        

        np_frame = np.array(im_frame.getdata()).reshape(im_frame.size)
        file.write(struct.pack('i',width))
        file.write(struct.pack('i',height))
        file.write(struct.pack('i',kind))

        for i in range(height):
            for j in range(width):
                file.write(struct.pack('d',np_frame[i,j]))
        print(count ,kind)
        count+=1


