executable: main.o fonctions.o back.o perso.o tictactoe.o enigme.o
	gcc main.o fonctions.o back.o perso.o tictactoe.o enigme.o  -o executable -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx -lm
	./executable
fonctions.o: tocompile/fonctions.c
	gcc -c tocompile/fonctions.c
perso.o: tocompile/perso.c tocompile/perso.h
	gcc -c tocompile/perso.c
back.o: tocompile/back.c tocompile/back.h
	gcc -c tocompile/back.c
tictactoe.o: tocompile/tictactoe.c tocompile/tictactoe.h
	gcc -c tocompile/tictactoe.c -o tictactoe.o
enigme.o: tocompile/enigme.c tocompile/enigme.h
	gcc -c tocompile/enigme.c 
main.o: tocompile/main.c 
	gcc -c tocompile/main.c

clean:
	rm -f *.o executable

