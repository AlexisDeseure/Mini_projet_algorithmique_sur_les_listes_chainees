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
            if (produit->prix == produitIntermediaire->prix){
                if (!strcmp(produit->designation, produitIntermediaire->designation)){
                    // cas o� le premier produit est identique � celui que l'on souhaite ajouter (on ne s'int�resse pas
                    // � la quantit� mais on estime que deux produits sont identiques s'ils ont le m�m prix et la m�me
                    // d�signation
                    return 0;
                }
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
                // cas g�n�ral (apr�s le premier produit du rayon)
                while ((produitIntermediaire->suivant != NULL) &&
                        (produit->prix >= produitIntermediaire->suivant->prix)) {
                    if (produit->prix == produitIntermediaire->suivant->prix) {
                        if (!strcmp(produit->designation, produitIntermediaire->suivant->designation)) {
                            // cas o� il existe un produit dont le nom est identique (autre que le premier car v�rification d�j� faite)
                            return 0;
                        }
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
 * Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
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
