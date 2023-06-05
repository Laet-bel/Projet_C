#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libCIPSI1.h>

//
//// Mettre variable globale avec nom d'élément structurant :nom =  "V4" hauteur = 3 largeur 3 
//
//// Ajouter si appui sur p ==> choix parametres 
//// Ajouter si appui sur a ==> Afficher Element structure (Pas tout de suite / si on a le temps)
//
//// Dans parametre demander choix element structurant 
//// Choix hauteur / largeur ??? 
//
//
//// Générer image pour envoyer à la fonction + SE

int main()
{
    char path[100] = "Source Images\\";
    char pathVT[100] = "Ground truth\\";
    char type[3];
    int choice;
    char start[5];
    char end[5];
    char input[10];
    char element[10];
    ELEMENT_STRUCTURANT se;
    char** imagePaths;
    char** veriteTerrainPaths;
    float* results = NULL;

    while (1)
    {
        printf("Choix du type d'image :\n");
        printf("1 pour In\n");
        printf("2 pour Sc\n");

        printf("Entrez q pour quitter.\n");
        scanf("%s", type);

        if (strcmp(type, "1") == 0)
        {
            strcpy(type, "In");
            break;
        }
        else if (strcmp(type, "2") == 0)
        {
            strcpy(type, "Sc");
            break;
        }

        else if (strcmp(type, "Q") == 0 || strcmp(type, "q") == 0)
        {
            printf("Programme quitte.\n");
            return 0;
        }
        else
        {
            printf("Choix invalide.\n");
        }
    }

    while (1) {
        printf("\nChoix de la selection :\n");
        printf("1 pour une seule image\n");
        printf("2 pour toutes les images\n");
        printf("3 pour un certain nombre d'images\n");
        printf("Entrez p pour choisir l'element structurant\n");
        printf("Entrez q pour quitter.\n");
        scanf("%s", input);

        if (strcmp(input, "1") == 0)
        {
            printf("\nEntrez le numero de l'image : ");
            scanf("%s", start);
            if (atoi(start) < 1 || atoi(start) > 300)
            {
                printf("L'image n'existe pas.\n");
            }
            else
            {
                strcat(path, type);
                strcat(path, "_");
                strcat(path, start);
                strcat(path, ".pgm");
                printf("\nVous avez choisi l'image : %s\n", path);
                break;
            }
        }
        else if (strcmp(input, "2") == 0)
        {
            imagePaths = malloc(sizeof(char*) * 300);
            veriteTerrainPaths = malloc(sizeof(char*) * 300);
            
            if (strcmp(type, "In") == 0) 
            {
                for (int i = 0; i < 300; i++) {
                    imagePaths[i] = malloc(sizeof(char) * 100);
                    veriteTerrainPaths[i] = malloc(sizeof(char) * 100);

                    sprintf(imagePaths[i], "%s%s_%d.pgm", path, type, i + 1);
                    sprintf(veriteTerrainPaths[i], "%s%s_%d.pgm", pathVT, type, i + 1);
                }
                results = Image_In(imagePaths, veriteTerrainPaths, se, 300);
            }
            else if (strcmp(type, "Sc") == 0) 
            {
                for (int i = 0; i < 300; i++) 
                {
                    imagePaths[i] = malloc(sizeof(char) * 100);
                    veriteTerrainPaths[i] = malloc(sizeof(char) * 100);
                    sprintf(imagePaths[i], "%s%s_%d.pgm", path, type, i + 1);
                    sprintf(veriteTerrainPaths[i], "%s%s_%d.pgm", pathVT, type, i + 1);
                }
                results = Image_Sc(imagePaths, veriteTerrainPaths, se, 300);
            }
            printf("Résultats :\n");
            printf("Score IOU : %f\n", results[0]);
            printf("Moyenne : %f\n", results[1]);
            free(results);
            break;
        }
        else if (strcmp(input, "3") == 0)
        {
            printf("\nEntrez le numero de debut : ");
            scanf("%s", start);
            printf("\nEntrez le numero de fin : ");
            scanf("%s", end);
            if (atoi(start) < 1 || atoi(start) > 300 || atoi(end) < 1 || atoi(end) > 300 || atoi(end) < atoi(start))
            {
                printf("L'image n'existe pas.\n");
            }
            else
            {
                strcat(path, type);
                strcat(path, "_");
                strcat(path, start);
                strcat(path, ".pgm");
                printf("\nVous avez choisi les images suivantes : \n");
                printf("%s\n", path);
                for (int i = atoi(start) + 1; i <= atoi(end); i++)
                {
                    char str[5];
                    sprintf(str, "%d", i);
                    char temp[100];
                    strcpy(temp, path);
                    temp[strlen(temp) - strlen(start) - 4] = '\0';
                    strcat(temp, str);
                    strcat(temp, ".pgm");
                    printf("%s\n", temp);
                }
                break;
            }
        }
        else if (strcmp(input, "p") == 0 || strcmp(input, "P") == 0)
        {
            while (1)
            {
                int rayon = 3;
                int hauteur = 3;
                int largeur = 3;
                printf("\nChoix de l'element structurant :\n");
                printf("1 pour disk\n");
                printf("2 pour rectangle\n");
                printf("3 pour ligne verticale\n");
                printf("4 pour ligne horizontale\n");
                printf("5 pour ellipse\n");
                printf("6 pour V4\n");
                printf("7 pour V8\n");
                scanf("%s", element);

                if (strcmp(element, "1") == 0)
                {
                    strcpy(element, "disk");
                    ELEMENT_STRUCTURANT se = allocation_ElementStructurant('disk', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "2") == 0)
                {
                    strcpy(element, "rectangle");
                    ELEMENT_STRUCTURANT se = allocation_ElementStructurant('rect', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "3") == 0)
                {
                    strcpy(element, "ligne verticale");
                    ELEMENT_STRUCTURANT se = allocation_ElementStructurant('ligV', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "4") == 0)
                {
                    strcpy(element, "ligne horizontale");
                    ELEMENT_STRUCTURANT se = allocation_ElementStructurant('ligH', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "5") == 0)
                {
                    strcpy(element, "ellipse");
                    ELEMENT_STRUCTURANT se = allocation_ElementStructurant('elli', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "6") == 0)
                {
                    strcpy(element, "V4");
                    ELEMENT_STRUCTURANT se = allocation_ElementStructurant('V4', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "7") == 0)
                {
                    strcpy(element, "V8");
                    ELEMENT_STRUCTURANT se = allocation_ElementStructurant('V8', hauteur, largeur);
                    break;
                }
            }
        }
        else if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0)
        {
            printf("Programme quitte.\n");
            return 0;
        }
        else
        {
            printf("Choix invalide.\n");
        }
    }

    printf("\nResume de vos choix : \n");
    printf("Type d'image : %s\n", type);
    printf("Element structurant : %s\n", element);
    printf("Selection : %s\n", input);

    if (strcmp(input, "1") == 0)
        printf("Image selectionnee : %s\n", path);
    else if (strcmp(input, "2") == 0)
        printf("Toutes les images selectionnees.\n");
    else if (strcmp(input, "3") == 0)
        printf("Images selectionnees : voir ci-dessus.\n");

    return 0;
}