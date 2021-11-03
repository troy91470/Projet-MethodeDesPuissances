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


void calculeProduitScalaireMatriceCarree(int facteurScalaire,int** matrice,int taille)
{
	int i,j;

	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
				matrice[i][j] *= facteurScalaire;
	}
}


void produitMatriceCarreeParVecteur(int** matrice,float* vecteur,int taille)
{
	int i,j;
	int produitColonne;

	for(i=0;i<taille;i++)
	{
		produitColonne = 0;
		for(j=0;j<taille;j++)
			produitColonne += matrice[i][j] * vecteur[j];
		vecteur[i] = produitColonne;
	}

}


void diviseVecteurParFloat(float* vecteur,int taille,float diviseur)
{
	int i;

	if(diviseur != 0)
	{
		for(i=0;i<taille;i++)
			vecteur[i] = vecteur[i]/diviseur;
	}
}


int main()
{
	srand(time(NULL));

	float * vecteur = NULL;
	int ** matrice = NULL;
	int taille = rand()%4 + 2;
	int iteration = 0;
	float maxVecteur;
	float ancienMaxVecteur;
	float taux;
	int resultat;


	vecteur = creeVecteurAleatoire(taille);
	litVecteur(vecteur,taille);

	maxVecteur = chercheMaxVecteur(vecteur,taille);
	printf("Max: %.3f\n", maxVecteur);

	diviseVecteurParFloat(vecteur,taille,maxVecteur);
	litVecteur(vecteur,taille);

	matrice = creeMatriceCarreeAleatoire(taille);
	litMatriceCarree(matrice,taille);


	do{

		iteration++;
		printf("Iteration: %d\n", iteration);

		produitMatriceCarreeParVecteur(matrice,vecteur,taille);
		litVecteur(vecteur,taille);

		maxVecteur = chercheMaxVecteur(vecteur,taille);
		printf("Max: %.3f\n", maxVecteur);
		maxVecteur = 0;
		if(maxVecteur == 0)
			break;

		diviseVecteurParFloat(vecteur,taille,maxVecteur);
		litVecteur(vecteur,taille);
		
		if(iteration == 1)
			ancienMaxVecteur = maxVecteur * 2;
		taux = 1 - maxVecteur / ancienMaxVecteur;
		printf("-- taux: %.3f --\n",taux);
		ancienMaxVecteur = maxVecteur; 

	}while(taux > 0.1);


	resultat = ceilf(maxVecteur);
	printf("Le résultat est %d.\n",resultat);

	return 0;
}

