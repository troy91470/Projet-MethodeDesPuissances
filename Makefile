main.o: LIMCHOUSANGBjorn-ROYThomas_codeSourcePUISS.c lectureMatrice.c mmio.c
	gcc LIMCHOUSANGBjorn-ROYThomas_codeSourcePUISS.c lectureMatrice.c mmio.c -o methodeDesPuissances -fopenmp -lm

forte1: methodeDesPuissancesV1Forte.c lectureMatrice.c mmio.c
	gcc methodeDesPuissancesV1Forte.c lectureMatrice.c mmio.c -o methodeDesPuissances -fopenmp -lm

forte2: methodeDesPuissancesV2Forte.c lectureMatrice.c mmio.c
	gcc methodeDesPuissancesV2Forte.c lectureMatrice.c mmio.c -o methodeDesPuissances -fopenmp -lm

faible1: methodeDesPuissancesV1Faible.c lectureMatrice.c mmio.c
	gcc methodeDesPuissancesV1Faible.c lectureMatrice.c mmio.c -o methodeDesPuissances -fopenmp -lm

faible2: methodeDesPuissancesV2Faible.c lectureMatrice.c mmio.c
	gcc methodeDesPuissancesV2Faible.c lectureMatrice.c mmio.c -o methodeDesPuissances -fopenmp -lm