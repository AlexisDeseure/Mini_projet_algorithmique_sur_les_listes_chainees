#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"



/* **********************************
 * Cr�ation et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace m�moire d�di� pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

    return nouveauProduit;
}



/* ********************************
 * Cr�ation et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom) {
    T_Rayon *nouveauRayon = NULL;

    nouveauRayon = malloc(sizeof(T_Rayon));
    if (nouveauRayon != NULL) {
        // l'allocation m�moire s'est bien pass�e
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Cr�ation et initialisation Magasin
 ********************************** */
T_Magasin *creerMagasin(char *nom) {
    T_Magasin *nouveauMagasin = NULL;

    nouveauMagasin = malloc(sizeof(T_Magasin));
    if (nouveauMagasin != NULL) {
        nouveauMagasin->nom = malloc(strlen(nom) + 1);
        strcpy(nouveauMagasin->nom,nom);
        nouveauMagasin->liste_rayons = NULL;
    }

    return nouveauMagasin;
}



/* *************************************************************************
 * Cr�ation et initialisation de la structure de Produits pour la question 8
 ************************************************************************* */
T_ProduitTrie *creerProduitTrie(T_Produit *produit, T_Rayon *rayon) {
    T_ProduitTrie *ProduitTrie = NULL;

    ProduitTrie = malloc(sizeof(T_ProduitTrie));
    if (ProduitTrie != NULL) {
        // l'allocation m�moire s'est bien pass�e
        ProduitTrie->suivant = NULL;
        ProduitTrie->produit = produit;
        ProduitTrie->rayon = rayon;
    }

    return ProduitTrie;
}



/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {
    if (magasin != NULL) {
        T_Rayon *rayon = creerRayon(nomRayon);
        T_Rayon *rayonIntermediaire = magasin->liste_rayons;
        if (rayonIntermediaire == NULL) {
            // cas o� le magasion n'a pas de rayon
            magasin->liste_rayons = rayon;
            return 1;
        }
        else {
            // cas o� le magasin a au moins 1 rayon
            int cmp = strcmp(rayon->nom_rayon, rayonIntermediaire->nom_rayon);
            if (!cmp){
                // cas o� le premier rayon est identique � celui que l'on souhaite ajouter
                return 0;
            }
            else if (cmp < 0){
                // cas o� le rayon � ajouter doit �tre situ� avant le premier du magasin
                rayon->suivant = rayonIntermediaire;
                magasin->liste_rayons = rayon;
                return 1;
            }
            else{
                // cas g�n�ral (apr�s le premier rayon du magasin)
                while ((rayonIntermediaire->suivant != NULL) &&
                       ((cmp = strcmp(rayon->nom_rayon, rayonIntermediaire->suivant->nom_rayon)) >= 0)) {
                    if (!cmp){
                        // cas o� il existe un rayon dont le nom est identique (autre que le premier car v�rification d�j� faite)
                        return 0;
                    }
                    rayonIntermediaire = rayonIntermediaire->suivant;
                }
                rayon->suivant = rayonIntermediaire->suivant;
                rayonIntermediaire->suivant = rayon;
                return 1;
            }
        }
    }
    // Si le magasin n'existe pas, on ne fait rien
    return 0;
}



