#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "libCIPSI1.h"

#define PI acos(-1)

/* static -> non extern */

#pragma region Points
POINT LecturePoint() {
	POINT point;
	printf("Entrer x : ");
	scanf("%f", &point.x);
	printf("Entrer y : ");
	scanf("%f", &point.y);
	return point;
}

void AffichePoint(POINT point) {
	printf("x : %f ,y :  %f \n", point.x, point.y);
}

float DistancePoints(POINT p1, POINT p2) {
	float dist = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	return dist;
}

POINT MilieuPoints(POINT p1, POINT p2) {

	POINT centre;
	centre.x = (p1.x + p2.x) / 2;
	centre.y = (p1.y + p2.y) / 2;
	return centre;
}

void GenerationAleatoirePoints(POINT t[], int n, float min, float max) {
	for (int i = 0; i < n; i++) {
		POINT p;
		float scale1 = rand() / (float)RAND_MAX;
		p.x = min + scale1 * (max - min);
		float scale2 = rand() / (float)RAND_MAX;
		p.y = min + scale2 * (max - min);

		t[i] = p;
	}
}

POINT* GenerationAleatoirePointsDyn(int n, float min, float max) {

	POINT* tab = (POINT*)calloc(n, sizeof(POINT));
	GenerationAleatoirePoints(tab, n, min, max);

	return tab;
}


POINT CentreGravitePoints(POINT t[], int n) {
	POINT centreGravite = { 0,0 };
	for (int i = 0; i < n; i++) {
		centreGravite.x += t[i].x;
		centreGravite.y += t[i].y;
	}
	centreGravite.x /= n;
	centreGravite.y /= n;

	return centreGravite;
}

#pragma region Points avec pointeurs 
void RechercheAbscissesExtremes(POINT tab[], int n, float* absMin, float* absMax) {
	*absMin = tab[0].x;
	for (int i = 0; i < n; i++) {
		if (tab[i].x < *absMin) {
			*absMin = tab[i].x;
		}
	}

	*absMax = tab[0].x;
	for (int i = 0; i < n; i++) {
		if (tab[i].x > *absMax) {
			*absMax = tab[i].x;
		}
	}
}

void RecherchePointsExtremes(POINT tab[], int n, POINT* ptDistMin, POINT* ptDistMax) {
	POINT centre = CentreGravitePoints(tab, n);

	float distMin = DistancePoints(centre, tab[0]), distMax = distMin;
	*ptDistMin = tab[0];
	*ptDistMax = tab[0];

	for (int i = 1; i < n; i++) {
		float temp = DistancePoints(centre, tab[i]);
		if (distMin > temp) {
			distMin = temp;
			*ptDistMin = tab[i];
		}
		if (distMax < temp) {
			distMax = temp;
			*ptDistMax = tab[i];
		}
	}
}
#pragma endregion

#pragma endregion

static intIMAGE allocationIntImage(int Nblig, int Nbcol)
{
	intIMAGE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (int*)calloc(Nblig * Nbcol, sizeof(int)); /* mise à 0 par défaut, gestion des bords lors de l'agrandissement opéré dans l'étiquetage */
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (int**)malloc(Nblig * sizeof(int*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &mat.data[i * Nbcol];

	return(mat);
}

static void liberationIntImage(intIMAGE* image)
{
	if (image->data != NULL) {
		free(image->data);
		image->data = NULL;
	}
	if (image->pixel != NULL) {
		free(image->pixel);
		image->pixel = NULL;
	}
}

/* fonctionnalités -> exportables */

IMAGE allocationImage(int Nblig, int Nbcol)
{
	IMAGE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (unsigned char*)malloc(Nblig * Nbcol * sizeof(unsigned char));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (unsigned char**)malloc(Nblig * sizeof(unsigned char*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &mat.data[i * Nbcol];

	return(mat);
}

void initialisationAleatoireImage(IMAGE image, int ngMin, int ngMax)
{
	int i, j;
	printf("Dans initialisation : image -> %p image.data -> %p image.pixel -> %p\n", &image, image.data, image.pixel);

	for (i = 0; i < image.Nblig; i++)
		for (j = 0; j < image.Nbcol; j++)
			image.pixel[i][j] = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));

	/* solution avec un seul indice
	for (i=0;i<image.Nblig*image.Nbcol;i++)
	image.data[i] = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));
	*/
}

void liberationImage(IMAGE* image)
{
	if (image->data != NULL) {
		free(image->data);
		image->data = NULL;
	}
	if (image->pixel != NULL) {
		free(image->pixel);
		image->pixel = NULL;
	}
}

IMAGE lectureImage(const char* in)
{
	FILE* F = NULL;
	IMAGE image = { 0,0,NULL };
	int dynamique = 0;

	if ((F = fopen(in, "r")) == NULL)
	{
		printf("Pb image inexistante");
	}
	else
	{
		char type[3];

		fgets(type, 3, F);
		fclose(F);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			char buf;

			F = fopen(in, "r");

			/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
			fscanf(F, "%c", &type[0]);
			fscanf(F, "%c", &type[1]);
			fscanf(F, "%c", &buf); /* caractère espacement */

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
				image.Nbcol = image.Nbcol * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				image.Nblig = image.Nblig * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				dynamique = dynamique * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			/* début des data */

			printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, image.Nblig, image.Nbcol);

			/* taille connue, allocation dynamique possible */
			image = allocationImage(image.Nblig, image.Nbcol);

			/* lecture pixel par pixel */
			{
				int i, j;
				int tmp;

				for (i = 0; i < image.Nblig; i++)
					for (j = 0; j < image.Nbcol; j++)
					{
						fscanf(F, "%d", &tmp);
						image.pixel[i][j] = (unsigned char)tmp;
					}
			}
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char buf;

				F = fopen(in, "rb");

				/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
				type[0] = fgetc(F);
				type[1] = fgetc(F);
				buf = fgetc(F); /* caractère espacement */

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
					image.Nbcol = image.Nbcol * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					image.Nblig = image.Nblig * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					dynamique = dynamique * 10 + (buf - '0');
					buf = fgetc(F);
				}

				/* début des data */

				printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, image.Nblig, image.Nbcol);

				/* taille connue, allocation dynamique possible */
				image = allocationImage(image.Nblig, image.Nbcol);

				/* lecture d'un bloc */
				fread(image.data, sizeof(unsigned char), image.Nbcol * image.Nblig, F);
			}
			else
				printf("Format non supporte pour l'instant...\n");
		fclose(F);
	}
	return image;
}

void sauvegardeImage(IMAGE image, const char* type, const char* out)
{
	FILE* F = NULL;

	if (image.data) /* image non vide */
	{
		printf("Sauvegarde image au type %s avec %d lignes et %d colonnes...\n", type, image.Nblig, image.Nbcol);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			F = fopen(out, "w");

			fprintf(F, "%s\n", type);
			fprintf(F, "# Created by TSE FISA IPSI\n");
			fprintf(F, "%d %d %d\n", image.Nbcol, image.Nblig, 255);
			/* sauvegarde pixel par pixel */
			{
				int i, j;

				for (i = 0; i < image.Nblig; i++)
					for (j = 0; j < image.Nbcol; j++)
						fprintf(F, "%d ", image.pixel[i][j]);
			}
			fclose(F);
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char tmp[255];

				F = fopen(out, "wb");

				fputs("P5\n", F);
				fputs("# Created by TSE FISA IPSI\n", F);
				sprintf(tmp, "%d %d %d\n", image.Nbcol, image.Nblig, 255);
				fputs(tmp, F);
				/* sauvegarde par bloc */
				fwrite(image.data, sizeof(unsigned char), image.Nbcol * image.Nblig, F);
				fclose(F);
			}
	}
	else
		printf("Image vide\n");
}

