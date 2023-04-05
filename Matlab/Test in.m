clc;
close all;
clear all;

for i = 1:15
I = imread("../Source Images/In_"+ i+".pgm");
Inv = imcomplement(I);


SE = strel('disk',20,0);
ImTopHat = imtophat(Inv,SE);

Ibinaire = imbinarize(ImTopHat, graythresh(ImTopHat));

SE = strel('disk',2,0);
IFinal = imerode(Ibinaire,SE);
SE = strel('disk',1,0);
IFinal = imdilate(IFinal,SE);

Igt = imread("../Ground truth/In_"+i+".pgm");
Igt = imbinarize(Igt,graythresh(Igt));
Idiff1 = Igt - IFinal;
Idiff2 = IFinal -Igt;
If = max(Idiff1,Idiff2);

figure(i),
subplot(3,3,1),imshow(image);
title('Image initiale')
subplot(3,3,2),imshow(Inv);
title('Image inversée')
subplot(3,3,3),imshow(ImTopHat);
title('Top Hat')
subplot(3,3,4),imshow(Ibinaire);
title('Seuil OTSU')
subplot(3,3,5),imshow(IFinal);
title('Erosion / Dilatation')
subplot(3,3,6),imshow(iIgt);
title('Véritée terrain')
subplot(3,3,7),imshow(If);
title('Différences')

end
% 
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