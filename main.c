#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main()
{
    T_Magasin *mon_magasin = NULL;

    // ============= MENU UTILISATEUR ============= */
    char choix = '0';

    while (choix != '9') {
//        system("cls");
        printf("\n========== MENU UTILISATEUR ==========");
        printf("\n1. Creer un magasin");
        printf("\n2. Ajouter un rayon au magasin");
        printf("\n3. Ajouter un produit dans un rayon");
        printf("\n4. Afficher les rayons du magasin");
        printf("\n5. Afficher les produits d'un rayon");
        printf("\n6. Supprimer un produit");
        printf("\n7. Supprimer un rayon");
        printf("\n8. Rechercher un produit par prix");
        printf("\n9. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur

        switch (choix) {
            case '1' : {
                char test[5] = "test";
                T_Magasin* magasin = creerMagasin(test);
                ajouterRayon(magasin, "rayon 1");
                ajouterRayon(magasin, "Bayon 1");
                ajouterRayon(magasin, "bayon 1");
                ajouterRayon(magasin, "rbyon 1");
                ajouterRayon(magasin, "zayon 1");
                ajouterRayon(magasin, "1zayon 1");
                T_Rayon* debut= magasin->liste_rayons;
                printf("Rayons : %s ",debut->nom_rayon);
                while((debut = debut->suivant)!=NULL)
                {
                    printf("-> %s ",debut->nom_rayon);
                }
                printf("\n|------------------------------|------------------------------|\n");
                printf("|Nom                           |Nombre de produits            |");
                char str[30]="Boissons";
                char str2[30];
                itoa(14, str2, 10);
                printf("\n|------------------------------|------------------------------|\n");
                printf("|%s|%s|",strncat(str,"                      ", 30),strncat(str2,"                            ",30));
                printf("\n|------------------------------|------------------------------|\n");
                break;
            }
            case '2' :
                break;

            case '3' :
                break;

            case '4' :
                break;

            case '5' :
                break;

            case '6' :
                break;

            case '7' :
               break;

            case '8' :
               break;

            case '9' :
                printf("\n========== PROGRAMME TERMINE ==========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide ! ");
        }
        printf("\n\n\n");
    }

    return 0;
}