IMAGERGB allocationImageRGB(int Nblig, int Nbcol)
{
	IMAGERGB mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (RGB*)malloc(Nblig * Nbcol * sizeof(RGB));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (RGB**)malloc(Nblig * sizeof(RGB*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &(mat.data[i * Nbcol]);

	return(mat);
}

void initialisationAleatoireImageRGB(IMAGERGB image, int min, int max) {

	for (int i = 0; i < image.Nbcol * image.Nblig; i++) {
		image.data[i].B = min + rand() % (max + 1 - min);
		image.data[i].G = min + rand() % (max + 1 - min);
		image.data[i].R = min + rand() % (max + 1 - min);
	}
}


void liberationImageRGB(IMAGERGB* m)
{
	if (m->data != NULL) {
		free(m->data);
		m->data = NULL;
	}
	if (m->pixel != NULL) {
		free(m->pixel);
		m->pixel = NULL;
	}
}

IMAGERGB lectureImageRGB(const char* in)
{
	FILE* F = NULL;
	IMAGERGB image = { 0,0,NULL };
	int dynamique = 0;

	if ((F = fopen(in, "r")) == NULL)
	{
		printf("Pb image inexistante");
	}
	else
	{
		char type[3];

		fgets(type, 3, F);
		fclose(F);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P3") == 0)  /* cas ASCII couleur */
		{
			char tmp[255] = "";
			char buf;

			F = fopen(in, "r");

			/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
			fscanf(F, "%c", &type[0]);
			fscanf(F, "%c", &type[1]);
			fscanf(F, "%c", &buf); /* caractère espacement */

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
				image.Nbcol = image.Nbcol * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				image.Nblig = image.Nblig * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				dynamique = dynamique * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			/* début des data */

			printf("Lecture image RGB type %s avec %d lignes et %d colonnes...\n", type, image.Nblig, image.Nbcol);

			/* taille connue, allocation dynamique possible */
			image = allocationImageRGB(image.Nblig, image.Nbcol);

			/* lecture pixel par pixel */
			{
				int i, j;
				int tmp;

				for (i = 0; i < image.Nblig; i++)
					for (j = 0; j < image.Nbcol; j++)
					{
						fscanf(F, "%d", &tmp);
						image.pixel[i][j].R = (unsigned char)tmp;
						fscanf(F, "%d", &tmp);
						image.pixel[i][j].G = (unsigned char)tmp;
						fscanf(F, "%d", &tmp);
						image.pixel[i][j].B = (unsigned char)tmp;
					}
			}
		}
		else
			if (strcmp(type, "P6") == 0)  /* cas brut couleur */
			{
				char buf;

				F = fopen(in, "rb");

				/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
				type[0] = fgetc(F);
				type[1] = fgetc(F);
				buf = fgetc(F); /* caractère espacement */

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
					image.Nbcol = image.Nbcol * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					image.Nblig = image.Nblig * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					dynamique = dynamique * 10 + (buf - '0');
					buf = fgetc(F);
				}

				/* début des data */

				printf("Lecture image RGB type %s avec %d lignes et %d colonnes...\n", type, image.Nblig, image.Nbcol);

				/* taille connue, allocation dynamique possible */
				image = allocationImageRGB(image.Nblig, image.Nbcol);

				/* lecture d'un bloc */
				fread(image.data, sizeof(RGB), image.Nbcol * image.Nblig, F);
			}
			else
				printf("Format non supporte pour l'instant...\n");
		fclose(F);
	}
	return image;
}

void sauvegardeImageRGB(IMAGERGB image, const char* type, const char* out)
{
	FILE* F = NULL;

	if (image.data) /* image non vide */
	{
		printf("Sauvegarde image au type %s avec %d lignes et %d colonnes...\n", type, image.Nblig, image.Nbcol);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P3") == 0)  /* cas ASCII couleur */
		{
			F = fopen(out, "w");

			fprintf(F, "%s\n", type);
			fprintf(F, "# Created by TSE FISA IPSI\n");
			fprintf(F, "%d %d %d\n", image.Nbcol, image.Nblig, 255);
			/* sauvegarde pixel par pixel */
			{
				int i, j;

				for (i = 0; i < image.Nblig; i++)
					for (j = 0; j < image.Nbcol; j++) {
						fprintf(F, "%d ", image.pixel[i][j].R);
						fprintf(F, "%d ", image.pixel[i][j].G);
						fprintf(F, "%d ", image.pixel[i][j].B);
					}
				fclose(F);
			}
		}
		else
			if (strcmp(type, "P6") == 0)  /* cas brut couleur */
			{
				char tmp[255];

				F = fopen(out, "wb");

				fputs("P6\n", F);
				fputs("# Created by TSE FISA IPSI\n", F);
				sprintf(tmp, "%d %d %d\n", image.Nbcol, image.Nblig, 255);
				fputs(tmp, F);

				/* sauvegarde par bloc */
				fwrite(image.data, sizeof(RGB), image.Nbcol * image.Nblig, F);
				fclose(F);
			}
	}
	else
		printf("Image vide\n");
}

IMAGE inverseImage(IMAGE image)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;

	lut = (int*)calloc(256, sizeof(int)); /* LUT pour optimiser */
	for (i = 0; i < 256; i++)
		lut[i] = 255 - i;

	out = allocationImage(image.Nblig, image.Nbcol);
	for (i = 0; i < image.Nbcol * image.Nblig; i++)
		out.data[i] = lut[image.data[i]];

	free(lut);

	return out;
}

IMAGE seuillageImage(IMAGE image, int sInf, int sSup)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;

	lut = (int*)calloc(256, sizeof(int));
	for (i = sInf; i <= sSup; i++)
		lut[i] = 255;

	out = allocationImage(image.Nblig, image.Nbcol);
	for (i = 0; i < image.Nbcol * image.Nblig; i++)
		out.data[i] = lut[image.data[i]];

	free(lut);

	return out;
}


IMAGE planImage(IMAGERGB image, int plan)
{
	IMAGE out = { 0,0,NULL,NULL };
	int i;

	out = allocationImage(image.Nblig, image.Nbcol);
	switch (plan)
	{
	case 0: /* plan rouge */
		for (i = 0; i < out.Nbcol * out.Nblig; i++)
			out.data[i] = image.data[i].R;
		break;
	case 1: /* plan vert */
		for (i = 0; i < out.Nbcol * out.Nblig; i++)
			out.data[i] = image.data[i].G;
		break;
	case 2: /* plan bleu */
		for (i = 0; i < out.Nbcol * out.Nblig; i++)
			out.data[i] = image.data[i].B;
		break;
	}
	return(out);
}

IMAGE luminanceImage(IMAGERGB image, float r, float g, float b)
{
	IMAGE out = { 0,0,NULL,NULL };
	int i;

	out = allocationImage(image.Nblig, image.Nbcol);

	for (i = 0; i < out.Nbcol * out.Nblig; i++)
		out.data[i] = (unsigned char)((float)image.data[i].R * r + (float)image.data[i].G * g + (float)image.data[i].B * b);
	return(out);
}

