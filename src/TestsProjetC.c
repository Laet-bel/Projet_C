//#include <stdlib.h>
//#include <stdio.h>
//
//#include "libCIPSI1.h"
//
//int main(void)
//{
//	/*IMAGE test = lectureImage("Source Images/In_30.pgm");
//	IMAGE testInv = inverseImage(test);
//	sauvegardeImage(test, "P5", "W_inv.pgm");
//
//	IMAGE WTH = whiteTopHat(testInv, 4,30);
//	sauvegardeImage(WTH, "P5", "WTH.pgm");
//
//	WTH = seuillageOtsu(WTH);
//	sauvegardeImage(WTH, "P5", "WTH_OTSU.pgm");
//
//	WTH = erosionImage(WTH, 4);
//	WTH = erosionImage(WTH, 4);
//	WTH = dilatationImage(WTH, 4);
//
//
//	sauvegardeImage(WTH, "P5", "In_30_WTH_OTSU_erode.pgm");*/
//
//	int rayon = 20;
//	ELEMENT_STRUCTURANT ElementStructurant = allocation_ElementStructurant('disk', rayon);
//
//	for (int i = 0; i < 2 * rayon + 1; i++)
//	{
//		for (int j = 0; j < 2 * rayon + 1; j++)
//		{
//			printf("%d", ElementStructurant.pixel[i][j]);
//		}
//		printf("\n");
//	}
//
//	return 0;
//}
