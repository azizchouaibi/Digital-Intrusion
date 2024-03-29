executable: main.o fonctions.o
	gcc main.o fonctions.o -o executable -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
	./executable

main.o: tocompile/main.c
	gcc -c tocompile/main.c

fonctions.o: tocompile/fonctions.c
	gcc -c tocompile/fonctions.c

clean:
	rm -f *.o executable