int* histogrammeImageAncien(IMAGE image, int choix)
{
	int* h = NULL;

	if (image.data)
	{
		int i;

		h = (int*)calloc(256, sizeof(int));

		for (i = 0; i < image.Nbcol * image.Nblig; i++)
			h[(int)image.data[i]] += 1;

		if (choix)
		{
			/* sauvegarde dans histo.csv */
			FILE* F;

			F = fopen("histo.csv", "w");
			int i;
			for (i = 0; i < 256; i++)
				fprintf(F, "%d ; %d\n", i, h[i]);
			fclose(F);
		}
	}

	return h;
}

/// <summary>
/// Récupère l'histogramme d'une image en nuance de gris
/// </summary>
/// <param name="image"></param>
/// <param name="choix">Choix = 1 ==> enregistre l'histogramme en CSV</param>
/// <param name="nbNiveaux">Choix du nombre de niveaux qu'on veut dans l'histogramme</param>
/// <returns></returns>
int* histogrammeImage(IMAGE image, int choix, int nbNiveaux)
{
	//n : puissance (pas de quantification) 2^n
	// Avec 8 nous avons touts les niveau de gris 
	int n;

	if (nbNiveaux == 0) {
		n = 256;
	}
	n = log(nbNiveaux) / log(2);

	int* h = NULL;

	if (image.data)
	{
		int i;
		int bins = 256 >> (8 - n);

		h = (int*)calloc(bins, sizeof(int));

		for (i = 0; i < image.Nbcol * image.Nblig; i++)
			h[((int)image.data[i]) >> (8 - n)] += 1;

		if (choix)
		{
			/* sauvegarde dans histo.csv */
			FILE* F;

			F = fopen("res/histo.csv", "w");
			int i;
			for (i = 0; i < bins; i++)
				fprintf(F, "%d ; %d\n", i, h[i]);
			fclose(F);
		}
	}
	return h;
}

int* histogrammeImageRGB(IMAGERGB image, int choix, int nbNiveaux)
{
	int n;

	if (nbNiveaux == 0) {
		n = 256;
	}
	n = log(nbNiveaux) / log(2);

	int* h = NULL; /* RGB pas possible car UC, donc 3xint avec R G B successivement pour chaque niveau */

	if (image.data)
	{
		int i;
		int bins = 256 >> (8 - n);

		h = (int*)calloc(3 * bins, sizeof(int));

		for (i = 0; i < image.Nbcol * image.Nblig; i++)
		{
			h[3 * (((int)image.data[i].R) >> (8 - n))] += 1; /* R */
			h[3 * (((int)image.data[i].G) >> (8 - n)) + 1] += 1; /* G */
			h[3 * (((int)image.data[i].B) >> (8 - n)) + 2] += 1; /* B */
		}

		if (choix)
		{
			/* sauvegarde dans histo.csv */
			FILE* F;

			F = fopen("res/histoRGB.csv", "w");
			int i;
			for (i = 0; i < bins; i++)
				fprintf(F, "%d ; %d; %d; %d\n", i, h[3 * i], h[3 * i + 1], h[3 * i + 2]);
			fclose(F);
		}
	}

	return h;
}


IMAGE expansionImage(IMAGE image, int outMin, int outMax)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;
	float a, b;
	int mini = 255, maxi = 0;

	for (i = 0; i < image.Nblig * image.Nbcol; i++)
	{
		mini = (image.data[i] < mini) ? image.data[i] : mini;
		maxi = (image.data[i] > maxi) ? image.data[i] : maxi;
	}

	a = (float)(outMax - outMin) / ((float)(maxi - mini));
	b = (float)outMin - a * mini;

	lut = (int*)calloc(256, sizeof(int));
	for (i = mini; i <= maxi; i++)
		lut[i] = (int)(a * i + b);

	out = allocationImage(image.Nblig, image.Nbcol);
	for (i = 0; i < image.Nbcol * image.Nblig; i++)
		out.data[i] = lut[image.data[i]];

	free(lut);

	return out;
}

IMAGE egalisationImage(IMAGE image)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* h = histogrammeImage(image, 0, 256);
	int* hC = NULL;
	int* lut = NULL;
	int i;

	hC = (int*)calloc(256, sizeof(int));
	hC[0] = h[0];
	for (i = 1; i < 256; i++)
		hC[i] = hC[i - 1] + h[i];
	free(h);
	h = NULL;

	lut = (int*)calloc(256, sizeof(int));
	for (i = 0; i < 256; i++)
		lut[i] = (int)((255 / (float)(image.Nbcol * image.Nblig)) * hC[i]);
	free(hC);
	hC = NULL;

	out = allocationImage(image.Nblig, image.Nbcol);
	for (i = 0; i < image.Nbcol * image.Nblig; i++)
		out.data[i] = lut[image.data[i]];
	free(lut);

	return(out);
}

SIGNATURES statistiquesImage(IMAGE image)
{
	SIGNATURES sig;
	int i;
	double som = 0, som2 = 0;
	int somme, moitPop = (image.Nbcol * image.Nblig) / 2;
	int* h = histogrammeImage(image, 0, 256);

	for (i = 0; i < image.Nbcol * image.Nblig; i++) {
		som += (double)image.data[i];
		som2 += (double)image.data[i] * (double)image.data[i];
	}

	som /= (double)(image.Nblig * image.Nbcol);
	som2 = sqrt(som2 / (double)(image.Nblig * image.Nbcol) - som * som);

	sig.moyenne = som;
	sig.ecartType = som2;

	i = 0;
	while (h[i] == 0)
		i += 1;
	sig.min = i;

	i = 255;
	while (h[i] == 0)
		i -= 1;
	sig.max = i;

	i = 0;
	somme = h[i];
	while (somme < moitPop) {
		i += 1;
		if (i < 256)
			somme += h[i];
	}
	sig.mediane = i;

	free(h);
	h = NULL;

	return sig;
}

IMAGE seuillageOtsu(IMAGE image)
{
	IMAGE out = { 0, 0, NULL, NULL };
	int* h = histogrammeImage(image, 0, 256);
	int* hC = NULL;

	double* tab = NULL;
	int i, seuil;
	double M1, M2;
	double w1;
	int* lut = NULL;
	int min, max;

	/* recherche min et max */
	i = 0;
	while (h[i] == 0)
		i++;
	min = i;
	i = 255;
	while (h[i] == 0)
		i--;
	max = i;

	hC = (int*)calloc(256, sizeof(int));
	hC[0] = h[0];
	for (i = 1; i < 256; i++)
		hC[i] = hC[i - 1] + h[i];

	tab = (double*)calloc(256, sizeof(double));

	/* parcours entre min et max pour éviter divisions par 0 */
	/* initialisation */
	M1 = min;
	seuil = min;
	w1 = (double)hC[min] / (double)(image.Nbcol * image.Nblig);
	M2 = 0;
	for (int i = min + 1; i <= max; i++)
		M2 += (double)h[i] * i;
	M2 /= (double)(hC[max] - h[min]);
	tab[min] = w1 * (1 - w1) * (M1 - M2) * (M1 - M2);

	// parcours
	for (int i = min + 1; i < max; i++) {
		M1 = ((double)hC[i - 1] * M1 + (double)h[i] * i) / hC[i];
		M2 = ((double)(hC[255] - hC[i - 1]) * M2 - (double)(h[i] * i)) / (double)(hC[255] - hC[i]);
		w1 = (double)hC[i] / (double)(image.Nbcol * image.Nblig);
		tab[i] = w1 * (1 - w1) * (M1 - M2) * (M1 - M2);
		if (tab[i] > tab[seuil])
			seuil = i;
	}

	free(h); h = NULL;
	free(hC); hC = NULL;

	free(tab);

	lut = (int*)calloc(256, sizeof(int));
	for (i = seuil; i <= max; i++)
		lut[i] = 255;

	out = allocationImage(image.Nblig, image.Nbcol);
	for (i = 0; i < image.Nbcol * image.Nblig; i++)
		out.data[i] = lut[image.data[i]];

	free(lut);
	return out;
}

