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
	float max = fabs(vecteur[0]);

	for(i = 1;i < taille;i++)
	{
		if(fabs(vecteur[i]) > max)
			max = fabs(vecteur[i]);
	}

	return max;
}

int estMatriceNulle(int** matrice, int taille)
{
	int i,j;
	for (i = 0; i < taille; i++)
	{
		for (j = 0; j < taille; j++)
		{
			if(matrice[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
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


float* produitMatriceCarreeParVecteur(int** matrice,float* vecteur,int taille)
{
	int i,j;
	float produitColonne;
	float* resultat = malloc(taille * sizeof(int));
	for(i=0;i<taille;i++)
	{
		produitColonne = 0;
		for(j=0;j<taille;j++)
		{
			produitColonne += matrice[i][j] * vecteur[j];
			//printf("Produit : matrice : %d vecteur : %f resultat : %f  \n",matrice[i][j],vecteur[j],matrice[i][j] * vecteur[j]);
		}
		resultat[i] = produitColonne;
		//printf("Résultat : %f %f \n",resultat[i],produitColonne);
	}
	return resultat;
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
int methodeDesPuissances(int ** matrice,float* vecteur,int taille)
{
	int iteration = 0;
	float maxVecteur;
	float ancienMaxVecteur;
	float taux;
	int resultat;
	litVecteur(vecteur,taille);
	litMatriceCarree(matrice,taille);

	ancienMaxVecteur = chercheMaxVecteur(vecteur,taille);
	if (estMatriceNulle(matrice,taille))
	{
		printf("ERREUR : LA MATRICE EST NULLE");
		return -1;	
	}
	
	printf("Max: %.3f\n", ancienMaxVecteur);
	diviseVecteurParFloat(vecteur,taille,ancienMaxVecteur);
	litVecteur(vecteur,taille);

	do{

		iteration++;
		printf("Iteration: %d\n", iteration);

		vecteur = produitMatriceCarreeParVecteur(matrice,vecteur,taille);
		litVecteur(vecteur,taille);

		maxVecteur = chercheMaxVecteur(vecteur,taille);
		printf("Max: %.3f\n", maxVecteur);

		diviseVecteurParFloat(vecteur,taille,maxVecteur);
		litVecteur(vecteur,taille);
		
		taux = (maxVecteur - ancienMaxVecteur)/ancienMaxVecteur;
		printf("-- taux: %.3f --\n",taux);
		ancienMaxVecteur = maxVecteur; 

	}while(taux > 0.05f || taux < -0.05f);


	resultat = roundf(maxVecteur);
	printf("\n------------------------------\n");
	printf("La valeur propre est %d.\n",resultat);
	printf("Le vecteur associé est ");
	litVecteur(vecteur,taille);
	return 0;
}



int main()
{
	srand(time(NULL));
	// EXEMPLE 1 RESULTAT ATTENDU : 16
	/*
	float * vecteur = NULL;
	int ** matrice = NULL;
	int taille = 2;

	vecteur = creeVecteurAleatoire(taille);
	vecteur[0] = -1;
	vecteur[1] = 0.5f;

	matrice = creeMatriceCarreeAleatoire(taille);
	matrice[0][0] = 7;
	matrice[0][1] = 9;
	matrice[1][1] = 7;
	matrice[1][0] = 9;
	*/
	//EXEMPLE 2 //RESULTAT ATTENDU : -1, 2 ou 8
	float * vecteur = NULL;
	int ** matrice = NULL;
	int taille = 3;

	vecteur = creeVecteurAleatoire(taille);

	matrice = creeMatriceCarreeAleatoire(taille);
	matrice[0][0] = 2;
	matrice[0][1] = 0;
	matrice[0][2] = 0;

	matrice[1][0] = 0;
	matrice[1][1] = 4;
	matrice[1][2] = 5;

	matrice[2][0] = 0;
	matrice[2][1] = 4;
	matrice[2][2] = 3;

	
	methodeDesPuissances(matrice,vecteur,taille);
	free(vecteur);
	free(matrice);
	return 0;
}

