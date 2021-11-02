#include "methodeDesPuissances.h"


int* creeVecteurAleatoire(int taille)
{
	int i;

	int * vecteur = NULL;
	vecteur = malloc(taille * sizeof(int));

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


void litVecteur(int* vecteur,int taille)
{
	int i;

	printf("Vecteur:\n");
	for(i=0;i<taille;i++)
		printf("|%d|\n",vecteur[i]);
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


int chercheMaxMatriceCarree(int** matrice,int taille)
{
	int i,j;
	int max = -9999;

	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
		{
			if(matrice[i][j] > max)
				max = matrice[i][j];
		}
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


int* produitMatriceCarreeParVecteur(int** matrice,int* vecteur,int taille)
{
	int i,j;
	int produitColonne;
	int * produitMatriceVecteur = NULL;
	produitMatriceVecteur = malloc(taille * sizeof(int));

	for(i=0;i<taille;i++)
	{
		produitColonne = 0;
		for(j=0;j<taille;j++)
		{
			produitColonne += matrice[i][j] * vecteur[j];
			printf("produitColonne: %d\n", produitColonne);
		}	
		produitMatriceVecteur[i] = produitColonne;
	}

	return produitMatriceVecteur;
}


int main()
{
	srand(time(NULL));

	int * vecteur = NULL;
	int ** matrice = NULL;
	int * produitMatriceVecteur = NULL;
	int taille = rand()%4 + 2;

	//int facteurScalaire = 3;

	vecteur = creeVecteurAleatoire(taille);
	matrice = creeMatriceCarreeAleatoire(taille);
	produitMatriceVecteur = produitMatriceCarreeParVecteur(matrice,vecteur,taille);
	litVecteur(vecteur,taille);
	litMatriceCarree(matrice,taille);
	litVecteur(produitMatriceVecteur,taille);
	printf("--------------------------------\n");
	//matrice = calculeProduitScalaireMatriceCarree(facteurScalaire,matrice,taille);
	//litMatriceCarree(matrice,taille);

	return 0;
}

