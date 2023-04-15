#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"


/* **********************************
 * Création et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite) {
    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit != NULL) {
        // l'allocation mémoire s'est bien passée
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace mémoire dédié pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

    return nouveauProduit;
}



/* ********************************
 * Création et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom) {
    T_Rayon *nouveauRayon = NULL;

    nouveauRayon = malloc(sizeof(T_Rayon));
    if (nouveauRayon != NULL) {
        // l'allocation mémoire s'est bien passée
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Création et initialisation Magasin
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



/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon) {
    if (magasin != NULL) {
        T_Rayon *rayon = creerRayon(nomRayon);
        T_Rayon *rayonIntermediaire = magasin->liste_rayons;
        if (rayonIntermediaire == NULL) {
            // cas où le magasion n'a pas de rayon
            magasin->liste_rayons = rayon;
            return 1;
        }
        else {
            // cas où le magasin a au moins 1 rayon
            int cmp = strcmp(rayon->nom_rayon, rayonIntermediaire->nom_rayon);
            if (!cmp){
                // cas où le premier rayon est identique à celui que l'on souhaite ajouter
                return 0;
            }
            else if (cmp < 0){
                // cas où le rayon à ajouter doit être situé avant le premier du magasin
                rayon->suivant = rayonIntermediaire;
                magasin->liste_rayons = rayon;
                return 1;
            }
            else{
                // cas général (après le premier rayon du magasin)
                while ((rayonIntermediaire->suivant != NULL) &&
                       ((cmp = strcmp(rayon->nom_rayon, rayonIntermediaire->suivant->nom_rayon)) >= 0)) {
                    if (!cmp){
                        // cas où il existe un rayon dont le nom est identique (autre que le premier car vérification déjà faite)
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
            // cas où le rayon n'a pas de produit
            rayon->liste_produits = produit;
            return 1;
        }
        else {
            // cas où le rayon a au moins 1 produit
            if (!strcmp(produit->designation, produitIntermediaire->designation)){
                // cas où le premier produit est identique à celui que l'on souhaite ajouter
                return 0;
            }
            else if (produit->prix == produitIntermediaire->prix){
                // cas où le prix du premier produit est le même que le nouveau, on ajoute le nouveau à la suite
                produit->suivant = produitIntermediaire->suivant;
                produitIntermediaire->suivant = produit;
                return 1;
            }
            else if (produit->prix < produitIntermediaire->prix){
                // cas où le produit à ajouter doit être situé avant le premier du rayon (prix inférieur)
                produit->suivant = produitIntermediaire;
                rayon->liste_produits = produit;
                return 1;
            }
            else{
                while (produitIntermediaire->suivant != NULL)
                {
                    if (!strcmp(produit->designation, produitIntermediaire->suivant->designation)) {
                        // cas où il existe un produit dont le nom est identique (autre que le premier car vérification déjà faite)
                        return 0;
                    }
                    produitIntermediaire = produitIntermediaire->suivant;
                }
                produitIntermediaire = rayon->liste_produits;
                // cas général (après le premier produit du rayon)
                while ((produitIntermediaire->suivant != NULL) &&
                        (produit->prix >= produitIntermediaire->suivant->prix)) {
                    if (produit->prix == produitIntermediaire->suivant->prix) {
                        // cas où le prix du produit est le même que le nouveau, on ajoute le nouveau à la suite
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
            // cas où le produit est trouvé
            if (produitPrecedent == NULL){
                rayon->liste_produits = produitIntermediaire->suivant;
            }
            else{
                produitPrecedent->suivant = produitIntermediaire->suivant;
            }
            free(produitIntermediaire);
            return 1;
        }
        produitPrecedent = produitIntermediaire;
        produitIntermediaire = produitIntermediaire->suivant;
    }
    // cas où le produit n'a pas été trouvé
    return 0;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {
    if (magasin == NULL){
        // cas où le magasin n'existe pas
        return 0;
    }
    T_Rayon *rayonIntermediaire = magasin->liste_rayons;
    T_Rayon *rayonPrecedent = NULL;
    while(rayonIntermediaire != NULL){
        if (!strcmp(rayonIntermediaire->nom_rayon,nom_rayon)){
            // cas où le produit est trouvé
            if (rayonPrecedent == NULL){
                magasin->liste_rayons = rayonIntermediaire->suivant;
            }
            else{
                rayonPrecedent->suivant = rayonIntermediaire->suivant;
            }
            while(rayonIntermediaire->liste_produits != NULL){
                // on libère l'espace mémoire de chacun des produits du rayon
                supprimerProduit(rayonIntermediaire, rayonIntermediaire->liste_produits->designation);
            }
            free(rayonIntermediaire);
            return 1;
        }
        rayonPrecedent = rayonIntermediaire;
        rayonIntermediaire = rayonIntermediaire->suivant;
    }
    // cas où le produit n'a pas été trouvé
    return 0;
}



/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {

}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {
    // TODO
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

// Obtenir le rayon à partir de son nom
T_Rayon *obtenirRayon(T_Magasin *magasin, char *nom){
    T_Rayon *rayonIntermediaire = NULL;
    rayonIntermediaire = magasin->liste_rayons;
    while (rayonIntermediaire != NULL){
        // parcourt de la liste chainee des rayons du magasin
        if (!strcmp(rayonIntermediaire->nom_rayon, nom)){
            // le rayon est trouvé
            break;
        }
        rayonIntermediaire = rayonIntermediaire->suivant;
    }
    return rayonIntermediaire;
}

/* **************************************************
 * Fonctions pour le formatage du texte des tableaux
 ************************************************** */
// cette fonction permet de faire tenir le nom des éléments des tableaux dans n>=3 caractères (en rajoutant des espaces
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

// cette fonction permet de faire la même chose que formatageNom mais avec en entrée un entier
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

// cette fonction permet de faire la même chose que formatageNom mais avec en entrée un float
char* formatageFloat(float nombre, int n){
    int compteur = 0;
    float temp = nombre;
    do{
        temp = temp / 10;
        compteur++;
    }while (temp >= 1);
    // on asssigne compteur+4 emplacement mémoire à la chaine (1 pour le caractère de fin de chaine, 1 pour le "." et 2
    // pour les chiffres après la virgule
    char* chaine = (char*) malloc((compteur+4) * sizeof(char));
    snprintf(chaine, compteur+4, "%.2f", nombre);
    return formatageNom(chaine, n);
}