/* étiquetage V8 */
IMAGE labelImage(IMAGE image, int* nbComp)
{
	IMAGE out = { 0,0,NULL,NULL };

	int i, ii, j, jj;

	int k = 1, kk;
	int eps;
	int predNonNul[5];
	int nbPredNonNuls;

	int nbMaxEtiquettes = image.Nblig * image.Nbcol;
	intIMAGE withBords = { 0,0,NULL,NULL };

	withBords = allocationIntImage(image.Nblig + 2, image.Nbcol + 2);

	for (i = 0, ii = 1; i < image.Nblig; i++, ii++) // pure copie 
		for (j = 0, jj = 1; j < image.Nbcol; j++, jj++)
			withBords.pixel[ii][jj] = (int)image.pixel[i][j];

	int* tableEtiquette = NULL;
	tableEtiquette = (int*)calloc(nbMaxEtiquettes, sizeof(int));

	for (kk = 0; kk < nbMaxEtiquettes; kk++) {
		tableEtiquette[kk] = kk;
	}

	for (i = 1; i < withBords.Nblig - 1; i++)
		for (j = 1; j < withBords.Nbcol - 1; j++) {
			if (withBords.pixel[i][j] != 0) {
				// voisinage V8 
				int pred1 = withBords.pixel[i][j - 1];
				int pred2 = withBords.pixel[i - 1][j - 1];
				int pred3 = withBords.pixel[i - 1][j];
				int pred4 = withBords.pixel[i - 1][j + 1];

				nbPredNonNuls = 0;
				if (pred1) predNonNul[nbPredNonNuls++] = pred1;
				if (pred2) predNonNul[nbPredNonNuls++] = pred2;
				if (pred3) predNonNul[nbPredNonNuls++] = pred3;
				if (pred4) predNonNul[nbPredNonNuls++] = pred4;

				if (nbPredNonNuls == 0) {
					withBords.pixel[i][j] = k;
					k++;
				}
				else {
					eps = 0;
					int minPred = tableEtiquette[predNonNul[0]];
					int maxPred = tableEtiquette[predNonNul[0]];
					while (eps < nbPredNonNuls) {
						if (tableEtiquette[predNonNul[eps]] < minPred) minPred = tableEtiquette[predNonNul[eps]];
						if (tableEtiquette[predNonNul[eps]] > maxPred) maxPred = tableEtiquette[predNonNul[eps]];
						eps++;
					}
					if (minPred == maxPred)
						withBords.pixel[i][j] = minPred;
					else {
						withBords.pixel[i][j] = minPred;
						for (eps = 0; eps < nbPredNonNuls; eps++) {
							int beta = predNonNul[eps];
							while (tableEtiquette[beta] != minPred) {
								int m = tableEtiquette[beta];
								tableEtiquette[beta] = minPred;
								beta = m;
							}
						}
					}
				}
			}
		}


	// actualisation de la table d'équivalence
	for (int kk = 1; kk < k; kk++) {
		int m = kk;
		while (tableEtiquette[m] != m)
			m = tableEtiquette[m];
		tableEtiquette[kk] = m;
	}

	int* etiquettes = (int*)calloc(k + 1, sizeof(int));

	// histo pour repérer les trous
	for (int kk = 1; kk < k; kk++)
		etiquettes[tableEtiquette[kk]]++;

	// on remet à jour les index (etiquetage définitif hors trou)
	etiquettes[0] = 0;
	int compt = 1;
	for (int kk = 1; kk < k; kk++) {
		if (etiquettes[kk])
			etiquettes[kk] = compt++;
	}

	for (i = 0; i < withBords.Nblig; i++)
		for (j = 0; j < withBords.Nbcol; j++) {
			withBords.pixel[i][j] = etiquettes[tableEtiquette[withBords.pixel[i][j]]];
		}

	free(etiquettes);
	free(tableEtiquette);

	out = allocationImage(image.Nblig, image.Nbcol);

	*nbComp = compt - 1;
	for (i = 0, ii = 1; i < image.Nblig; i++, ii++)
		for (j = 0, jj = 1; j < image.Nbcol; j++, jj++)
			out.pixel[i][j] = (unsigned char)withBords.pixel[ii][jj];

	liberationIntImage(&withBords);

	return out;
}

/// <summary>
/// Coloriser l'image 
/// </summary>
/// <param name="image"></param>
/// <param name="table">Chemin d'accès du fichier</param>
/// <returns></returns>
IMAGERGB colorisationImage(IMAGE image, char* table) {
	char ligne[255];
	int index, r = 0, g = 0, b = 0;
	FILE* lut = fopen(table, "r");
	int i = 0;
	RGB* LUT = (RGB*)calloc(256, sizeof(RGB));


	while (fgets(ligne, 255, lut) != NULL)
	{
		sscanf(ligne, "%d %d %d %d", &index, &r, &g, &b);
		LUT[index].R = r;
		LUT[index].G = g;
		LUT[index].B = b;

	}
	fclose(lut);

	IMAGERGB imageRGB = { 0 , 0 , NULL , NULL };
	imageRGB = allocationImageRGB(image.Nblig, image.Nbcol);
	int valeur;
	for (i = 0; i < (image.Nblig * image.Nbcol); i++) {
		valeur = image.data[i];
		imageRGB.data[i].B = LUT[valeur].B;
		imageRGB.data[i].G = LUT[valeur].G;
		imageRGB.data[i].R = LUT[valeur].R;
	}

	free(LUT);
	return imageRGB;
}

double distanceHistogrammeImage(int* h1, int* h2, int taille) {
	double distance = 0;

	for (int i = 0; i < taille; i++) {
		distance += pow(h1[i] - h2[i], 2);
	}
	distance *= 1.0 / taille;
	distance = sqrt(distance);

	return distance;
}

