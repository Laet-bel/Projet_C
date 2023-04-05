clc;
close all;
clear all;

for i = 15:15
I = imread("../Source Images/In_"+ i+".pgm");
Inv = imcomplement(I);

% Expansion_dynamique =(a-min(a(:))./(max(a(:)).-min(a(:))))*255;


SE = strel('disk', 30,0);
ImTopHat = imtophat(Inv,SE);

Ibinaire = imbinarize(ImTopHat, graythresh(ImTopHat));

% n = 5;
% m = 5;
% image_median = ordfilt2(Ibinaire,(m*n+1)/2,ones(m,m),'symmetric');

SE = strel('disk',1,0);
IFinal = imerode(Ibinaire,SE);
IFinal = imerode(IFinal,SE);
IFinal = imdilate(IFinal,SE);
IFinal = imdilate(IFinal,SE);



Igt = imread("../Ground truth/In_"+i+".pgm");
Igt = imbinarize(Igt,graythresh(Igt));
Idiff1 = Igt - IFinal;
Idiff2 = IFinal -Igt;
If = max(Idiff1,Idiff2);

figure(1),
subplot(3,3,1),imshow(I);
title('Image initiale')
subplot(3,3,2),imshow(Inv);
title('Image inversée')
subplot(3,3,3),imshow(ImTopHat);
title('Top Hat')
subplot(3,3,4),imshow(Ibinaire);
title('Seuil OTSU')
subplot(3,3,5),imshow(IFinal);
title('Erosion / Dilatation')
subplot(3,3,6),imshow(Igt);
title('Véritée terrain')
subplot(3,3,7),imshow(If);
title('Différences')
pause(0.5);
end

% figure,title('Image inversée'),imshow(Inv);
% figure, imshow(ImTopHat);
% figure,imshow(Ibinaire);
% figure,imshow(IFinal);
% figure,title('Différences'),imshow(If);


% SE = strel('disk', 1,0);
% figure, imshow(SE.Neighborhood)
% SE = strel('disk', 2,0);
% figure, imshow(SE.Neighborhood)
% SE = strel('disk', 2,0);
% figure, imshow(SE.Neighborhood)
% SE = strel('disk', 20,0);
% figure, imshow(SE.Neighborhood)