/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite) {
    if (rayon != NULL) {
        T_Produit *produit = creerProduit(designation, prix, quantite);
        T_Produit *produitIntermediaire = rayon->liste_produits;
        if (produitIntermediaire == NULL) {
            // cas o� le rayon n'a pas de produit
            rayon->liste_produits = produit;
            return 1;
        }
        else {
            // cas o� le rayon a au moins 1 produit
            if (!strcmp(produit->designation, produitIntermediaire->designation)){
                // cas o� le premier produit est identique � celui que l'on souhaite ajouter
                return 0;
            }
            else if (produit->prix == produitIntermediaire->prix){
                // cas o� le prix du premier produit est le m�me que le nouveau, on ajoute le nouveau � la suite
                produit->suivant = produitIntermediaire->suivant;
                produitIntermediaire->suivant = produit;
                return 1;
            }
            else if (produit->prix < produitIntermediaire->prix){
                // cas o� le produit � ajouter doit �tre situ� avant le premier du rayon (prix inf�rieur)
                produit->suivant = produitIntermediaire;
                rayon->liste_produits = produit;
                return 1;
            }
            else{
                while (produitIntermediaire->suivant != NULL)
                {
                    if (!strcmp(produit->designation, produitIntermediaire->suivant->designation)) {
                        // cas o� il existe un produit dont le nom est identique (autre que le premier car v�rification d�j� faite)
                        return 0;
                    }
                    produitIntermediaire = produitIntermediaire->suivant;
                }
                produitIntermediaire = rayon->liste_produits;
                // cas g�n�ral (apr�s le premier produit du rayon)
                while ((produitIntermediaire->suivant != NULL) &&
                        (produit->prix >= produitIntermediaire->suivant->prix)) {
                    if (produit->prix == produitIntermediaire->suivant->prix) {
                        // cas o� le prix du produit est le m�me que le nouveau, on ajoute le nouveau � la suite
                        produit->suivant = produitIntermediaire->suivant->suivant;
                        produitIntermediaire->suivant->suivant = produit;
                        return 1;
                    }
                    produitIntermediaire = produitIntermediaire->suivant;
                }
                produit->suivant = produitIntermediaire->suivant;
                produitIntermediaire->suivant = produit;
                return 1;
            }
        }
    }
    // Si le rayon n'existe pas, on ne fait rien
    return 0;
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin) {
    if (magasin != NULL) {
        T_Rayon *rayonIntermediaire = magasin->liste_rayons;
        if (rayonIntermediaire != NULL){
            char* nomFormat;
            char* nombreFormat;
            printf("\nVoici le(s) rayon(s) de %s :", magasin->nom);
            printf("\n+-------------------------------------------------------------+\n");
            printf("|Nom                           |Nombre de produits            |");
            do{
                printf("\n+------------------------------+------------------------------+\n");
                T_Produit *produitIntermediaire = rayonIntermediaire->liste_produits;
                int nombre = 0;
                if (produitIntermediaire != NULL){
                    do{
                        nombre += produitIntermediaire->quantite_en_stock;
                    }while((produitIntermediaire = produitIntermediaire->suivant) != NULL);
                }
                nomFormat = formatageNom(rayonIntermediaire->nom_rayon,30);
                nombreFormat = formatageChiffre(nombre,30);
                printf("|%s|%s|", nomFormat, nombreFormat);
            } while ((rayonIntermediaire = rayonIntermediaire->suivant) != NULL);
            free(nomFormat);
            free(nombreFormat);
            printf("\n+-------------------------------------------------------------+\n");
        }
        else{
            printf("\nAttention : le magasin \"%s\" n'a aucun rayon\n", magasin->nom);
        }
    }
    else{
        printf("\nAttention : ce magasin n'existe pas\n");
    }
}