/// <summary>
/// Prend une image labélisé (pas colorisé) et récupère différentes signature pour nos composantes connexes
/// </summary>
/// <param name="image"></param>
/// <param name="nbComp"></param>
/// <returns></returns>
SIGNATURE_COMPOSANTE_CONNEXE* signaturesImage(IMAGE image, int nbComp) {
	SIGNATURE_COMPOSANTE_CONNEXE* tab = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbComp + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));

	//Récupère la surface
	int* histo = (int*)malloc(256 * sizeof(int));
	histo = histogrammeImage(image, 0, 256); //Enregistre notre histograme dans res

	for (int i = 0; i < nbComp + 1; i++) {
		SIGNATURE_COMPOSANTE_CONNEXE temp = { 0 };
		temp.surface = histo[i];

		temp.rayon = sqrt(temp.surface / 3.14);
		//temp.perimetre = 2 * 3.14 * temp.rayon; //TODO 
		temp.compacite = (temp.perimetre * temp.perimetre) / (4 * PI * temp.surface);

		tab[i] = temp;
	}

	//Centre de gravité : 
	for (int j = 0; j < image.Nbcol; j++) {
		for (int i = 0; i < image.Nblig; i++) {
			int val = image.pixel[i][j];
			tab[val].CG.x += j;
			tab[val].CG.y += i;
		}
	}
	for (int i = 0; i < (nbComp + 1); i++) {
		tab[i].CG.x /= tab[i].surface;
		tab[i].CG.y /= tab[i].surface;
	}

	//Bord : 
	//Gauche : 
	for (int i = 0; i < image.Nblig; i++) {
		int val = image.pixel[i][0];
		if (val) {
			tab[val].bord = 1;
		}
	}

	//Droite : 
	for (int i = 0; i < image.Nblig; i++) {
		int val = image.pixel[i][image.Nbcol - 1];
		if (val) {
			tab[val].bord = 1;
		}
	}

	//Haut : 
	for (int j = 0; j < image.Nblig; j++) {
		int val = image.pixel[0][j];
		if (val) {
			tab[val].bord = 1;
		}
	}

	//Bas : 
	for (int j = 0; j < image.Nblig; j++) {
		int val = image.pixel[image.Nblig - 1][j];
		if (val) {
			tab[val].bord = 1;
		}
	}

	return tab;
}

void affiche_signatures(SIGNATURE_COMPOSANTE_CONNEXE* signatures, int nbComp) {
	for (int i = 0; i < (nbComp + 1); i++) {
		printf("\nCOMPOSANTE %d : \n", i);
		printf("Surface : %d \n", signatures[i].surface);
		printf("Perimetre : %d \n", signatures[i].perimetre);
		printf("Compacite : %d \n", signatures[i].compacite);
		printf("Bord : %d \n", signatures[i].bord);
		printf("Rayon : %f \n", signatures[i].rayon);
		printf("Cenre de gravite : (%fx;%fy) \n", signatures[i].CG.x, signatures[i].CG.y);
		printf("\n");
	}
}

int* LUTsansBord(SIGNATURE_COMPOSANTE_CONNEXE* signatures, int nbComp) {
	int* LUT = (int*)calloc((nbComp + 1), sizeof(int));

	for (int i = 0; i < nbComp + 1; i++) {
		if (!signatures[i].bord) {
			LUT[i] = i;
		}
	}

	return LUT;
}

IMAGE ImageAvecLUT(IMAGE image, int* LUT) {
	IMAGE nouvelle = allocationImage(image.Nblig, image.Nbcol);
	for (int i = 0; i < (image.Nbcol * image.Nblig); i++) {
		int val = image.data[i];
		nouvelle.data[i] = LUT[val];
	}
	return nouvelle;
}

#pragma region Regression
void regression(POINT* tab, int n, float* a, float* b)
{
	float somme_x, somme_y, somme_x2, somme_xy;
	int i;

	somme_x = 0.;
	somme_y = 0.;
	somme_x2 = 0.;
	somme_xy = 0.;

	for (i = 0; i < n; i++) {
		somme_x += tab[i].x;
		somme_y += tab[i].y;
		somme_x2 += tab[i].x * tab[i].x;
		somme_xy += (tab[i].x * tab[i].y);
	}

	*a = (somme_xy - ((somme_x * somme_y) / (float)n)) / (somme_x2 - ((somme_x * somme_x) / (float)n));
	*b = (somme_y - ((*a) * somme_x)) / (float)n;
}

void sortieRegression(const char* nom, POINT* pts, int n)
{
	float a, b;
	regression(pts, n, &a, &b);

	FILE* F;
	F = fopen(nom, "w");
	int i;
	for (i = 0; i < n; i++)
	{
		fprintf(F, "%f ; %f ; %f \n", pts[i].x, pts[i].y, (a * pts[i].x + b));
	}

	fclose(F);
}

POINT* ImageVersPoints(IMAGE img, int* n, char axe)
{
	POINT* pts = (POINT*)calloc(img.Nbcol * img.Nblig, sizeof(POINT));
	int cmpt = 0;

	if (axe == 'i')
	{
		for (int i = 0; i < img.Nblig; i++)
		{
			for (int j = 0; j < img.Nbcol; j++)
			{
				if (img.pixel[i][j] == 1)
				{
					pts[cmpt].x = i;
					pts[cmpt].y = j;

					cmpt++;
				}
			}
		}


	}

	if (axe == 'j')
	{
		for (int i = 0; i < img.Nblig; i++)
		{
			for (int j = 0; j < img.Nbcol; j++)
			{
				if (img.pixel[i][j] == 1)
				{
					pts[cmpt].x = j;
					pts[cmpt].y = i;

					cmpt++;
				}
			}
		}
	}

	*n = cmpt;
	return pts;
}

IMAGE imageSortieRegression(IMAGE img, char axe)
{
	IMAGE imgSortie = img;
	float a, b;
	int n;

	if (axe == 'i')
	{
		POINT* PointI = ImageVersPoints(img, &n, 'i');
		regression(PointI, n, &a, &b);

		for (int i = 0; i < img.Nblig; i++)
		{
			if ((a * i + b) > img.Nbcol)
			{
				break;
			}
			imgSortie.pixel[i][(int)(a * i + b)] = 2;
		}
	}

	if (axe == 'j')
	{

		POINT* PointJ = ImageVersPoints(img, &n, 'j');
		regression(PointJ, n, &a, &b);

		for (int j = 0; j < img.Nbcol; j++)
		{
			if ((a * j + b) > img.Nblig)
			{
				break;
			}
			imgSortie.pixel[(int)(a * j + b)][j] = 2;
		}
	}

	return imgSortie;
}
#pragma endregion

#pragma region Morphologie

