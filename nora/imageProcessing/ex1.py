# /* mi3nts
# Written by: Nora Desmond
# - for -
# Lakitha's exercise
# Date: July 29th, 2019
# Atom
# Github
# Python */


import numpy as np
import cv2
# Load an color image in grayscale
img = cv2.imread('seal.jpg')

print(img.shape)

green = img[100,100,1]
blue = img[100,100,0]
red = img[100,100,2]


cv2.imshow('green',green)
cv2.imshow('red',red)
cv2.imshow('blue',blue)
cv2.waitKey(0)
cv2.destroyAllWindows()

# import matplotlib.pyplot as plt
# plt.imshow([[0, 0, 0],
#            [1, 1, 1],
#            [2, 2, 2],],)
# plt.colorbar()
# plt.show()
