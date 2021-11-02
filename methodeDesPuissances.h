#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int* creeVecteurAleatoire(int taille);
int** creeMatriceCarreeAleatoire(int taille);
void litMatriceCarree(int** matrice,int taille);
int chercheMaxMatriceCarree(int** matrice,int taille);
int* produitMatriceCarreeParVecteur(int** matrice,int* vecteur,int taille);
