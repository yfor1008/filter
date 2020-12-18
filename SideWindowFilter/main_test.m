close all; clear; clc;

im = imread('./src/lena.jpg');
result1(:,:,1) = medfilt2(im(:,:,1), [11, 11]);
result1(:,:,2) = medfilt2(im(:,:,2), [11, 11]);
result1(:,:,3) = medfilt2(im(:,:,3), [11, 11]);
result2 = SideWindowBoxFilter(im, 5, 1);

im_show = cat(2, im, result1, uint8(result2));
imshow(im_show)
