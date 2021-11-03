#include "methodeDesPuissances.h"


float* creeVecteurAleatoire(int taille)
{
	int i;

	float * vecteur = NULL;
	vecteur = malloc(taille * sizeof(float));

	for(i=0;i<taille;i++)
		vecteur[i] = rand()%10;

	return vecteur;
}


int** creeMatriceCarreeAleatoire(int taille)
{
	int i, j;

	int ** matrice = NULL;
	matrice = malloc(taille * sizeof(int*));

	for(i=0;i<taille;i++)
	{
		matrice[i] = malloc(taille * sizeof(int));
		for(j=0;j<taille;j++)
			matrice[i][j] = rand()%10;
	}

	return matrice;
}


void litVecteur(float* vecteur,int taille)
{
	int i;

	printf("Vecteur:\n");
	for(i=0;i<taille;i++)
		printf("|%.3f|\n",vecteur[i]);
}


void litMatriceCarree(int** matrice,int taille)
{
	int i,j;

	printf("Matrice carrée:\n");
	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
			printf("|%d|",matrice[i][j]);
		printf("\n");
	}
}


float chercheMaxVecteur(float* vecteur,int taille)
{
	int i;
	float max = -9999;

	for(i=0;i<taille;i++)
	{
		if(vecteur[i] > max)
			max = vecteur[i];
	}

	return max;
}


int** calculeProduitScalaireMatriceCarree(int facteurScalaire,int** matrice,int taille)
{
	int i,j;

	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
				matrice[i][j] *= facteurScalaire;
	}

	return matrice;
}


float* produitMatriceCarreeParVecteur(int** matrice,float* vecteur,int taille)
{
	int i,j;
	int produitColonne;
	float* produitMatriceVecteur = NULL;
	produitMatriceVecteur = malloc(taille * sizeof(float));

	for(i=0;i<taille;i++)
	{
		produitColonne = 0;
		for(j=0;j<taille;j++)
			produitColonne += matrice[i][j] * vecteur[j];
		produitMatriceVecteur[i] = produitColonne;
	}

	return produitMatriceVecteur;
}


float* diviseVecteurParFloat(float* vecteur,int taille,float diviseur)
{
	int i;
	float* nouveauVecteur = NULL;
	nouveauVecteur = malloc(taille * sizeof(float));

	//QUE FAIRE SI DIVISEUR = 0 (cad si maxVecteur = 0)
	for(i=0;i<taille;i++)
		nouveauVecteur[i] = vecteur[i]/diviseur;

	return nouveauVecteur;
}


int main()
{
	srand(time(NULL));

	float * vecteur = NULL;
	int ** matrice = NULL;
	int taille = rand()%4 + 2;
	float maxVecteur;
	float ancienMaxVecteur = 1;
	float taux;
	int resultat;
	//int facteurScalaire = 3;


	vecteur = creeVecteurAleatoire(taille);
	litVecteur(vecteur,taille);

	matrice = creeMatriceCarreeAleatoire(taille);
	litMatriceCarree(matrice,taille);


	/*do{
		vecteur = produitMatriceCarreeParVecteur(matrice,vecteur,taille);
		litVecteur(vecteur,taille);

		maxVecteur = chercheMaxVecteur(vecteur,taille);
		printf("Max: %.3f\n", maxVecteur);

		vecteur = diviseVecteurParFloat(vecteur,taille,maxVecteur);
		litVecteur(vecteur,taille);

		taux = maxVecteur / ancienMaxVecteur;
		printf("-- taux: %.3f --\n",taux);
		ancienMaxVecteur = maxVecteur; 
	}while(taux > 0.05);*/

	resultat = ceilf(maxVecteur);
	printf("Le résultat est %d.\n",resultat);

	return 0;
}

