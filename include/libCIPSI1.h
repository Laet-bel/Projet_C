#pragma once

/* librairie IPSI1 */

typedef struct image {
	int   Nblig;
	int   Nbcol;
	unsigned char*  data;
	unsigned char** pixel;
} IMAGE;

typedef struct rgb {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} RGB;

typedef struct imageRGB {
	int   Nblig;
	int   Nbcol;
	RGB*  data;
	RGB** pixel;
} IMAGERGB;

typedef struct point {
	float x;
	float y;
}POINT;

typedef struct signatures {
	int		min;
	int		max;
	double	moyenne;
	double	ecartType;
	int		mediane;
} SIGNATURES;

typedef struct signature_composantes_connexes {
	int surface;
	float perimetre;
	float compacite;
	int bord;
	POINT CG; /* pour le centre de gravité, cf libOutils */
	float rayon; /* rayon moyen calculé via la surface */
} SIGNATURE_COMPOSANTE_CONNEXE;

typedef struct
{
	int Nblig;
	int Nbcol;
	int* data;
	int** pixel;
} intIMAGE;

typedef struct element_structurant {
	char* type;
	int hauteur;
	int largeur;
	unsigned char* data;
	unsigned char** pixel;
} ELEMENT_STRUCTURANT;

#pragma region Points
void AffichePoint(POINT point);
POINT LecturePoint();
float DistancePoints(POINT p1, POINT p2);
POINT MilieuPoints(POINT p1, POINT p2);
void GenerationAleatoirePoints(POINT t[], int n, float min, float max);
POINT* GenerationAleatoirePointsDyn(int n, float min, float max);
POINT CentreGravitePoints(POINT t[], int n);

#pragma region Points avec pointeurs
void RechercheAbscissesExtremes(POINT tab[], int n, float* absMin, float* absMax);
void RecherchePointsExtremes(POINT tab[], int n, POINT* ptDistMin, POINT* ptDistMax);
#pragma endregion
#pragma endregion

IMAGE allocationImage(int Nblig, int Nbcol);
void initialisationAleatoireImage(IMAGE img, int ngMin, int ngMax);

void sauvegardeImage(IMAGE img, const char *type, const char *out);
void liberationImage(IMAGE *im);

IMAGE lectureImage(const char *nom);

IMAGERGB allocationImageRGB(int Nblig, int Nbcol);
void initialisationAleatoireImageRGB(IMAGERGB img, int ngMin, int ngMax);
IMAGERGB lectureImageRGB(const char *nom);

void sauvegardeImageRGB(IMAGERGB img, const char *type, const char *out);
void liberationImageRGB(IMAGERGB *im);

IMAGE planImage(IMAGERGB img, int plan);
IMAGE luminanceImage(IMAGERGB img, float r, float g, float b);
IMAGE inverseImage(IMAGE img);
IMAGE seuillageImage(IMAGE img, int sInf, int sSup);

int* histogrammeImageAncien(IMAGE img, int choix);
int* histogrammeImage(IMAGE img, int choix, int n);
int* histogrammeImageRGB(IMAGERGB img, int choix, int n);
IMAGE expansionImage(IMAGE img, int outMin, int outMax);
IMAGE egalisationImage(IMAGE img);
SIGNATURES statistiquesImage(IMAGE img);

IMAGE seuillageOtsu(IMAGE img);

IMAGE labelImage(IMAGE img, int *nbComp); /* image label + nb composantes connexes */
IMAGERGB colorisationImage(IMAGE img, char* table);

double distanceHistogrammeImage(int* h1, int* h2, int taille);
SIGNATURE_COMPOSANTE_CONNEXE* signaturesImage(IMAGE img, int nbComp);
void affiche_signatures(SIGNATURE_COMPOSANTE_CONNEXE* signatures, int nbCompo);
int* LUTsansBord(SIGNATURE_COMPOSANTE_CONNEXE* signatures, int nbComp);
IMAGE ImageAvecLUT(const IMAGE img, int* LUT);


#pragma region morphologie
/// <summary>
/// Erosion
/// </summary>
/// <param name="img"></param>
/// <param name="4 => V4 / 8 => V8"></param>
/// <returns></returns>
IMAGE erosionImage(IMAGE img, int voisinage);
/// <summary>
/// Dilatation
/// </summary>
/// <param name="img"></param>
/// <param name="4 => V4 / 8 => V8"></param>
/// <returns></returns>
IMAGE dilatationImage(IMAGE img, int voisinage);

