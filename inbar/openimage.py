import numpy as np
import cv2
import sys
import csv
from skimage import io, color

img = cv2.imread('startrails.jpg')


# Get RGB data
inputImage_RGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGBA)
Image_Array_RGB = np.array(inputImage_RGB)
Image_Shape = Image_Array_RGB.shape

One_D_Image_Red   = np.transpose(np.matrix(Image_Array_RGB[:, :, 0].ravel()))
One_D_Image_Green = np.transpose(np.matrix(Image_Array_RGB[:, :, 1].ravel()))
One_D_Image_Blue  = np.transpose(np.matrix(Image_Array_RGB[:, :, 2].ravel()))


One_D_Image_RGB = np.concatenate((One_D_Image_Red, One_D_Image_Green, One_D_Image_Blue), axis=1)


# Get HSV data
inputImage_HSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
Image_Array_HSV = np.array(inputImage_HSV)

One_D_Image_Hue   = np.transpose(np.matrix(Image_Array_HSV[:, :, 0].ravel()))
One_D_Image_Saturation   = np.transpose(np.matrix(Image_Array_HSV[:, :, 1].ravel()))
One_D_Image_Value   = np.transpose(np.matrix(Image_Array_HSV[:, :, 2].ravel()))

One_D_Image_HSV = np.concatenate((One_D_Image_Hue, One_D_Image_Saturation, One_D_Image_Value), axis=1)


# Get LAB Data
inputImage_LAB = color.rgb2lab(io.imread('startrails.jpg'))
Image_Array_LAB = np.array(inputImage_LAB)

One_D_Image_L   = np.transpose(np.matrix(Image_Array_LAB[:, :, 0].ravel()))
One_D_Image_A   = np.transpose(np.matrix(Image_Array_LAB[:, :, 1].ravel()))
One_D_Image_B   = np.transpose(np.matrix(Image_Array_LAB[:, :, 2].ravel()))

One_D_Image_LAB = np.concatenate((One_D_Image_L, One_D_Image_A, One_D_Image_B), axis=1)


One_D_Image = np.concatenate((One_D_Image_RGB, One_D_Image_HSV, One_D_Image_LAB), axis=1)

title = "Red, Green, Blue, Hue, Saturation, Color, Lightness, A*, B*"
with open("colors.csv", "a") as csvFile:
    np.savetxt("colors.csv", One_D_Image, delimiter=",", header=title, fmt='%3.f', comments='')

    # writer.writerows(One_D_Image)
