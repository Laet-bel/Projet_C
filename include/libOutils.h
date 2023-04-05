#pragma once
#include <stdlib.h>
#include <stdio.h>

#pragma region structs
typedef struct couleur {
	char couleur[20];
	int R;
	int G;
	int B;
}COULEUR;

typedef struct disque {
	int rayon;
	double surface;
	double perimetre;
} DISQUE;

typedef struct complexe {
	double Re;
	double Im;
} COMPLEXE;

typedef struct {
	int a;
	int b;
} TEMPORAIRE;

typedef struct {
	int h;
	int min;
	int s;
}TEMPS;

typedef struct {
	int* TDyn;
	int size;
}TAB_INT;

typedef struct {
	int longueur;
	int* data;
}INT_TABLEAU;

typedef struct mot {
	int longueur;
	char* data;
} MOT;

typedef struct matrice {
	int hauteur;
	int largeur;
	int** valeurs;
} MATRICE;

typedef struct iMatrice {
	int hauteur;
	int largeur;
	int* valeurs;
	int** ptLignes;
} iMATRICE;

typedef struct tab_resistance {
	int nombre;
	float* data;
} TAB_RESISTANCE;

#pragma endregion

#pragma region Algorithmique

#pragma region calcul1
int calcul1(int a, int b);
int factorielle(int n);
int arrangements(int n, int k);
int combinaisons(int n, int k);
void affichageCombinatoire(int n, int k);
#pragma endregion

#pragma region calcul2
void miseTableauAuCarre(int tIn[], int n, int sortie[]);
#pragma endregion

#pragma region calcul3
void affichagetableauint(int t[], int n);
void initialisationaleatoiretableauint(int t[], int n, int valmin, int valmax);
void copieTableauInt(int t1[], int t2[], int n);
int minTableauInt(int t[], int n);
int maxTableauInt(int t[], int n);
int indiceMinimum(int t[], int n);
int indiceMaximum(int t[], int n);
//void triEchangeTableauInt(int t[], int n);
#pragma endregion

#pragma region TP2
void histogramme(int t[], int n, int hist[]);
int OTSU(int t[], int n);
#pragma endregion

#pragma endregion

#pragma region DEVELOPPEMENT IMAGE EN C

#pragma region TD1

#pragma region Couleurs
void afficheCouleur(COULEUR color);
double DistanceEuclidienneColor(COULEUR color1, COULEUR color2);
#pragma endregion

#pragma region Complexes 
void AfficheComplexe(COMPLEXE complexe);
COMPLEXE LectureComplexe(void);
COMPLEXE ConjugueComplexe(COMPLEXE complexe);
double ModuleComplexe(COMPLEXE complexe);
COMPLEXE AdditionComplexe(COMPLEXE complexe1, COMPLEXE complexe2);
COMPLEXE MultiplicationComplexe(COMPLEXE complexe1, COMPLEXE complexe2);
#pragma endregion

#pragma endregion

#pragma region TD_Pointeur

#pragma region EchangeVariables
void Echange(int a, int b);
void EchangeStruct(TEMPORAIRE tmp);
void EchangeTab(int* pt);
void EchangeInt(int* pa, int* pb);
#pragma endregion

#pragma region Temps
void AfficheTemps(TEMPS t);
TEMPS Decomposition(int tps);
void DecompositionPointeur(int tps, int* h, int* m, int* s);
void LectureTemps(int* tps);
#pragma endregion

#pragma endregion

#pragma region TD_Allocation Pointeur

void* CallocInt(TAB_INT tab);

#pragma region Lettres/Mots
char TirageLettre(void);
char* TirageMot(int taille);
char* CopieMot(char* mot, int taille);

void transformMotMajuscule(char* mot);
void transformMotMinuscule(char* mot);

void multiplicationVoyellesMot(char* mot1, int taille1, int coef, char* mot2, int* taille2);
#pragma endregion

#pragma region Phrase
MOT generationMot(int n);
void libereMot(MOT mot);
MOT* tiragePhrase(int nbMots);
void AfficheMot(MOT mot);
#pragma endregion






#pragma endregion

#pragma region Matrices
void affichageMatrice(MATRICE matrice);
MATRICE initialisationMatrice(int hauteur, int largeur, int min, int max);
MATRICE allocationMatrice(int hauteur, int largeur);
void liberationMatrice(MATRICE* matrice);

int traceMatrice(MATRICE matrice);

int VerificationMatriceCarre(MATRICE matrice);
MATRICE AdditionMatrices(MATRICE a, MATRICE b);

int VerificationMatriceMultiplication(MATRICE a, MATRICE b);
MATRICE multiplicationMatrice(MATRICE a, MATRICE b);

#pragma endregion

#pragma region iMatrice 
iMATRICE allocation_iMatrice(int hauteur, int largeur);
void remplissageAleatoire_iMatrice(iMATRICE iMatrice, int valMin, int valMax);
void liberation_iMatrice(iMATRICE* iMatrice);
void affichage_iMatrice(iMATRICE matrice);

#pragma endregion



#pragma endregion


#pragma region Eval Algorithmique 2
int carre(int x);
int fonction1(int T[], int n, int a);
int minTableauIntViaHisto(int T[], int n);
int maxTableauIntViaHisto(int T[], int n);
int trace(int T[], int N);
int puissance(int x, int n);
int evalPolynome(int P[], int n, int x);
int evalPolynomeV2(int P[], int n, int x);


#pragma endregion

#pragma region révision_eval2

INT_TABLEAU allocation_tab_int(int n);
INT_TABLEAU creer_tab_int_alleatoire(int n, int valMin, int valMax);
DISQUE remplir_parametres_disque(int r);
void affiche_disque(DISQUE d);
DISQUE* tab_disques(INT_TABLEAU rayons);
#pragma endregion

#pragma region Evaluation 2

TAB_RESISTANCE allocTabResistance(int nb);
float resistanceEquivalente(TAB_RESISTANCE tab, int type);
TAB_RESISTANCE lectureData(const char* nom);
void enregistreData(const char* nom, TAB_RESISTANCE tab);

#pragma endregion