IMAGE erosionImage(IMAGE image, int voisinage)
{
	IMAGE imageErode = allocationImage(image.Nblig, image.Nbcol);

	if (voisinage == 4)
	{
		//Pixel HG
		imageErode.pixel[0][0] = min(image.pixel[0][0], min(image.pixel[1][0], image.pixel[0][1]));
		//Pixel HD
		imageErode.pixel[0][image.Nbcol - 1] = min(image.pixel[0][image.Nbcol - 1], min(image.pixel[1][image.Nbcol - 1], image.pixel[0][image.Nbcol - 2]));
		//Pixel BG
		imageErode.pixel[image.Nblig - 1][0] = min(image.pixel[image.Nblig - 1][0], min(image.pixel[image.Nblig - 2][0], image.pixel[image.Nblig - 1][1]));
		//Pixel BD
		imageErode.pixel[image.Nblig - 1][image.Nbcol - 1] = min(image.pixel[image.Nblig - 1][image.Nbcol - 1], min(image.pixel[image.Nblig - 1][image.Nbcol - 2], image.pixel[image.Nblig - 2][image.Nbcol - 1]));

		//BH
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageErode.pixel[0][j] = min(min(image.pixel[0][j], image.pixel[0][j - 1]), min(image.pixel[1][j], image.pixel[0][j + 1]));
		}
		//BB
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageErode.pixel[image.Nblig - 1][j] = min(min(image.pixel[image.Nblig - 1][j], image.pixel[image.Nblig - 1][j - 1]), min(image.pixel[image.Nblig - 2][j], image.pixel[image.Nblig - 1][j + 1]));
		}
		//BG
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageErode.pixel[i][0] = min(min(image.pixel[i][0], image.pixel[i - 1][0]), min(image.pixel[i + 1][0], image.pixel[i][1]));
		}
		//BD
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageErode.pixel[i][image.Nbcol - 1] = min(min(image.pixel[i][image.Nbcol - 1], image.pixel[i - 1][image.Nbcol - 1]), min(image.pixel[i + 1][image.Nbcol - 1], image.pixel[i][image.Nbcol - 2]));
		}

		//Centre image
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			for (int j = 1; j < image.Nbcol - 1; j++)
			{
				imageErode.pixel[i][j] = min(min(image.pixel[i][j], image.pixel[i][j]), min(min(image.pixel[i - 1][j], image.pixel[i + 1][j]), min(image.pixel[i][j - 1], image.pixel[i][j + 1])));
			}
		}
	}
	if (voisinage == 8)
	{
		//Pixel HG
		imageErode.pixel[0][0] = min(min(image.pixel[0][0], image.pixel[1][1]), min(image.pixel[1][0], image.pixel[0][1]));
		//Pixel HD
		imageErode.pixel[0][image.Nbcol - 1] = min(min(image.pixel[0][image.Nbcol - 1], image.pixel[1][image.Nbcol - 2]), min(image.pixel[1][image.Nbcol - 1], image.pixel[0][image.Nbcol - 2]));
		//Pixel BG
		imageErode.pixel[image.Nblig - 1][0] = min(min(image.pixel[image.Nblig - 1][0], image.pixel[image.Nblig - 2][1]), min(image.pixel[image.Nblig - 2][0], image.pixel[image.Nblig - 1][1]));
		//Pixel BD
		imageErode.pixel[image.Nblig - 1][image.Nbcol - 1] = min(min(image.pixel[image.Nblig - 1][image.Nbcol - 1], image.pixel[image.Nblig - 2][image.Nbcol - 2]), min(image.pixel[image.Nblig - 1][image.Nbcol - 2], image.pixel[image.Nblig - 2][image.Nbcol - 1]));

		//BH
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageErode.pixel[0][j] = min(min(image.pixel[1][j - 1], image.pixel[1][j + 1]), min(min(image.pixel[0][j], image.pixel[0][j - 1]), min(image.pixel[1][j], image.pixel[0][j + 1])));
		}
		//BB
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageErode.pixel[image.Nblig - 1][j] = min(min(image.pixel[image.Nblig - 1][j - 1], image.pixel[image.Nblig - 1][j + 1]), min(min(image.pixel[image.Nblig - 1][j], image.pixel[image.Nblig - 1][j - 1]), min(image.pixel[image.Nblig - 2][j], image.pixel[image.Nblig - 1][j + 1])));
		}
		//BG
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageErode.pixel[i][0] = min(min(image.pixel[i + 1][1], image.pixel[i - 1][1]), min(min(image.pixel[i][0], image.pixel[i - 1][0]), min(image.pixel[i + 1][0], image.pixel[i][1])));
		}
		//BD
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageErode.pixel[i][image.Nbcol - 1] = min(min(image.pixel[i + 1][image.Nbcol - 2], image.pixel[i - 1][image.Nbcol - 2]), min(min(image.pixel[i][image.Nbcol - 1], image.pixel[i - 1][image.Nbcol - 1]), min(image.pixel[i + 1][image.Nbcol - 1], image.pixel[i][image.Nbcol - 2])));
		}

		//Centre image
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			for (int j = 1; j < image.Nbcol - 1; j++)
			{
				imageErode.pixel[i][j] = min(min(min(image.pixel[i][j], image.pixel[i][j]), min(image.pixel[i - 1][j], image.pixel[i + 1][j])), min(min(min(image.pixel[i][j - 1], image.pixel[i][j + 1]), min(image.pixel[i - 1][j - 1], image.pixel[i - 1][j + 1])), min(image.pixel[i + 1][j - 1], image.pixel[i + 1][j + 1])));
			}
		}
	}
	return imageErode;
}


IMAGE dilatationImage(IMAGE image, int voisinage)
{
	IMAGE imageDilate = allocationImage(image.Nblig, image.Nbcol);

	if (voisinage == 4)
	{
		//Pixel HG
		imageDilate.pixel[0][0] = max(image.pixel[0][0], max(image.pixel[1][0], image.pixel[0][1]));
		//Pixel HD
		imageDilate.pixel[0][image.Nbcol - 1] = max(image.pixel[0][image.Nbcol - 1], max(image.pixel[1][image.Nbcol - 1], image.pixel[0][image.Nbcol - 2]));
		//Pixel BG
		imageDilate.pixel[image.Nblig - 1][0] = max(image.pixel[image.Nblig - 1][0], max(image.pixel[image.Nblig - 2][0], image.pixel[image.Nblig - 1][1]));
		//Pixel BD
		imageDilate.pixel[image.Nblig - 1][image.Nbcol - 1] = max(image.pixel[image.Nblig - 1][image.Nbcol - 1], max(image.pixel[image.Nblig - 1][image.Nbcol - 2], image.pixel[image.Nblig - 2][image.Nbcol - 1]));

		//BH
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageDilate.pixel[0][j] = max(max(image.pixel[0][j], image.pixel[0][j - 1]), max(image.pixel[1][j], image.pixel[0][j + 1]));
		}
		//BB
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageDilate.pixel[image.Nblig - 1][j] = max(max(image.pixel[image.Nblig - 1][j], image.pixel[image.Nblig - 1][j - 1]), max(image.pixel[image.Nblig - 2][j], image.pixel[image.Nblig - 1][j + 1]));
		}
		//BG
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageDilate.pixel[i][0] = max(max(image.pixel[i][0], image.pixel[i - 1][0]), max(image.pixel[i + 1][0], image.pixel[i][1]));
		}
		//BD
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageDilate.pixel[i][image.Nbcol - 1] = max(max(image.pixel[i][image.Nbcol - 1], image.pixel[i - 1][image.Nbcol - 1]), max(image.pixel[i + 1][image.Nbcol - 1], image.pixel[i][image.Nbcol - 2]));
		}

		//Centre image
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			for (int j = 1; j < image.Nbcol - 1; j++)
			{
				imageDilate.pixel[i][j] = max(max(image.pixel[i][j], image.pixel[i][j]), max(max(image.pixel[i - 1][j], image.pixel[i + 1][j]), max(image.pixel[i][j - 1], image.pixel[i][j + 1])));
			}
		}
	}
	if (voisinage == 8)
	{
		//Pixel HG
		imageDilate.pixel[0][0] = max(max(image.pixel[0][0], image.pixel[1][1]), max(image.pixel[1][0], image.pixel[0][1]));
		//Pixel HD
		imageDilate.pixel[0][image.Nbcol - 1] = max(max(image.pixel[0][image.Nbcol - 1], image.pixel[1][image.Nbcol - 2]), max(image.pixel[1][image.Nbcol - 1], image.pixel[0][image.Nbcol - 2]));
		//Pixel BG
		imageDilate.pixel[image.Nblig - 1][0] = max(max(image.pixel[image.Nblig - 1][0], image.pixel[image.Nblig - 2][1]), max(image.pixel[image.Nblig - 2][0], image.pixel[image.Nblig - 1][1]));
		//Pixel BD
		imageDilate.pixel[image.Nblig - 1][image.Nbcol - 1] = max(max(image.pixel[image.Nblig - 1][image.Nbcol - 1], image.pixel[image.Nblig - 2][image.Nbcol - 2]), max(image.pixel[image.Nblig - 1][image.Nbcol - 2], image.pixel[image.Nblig - 2][image.Nbcol - 1]));

		//BH
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageDilate.pixel[0][j] = max(max(image.pixel[1][j - 1], image.pixel[1][j + 1]), max(max(image.pixel[0][j], image.pixel[0][j - 1]), max(image.pixel[1][j], image.pixel[0][j + 1])));
		}
		//BB
		for (int j = 1; j < image.Nbcol - 1; j++)
		{
			imageDilate.pixel[image.Nblig - 1][j] = max(max(image.pixel[image.Nblig - 1][j - 1], image.pixel[image.Nblig - 1][j + 1]), max(max(image.pixel[image.Nblig - 1][j], image.pixel[image.Nblig - 1][j - 1]), max(image.pixel[image.Nblig - 2][j], image.pixel[image.Nblig - 1][j + 1])));
		}
		//BG
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageDilate.pixel[i][0] = max(max(image.pixel[i + 1][1], image.pixel[i - 1][1]), max(max(image.pixel[i][0], image.pixel[i - 1][0]), max(image.pixel[i + 1][0], image.pixel[i][1])));
		}
		//BD
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			imageDilate.pixel[i][image.Nbcol - 1] = max(max(image.pixel[i + 1][image.Nbcol - 2], image.pixel[i - 1][image.Nbcol - 2]), max(max(image.pixel[i][image.Nbcol - 1], image.pixel[i - 1][image.Nbcol - 1]), max(image.pixel[i + 1][image.Nbcol - 1], image.pixel[i][image.Nbcol - 2])));
		}

		//Centre image
		for (int i = 1; i < image.Nblig - 1; i++)
		{
			for (int j = 1; j < image.Nbcol - 1; j++)
			{
				imageDilate.pixel[i][j] = max(max(max(image.pixel[i][j], image.pixel[i][j]), max(image.pixel[i - 1][j], image.pixel[i + 1][j])), max(max(max(image.pixel[i][j - 1], image.pixel[i][j + 1]), max(image.pixel[i - 1][j - 1], image.pixel[i - 1][j + 1])), max(image.pixel[i + 1][j - 1], image.pixel[i + 1][j + 1])));
			}
		}
	}
	return imageDilate;
}

