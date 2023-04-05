clc;
close all;
clear all;

for i = 30:60

image = imread("../Source Images/Sc_"+ i+".pgm");
image_finale = imread("../Ground truth/Sc_"+ i+".pgm");

SE = strel('disk', 20);
% m = 3;
% n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

SE = strel('disk', 1);

level = graythresh(image_TopHat);
image_seuil = imbinarize(image_TopHat,level);

IFinal = imclose(image_seuil,SE);

Igt = image_finale;
Igt = imbinarize(Igt,graythresh(Igt));
Idiff1 = Igt - IFinal;
Idiff2 = IFinal -Igt;
If = max(Idiff1,Idiff2);

figure(1),
subplot(3,3,1),imshow(image);
title('Image initiale')
subplot(3,3,2),imshow(image_TopHat);
title('Top Hat')
subplot(3,3,4),imshow(image_seuil);
title('Seuil OTSU')
subplot(3,3,5),imshow(IFinal);
title('Erosion / Dilatation')
subplot(3,3,6),imshow(image_finale);
title('Véritée terrain')
subplot(3,3,7),imshow(If);
title('Différences')
pause(0.5);
end