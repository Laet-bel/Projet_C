clc
close all;
clear all;

% Seuillage auto (binarisation)
C=imread('In_12.png');

I=imread('In_12.bmp');
I =imcomplement(I);

se = strel('disk',10);
tophat = imtophat(I,se);


BW=im2bw(tophat,graythresh(tophat));
BW =medfilt2(BW,[4 4]);
sf = strel('disk',1);
BW = imerode(BW, sf);
BW = imdilate(BW, sf);

subplot(2,2,1), imshow(I), title('Image originale');
subplot(2,2,2), imshow(tophat), title('Image top-hat');
subplot(2,2,3), imshow(BW), title('Image finale');
subplot(2,2,4), imshow(C), title('Comparaison');
