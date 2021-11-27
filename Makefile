main.o: methodeDesPuissances.h methodeDesPuissances.c lectureMatrice.c mmio.c
	gcc methodeDesPuissances.h methodeDesPuissances.c lectureMatrice.c mmio.c -o methodeDesPuissances -Wall -lm -g
