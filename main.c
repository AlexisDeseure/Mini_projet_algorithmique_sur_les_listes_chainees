#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main()
{
    T_Magasin *mon_magasin = NULL;

    // ============= MENU UTILISATEUR ============= */
    char choix = 0;
    char str[1000]; // initialisation de la chaine de caractères qui contiendra les noms des éléments à ajouter
    char input[100];
    char *chaineNonConvertie; // permet de pointer vers la chaîne de caractères non convertie en utilisant strtof ou strtol
    long int entier = 0; // initialisation du nombre qui contiendra les nombres entier à ajouter (long int car utilisation de strtol)
    float flottant = 0; // initialisation du nombre qui contiendra les nombres flottants à ajouter
    float flottant2 = 0; // initialisation du nombre qui contiendra les potentiels second nombres flottants à ajouter (prix_min et prix_max)
    T_Rayon *rayon;
    T_Rayon *inte =NULL;
    T_Produit *prod = NULL;
    while (choix != '0') {
        printf("\n========== MENU UTILISATEUR ==========");
        printf("\n1. Creer un magasin");
        printf("\n2. Ajouter un rayon au magasin");
        printf("\n3. Ajouter un produit dans un rayon");
        printf("\n4. Afficher les rayons du magasin");
        printf("\n5. Afficher les produits d'un rayon");
        printf("\n6. Supprimer un produit");
        printf("\n7. Supprimer un rayon");
        printf("\n8. Rechercher un produit par prix");
        printf("\n9. Fusionner deux rayons du magasin");
        printf("\n0. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer(); // supprimer de l'entrée standard le retour charriot et les éventuels caractères supplémentaires tapés par l'utilisateur

        switch (choix) {
            case '1' :
                if (mon_magasin == NULL){
                    printf("\nQuel est le nom du magasin que vous souhaitez ajouter au systeme (strictement inferieur a 1000 caracteres)?\n");
                    fgets(str, 1000, stdin);
                    str[strcspn(str, "\n")] = '\0';
                    mon_magasin = creerMagasin(str);
                    printf("\nCreation effectuee avec succes !\nVotre magasin se nomme : %s\n",str);
                }
                else{
                    printf("\nAttention !! Votre magasin a deja ete cree avec le nom : %s",mon_magasin->nom);
                    printf("\nSouhaitez-vous changer ce nom ? (y/n)");
                    choix = getchar();
                    viderBuffer();
                    if (choix == 'y'){
                        printf("\nEntrez le nouveau nom :\n");
                        fgets(str, 1000, stdin);
                        str[strcspn(str, "\n")] = '\0';
                        strcpy(mon_magasin->nom,str);
                        printf("\nChangement effectue avec succes !\nVotre magasin se nomme desormais: %s\n",str);
                    }
                }
                viderBuffer();
                break;
            case '2' :
                if (mon_magasin == NULL) {
                    printf("\nLe magasin n'a pas encore ete cree !\nVeuillez le faire en accedant a la page 1 du Menu puis reessayer\n");
                    break;
                }
                printf("\nQuel est le nom du rayon que vous souhaitez ajouter au magasin (strictement inferieur a 1000 caracteres)?\n");
                fgets(str, 1000, stdin);// récupère au maximum les 999 caractères écris dans la console et les stocke dans la variable str
                str[strcspn(str, "\n")] = '\0';// remplace le premier saut de ligne par le caractère de fin
                // de ligne (strcspn renvoie la longueur de la plus grande sous chaine ne contenant aucun des caractères spécifiés)
                if (ajouterRayon(mon_magasin,str)){
                    printf("Rayon %s ajoute avec succes !\n",str);
                }
                else{
                    printf("Une erreur a ete rencontree durant l'ajout du rayon !\n");
                    printf("Assurez-vous que le rayon que vous souhaitez ajouter n'existe pas deja.\n");
                }
                viderBuffer();
                break;

            case '3' :
                if (mon_magasin == NULL) {
                    printf("\nLe magasin n'a pas encore ete cree !\nVeuillez le faire en accedant a la page 1 du Menu puis reessayer\n");
                    break;
                }
                printf("\nEntrez le nom du rayon dans lequel ajouter le produit:");
                fgets(str, 1000, stdin); // récupère au maximum les 999 caractères écris dans la console et les stocke dans la variable str
                viderBuffer();
                str[strcspn(str, "\n")] = '\0'; // remplace le premier saut de ligne par le caractère de fin
                // de ligne (strcspn renvoie la longueur de la plus grande sous chaine ne contenant aucun des caractères spécifiés)
                rayon = obtenirRayon(mon_magasin, str);
                if (rayon == NULL){
                    // cas où il n'existe aucun rayon portant le même nom que celui entree par l'utilisateur
                    printf("\nErreur: le rayon n'existe pas\n");
                    break;
                }
                printf("\nQuel est le nom du produit que vous souhaitez ajouter au rayon (strictement inferieur a 1000 caracteres)?\n");
                fgets(str, 1000, stdin); // récupère au maximum les 999 caractères écris dans la console et les stocke dans la variable str
                viderBuffer();
                str[strcspn(str, "\n")] = '\0'; // remplace le premier saut de ligne par le caractère de fin
                // de ligne (strcspn renvoie la longueur de la plus grande sous chaine ne contenant aucun des caractères spécifiés)
                printf("\nEntrez le prix du produit:");
                fgets(input, sizeof(input), stdin);
                viderBuffer();
                input[strcspn(input, "\n")] = '\0';
                flottant = strtof(input, &chaineNonConvertie);
                if (*chaineNonConvertie != '\0') {
                    // s'il y a des caracteres autres que des chiffres (ou le "."), la chaine non converie les contiendra
                    printf("Une erreur de conversion est survenue : assurez vous que les caracteres entres forment bien un nombre valide\n");
                    break;
                }
                printf("\nEntrez le nombre de produits disponibles:");
                fgets(input, sizeof(input), stdin);
                viderBuffer();
                input[strcspn(input, "\n")] = '\0';
                entier = strtol(input, &chaineNonConvertie,10);
                if (*chaineNonConvertie != '\0') {
                    // s'il y a des caracteres autres que des chiffres, la chaine non converie les contiendra
                    printf("Une erreur de conversion est survenue : assurez vous que les caracteres entres forment bien un nombre valide\n");
                    break;
                }
                if (ajouterProduit(rayon,str,flottant,entier)){
                    printf("Le produit %s, ayant une valeur de %.2f euros et de quantite %ld, a ete ajoute avec succes dans le rayon %s !\n",str, flottant, entier, rayon->nom_rayon);
                }
                else{
                    printf("Une erreur a ete rencontree durant l'ajout du rayon !\n");
                    printf("Assurez-vous que le produit \"%s\" que vous souhaitez ajouter n'existe pas deja.\n", str);
                }
                break;

            case '4' :
                if (mon_magasin == NULL) {
                    printf("\nLe magasin n'a pas encore ete cree !\nVeuillez le faire en accedant a la page 1 du Menu puis reessayer\n");
                    break;
                }
                afficherMagasin(mon_magasin);
                break;

            case '5' :
                if (mon_magasin == NULL) {
                    printf("\nLe magasin n'a pas encore ete cree !\nVeuillez le faire en accedant a la page 1 du Menu puis reessayer\n");
                    break;
                }
                printf("\nEntrez le nom du rayon a afficher:");
                fgets(str, 1000, stdin); // récupère au maximum les 999 caractères écris dans la console et les stocke dans la variable str
                viderBuffer();
                str[strcspn(str, "\n")] = '\0'; // remplace le premier saut de ligne par le caractère de fin
                // de ligne (strcspn renvoie la longueur de la plus grande sous chaine ne contenant aucun des caractères spécifiés)
                rayon = obtenirRayon(mon_magasin, str);
                if (rayon == NULL){
                    // cas où il n'existe aucun rayon portant le même nom que celui entree par l'utilisateur
                    printf("\nErreur: le rayon n'existe pas\n");
                    break;
                }
                afficherRayon(rayon);
                break;

            case '6' :
                if (mon_magasin == NULL) {
                    printf("\nLe magasin n'a pas encore ete cree !\nVeuillez le faire en accedant a la page 1 du Menu puis reessayer\n");
                    break;
                }
                printf("\nEntrez le nom du rayon dans lequel se trouve le produit a supprimer:");
                fgets(str, 1000, stdin); // récupère au maximum les 999 caractères écris dans la console et les stocke dans la variable str
                viderBuffer();
                str[strcspn(str, "\n")] = '\0'; // remplace le premier saut de ligne par le caractère de fin
                // de ligne (strcspn renvoie la longueur de la plus grande sous chaine ne contenant aucun des caractères spécifiés)
                rayon = obtenirRayon(mon_magasin, str);
                if (rayon == NULL){
                    // cas où il n'existe aucun rayon portant le même nom que celui entree par l'utilisateur
                    printf("\nErreur: le rayon n'existe pas\n");
                    break;
                }
                printf("\nEntrez le nom du produit a supprimer dans le rayon %s:", rayon->nom_rayon);
                fgets(str, 1000, stdin); // récupère au maximum les 999 caractères écris dans la console et les stocke dans la variable str
                viderBuffer();
                str[strcspn(str, "\n")] = '\0'; // remplace le premier saut de ligne par le caractère de fin
                // de ligne (strcspn renvoie la longueur de la plus grande sous chaine ne contenant aucun des caractères spécifiés)
                if (supprimerProduit(rayon, str)){
                    printf("\nLe produit %s du rayon %s a ete supprime avec succes !", str, rayon->nom_rayon);
                }
                else{
                    printf("\nErreur : Le produit n'existe pas !");
                }
                break;

            case '7' :
                if (mon_magasin == NULL) {
                    printf("\nLe magasin n'a pas encore ete cree !\nVeuillez le faire en accedant a la page 1 du Menu puis reessayer\n");
                    break;
                }
                printf("\nEntrez le nom du rayon a supprimer:");
                fgets(str, 1000, stdin); // récupère au maximum les 999 caractères écris dans la console et les stocke dans la variable str
                viderBuffer();
                str[strcspn(str, "\n")] = '\0'; // remplace le premier saut de ligne par le caractère de fin
                // de ligne (strcspn renvoie la longueur de la plus grande sous chaine ne contenant aucun des caractères spécifiés)
                if (supprimerRayon(mon_magasin, str)){
                   printf("\nLe rayon %s a ete supprime avec succes !", str);
                }
                else{
                    printf("\nErreur : Le rayon n'existe pas !");
                }
                break;



            case '8' :
                if (mon_magasin == NULL) {
                    printf("\nLe magasin n'a pas encore ete cree !\nVeuillez le faire en accedant a la page 1 du Menu puis reessayer\n");
                    break;
                }
                printf("\nEntrez le prix minimum du produit:");
                fgets(input, sizeof(input), stdin);
                viderBuffer();
                input[strcspn(input, "\n")] = '\0';
                flottant = strtof(input, &chaineNonConvertie);
                if (*chaineNonConvertie != '\0') {
                    // s'il y a des caracteres autres que des chiffres (ou le "."), la chaine non converie les contiendra
                    printf("Une erreur de conversion est survenue : assurez vous que les caracteres entres forment bien un nombre valide\n");
                    break;
                }
                printf("\nEntrez le prix maximum du produit:");
                fgets(input, sizeof(input), stdin);
                viderBuffer();
                input[strcspn(input, "\n")] = '\0';
                flottant2 = strtof(input, &chaineNonConvertie);
                if (*chaineNonConvertie != '\0') {
                    // s'il y a des caracteres autres que des chiffres (ou le "."), la chaine non converie les contiendra
                    printf("Une erreur de conversion est survenue : assurez vous que les caracteres entres forment bien un nombre valide\n");
                    break;
                }
                if(flottant > flottant2){
                    printf("Erreur: le minimum ne peut etre superieur au maximum !");
                    break;
                }
                rechercheProduits(mon_magasin, flottant, flottant2);
               break;

            case '9' :
                mon_magasin = creerMagasin("t");
                printf("t %d\n", ajouterRayon(mon_magasin,"test1"));
                printf("%d\n",ajouterProduit(mon_magasin->liste_rayons,"p1", 5, 52));
                printf("%d\n",ajouterProduit(mon_magasin->liste_rayons,"p2", 4, 52));
                printf("%d\n",ajouterProduit(mon_magasin->liste_rayons,"p3", 2, 52));
                ajouterRayon(mon_magasin,"test2");
                ajouterProduit(mon_magasin->liste_rayons->suivant,"p4", 6, 52);
                ajouterProduit(mon_magasin->liste_rayons->suivant,"p2", (float)3.5, 52);
                ajouterProduit(mon_magasin->liste_rayons->suivant,"p5", (float)1.8, 52);
                ajouterRayon(mon_magasin,"test3");
                ajouterProduit(mon_magasin->liste_rayons->suivant->suivant,"p6", 1, 52);
                ajouterProduit(mon_magasin->liste_rayons->suivant->suivant,"p2", (float)7.5, 52);
                ajouterProduit(mon_magasin->liste_rayons->suivant->suivant,"p8", (float)1.8, 52);
                break;


            case '0' :
                printf("\n========== PROGRAMME TERMINE ==========\n");
                getchar();
                break;

            default :
                printf("\n\nERREUR : votre choix n'est pas valide ! ");
        }
        printf("\n\n\n");
    }

    return 0;
}
