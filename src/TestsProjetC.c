#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"

int main(void)
{
	/*IMAGE test = lectureImage("Source Images/In_30.pgm");
	IMAGE testInv = inverseImage(test);
	sauvegardeImage(test, "P5", "W_inv.pgm");

	IMAGE WTH = whiteTopHat(testInv, 4,30);
	sauvegardeImage(WTH, "P5", "WTH.pgm");

	WTH = seuillageOtsu(WTH);
	sauvegardeImage(WTH, "P5", "WTH_OTSU.pgm");

	WTH = erosionImage(WTH, 4);
	WTH = erosionImage(WTH, 4);
	WTH = dilatationImage(WTH, 4);


	sauvegardeImage(WTH, "P5", "In_30_WTH_OTSU_erode.pgm");*/

	int rayon = 20;
	int hauteur = 8;
	int largeur = 50;
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

	ELEMENT_STRUCTURANT ElementStructurant_ellipse = allocation_ElementStructurant('elip', hauteur, largeur);

	for (int i = 0; i < ElementStructurant_ellipse.hauteur; i++)
	{
		for (int j = 0; j < ElementStructurant_ellipse.largeur; j++)
		{
			printf("%d", ElementStructurant_ellipse.pixel[i][j]);
		}
		printf("\n");
	}



	return 0;
}
