%% Avec Top Hat / Seuil OTSU
clc
clear all;

image = imread('../Source Images/Sc_1.pgm');
%image = imcomplement(image);
image_finale = imread('../Ground truth/SC_1.pgm');

SE = strel('disk', 10);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

image_median = ordfilt2(image_TopHat,(m*n+1)/2,ones(m,m),'symmetric');

OTSU_Level = graythresh(image_TopHat);
image_seuil = imbinarize(image_median,OTSU_Level);

image_filter = imclose(image_seuil, SE);

figure(1),
subplot(3,3,1),imshow(image);
subplot(3,3,2),imshow(image_TopHat);
subplot(3,3,3),imshow(image_median);
subplot(3,3,4),imshow(image_seuil);
subplot(3,3,5),imshow(image_filter);
subplot(3,3,6),imshow(image_finale);
%% Test 2 avec Egalisation NUL A CHIER
clc
clear all;

image = imread('../Source Images/Sc_1.pgm');
%image = imcomplement(image);
image_finale = imread('../Ground truth/SC_1.pgm');

SE = strel('disk', 3);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

image_median = ordfilt2(image_TopHat,(m*n+1)/2,ones(m,m),'symmetric');

% Egalisation 
Image_egalise = histeq(image_median); 

OTSU_Level = graythresh(Image_egalise);
image_seuil = imbinarize(Image_egalise,OTSU_Level);

image_filter = imclose(image_seuil, SE);



figure(2),
subplot(3,3,1),imshow(image);
subplot(3,3,2),imshow(image_TopHat);
subplot(3,3,3),imshow(image_median);
subplot(3,3,4),imshow(Image_egalise);
subplot(3,3,5),imshow(image_seuil);
subplot(3,3,6),imshow(image_filter);

subplot(3,3,7),imshow(image_finale);

%% Avec Expension de la dynamique ENCORE PIRE

clc
clear all;

image = imread('../Source Images/Sc_1.pgm');
%image = imcomplement(image);
image_finale = imread('../Ground truth/SC_1.pgm');

SE = strel('disk', 3);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

%Expansion de la dynamique
min = min( image_TopHat );
max = max( image_TopHat );
image_ajout_contraste = 255.*((image_TopHat-min)./(max-min));


image_median = ordfilt2(image_ajout_contraste,(m*n+1)/2,ones(m,m),'symmetric');

OTSU_Level = graythresh(image_TopHat);
image_seuil = imbinarize(image_median,OTSU_Level);

image_filter = imclose(image_seuil, SE);



figure(3),
subplot(3,3,1),imshow(image);
subplot(3,3,2),imshow(image_TopHat);
subplot(3,3,3),imshow(image_ajout_contraste);
subplot(3,3,4),imshow(image_median);
subplot(3,3,5),imshow(image_seuil);
subplot(3,3,6),imshow(image_filter);

subplot(3,3,7),imshow(image_finale);

%% Avec Top Hat /Sans filtre median
clc
clear all;

image = imread('../Source Images/Sc_5.pgm');
%image = imcomplement(image);
image_finale = imread('../Ground truth/SC_5.pgm');

SE = strel('disk', 20);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

SE = strel('disk', 1);

% image_median = ordfilt2(image_TopHat,(m*n+1)/2,ones(m,m),'symmetric');

image_seuil = imbinarize(image_TopHat,"global");

image_filter = imdilate(image_seuil,SE);
image_filter = imerode(image_filter,SE);


figure(4),
subplot(3,3,1),imshow(image);
subplot(3,3,2),imshow(image_TopHat);
% subplot(3,3,3),imshow(image_median);
subplot(3,3,4),imshow(image_seuil);
subplot(3,3,5),imshow(image_filter);
subplot(3,3,6),imshow(image_finale);

%% Avec Top Hat / Seuil à 60
clc
clear all;

image = imread('../Source Images/Sc_5.pgm');
%image = imcomplement(image);
image_finale = imread('../Ground truth/SC_5.pgm');

SE = strel('disk', 20);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

SE = strel('disk', 1);

% image_median = ordfilt2(image_TopHat,(m*n+1)/2,ones(m,m),'symmetric');

