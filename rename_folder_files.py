import glob
import os
import random
import string
def gen_random_string():
    # printing lowercase
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(15)) 
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

# Iterating the list with the count
count = 1
for file_name in result:
    old_name = file_name
    search_digit(old_name)

    new_name = path + gen_random_string() + search_digit(old_name) + ".png"
    os.rename(old_name, new_name)
    count = count + 1

# printing all revenue txt files
res = glob.glob(path +  "*.png")
for name in res:
    print(name)
