#include <stdlib.h>
#include <stdio.h>
#include "libCIPSI1.h"

int main(void)
{
	int rayon = 3;
	int hauteur = 3;
	int largeur = 3;
	
	ELEMENT_STRUCTURANT ElementStructurant_V4 = allocation_ElementStructurant('V4', hauteur, largeur);

	for (int i = 0; i < ElementStructurant_V4.hauteur; i++)
	{
		for (int j = 0; j < ElementStructurant_V4.largeur; j++)
		{
			printf("%d", ElementStructurant_V4.pixel[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	IMAGE test_SE = lectureImage("Source Images/In_30.pgm");
	IMAGE true_SE = lectureImage("Ground truth/In_30.pgm");
	IMAGE testInv_SE = inverseImage(test_SE);
	IMAGE WTH_SE = whiteTopHatavecSE(testInv_SE, ElementStructurant_V4, 30);
	WTH_SE = seuillageOtsu(WTH_SE);
	WTH_SE = erosionImageavecSE(WTH_SE, ElementStructurant_V4);
	WTH_SE = erosionImageavecSE(WTH_SE, ElementStructurant_V4);
	WTH_SE = dilatationImageavecSE(WTH_SE, ElementStructurant_V4);
	float IOU = IOU_score(WTH_SE, true_SE);
	printf("IOU 1 : %f", IOU);

	// Fonction principale In (Image , Vérité terrain, SE , nb_it) ==> (sortie score moyenne) 
	// (Faire le tout nb itération fois)
	// - Traitement In (Image) ==> (ressort Image Traitée)
	// - Générer tableau IOU (Création tableau plus dernière case de moyenne) (Image / Vérité / compteur / ajout_score_ancien) ==> (Tableau , ajout_score)
	// 
	// (Sortir boucle)
	// - Calcul moyenne finale (ajouter au tableau)
	// - Export CSV Tableau 

	return 0;
}