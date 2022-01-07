#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<omp.h>


double* creeVecteurAleatoire(int taille);
double** creeMatriceCarreeAleatoire(int taille);
void litVecteur(double* vecteur,int taille);
void litMatriceCarree(double** matrice,int taille);
double chercheMaxVecteur(double* vecteur,int taille);
int estMatriceNulle(double** matrice, int taille);
void calculeProduitScalaireMatriceCarree(int facteurScalaire,double** matrice,int taille);
double* produitMatriceCarreeParVecteur(double** matrice,double* vecteur,int taille);
void diviseVecteurParDouble(double* vecteur,int taille,double diviseur);
int methodeDesPuissances(double** matrice,double* vecteur,int taille);
