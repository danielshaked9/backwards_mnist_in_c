import numpy as np


import cv2
import numpy as np

img = ... # Your image as a numpy array 

import glob
import os


def main():

    path = 'results/'
    # search text files starting with the word "sales"
    pattern = path + "*.csv"

    # List of the files that match the pattern
    result = glob.glob(pattern)

    # Iterating the list with the count
    count = 1
    for file_name in result:
        old_name = file_name
        new_name = old_name + "res"+  ".png"
        count = count + 1
        img=np.genfromtxt(old_name, delimiter=',')
        img=img.reshape(28,28)



        img*=256.0/img.max()
        cv2.imwrite(new_name, img)





if __name__ == '__main__':
    main()