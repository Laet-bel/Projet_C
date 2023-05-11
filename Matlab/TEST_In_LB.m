clc
close all;
clear all;


    % Initialiser le vecteur pour stocker les résultats IoU
IoU_results = zeros(1,300);

for i=1:100

    I= imread("C:\Users\loic\OneDrive\Documents\Analyse d'image\Projet Image\Source Images - bmp\Sc_"+ i+".bmp"); 
    C= imread("C:\Users\loic\OneDrive\Documents\Analyse d'image\Projet Image\Ground truth - png\Sc_"+ i+".png"); 

  % Traitement de l'image
    se = strel('disk',5);
    tophat = imtophat(I,se);

    % Augmenter la taille du filtre médian
    img_fil = imgaussfilt(tophat,2);  % Augmentation à un filtre 3x3

    %morpho = imdilate(I, se);
    %morpho1 = imerode(morpho, se);
    
    BW = im2bw(img_fil,graythresh(img_fil));

    % Traitement de l'image_finale
    Igt = imbinarize(C,graythresh(C)); 

    % Différence
    Idiff1 = Igt - BW; 
    Idiff2 = BW -Igt; 
    If = max(Idiff1,Idiff2); 

    % Calcul de l'IoU
    intersection = sum(sum(Igt & BW));
    union = sum(sum(Igt | BW));
    IoU = intersection / union;

    % Ignorer les IoU en dessous de 40%
    %if IoU < 0.4
    %   IoU = 0;  % Mettre l'IoU à zéro
    %end

    % Stocker l'IoU pour cette image
    IoU_results(i) = IoU;

    % Afficher l'image originale, l'image top-hat, l'image finale et la comparaison
    subplot(2,2,1), imshow(I), title('Image originale');
    subplot(2,2,2), imshow(BW), title('Image finale');
    subplot(2,2,3), imshow(C), title('Image prof');
    subplot(2,2,4), imshow(If), title('Différence');

    disp(['L''IoU pour l''image ', num2str(i), ' est : ', num2str(IoU)]);

    pause(0.5); % Pause pour éviter de surcharger le processeur
end

% Calculer la moyenne de l'IoU
mean_IoU = mean(IoU_results);

% Afficher la moyenne de l'IoU
disp(['La moyenne de l''IoU pour toutes les images est : ', num2str(mean_IoU)]);