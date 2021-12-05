#include "methodeDesPuissances.h"
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
	double maxValeur = fabs(vecteur[0]);
	//double debut, fin;	

	//debut = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for reduction(max : maxValeur) schedule(static,taille/omp_get_num_threads())
		for(i = 1;i < taille;i++)
		{
			//if(fabs(vecteur[i]) > maxValeur)
				//maxValeur = fabs(vecteur[i]);
			double temp = fabs(vecteur[i]);
			//#pragma omp critical
			maxValeur = maxValeur > temp ? maxValeur : temp;
		}
	}
	//fin = omp_get_wtime();
	//printf("Temps d'execution MAXVALEUR: %f secondes\n", fin-debut);
	return maxValeur;
}

int estMatriceNulle(double** matrice, int taille)
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


void calculeProduitScalaireMatriceCarree(int facteurScalaire,double** matrice,int taille)
{
	int i,j;
	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
				matrice[i][j] *= facteurScalaire;
	}
}


double* produitMatriceCarreeParVecteur(double** matrice,double* vecteur,int taille,int rang)
{	
	/*
	double* resultat = malloc(taille * sizeof(double));
	int nbThreads = omp_get_num_threads();
	if(nbThreads > taille)
	{
		nbThreads = taille;
	}
	//#pragma omp parallel num_threads(nbThreads)
	//{
		int i,j;
		double produitColonne;
		//#pragma omp for schedule(static,taille/nbThreads)
		for(i=rang * (taille / nbThreads);i< (rang + 1) * (taille / nbThreads);i++)
		{
			produitColonne = 0;
			for(j=0;j<taille;j++)
			{
				//printf("%d %d \n",i,j);
				produitColonne += matrice[i][j] * vecteur[j];
				//printf("Produit : matrice : %d vecteur : %f resultat : %f  \n",matrice[i][j],vecteur[j],matrice[i][j] * vecteur[j]);
			}
			resultat[i] = produitColonne;
			//printf("Résultat : %f %f \n",resultat[i],produitColonne);
		}
	//}
	return resultat;

	*/
	double* resultat = malloc(taille * sizeof(double));
	int nbThreads = omp_get_max_threads();
	
	if(nbThreads > taille)
	{
		nbThreads = taille;
	}
	#pragma omp  parallel num_threads(nbThreads)
	{
		int i,j;
		double produitColonne;
		//printf("THREADS : %d\n",omp_get_num_threads());
		#pragma omp for schedule(static,taille/omp_get_num_threads())
		for(i=0;i<taille;i++)
		{
			produitColonne = 0;
			for(j=0;j<taille;j++)
			{
				//printf("%d %d \n",i,j);
				produitColonne += matrice[i][j] * vecteur[j];
				//printf("Produit : matrice : %d vecteur : %f resultat : %f  \n",matrice[i][j],vecteur[j],matrice[i][j] * vecteur[j]);
			}
			resultat[i] = produitColonne;
			//printf("Résultat : %f %f \n",resultat[i],produitColonne);
		}
	}
	return resultat;
}



void diviseVecteurPardouble(double* vecteur,int taille,double diviseur)
{
	int i;

	if(diviseur != 0)
	{
		#pragma omp parallel for schedule(static,taille/omp_get_num_threads())
		for(i=0;i<taille;i++)
			vecteur[i] = vecteur[i]/diviseur;
	}
}
void multiplieVecteurPardouble(double* vecteur,int taille,double facteur)
{
	int i;
	#pragma omp parallel for schedule(static,taille/omp_get_num_threads())
	for(i=0;i<taille;i++)
		vecteur[i] = vecteur[i]*facteur;

}

int methodeDesPuissances(double** matrice,double* vecteur,int taille)
{
	int iteration = 0;
	double maxVecteur;
	double ancienMaxVecteur;
	double taux;
	int resultat;
	// litVecteur(vecteur,taille);
	// litMatriceCarree(matrice,taille);

	ancienMaxVecteur = chercheMaxVecteur(vecteur,taille);
	if (estMatriceNulle(matrice,taille))
	{
		printf("ERREUR : LA MATRICE EST NULLE");
		return -1;	
	}
	
	// printf("Max: %.3f\n", ancienMaxVecteur);
	diviseVecteurPardouble(vecteur,taille,ancienMaxVecteur);
	// litVecteur(vecteur,taille);
	do{

				iteration++;
				// printf("Iteration: %d\n", iteration);
			//}
			vecteur = produitMatriceCarreeParVecteur(matrice,vecteur,taille,omp_get_thread_num());
			//litVecteur(vecteur,taille);
				maxVecteur = chercheMaxVecteur(vecteur,taille);
				// printf("Max: %.3f\n", maxVecteur);

				//diviseVecteurPardouble(vecteur,taille,maxVecteur);
				multiplieVecteurPardouble(vecteur,taille,1/maxVecteur);
				// litVecteur(vecteur,taille);
				
				taux = (maxVecteur - ancienMaxVecteur)/ancienMaxVecteur;
				// printf("-- taux: %.3f --\n",taux);
				ancienMaxVecteur = maxVecteur; 
	}while(taux > 0.01f || taux < -0.01f);

	

	resultat = roundf(maxVecteur);
	//printf("\n------------------------------\n");
	//printf("La valeur propre est %d.\n",resultat);
	//printf("Le vecteur associé est ");
	//litVecteur(vecteur,taille);
	return 0;
}



int main()
{
	srand(time(NULL));
	double debut, fin;	
	for (int i = 0; i < 20; ++i)
	{
		/* code */
	
	debut = omp_get_wtime();

	// EXEMPLE 1 RESULTAT ATTENDU : 16
	/*
	double * vecteur = NULL;
	double** matrice = NULL;
	int taille = 2;

	vecteur = creeVecteurAleatoire(taille);
	vecteur[0] = -1;
	vecteur[1] = 0.5f;

	matrice = creeMatriceCarreeAleatoire(taille);
	matrice[0][0] = 7;
	matrice[0][1] = 9;
	matrice[1][1] = 7;
	matrice[1][0] = 9;

	methodeDesPuissances(matrice,vecteur,taille);
	free(vecteur);
	free(matrice);
	*/
		
	//EXEMPLE 2 //RESULTAT ATTENDU : -1, 2, 6, 8, 9, ou 10 (8 et 9 à 90%)
	/*
	double * vecteur = NULL;
	double** matrice = NULL;
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
	*/

	//EXEMPLE 3 RESULTAT ATTENDU : 11 -35 -79 -120 ???? Donne entre 145 et 166
	
	double * vecteur = NULL;
	double** matrice = NULL;
	int taille;
	matrice = lectureFichier("rdb1250.mtx",&taille);
	//printf("TAille : %d\n",taille);
	vecteur = creeVecteurAleatoire(taille);
	for (int i = 0; i < 30; i++)
	{
		methodeDesPuissances(matrice,vecteur,taille);
	}
	
	free(vecteur);
	free(matrice);
	

	// EXEMPLE 4 RESULTAT ATTENDU : 2 , -1, 1/2, 9, 3 , ou -6, ==> WTF, moi j'ai 9 à 95% et j'ai eu 10 une fois
	/**
	double * vecteur = NULL;
	double** matrice = NULL;
	int taille = 6;

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

	methodeDesPuissances(matrice,vecteur,taille);
	free(vecteur);
	free(matrice);
	*/
	fin = omp_get_wtime();
	printf("Temps d'execution total: %f secondes\n", fin-debut);
	}
	return 0;
}

