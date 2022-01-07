#include "LIMCHOUSANGBjorn-ROYThomas_codeSourcePUISS.h"
#include "lectureMatrice.h"

double* creeVecteurAleatoire(int taille)
{
	int i;

	double * vecteur = NULL;
	vecteur = malloc(taille * sizeof(double));

	for(i=0;i<taille;i++)
		vecteur[i] = rand()%10;

	return vecteur;
}


double** creeMatriceCarreeAleatoire(int taille)
{
	int i, j;

	double** matrice = NULL;
	matrice = malloc(taille * sizeof(double*));

	for(i=0;i<taille;i++)
	{
		matrice[i] = malloc(taille * sizeof(double));
		for(j=0;j<taille;j++)
			matrice[i][j] = rand()%10;
	}

	return matrice;
}


void litVecteur(double* vecteur,int taille)
{
	int i;

	printf("Vecteur:\n");
	for(i=0;i<taille;i++)
		printf("|%.3f|\n",vecteur[i]);
}


void litMatriceCarree(double** matrice,int taille)
{
	int i,j;

	printf("Matrice carrée:\n");
	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
			printf("|%f|",matrice[i][j]);
		printf("\n");
	}
}


double chercheMaxVecteur(double* vecteur,int taille)
{
	int i;
	double max = fabs(vecteur[0]);
	int nbThreads = omp_get_num_threads();

	if(nbThreads > taille)
	{
		nbThreads = taille;
	}

	#pragma omp parallel num_threads(nbThreads) 
	{
		#pragma omp for schedule(static,taille/nbThreads) 
		for(i = 1;i < taille;i++)
		{
			#pragma omp critical
			{
				if(fabs(vecteur[i]) > max)
					max = fabs(vecteur[i]);
			}
		}
	}

	return max;
}


int estMatriceNulle(double** matrice, int taille)
{
	int i,j;

	for (i = 0; i < taille; i++)
	{
		for(j = 0; j < taille; j++)
		{
			if(matrice[i][j] != 0)
			{
				return 0;
			}
		}
	}

	return 1;
}


void calculeProduitScalaireMatriceCarree(int facteurScalaire,double** matrice,int taille)
{
	int i,j;

	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
				matrice[i][j] *= facteurScalaire;
	}
}


double* produitMatriceCarreeParVecteur(double** matrice,double* vecteur,int taille)
{	
	double* resultat = malloc(taille * sizeof(double));
	int nbThreads = omp_get_num_threads();

	if(nbThreads > taille)
	{
		nbThreads = taille;
	}


	#pragma omp parallel num_threads(nbThreads)
	{
		int i,j;
		double produitColonne;

		#pragma omp for schedule(static,taille/nbThreads)
		for(i=0;i<taille;i++)
		{
			produitColonne = 0;
			for(j=0;j<taille;j++)
			{
				produitColonne += matrice[i][j] * vecteur[j];
			}
			resultat[i] = produitColonne;
		}
	}
	return resultat;
}



void diviseVecteurParDouble(double* vecteur,int taille,double diviseur)
{
	int i;
	
	if(diviseur != 0)
	{
		for(i=0;i<taille;i++)
			vecteur[i] = vecteur[i]/diviseur;
	}
}