/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    if (rayon != NULL){

        T_Produit *produitIntermediaire = rayon->liste_produits;
        if (produitIntermediaire != NULL){
            char* designationFormat;
            char* prixFormat;
            char* quantiteFormat;
            printf("\n%s :", rayon->nom_rayon);
            printf("\n+-----------------------------------------------------------------------------+\n");
            printf("|Designation                   |Prix           |Quantite en stock             |");
            do{
                printf("\n+------------------------------+---------------+------------------------------+\n");
                designationFormat = formatageNom(produitIntermediaire->designation,30);
                prixFormat = formatageFloat(produitIntermediaire->prix,15);
                quantiteFormat = formatageChiffre(produitIntermediaire->quantite_en_stock,30);
                printf("|%s|%s|%s|", designationFormat, prixFormat, quantiteFormat);
            } while ((produitIntermediaire = produitIntermediaire->suivant) != NULL);
            free(designationFormat);
            free(prixFormat);
            free(quantiteFormat);
            printf("\n+-----------------------------------------------------------------------------+\n");
        }
        else{
            printf("\nAttention : le rayon \"%s\" n'a aucun produit\n", rayon->nom_rayon);
        }
    }
    else{
        printf("\nAttention : ce rayon n'existe pas\n");
    }
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {
    if (rayon == NULL){
        // si le rayon n'existe pas on ne fait rien
        return 0;
    }
    T_Produit *produitIntermediaire = rayon->liste_produits;
    T_Produit *produitPrecedent = NULL;
    while(produitIntermediaire != NULL){
        if (!strcmp(produitIntermediaire->designation,designation_produit)){
            // cas o� le produit est trouv�
            if (produitPrecedent == NULL){
                rayon->liste_produits = produitIntermediaire->suivant;
            }
            else{
                produitPrecedent->suivant = produitIntermediaire->suivant;
            }
            free(produitIntermediaire->designation);
            free(produitIntermediaire);
            return 1;
        }
        produitPrecedent = produitIntermediaire;
        produitIntermediaire = produitIntermediaire->suivant;
    }
    // cas o� le produit n'a pas �t� trouv�
    return 0;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {
    if (magasin == NULL){
        // cas o� le magasin n'existe pas
        return 0;
    }
    T_Rayon *rayonIntermediaire = magasin->liste_rayons;
    T_Rayon *rayonPrecedent = NULL;
    while(rayonIntermediaire != NULL){
        if (!strcmp(rayonIntermediaire->nom_rayon,nom_rayon)){
            // cas o� le rayon est trouv�
            if (rayonPrecedent == NULL){
                magasin->liste_rayons = rayonIntermediaire->suivant;
            }
            else{
                rayonPrecedent->suivant = rayonIntermediaire->suivant;
            }
            while(rayonIntermediaire->liste_produits != NULL){
                // on lib�re l'espace m�moire de chacun des produits du rayon
                supprimerProduit(rayonIntermediaire, rayonIntermediaire->liste_produits->designation);
            }
            free(rayonIntermediaire->nom_rayon);
            free(rayonIntermediaire);
            return 1;
        }
        rayonPrecedent = rayonIntermediaire;
        rayonIntermediaire = rayonIntermediaire->suivant;
    }
    // cas o� le produit n'a pas �t� trouv�
    return 0;
}



/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {
    if (magasin == NULL){
        printf("\nAttention : ce magasin n'existe pas\n");
        return;
    }
    T_ProduitTrie *listeProduitTrie = NULL; // pointeur vers la t�te de liste chain�e pour l'ensemble des produits correspondants aux crit�res tri�s par ordre croissant sur le prix
    T_ProduitTrie *produitTrieIntermediaire = NULL; // pointeur vers les produits tri�s cr��s � partir des produits correspondant aux crit�res
    T_ProduitTrie *produitTrieIntermediaireParcourt = NULL; // pointeur pour parcourir la liste des produits tri�s
    T_Rayon *rayonIntermediaire = magasin->liste_rayons; // pointeur vers les rayons du magasin
    T_Produit *produitIntermediaire = NULL; // pointeur pour parcourir les produits d'un rayon
    if (rayonIntermediaire == NULL){
        printf("\nAttention : ce magasin n'a pas encore de rayon\n");
        return;
    }
    while(rayonIntermediaire != NULL){
        produitIntermediaire = rayonIntermediaire->liste_produits;
        while(produitIntermediaire != NULL && produitIntermediaire->prix <= prix_max){
            if(produitIntermediaire->prix >= prix_min){
                produitTrieIntermediaire = creerProduitTrie(produitIntermediaire, rayonIntermediaire);
                if (listeProduitTrie == NULL){
                    listeProduitTrie = produitTrieIntermediaire;
                    produitIntermediaire = produitIntermediaire->suivant;
                    continue;
                }
                if (produitTrieIntermediaire->produit->prix < listeProduitTrie->produit->prix){
                    produitTrieIntermediaire->suivant = listeProduitTrie;
                    listeProduitTrie = produitTrieIntermediaire;
                    produitIntermediaire = produitIntermediaire->suivant;
                    continue;
                }
                produitTrieIntermediaireParcourt = listeProduitTrie;
                while(produitTrieIntermediaireParcourt->suivant != NULL && produitTrieIntermediaire->produit->prix >= produitTrieIntermediaireParcourt->suivant->produit->prix){
                    produitTrieIntermediaireParcourt = produitTrieIntermediaireParcourt->suivant;
                }
                produitTrieIntermediaire->suivant = produitTrieIntermediaireParcourt->suivant;
                produitTrieIntermediaireParcourt->suivant = produitTrieIntermediaire;
            }
            produitIntermediaire = produitIntermediaire->suivant;
        }
        rayonIntermediaire = rayonIntermediaire->suivant;
    }
    if (listeProduitTrie == NULL){
        printf("\nAttention : aucun produit ne correspond a vos criteres\n");
        return;
    }
    // on affiche maintenant le resultat
    printf("\n+-----------------------------------------------------------------------------------------------------------+\n");
    printf("|Marque                        |Prix           |Quantite en stock             |Rayon                        |");
    do{
        produitTrieIntermediaireParcourt = listeProduitTrie;
        printf("\n+-----------------------------------------------------------------------------------------------------------+\n");
        printf("|%s|%s|%s|%s|", formatageNom(produitTrieIntermediaireParcourt->produit->designation,30),
                                formatageFloat(produitTrieIntermediaireParcourt->produit->prix,15),
                                formatageChiffre(produitTrieIntermediaireParcourt->produit->quantite_en_stock,30),
                                formatageNom(produitTrieIntermediaireParcourt->rayon->nom_rayon, 30)
        );
        listeProduitTrie = produitTrieIntermediaireParcourt->suivant;
        free(produitTrieIntermediaireParcourt);
    }while(listeProduitTrie != NULL);
    printf("\n+-----------------------------------------------------------------------------------------------------------+\n");
}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {
    char str[1000];
    T_Rayon *rayon1, *rayon2;
    T_Produit *produit1;
    T_Produit *produit2;
    printf("\nEntrez le nom du premier rayon avec lequel fusionner:");
    fgets(str, 1000, stdin); // r�cup�re au maximum les 999 caract�res �cris dans la console et les stocke dans la variable str
    viderBuffer();
    str[strcspn(str, "\n")] = '\0';
    rayon1 = obtenirRayon(magasin, str);
    if (rayon1 == NULL){
        // cas o� il n'existe aucun rayon portant le m�me nom que celui entree par l'utilisateur
        printf("\nErreur: le rayon n'existe pas\n");
        return;
    }
    printf("\nEntrez le nom du deuxieme rayon avec lequel fusionner:");
    fgets(str, 1000, stdin); // r�cup�re au maximum les 999 caract�res �cris dans la console et les stocke dans la variable str
    viderBuffer();
    str[strcspn(str, "\n")] = '\0';
    rayon2 = obtenirRayon(magasin, str);
    if (rayon2 == NULL){
        // cas o� il n'existe aucun rayon portant le m�me nom que celui entree par l'utilisateur
        printf("\nErreur: le rayon n'existe pas\n");
        return;
    }
    produit1 = rayon2->liste_produits;
    while (produit1 != NULL){
        // parcourt du 2e rayon pour ajouter dans le 1er les produits en utilisants la fonction ajouterProduit
        produit2 = rayon1->liste_produits;
        while (produit2 != NULL){
            if (!strcmp(produit2->designation,produit1->designation)){
                // cas o� 2 produits portent le m�me noms : on rajoute alors "-nom_rayon" � la suite du nom de ce dernier pour pouvoir les distinguer
                strcpy(str,produit1->designation);
                free(produit1->designation);
                produit1->designation = malloc(strlen(str)+strlen(rayon2->nom_rayon)+2);
                strcpy(produit1->designation, str);
                strcat(produit1->designation, "-");
                strcat(produit1->designation, rayon2->nom_rayon);
                strcpy(str, produit2->designation);
                free(produit2->designation);
                produit2->designation = malloc(strlen(str)+strlen(rayon1->nom_rayon)+2);
                strcpy(produit2->designation, str);
                strcat(produit2->designation, "-");
                strcat(produit2->designation, rayon1->nom_rayon);
            }
            produit2 = produit2->suivant;
        }
        ajouterProduit(rayon1,produit1->designation, produit1->prix, produit1->quantite_en_stock);
        produit1 = produit1->suivant;
    }
    printf("\nEntrez le nom du nouveau rayon resultant de la fusion:");
    fgets(str, 1000, stdin); // r�cup�re au maximum les 999 caract�res �cris dans la console et les stocke dans la variable str
    viderBuffer();
    str[strcspn(str, "\n")] = '\0';
    free(rayon1->nom_rayon);
    rayon1->nom_rayon = malloc(strlen(str) + 1);
    strcpy(rayon1->nom_rayon,str);
    printf("\nLa fusion en un seul rayon \"%s\" est un succes !", rayon1->nom_rayon);
    supprimerRayon(magasin, rayon2->nom_rayon);
}



/* *********************
 * Fonctions utilitaires
 ********************* */
// Vider le buffer (utile quand on utlise des getchar() )
void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) { // feof(stdin) renvoie une valeur non nulle si le buffer est vide
        c = getchar();
    }
}

