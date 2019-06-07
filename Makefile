#Makefile Générique
#Projet 3 / PI2
#Etienne PENAULT / Lies AMAROUCHE

OBJS	= main.o memoire.o contraste.o pixel.o image.o alignement.o forms.o affichage.o
OUT	= Exe
CC	 = gcc
FLAGS	 = -O3 -c -Wall

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) -lm -lglut -lGL -lGLU
main.o: main.c ppm.h
	$(CC) $(FLAGS) main.c 
image.o: image.c ppm.h
	$(CC) $(FLAGS) image.c
memoire.o: memoire.c ppm.h
	$(CC) $(FLAGS) memoire.c
contraste.o: contraste.c ppm.h
	$(CC) $(FLAGS) contraste.c
pixel.o: pixel.c ppm.h
	$(CC) $(FLAGS) pixel.c
alignement.o: alignement.c ppm.h
	$(CC) $(FLAGS) alignement.c
forms.o: forms.c ppm.h
	$(CC) $(FLAGS) forms.c
affichage.o: affichage.c ppm.h
	$(CC) $(FLAGS) affichage.c
clean:
	rm -f $(OBJS) $(OUT)
