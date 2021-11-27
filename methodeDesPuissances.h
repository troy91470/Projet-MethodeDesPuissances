#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


float* creeVecteurAleatoire(int taille);
int** creeMatriceCarreeAleatoire(int taille);
void litVecteur(float* vecteur,int taille);
void litMatriceCarree(int** matrice,int taille);
float chercheMaxVecteur(float* vecteur,int taille);
int estMatriceNulle(int** matrice, int taille);
void calculeProduitScalaireMatriceCarree(int facteurScalaire,int** matrice,int taille);
float* produitMatriceCarreeParVecteur(int** matrice,float* vecteur,int taille);
void diviseVecteurParFloat(float* vecteur,int taille,float diviseur);
int methodeDesPuissances(int ** matrice,float* vecteur,int taille);