int methodeDesPuissances(double** matrice,double* vecteur,int taille)
{
	int iteration = 0;
	double maxVecteur;
	double ancienMaxVecteur;
	double taux;
	int resultat;

	ancienMaxVecteur = chercheMaxVecteur(vecteur,taille);
	if (estMatriceNulle(matrice,taille))
	{
		printf("ERREUR : LA MATRICE EST NULLE");
		return -1;
	}

	printf("Max: %.3f\n", ancienMaxVecteur);
	diviseVecteurParDouble(vecteur,taille,ancienMaxVecteur);

	do{

		iteration++;
		printf("Iteration: %d\n", iteration);

		vecteur = produitMatriceCarreeParVecteur(matrice,vecteur,taille);

		maxVecteur = chercheMaxVecteur(vecteur,taille);
		printf("Max: %.3f\n", maxVecteur);

		diviseVecteurParDouble(vecteur,taille,maxVecteur);
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
	double debut, fin;
	double * vecteur = NULL;
	double** matrice = NULL;
	int taille = 0;
	int choix;
	printf("Choisissez un exemple :\n 1) Matrice 2*2\n 2) Matrice 3*3\n 3) Matrice 1250*1250\n 4) Matrice 6*6\n");
    printf("Donner un entier: ");
    scanf("%d", &choix);
	printf("\n");
	switch (choix)
	{
	case 1: // EXEMPLE 1 RESULTAT ATTENDU : 16
			debut = omp_get_wtime();
			taille = 2;
			vecteur = creeVecteurAleatoire(taille);
			vecteur[0] = -1;
			vecteur[1] = 0.5f;

			matrice = creeMatriceCarreeAleatoire(taille);
			matrice[0][0] = 7;
			matrice[0][1] = 9;
			matrice[1][1] = 7;
			matrice[1][0] = 9;
			litVecteur(vecteur,taille);
			litMatriceCarree(matrice,taille);
			methodeDesPuissances(matrice,vecteur,taille);
			free(vecteur);
			free(matrice);
			fin = omp_get_wtime();
			printf("Temps d'execution total: %f secondes\n", fin-debut);
		break;
	case 2: //EXEMPLE 2 RESULTAT ATTENDU : -1, 2, 6, 8, 9, ou 10
			debut = omp_get_wtime();

			taille = 3;
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
			litVecteur(vecteur,taille);
			litMatriceCarree(matrice,taille);
			methodeDesPuissances(matrice,vecteur,taille);
			free(vecteur);
			free(matrice);
			fin = omp_get_wtime();
			printf("Temps d'execution total: %f secondes\n", fin-debut);
		break;
	case 3: //EXEMPLE 3
			debut = omp_get_wtime();
			matrice = lectureFichier("rdb1250.mtx",&taille);
			vecteur = creeVecteurAleatoire(taille);
			for (int i = 0; i < 30; i++)
			{
				methodeDesPuissances(matrice,vecteur,taille);
			}
			free(vecteur);
			free(matrice);
			fin = omp_get_wtime();
			printf("Temps d'execution total: %f secondes\n", fin-debut);
		break;
	case 4: // EXEMPLE 4 RESULTAT ATTENDU : 2 , -1, 1/2, 9, 3 , ou -6,
			debut = omp_get_wtime();
			taille = 6;

			vecteur = creeVecteurAleatoire(taille);

			matrice = creeMatriceCarreeAleatoire(taille);
			matrice[0][0] = 2;
			matrice[0][1] = 7;
			matrice[0][2] = -1;
			matrice[0][3] = 4;
			matrice[0][4] = 5;
			matrice[0][5] = 11;

			matrice[1][0] = 0;
			matrice[1][1] = -1;
			matrice[1][2] = 2;
			matrice[1][3] = 0;
			matrice[1][4] = 0;
			matrice[2][5] = 6;

			matrice[2][0] = 0;
			matrice[2][1] = 0;
			matrice[2][2] = 0.5f;
			matrice[2][3] = 1;
			matrice[2][4] = 0;
			matrice[2][5] = 5;
			
			matrice[3][0] = 0;
			matrice[3][1] = 0;
			matrice[3][2] = 0;
			matrice[3][3] = 9;
			matrice[3][4] = 5;
			matrice[3][5] = -2;

			matrice[4][0] = 0;
			matrice[4][1] = 0;
			matrice[4][2] = 0;
			matrice[4][3] = 0;
			matrice[4][4] = 3;
			matrice[4][5] = 3;

			matrice[5][0] = 0;
			matrice[5][1] = 0;
			matrice[5][2] = 0;
			matrice[5][3] = 0;
			matrice[5][4] = 0;
			matrice[5][5] = -6;
			litVecteur(vecteur,taille);
			litMatriceCarree(matrice,taille);
			methodeDesPuissances(matrice,vecteur,taille);
			free(vecteur);
			free(matrice);
			fin = omp_get_wtime();
			printf("Temps d'execution total: %f secondes\n", fin-debut);
		break;
	default:
		printf("Choisissez un exemple valide...\n");
		break;
	}
	return 0;
}

