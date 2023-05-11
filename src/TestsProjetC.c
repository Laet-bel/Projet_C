#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"

int main(void)
{
	IMAGE test = lectureImage("Source Images/In_30.pgm");
	IMAGE testInv = inverseImage(test);
	sauvegardeImage(test, "P5", "W_inv.pgm");

	IMAGE WTH = whiteTopHat(testInv, 4,30);
	sauvegardeImage(WTH, "P5", "WTH.pgm");

	WTH = seuillageOtsu(WTH);
	sauvegardeImage(WTH, "P5", "WTH_OTSU.pgm");

	WTH = erosionImage(WTH, 4);
	WTH = erosionImage(WTH, 4);
	WTH = dilatationImage(WTH, 4);


	sauvegardeImage(WTH, "P5", "In_30_WTH_OTSU_erode.pgm");

	int rayon = 3;
	int hauteur = 3;
	int largeur = 3;
	ELEMENT_STRUCTURANT ElementStructurant_disk = allocation_ElementStructurant('disk', rayon, rayon);

	for (int i = 0; i < 2 * rayon + 1; i++)
	{
		for (int j = 0; j < 2 * rayon + 1; j++)
		{
			printf("%d", ElementStructurant_disk.pixel[i][j]);
		}
		printf("\n");
	}


	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	ELEMENT_STRUCTURANT ElementStructurant_rect = allocation_ElementStructurant('rect', hauteur, largeur);

	for (int i = 0; i < hauteur; i++)
	{
		for (int j = 0; j < largeur; j++)
		{
			printf("%d", ElementStructurant_rect.pixel[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	ELEMENT_STRUCTURANT ElementStructurant_ligneVerticale = allocation_ElementStructurant('ligV', hauteur, largeur);

	for (int i = 0; i < ElementStructurant_ligneVerticale.hauteur; i++)
	{
		for (int j = 0; j < ElementStructurant_ligneVerticale.largeur; j++)
		{
			printf("%d", ElementStructurant_ligneVerticale.pixel[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	ELEMENT_STRUCTURANT ElementStructurant_ligneHorizontale = allocation_ElementStructurant('ligH', hauteur, largeur);

	for (int i = 0; i < ElementStructurant_ligneHorizontale.hauteur; i++)
	{
		for (int j = 0; j < ElementStructurant_ligneHorizontale.largeur; j++)
		{
			printf("%d", ElementStructurant_ligneHorizontale.pixel[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	ELEMENT_STRUCTURANT ElementStructurant_ellipse = allocation_ElementStructurant('elli', hauteur, largeur);

	for (int i = 0; i < ElementStructurant_ellipse.hauteur; i++)
	{
		for (int j = 0; j < ElementStructurant_ellipse.largeur; j++)
		{
			printf("%d", ElementStructurant_ellipse.pixel[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

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

	ELEMENT_STRUCTURANT ElementStructurant_V8 = allocation_ElementStructurant('V8', hauteur, largeur);

	for (int i = 0; i < ElementStructurant_V8.hauteur; i++)
	{
		for (int j = 0; j < ElementStructurant_V8.largeur; j++)
		{
			printf("%d", ElementStructurant_V8.pixel[i][j]);
		}
		printf("\n");
	}

	IMAGE test_SE = lectureImage("Source Images/In_30.pgm");
	IMAGE testInv_SE = inverseImage(test_SE);
	sauvegardeImage(test_SE, "P5", "W_inv.pgm");

	IMAGE WTH_SE = whiteTopHat(testInv_SE, 4, 30);
	sauvegardeImage(WTH_SE, "P5", "WTH_SE.pgm");

	WTH_SE = seuillageOtsu(WTH_SE);
	sauvegardeImage(WTH_SE, "P5", "WTH_OTSU_SE.pgm");

	WTH_SE = erosionImageavecSE(WTH_SE, ElementStructurant_V4);
	WTH_SE = erosionImageavecSE(WTH_SE, ElementStructurant_V4);
	WTH_SE = dilatationImageavecSE(WTH_SE, ElementStructurant_V4);


	sauvegardeImage(WTH_SE, "P5", "In_30_WTH_OTSU_erode_SE.pgm");






	return 0;
}
