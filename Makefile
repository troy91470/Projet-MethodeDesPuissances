main.o: methodeDesPuissances.c lectureMatrice.c mmio.c
	gcc methodeDesPuissances.c lectureMatrice.c mmio.c -o methodeDesPuissances -Wall -fopenmp -lm -g