image_seuil = image_TopHat > 60;

image_filter = imclose(image_seuil,SE);


figure(5),
subplot(3,3,1),imshow(image);
title('Image initiale')
subplot(3,3,2),imshow(image_TopHat);
title('Top Hat')
subplot(3,3,4),imshow(image_seuil);
title('Seuil OTSU')
subplot(3,3,5),imshow(image_filter);
title('Erosion / Dilatation')
subplot(3,3,6),imshow(image_finale);
title('Véritée terrain')

%% Avec Top Hat / Seuil par moyenne
clc
clear all;

image = imread('../Source Images/Sc_5.pgm');
%image = imcomplement(image);
image_finale = imread('../Ground truth/SC_5.pgm');

SE = strel('disk', 20);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

SE = strel('disk', 1);

% Seuil par moyenne : J'y arrive pas ta mère la p***
h = histogram(image_TopHat);
h = h.get;
mean = 0;
size = size(h.Values);
for i=1:1:size(2)
    mean = mean + h.Values(i)*(i-1);
end

image_filter = imclose(image_seuil,SE);


figure(6),
subplot(3,3,1),imshow(image);
subplot(3,3,2),imshow(image_TopHat);
subplot(3,3,4),imshow(image_seuil);
subplot(3,3,5),imshow(image_filter);
subplot(3,3,6),imshow(image_finale);

%% Avec Top Hat / Seuil à 60 / SE square 
clc
clear all;

image = imread('../Source Images/Sc_1.pgm');
%image = imcomplement(image);
image_finale = imread('../Ground truth/SC_1.pgm');

SE = strel('square', 20);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

SE = strel('square', 3);

% image_median = ordfilt2(image_TopHat,(m*n+1)/2,ones(m,m),'symmetric');

image_seuil = image_TopHat > 60;

image_filter = imclose(image_seuil,SE);


figure(7),
subplot(3,3,1),imshow(image);
subplot(3,3,2),imshow(image_TopHat);
subplot(3,3,4),imshow(image_seuil);
subplot(3,3,5),imshow(image_filter);
subplot(3,3,6),imshow(image_finale);


%% Avec Top Hat / Seuil OTSU / SC
clc
clear all;


image = imread('../Source Images/Sc_2.pgm');
image_finale = imread('../Ground truth/Sc_2.pgm');

SE = strel('disk', 20);
m = 3;
n = 3;

% TOP HAT ==> uniformiser fond 
image_TopHat = imtophat(image , SE);

SE = strel('disk', 1);

level = graythresh(image_TopHat);
image_seuil = imbinarize(image_TopHat,level);

image_filter = imclose(image_seuil,SE);


figure(8),
subplot(3,3,1),imshow(image);
title('Image initiale')
subplot(3,3,2),imshow(image_TopHat);
title('Top Hat')
subplot(3,3,4),imshow(image_seuil);
title('Seuil OTSU')
subplot(3,3,5),imshow(image_filter);
title('Erosion / Dilatation')
subplot(3,3,6),imshow(image_finale);
title('Véritée terrain')

%% Avec Top Hat / Seuil à 60 / IN
clc
close all;
clear all;

for i = 1:15
image = imread("../Source Images/In_"+ i+".pgm");
image_finale = imread("../Ground truth/In_"+i+".pgm");

SE = strel('disk', 1);
% m = 3;
% n = 3;

image = imcomplement(image);

% TOP HAT ==> uniformiser fond 
for j = 0 : 30
image_TopHat = imtophat(image , SE);
end
% image_TopHat = imadjust(image_TopHat);

SE = strel('disk', 1);

level = graythresh(image_TopHat);
image_seuil = imbinarize(image_TopHat,level);

image_filter = imerode(image_seuil,SE);
image_filter = imopen(image_filter,SE);


figure(i),
subplot(3,3,1),imshow(image);
title('Image initiale')
subplot(3,3,2),imshow(image_TopHat);
title('Top Hat')
subplot(3,3,4),imshow(image_seuil);
title('Seuil OTSU')
subplot(3,3,5),imshow(image_filter);
title('Erosion / Dilatation')
subplot(3,3,6),imshow(image_finale);
title('Véritée terrain')
end