IMAGE erosionImageavecSE(IMAGE image,const ELEMENT_STRUCTURANT se) {
	return image;
}

IMAGE ouvertureImage(IMAGE image, int voisinage)
{
	IMAGE imageOuverte = allocationImage(image.Nblig, image.Nbcol);
	IMAGE imageErode = erosionImage(image, voisinage);
	imageOuverte = dilatationImage(imageErode, voisinage);

	return imageOuverte;
}


IMAGE fermetureImage(IMAGE image, int voisinage)
{
	IMAGE imageFerme = allocationImage(image.Nblig, image.Nbcol);
	IMAGE imageDilate = dilatationImage(image, voisinage);
	imageFerme = erosionImage(image, voisinage);

	return imageFerme;
}

IMAGE contourImage(IMAGE image, int voisinage)
{
	IMAGE contour = allocationImage(image.Nblig, image.Nbcol);
	IMAGE imageErode = erosionImage(image, voisinage);
	int temp;
	for (int i = 0; i < image.Nbcol * image.Nblig; i++)
	{
		temp = image.data[i] - imageErode.data[i];

		if (temp < 0)
		{
			temp = 0;
		}
		if (temp > 255)
		{
			temp = 255;
		}

		contour.data[i] = temp;
	}


	return contour;
}

IMAGE whiteTopHat(IMAGE image, int voisinage, int n_iteration)
{

	IMAGE whiteTopHat = allocationImage(image.Nblig, image.Nbcol);
	IMAGE imageTemp = allocationImage(image.Nblig, image.Nbcol);
	imageTemp = erosionImage(image, voisinage);
	for (int i = 0; i < n_iteration - 1; i++)
	{
		imageTemp = erosionImage(imageTemp, voisinage);
	}
	for (int i = 0; i < n_iteration; i++)
	{
		imageTemp = dilatationImage(imageTemp, voisinage);
	}


	int temp;
	for (int i = 0; i < image.Nbcol * image.Nblig; i++)
	{
		temp = image.data[i] - imageTemp.data[i];

		if (temp < 0)
		{
			temp = 0;
		}
		if (temp > 255)
		{
			temp = 255;
		}

		whiteTopHat.data[i] = temp;
	}

	return whiteTopHat;
}

IMAGE blackTopHat(IMAGE image, int voisinage, int n_iteration)
{
	IMAGE blackTopHat = allocationImage(image.Nblig, image.Nbcol);
	IMAGE imageTemp = allocationImage(image.Nblig, image.Nbcol);
	imageTemp = dilatationImage(image, voisinage);
	for (int i = 0; i < n_iteration - 1; i++)
	{
		imageTemp = dilatationImage(imageTemp, voisinage);
	}
	for (int i = 0; i < n_iteration; i++)
	{
		imageTemp = erosionImage(imageTemp, voisinage);
	}

	int temp;
	for (int i = 0; i < image.Nbcol * image.Nblig; i++)
	{
		temp = imageTemp.data[i] - image.data[i];

		if (temp < 0)
		{
			temp = 0;
		}
		if (temp > 255)
		{
			temp = 255;
		}

		blackTopHat.data[i] = temp;
	}

	return blackTopHat;
}
#pragma endregion

#pragma region Element Structurant

void remplissageV4(unsigned char** pixel, int x, int y, int colcible, int colrep)
{
	if (pixel[x][y] == colcible)
	{
		pixel[x][y] = colrep;

		remplissageV4(pixel, x - 1, y, colcible, colrep);
		remplissageV4(pixel, x + 1, y, colcible, colrep);
		remplissageV4(pixel, x, y + 1, colcible, colrep);
		remplissageV4(pixel, x, y - 1, colcible, colrep);
	}
}

ELEMENT_STRUCTURANT allocation_ElementStructurant(const char* type, int hauteur, int largeur)
{

	if (type == 'disk')
	{
		if (hauteur >= largeur) {
			return allocation_ElementStructurant_disk(type, hauteur);
		}
		else {
			return allocation_ElementStructurant_disk(type, largeur);
		}
	}
	if (type == 'rect') {
		return allocation_ElementStructurant_rect(type, hauteur, largeur);
	}
	if (type == 'ligV') {
		return allocation_ElementStructurant_rect(type, hauteur, 1);
	}
	if (type == 'ligH') {
		return allocation_ElementStructurant_rect(type, 1, largeur);
	}
	if (type == 'elli') {
		return allocation_ElementStructurant_ellipse(type, hauteur, largeur);
	}
	if (type == 'V4') {
		return allocation_ElementStructurant_ellipse(type, 1,1);
	}
	if (type == 'V8') {
		return allocation_ElementStructurant_rect(type, 3, 3);
	}

	return;
}

