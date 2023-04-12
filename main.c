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
                ajouterRayon(magasin, "Boissons");
                ajouterRayon(magasin, "Yaourts");
                ajouterRayon(magasin, "Lessives");
                ajouterRayon(magasin, "Fromages");
                ajouterRayon(magasin, "Le rayon sympa long qui existe");
                ajouterRayon(magasin, "Le rayon sympa long qui n'existe pas");
                ajouterProduit(magasin->liste_rayons->suivant,"comte",(float)5.6,25);
                ajouterProduit(magasin->liste_rayons->suivant,"gruyere",(float)2.6,5);
//                T_Rayon* debut= magasin->liste_rayons;
//                printf("Rayons : %s ",magasin->liste_rayons->nom_rayon);
//                while((debut = debut->suivant)!=NULL)
//                {
//                    printf("-> %s ",debut->nom_rayon);
//                }
                afficherMagasin(magasin);
                afficherRayon(magasin->liste_rayons->suivant);
                break;
            }
            case '2' :
            {
                char *chaine = formatageNom("azertyuiopqsdfghjklmwxcvbn123456789",30);
                printf("%sfin",chaine);
                break;
            }

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
