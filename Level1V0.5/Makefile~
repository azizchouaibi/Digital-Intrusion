executable: main.o fonctions.o back.o perso.o
	gcc main.o fonctions.o back.o perso.o -o executable -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
	./executable
fonctions.o: tocompile/fonctions.c
	gcc -c tocompile/fonctions.c
perso.o: tocompile/perso.c perso.h
	gcc -c tocompile/perso.c
back.o: tocompile/back.c back.h
	gcc -c tocompile/back.c
main.o: tocompile/main.c 
	gcc -c tocompile/main.c

clean:
	rm -f *.o executable

