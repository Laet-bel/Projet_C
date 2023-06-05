#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"

int main(void)
{
	int hauteur = 3, largeur = 3;
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
	sauvegardeImage(test_SE, "P5", "W_inv.pgm");

	IMAGE WTH_SE = whiteTopHatavecSE(testInv_SE, ElementStructurant_V4, 30);
	sauvegardeImage(WTH_SE, "P5", "WTH_SE.pgm");

	WTH_SE = seuillageOtsu(WTH_SE);
	sauvegardeImage(WTH_SE, "P5", "WTH_OTSU_SE.pgm");

	WTH_SE = erosionImageavecSE(WTH_SE, ElementStructurant_V4);
	WTH_SE = erosionImageavecSE(WTH_SE, ElementStructurant_V4);
	WTH_SE = dilatationImageavecSE(WTH_SE, ElementStructurant_V4);

	sauvegardeImage(WTH_SE, "P5", "In_30_WTH_OTSU_erode_SE.pgm");

	IMAGE image_avec_blobs_communs = recuperation_blobs_communs(true_SE, WTH_SE);
	sauvegardeImage(image_avec_blobs_communs, "P5", "In_30_blobs_communs.pgm");


	float IOU = IOU_score(WTH_SE, true_SE);
	float IOU2 = IOU_score(image_avec_blobs_communs, true_SE);
	printf("IOU : %f \t IOU2 : %f", IOU , IOU2);





	return 0;
}
