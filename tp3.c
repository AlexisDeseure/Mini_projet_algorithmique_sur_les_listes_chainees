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
            if (produit->prix == produitIntermediaire->prix){
                if (!strcmp(produit->designation, produitIntermediaire->designation)){
                    // cas où le premier produit est identique à celui que l'on souhaite ajouter (on ne s'intéresse pas
                    // à la quantité mais on estime que deux produits sont identiques s'ils ont le mêm prix et la même
                    // désignation
                    return 0;
                }
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
                // cas général (après le premier produit du rayon)
                while ((produitIntermediaire->suivant != NULL) &&
                        (produit->prix >= produitIntermediaire->suivant->prix)) {
                    if (produit->prix == produitIntermediaire->suivant->prix) {
                        if (!strcmp(produit->designation, produitIntermediaire->suivant->designation)) {
                            // cas où il existe un produit dont le nom est identique (autre que le premier car vérification déjà faite)
                            return 0;
                        }
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

}



/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon) {
    // TODO
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {
    // TODO
    return 1;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon) {
    // TODO
    return 1;
}



/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max) {
    // TODO
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
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
