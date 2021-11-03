#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


float* creeVecteurAleatoire(int taille);
int** creeMatriceCarreeAleatoire(int taille);
void litVecteur(float* vecteur,int taille);
void litMatriceCarree(int** matrice,int taille);
float chercheMaxVecteur(float* vecteur,int taille);
int** calculeProduitScalaireMatriceCarree(int facteurScalaire,int** matrice,int taille);
float* produitMatriceCarreeParVecteur(int** matrice,float* vecteur,int taille);
float* diviseVecteurParFloat(float* vecteur,int taille,float diviseur);
