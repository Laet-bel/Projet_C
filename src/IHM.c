#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libCIPSI1.h>

int main()
{
    char path[100] = "Source Images\\";
    char type[3];
    int choice;
    char start[5];
    char end[5];
    char input[10];

    while (1) {
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
            strcat(path, type);
            strcat(path, "_*.pgm");
            printf("\nVous avez choisi toutes les images de ce groupe.\n");
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
    printf("Selection : %s\n", input);
    if (strcmp(input, "1") == 0)
        printf("Image selectionnee : %s\n", path);
    else if (strcmp(input, "2") == 0)
        printf("Toutes les images selectionnees.\n");
    else
        printf("Images selectionnees : voir ci-dessus.\n");

    return 0;
}