#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

// Structures et types
struct Produit {
    char *designation;
    float prix;
    int quantite_en_stock;
    struct Produit *suivant;
};
typedef struct Produit T_Produit;

struct Rayon {
    char *nom_rayon;
    T_Produit *liste_produits;
    struct Rayon *suivant;
};
typedef struct Rayon T_Rayon;

struct Magasin {
    char *nom;
    T_Rayon *liste_rayons;
};
typedef struct Magasin T_Magasin;

struct ProduitTrie {
    T_Produit *produit;
    struct ProduitTrie *suivant;
    T_Rayon *rayon;
};
typedef struct ProduitTrie T_ProduitTrie;


// Cr�ation et initialisation des structures
T_Produit *creerProduit(char *designation, float prix, int quantite);
T_Rayon *creerRayon(char *nom);
T_Magasin *creerMagasin(char *nom);
T_ProduitTrie *creerProduitTrie(T_Produit *produit, T_Rayon *rayon);

// Ajout (d'espaces) ou suppression de caract�res d'une chaine pour atteindre n caract�res
char* formatageNom(char* chaine, int n);
// Ajout (d'espaces) ou suppression de caract�res d'une chaine cr�� � partir d'un entier pour atteindre n caract�res
char* formatageChiffre(int nombre, int n);
// Ajout (d'espaces) ou suppression de caract�res d'une chaine cr�� � partir d'un float pour atteindre n caract�res
char* formatageFloat(float nombre, int n);

// Ajout d'un rayon dans un magasin
int ajouterRayon(T_Magasin *magasin, char *nomRayon);

// Ajout d'un produit dans un rayon
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite);

// Affichage de tous les rayons d'un magasin
void afficherMagasin(T_Magasin *magasin);

// Affichage de tous les produits d'un rayon
void afficherRayon(T_Rayon *rayon);

// Suppression d'un produit dans un rayon
int supprimerProduit(T_Rayon *rayon, char* designation_produit);

// Suppression d'un rayon et de tous les produits qu'il contient
int supprimerRayon(T_Magasin *magasin, char *nom_rayon);

// Recherche des produits se situant dans une fourchette de prix entr�e par l'utilisateur
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);

// Fusionner deux rayons
void fusionnerRayons(T_Magasin *magasin);

// Renvoie le rayon associ� au nom entr�
T_Rayon *obtenirRayon(T_Magasin *magasin, char *nom);
// UTILS
void viderBuffer() ;

#endif // TP3_H_INCLUDED
