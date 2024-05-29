executable: main.o fonctions.o back.o perso.o tictactoe.o enigme.o minimap.o second_person.o entity.o login.o
	gcc main.o fonctions.o back.o perso.o tictactoe.o enigme.o minimap.o second_person.o entity.o login.o -o executable -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx -lm
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
minimap.o: tocompile/minimap.c tocompile/minimap.h
	gcc -c tocompile/minimap.c
second_person.o: tocompile/second_person.c
	gcc -c tocompile/second_person.c
entity.o : tocompile/entity.c
	gcc -c tocompile/entity.c
login.o: tocompile/login.c
	gcc -c tocompile/login.c
main.o: tocompile/main.c 
	gcc -c tocompile/main.c

clean:
	rm -f *.o executable
mkbackup:
	mkdir /home/aziz/Desktop/Backup
	echo "Backup Created"
backup:
	cp -r /home/aziz/Desktop/Digital_Intrusion /home/aziz/Desktop/Backup


	

