executable: main.o back.o fonctions.o
	gcc main.o back.o fonctions.o -g -o executable -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
	./executable

main.o: main.c
	gcc -c main.c

back.o: back.c
	gcc -c back.c
fonctions.o: fonctions.c
	gcc -c fonctions.c

clean:
	rm -f *.o executable
