#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libCIPSI1.h>

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
    int useDefaultSE = 1;

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

    while (1)
    {
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

                imagePaths = malloc(sizeof(char*) * 200);
                veriteTerrainPaths = malloc(sizeof(char*) * 200);

                if (strcmp(type, "In") == 0)
                {
                    imagePaths[0] = malloc(sizeof(char) * 200);
                    veriteTerrainPaths[0] = malloc(sizeof(char) * 200);

                    sprintf(imagePaths[0], "%s%s_%d.pgm", path, type, atoi(start));
                    sprintf(veriteTerrainPaths[0], "%s%s_%d.pgm", pathVT, type, atoi(start));

                    if (useDefaultSE) {
                        strcpy(element, "V4");
                        se = allocation_ElementStructurant('V4', 3, 3);
                    }

                    results = Image_In(imagePaths, veriteTerrainPaths, se, 1);
                }
                else if (strcmp(type, "Sc") == 0)
                {
                    imagePaths[0] = malloc(sizeof(char) * 200);
                    veriteTerrainPaths[0] = malloc(sizeof(char) * 200);

                    sprintf(imagePaths[0], "%s%s_%d.pgm", path, type, atoi(start));
                    sprintf(veriteTerrainPaths[0], "%s%s_%d.pgm", pathVT, type, atoi(start));

                    if (useDefaultSE) {
                        strcpy(element, "V4");
                        se = allocation_ElementStructurant('V4', 3, 3);
                    }

                    results = Image_Sc(imagePaths, veriteTerrainPaths, se, 1);
                }

                printf("Resultats :\n");
                printf("Score IOU : %f\n", results[0]);
                free(results);
                break;
            }
        }
        else if (strcmp(input, "2") == 0)
        {
            imagePaths = malloc(sizeof(char*) * 300);
            veriteTerrainPaths = malloc(sizeof(char*) * 300);

            if (strcmp(type, "In") == 0)
            {
                for (int i = 0; i < 300; i++)
                {
                    imagePaths[i] = malloc(sizeof(char) * 100);
                    veriteTerrainPaths[i] = malloc(sizeof(char) * 100);
                    sprintf(imagePaths[i], "%s%s_%d.pgm", path, type, i + 1);
                    sprintf(veriteTerrainPaths[i], "%s%s_%d.pgm", pathVT, type, i + 1);
                }

                if (useDefaultSE) {
                    strcpy(element, "V4");
                    se = allocation_ElementStructurant('V4', 3, 3);
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

                if (useDefaultSE) {
                    strcpy(element, "V4");
                    se = allocation_ElementStructurant('V4', 3, 3);
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
                float* results = NULL;
                int nbImages = atoi(end) - atoi(start) + 1;

                imagePaths = malloc(sizeof(char*) * nbImages);
                veriteTerrainPaths = malloc(sizeof(char*) * nbImages);

                if (strcmp(type, "In") == 0)
                {
                    for (int i = atoi(start); i <= atoi(end); i++)
                    {
                        imagePaths[i - atoi(start)] = malloc(sizeof(char) * 100);
                        veriteTerrainPaths[i - atoi(start)] = malloc(sizeof(char) * 100);
                        sprintf(imagePaths[i - atoi(start)], "%s%s_%d.pgm", path, type, i);
                        sprintf(veriteTerrainPaths[i - atoi(start)], "%s%s_%d.pgm", pathVT, type, i);
                    }

                    if (useDefaultSE) {
                        strcpy(element, "V4");
                        se = allocation_ElementStructurant('V4', 3, 3);
                    }

                    results = Image_In(imagePaths, veriteTerrainPaths, se, nbImages);
                }
                else if (strcmp(type, "Sc") == 0)
                {
                    for (int i = atoi(start); i <= atoi(end); i++)
                    {
                        imagePaths[i - atoi(start)] = malloc(sizeof(char) * 100);
                        veriteTerrainPaths[i - atoi(start)] = malloc(sizeof(char) * 100);
                        sprintf(imagePaths[i - atoi(start)], "%s%s_%d.pgm", path, type, i);
                        sprintf(veriteTerrainPaths[i - atoi(start)], "%s%s_%d.pgm", pathVT, type, i);
                    }

                    if (useDefaultSE) {
                        strcpy(element, "V4");
                        se = allocation_ElementStructurant('V4', 3, 3);
                    }

                    results = Image_Sc(imagePaths, veriteTerrainPaths, se, nbImages);
                }

                printf("Resultats :\n");
                printf("Moyenne : %f\n", results[1]);
                free(results);
                break;
            }
        }
        else if (strcmp(input, "p") == 0 || strcmp(input, "P") == 0)
        {
            useDefaultSE = 0;
            while (1)
            {
                int rayon = 3;
                int hauteur = 3;
                int largeur = 3;
                printf("\nChoix de l'element structurant :\n");
                printf("1 pour rectangle\n");
                printf("2 pour ligne verticale\n");
                printf("3 pour ligne horizontale\n");
                printf("4 pour ellipse\n");
                printf("5 pour V4\n");
                printf("6 pour V8\n");
                scanf("%s", element);

                if (strcmp(element, "1") == 0)
                {
                    strcpy(element, "rectangle");
                    se = allocation_ElementStructurant('rect', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "2") == 0)
                {
                    strcpy(element, "ligne verticale");
                    se = allocation_ElementStructurant('ligV', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "3") == 0)
                {
                    strcpy(element, "ligne horizontale");
                    se = allocation_ElementStructurant('ligH', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "4") == 0)
                {
                    strcpy(element, "ellipse");
                    se = allocation_ElementStructurant('elli', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "5") == 0)
                {
                    strcpy(element, "V4");
                    se = allocation_ElementStructurant('V4', hauteur, largeur);
                    break;
                }
                else if (strcmp(element, "6") == 0)
                {
                    strcpy(element, "V8");
                    se = allocation_ElementStructurant('V8', hauteur, largeur);
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