clc
close all;
clear all;

for i=10:50

    I= imread("C:\Users\loic\OneDrive\Documents\Analyse d'image\Projet Image\Source Images - bmp\In_"+ i+".bmp"); 
    C= imread("C:\Users\loic\OneDrive\Documents\Analyse d'image\Projet Image\Ground truth - png\In_"+ i+".png"); 

    % Traitement de l'image
    
    I = imcomplement(I);

    se = strel('disk',10);
    tophat = medfilt2(I,[2 2]);
    tophat = imtophat(BW,se);
    
    sf = strel('disk',1);
   
    BW = im2bw(tophat,graythresh(tophat));
    
    BW = imerode(BW, sf);
    %BW = imdilate(BW, sf);
    %BW = imclose(BW,sf);
    
    % Traitement de l'image_finale

    Igt = imbinarize(C,graythresh(C)); 

    % Différence

    Idiff1 = Igt - BW; 
    Idiff2 = BW -Igt; 
    If = max(Idiff1,Idiff2); 

    % Afficher l'image originale, l'image top-hat, l'image finale et la comparaison
    subplot(2,3,1), imshow(I), title('Image originale');
    subplot(2,3,2), imshow(tophat), title('Image top-hat');
    subplot(2,3,3), imshow(BW), title('Image finale');
    subplot(2,3,4), imshow(C), title('Image prof');
    subplot(2,3,5), imshow(If), title('Différence');

    
    pause(0.5); % Pause pour éviter de surcharger le processeur
end