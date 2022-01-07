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
	double maxValeur = fabs(vecteur[0]);
	//double debut, fin;	

	//debut = omp_get_wtime();
	#pragma omp parallel
	{
		#pragma omp for // schedule(static,taille/omp_get_num_threads())
		for(i = 1;i < taille;i++)
		{
			//if(fabs(vecteur[i]) > maxValeur)
				//maxValeur = fabs(vecteur[i]);
			double temp = fabs(vecteur[i]);
			#pragma omp critical
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


double* produitMatriceCarreeParVecteur(double** matrice,double* vecteur,int taille)
{
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
		//#pragma omp parallel for schedule(static,taille/omp_get_num_threads())
		for(i=0;i<taille;i++)
			vecteur[i] = vecteur[i]/diviseur;
	}
}
void multiplieVecteurPardouble(double* vecteur,int taille,double facteur)
{
	int i;
	//#pragma omp parallel for schedule(static,taille/omp_get_num_threads())
	for(i=0;i<taille;i++)
		vecteur[i] = vecteur[i]*facteur;

}

int methodeDesPuissances(double** matrice,double* vecteur,int taille)
{
	int iteration = 0;
	double maxVecteur;
	double ancienMaxVecteur;
	double taux;
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
			vecteur = produitMatriceCarreeParVecteur(matrice,vecteur,taille);
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

	return 0;
}



int main()
{
	srand(time(NULL));
	double debut, fin;
	//debut = omp_get_wtime();
	//TEST SCALABILITE FAIBLE
	int nbThreads[6] = {1,2,4,8,16,32};
	int tailleProbleme[6] = {128,256,512,1024,2048,4096};
	for (int i = 0; i < 6; i++)
	{
		omp_set_num_threads(nbThreads[i]);
		double * vecteur = NULL;
		double** matrice = NULL;
		vecteur = creeVecteurAleatoire(tailleProbleme[i]);
		matrice = creeMatriceCarreeAleatoire(tailleProbleme[i]);
		printf("Nombre de Threads : %d Taille du probleme : %d\n",nbThreads[i],tailleProbleme[i]);
		printf("-------------------------------------\n");
		for (int j = 0; j < 20; ++j)
		{
		debut = omp_get_wtime();
		methodeDesPuissances(matrice,vecteur,tailleProbleme[i]);

		fin = omp_get_wtime();
		printf("Temps d'execution total: %f secondes\n", fin-debut);
		}
		printf("-------------------------------------\n");
	}
	return 0;
}