// Obtenir le rayon � partir de son nom
T_Rayon *obtenirRayon(T_Magasin *magasin, char *nom){
    T_Rayon *rayonIntermediaire = NULL;
    rayonIntermediaire = magasin->liste_rayons;
    while (rayonIntermediaire != NULL){
        // parcourt de la liste chainee des rayons du magasin
        if (!strcmp(rayonIntermediaire->nom_rayon, nom)){
            // le rayon est trouv�
            break;
        }
        rayonIntermediaire = rayonIntermediaire->suivant;
    }
    return rayonIntermediaire;
}

/* **************************************************
 * Fonctions pour le formatage du texte des tableaux
 ************************************************** */
// cette fonction permet de faire tenir le nom des �l�ments des tableaux dans n>=3 caract�res (en rajoutant des espaces
// si besoin ou des "..." si le texte est plus long que n
char* formatageNom(char* chaine, int n){
    char* resultat = (char*) malloc((n+1) * sizeof(char));
    memset(resultat, 0, (n+1));
    int len = (int)strlen(chaine);
    if (len > n){
        strncpy(resultat, chaine, n-3);
        resultat[n-3] = '.';
        resultat[n-2] = '.';
        resultat[n-1] = '.';
    }
    else{
        strncpy(resultat, chaine, len);
        char* espace = (char*) malloc((n+1) * sizeof(char));
        memset(espace, ' ', n);
        espace[n] = '\0';
        strncat(resultat, espace, n - len);
        free(espace);
    }
    resultat[n] = '\0';
    return resultat;
}

// cette fonction permet de faire la m�me chose que formatageNom mais avec en entr�e un entier
char* formatageChiffre(int nombre, int n){
    int compteur = 0;
    int temp = nombre;
    do{
        temp = temp / 10;
        compteur++;
    }while (temp != 0);
    char* chaine = (char*) malloc((compteur+1) * sizeof(char));
    snprintf(chaine, compteur+1, "%d", nombre);
    return formatageNom(chaine, n);
}

// cette fonction permet de faire la m�me chose que formatageNom mais avec en entr�e un float
char* formatageFloat(float nombre, int n){
    int compteur = 0;
    float temp = nombre;
    do{
        temp = temp / 10;
        compteur++;
    }while (temp >= 1);
    // on asssigne compteur+4 emplacement m�moire � la chaine (1 pour le caract�re de fin de chaine, 1 pour le "." et 2
    // pour les chiffres apr�s la virgule
    char* chaine = (char*) malloc((compteur+4) * sizeof(char));
    snprintf(chaine, compteur+4, "%.2f", nombre);
    return formatageNom(chaine, n);
}