IMAGE erosionImageavecSE(IMAGE image, const ELEMENT_STRUCTURANT se);
int min_SE(IMAGE img, ELEMENT_STRUCTURANT SE, int* i, int* j);
IMAGE dilatationImageavecSE(IMAGE image, const ELEMENT_STRUCTURANT SE);
int max_SE(IMAGE img, ELEMENT_STRUCTURANT SE, int* i, int* j);

/// <summary>
/// Ouverture
/// </summary>
/// <param name="img"></param>
/// <param name="4 => V4 / 8 => V8"></param>
/// <returns></returns>
IMAGE ouvertureImage(IMAGE img, int voisinage);
IMAGE ouvertureImageavecSE(IMAGE img, ELEMENT_STRUCTURANT SE);
/// <summary>
/// Fermeture
/// </summary>
/// <param name="img"></param>
/// <param name="4 => V4 / 8 => V8"></param>
/// <returns></returns>
IMAGE fermetureImage(IMAGE img, int voisinage);
IMAGE fermetureImageavecSE(IMAGE img, ELEMENT_STRUCTURANT SE);

/// <summary>
///Contour des blobs
/// </summary>
/// <param name="img"></param>
/// <param name="4 => V4 / 8 => V8"></param>
/// <returns>img des contours</returns>
IMAGE contourImage(IMAGE img, int voisinage);

/// <summary>
/// White tophat
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage">4 => V4 / 8 => V8</param>
/// <returns></returns>
IMAGE whiteTopHat(IMAGE img, int voisinage, int n_iteration);
IMAGE whiteTopHatavecSE(IMAGE img, ELEMENT_STRUCTURANT SE, int n_iteration);
/// <summary>
/// Black tophat
/// </summary>
/// <param name="img"></param>
/// <param name="4 => V4 / 8 => V8"</param>
/// <returns></returns>
IMAGE blackTopHat(IMAGE img, int voisinage, int n_iteration);
IMAGE blackTopHatavecSE(IMAGE img, ELEMENT_STRUCTURANT SE, int n_iteration);
#pragma endregion

#pragma region Element structurant
ELEMENT_STRUCTURANT allocation_ElementStructurant(const char* type, int hauteur , int largeur);
ELEMENT_STRUCTURANT allocation_ElementStructurant_disk(const char* type, int rayon);
ELEMENT_STRUCTURANT allocation_ElementStructurant_rect(const char* type, int hauteur, int largeur);
ELEMENT_STRUCTURANT allocation_ElementStructurant_ellipse(const char* type, int hauteur, int largeur);
void remplissageV4(unsigned char** pixel, int x, int y, int colcible, int colrep);
#pragma endregion

#pragma region Filtre
IMAGE recuperation_blobs_communs(IMAGE image_verite, IMAGE image_traitee, int largeur, int hauteur, SIGNATURE_COMPOSANTE_CONNEXE* blobs_verite, int nb_blobs_verite, SIGNATURE_COMPOSANTE_CONNEXE** blobs_communs, int* nb_blobs_communs);
int* recuperation_blobs_communs2(int* image_verite, int* image_traitee, int largeur, int hauteur, SIGNATURE_COMPOSANTE_CONNEXE* blobs_verite, int nb_blobs_verite);
int* recuperation_blobs_communs3(int* image_verite, int* image_traitee, int largeur, int hauteur, SIGNATURE_COMPOSANTE_CONNEXE* blobs_verite, int nb_blobs_verite);
IMAGE recuperation_blobs_communs4(IMAGE image_verite, IMAGE image_traitee, int largeur, int hauteur, SIGNATURE_COMPOSANTE_CONNEXE* blobs_verite, int nb_blobs_verite);
#pragma endregion


#pragma region IOU
float IOU_score(IMAGE traitee, IMAGE veritee);
#pragma endregion



#pragma region Revision Eval 3
IMAGE bruitAleatoireImage(IMAGE img, int amplitude);
IMAGERGB masqueImage(IMAGE img, IMAGERGB masque);
#pragma endregion

#pragma region Eval2 
POINT* imageVersPoints(IMAGE img, int* n, char axe);
#pragma endregion

#pragma region Regression 
void regression(POINT* tab, int n, float* a, float* b);
void sortieRegression(const char* nom, POINT* pts, int n);
POINT* ImageVersPoints(IMAGE img, int* n, char axe);
IMAGE imageSortieRegression(IMAGE img, char axe);
POINT* GenerationAleatoirePointsDyn(int n, float min, float max);
#pragma endregion