ELEMENT_STRUCTURANT allocation_ElementStructurant_disk(const char* type, int rayon) {
	ELEMENT_STRUCTURANT ElementStructurant;
	ElementStructurant.type = type;
	ElementStructurant.hauteur = rayon;
	ElementStructurant.largeur = rayon;

	int centreSE;
	int tailleSE;
	int i;

	tailleSE = pow((2 * rayon) + 1, 2);
	ElementStructurant.data = (unsigned char*)calloc(tailleSE, sizeof(unsigned char));
	if (ElementStructurant.data == NULL)
	{
		return(ElementStructurant);
	}
	ElementStructurant.pixel = (unsigned char**)malloc(((2 * rayon) + 1) * sizeof(unsigned char*));
	if (ElementStructurant.pixel == NULL) {
		free(ElementStructurant.data);
		ElementStructurant.data = NULL;
		return(ElementStructurant);
	}

	for (i = 0; i < ((2 * rayon) + 1); i++)
	{
		ElementStructurant.pixel[i] = &ElementStructurant.data[i * ((2 * rayon) + 1)];
	}

	centreSE = floor((tailleSE) / 2.0);
	int centerX = rayon;
	int centerY = rayon;

	int x = 0;
	int y = rayon;
	int m = 5 - 4 * rayon;

	while (x <= y)
	{
		ElementStructurant.pixel[centerX + x][centerY + y] = 1;
		ElementStructurant.pixel[centerX + x][centerY - y] = 1;
		ElementStructurant.pixel[centerX - x][centerY + y] = 1;
		ElementStructurant.pixel[centerX - x][centerY - y] = 1;
		ElementStructurant.pixel[centerX + y][centerY + x] = 1;
		ElementStructurant.pixel[centerX + y][centerY - x] = 1;
		ElementStructurant.pixel[centerX - y][centerY + x] = 1;
		ElementStructurant.pixel[centerX - y][centerY - x] = 1;

		if (m > 0)
		{
			y--;
			m -= 8 * y;
		}

		x++;

		m += 8 * x + 4;
	}

	remplissageV4(ElementStructurant.pixel, rayon, rayon, 0, 1);
	return ElementStructurant;
}

ELEMENT_STRUCTURANT allocation_ElementStructurant_rect(const char* type, int hauteur, int largeur) {
	ELEMENT_STRUCTURANT ElementStructurant;
	ElementStructurant.type = type;
	ElementStructurant.hauteur = hauteur;
	ElementStructurant.largeur = largeur;

	int tailleSE = hauteur * largeur;
	ElementStructurant.data = (unsigned char*)calloc(tailleSE, sizeof(unsigned char));
	if (ElementStructurant.data == NULL) {
		return ElementStructurant;
	}

	ElementStructurant.pixel = (unsigned char**)malloc(hauteur * sizeof(unsigned char*));
	if (ElementStructurant.pixel == NULL) {
		free(ElementStructurant.data);
		ElementStructurant.data = NULL;
		return ElementStructurant;
	}

	for (int i = 0; i < hauteur; i++) {
		ElementStructurant.pixel[i] = &ElementStructurant.data[i * largeur];
	}

	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < largeur; j++) {
			ElementStructurant.pixel[i][j] = 1;
		}
	}

	return ElementStructurant;
}

ELEMENT_STRUCTURANT allocation_ElementStructurant_ellipse(const char* type, int hauteur, int largeur)
{
	ELEMENT_STRUCTURANT ElementStructurant;
	ElementStructurant.type = type;
	ElementStructurant.hauteur = 2 * hauteur + 1;
	ElementStructurant.largeur = 2 * largeur + 1;

	int centreSE;
	int tailleSE;
	int i, j;

	tailleSE = ElementStructurant.hauteur * ElementStructurant.largeur;
	ElementStructurant.data = (unsigned char*)calloc(tailleSE, sizeof(unsigned char));
	if (ElementStructurant.data == NULL)
	{
		return(ElementStructurant);
	}
	ElementStructurant.pixel = (unsigned char**)malloc(ElementStructurant.hauteur * sizeof(unsigned char*));
	if (ElementStructurant.pixel == NULL) {
		free(ElementStructurant.data);
		ElementStructurant.data = NULL;
		return(ElementStructurant);
	}

	for (i = 0; i < ElementStructurant.hauteur; i++)
	{
		ElementStructurant.pixel[i] = &ElementStructurant.data[i * ElementStructurant.largeur];
	}

	centreSE = floor(tailleSE / 2.0);
	int centerX = largeur;
	int centerY = hauteur;

	double x, y;
	double test;

	for (i = 0; i < ElementStructurant.hauteur; i++)
	{
		for (j = 0; j < ElementStructurant.largeur; j++)
		{
			x = (j - centerX) * 1.0 / largeur;
			y = (i - centerY) * 1.0 / hauteur;
			test = x * x + y * y;

			if (test <= 1)
			{
				ElementStructurant.pixel[i][j] = 1;
			}
		}
	}
	return ElementStructurant;
}

#pragma endregion

#pragma region Revision Eval 3
IMAGE bruitAleatoireImage(IMAGE image, int amplitude) {
	IMAGE bruit = image;
	int valMin = (-1) * amplitude;

	for (int i = 0; i < (image.Nbcol * image.Nblig); i++) {
		int temp = bruit.data[i] + (valMin + rand() % (amplitude + 1 - valMin));
		if (temp < 0) temp = 0;
		if (temp > 255) temp = 255;
		bruit.data[i] = temp;
	}
	return image;
}

IMAGERGB masqueImage(IMAGE image, IMAGERGB masque) {
	IMAGERGB rgb = allocationImageRGB(image.Nblig, image.Nbcol);
	for (int i = 0; i < (masque.Nbcol * masque.Nblig); i++) {
		if (masque.data[i].B == 0 && masque.data[i].G == 0 && masque.data[i].R == 0) {
			rgb.data[i].B = image.data[i];
			rgb.data[i].G = image.data[i];
			rgb.data[i].R = image.data[i];
		}
		else {
			rgb.data[i] = masque.data[i];
		}
	}
	return rgb;
}
#pragma endregion

#pragma region Eval2 
POINT* imageVersPoints(IMAGE image, int* n, char axe) {
	int indice = 0;

	POINT* tab = (POINT*)calloc((image.Nbcol * image.Nblig), sizeof(POINT));
	if (axe == "x") {// Fixe le x à i et le y à j
		for (int j = 0; j < image.Nbcol; j++) {
			for (int i = 0; i < image.Nblig; i++) {
				if (image.pixel[i][j] != 0) {
					POINT temp = { i , j };
					tab[indice] = temp;
					indice++;
				}
			}
		}
	}
	else { // Fixe le x à j et le y à i 
		for (int j = 0; j < image.Nbcol; j++) {
			for (int i = 0; i < image.Nblig; i++) {
				if (image.pixel[i][j] != 0) {
					POINT temp = { j , i };
					tab[indice] = temp;
					indice++;
				}
			}
		}
	}

	*n = indice;
	tab = (POINT*)realloc(&tab, *n * sizeof(POINT)); //Ne fonctionne pas


	if (axe == "x") {
		sortieRegression("AxeX.csv", tab, indice);
	}
	else {
		sortieRegression("AxeY.csv", tab, indice);
	}
	return tab;
}

#pragma endregion



