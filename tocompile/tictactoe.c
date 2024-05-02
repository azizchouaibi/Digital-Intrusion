#include "tictactoe.h"


void initTictactoe(tic_tac_toe*t)
{
	t->img[0]=IMG_Load("image/x.png");
	t->img[1]=IMG_Load("image/o.png");
	t->j=0;
	t->select=-1;
	int x=39 ,y=90 ,w=138,h=134 ;
	for(int i=0;i<3;i++)
	{ 
		x=39;
		for(int j=0;j<3;j++)
		{
		/****INITIALISATION DU TABLEAU POS****/
			t->pos[i][j].x=x;
			t->pos[i][j].y=y;
                        t->pos[i][j].w=w;
                        t->pos[i][j].h=h;
		/****INITIALISATION DU TABLEAU TAB****/
			t->tab[i][j]=0 ; 
			x+=w;
                }
		y+=h;
	}
	t->nbr=0;
}
void afficherTictactoe(SDL_Surface *screen, tic_tac_toe t)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(t.tab[i][j]!=0)
			{
	SDL_BlitSurface(t.img[t.tab[i][j]-1],NULL,screen,&t.pos[i][j]);
			}
		}
	}
	
}
int atilganger(int tab[3][3])
{
	for(int i=0 ; i< 2 ; i++)
	{
		if(tab[0][0]==i+1 && tab[1][0]==i+1 && tab[2][0]==i+1
		|| tab[0][1]==i+1 && tab[1][1]==i+1 && tab[2][1]==i+1
		|| tab[0][2]==i+1 && tab[1][2]==i+1 && tab[2][2]==i+1
		|| tab[0][0]==i+1 && tab[0][1]==i+1 && tab[0][2]==i+1
		|| tab[1][0]==i+1 && tab[1][1]==i+1 && tab[1][2]==i+1
		|| tab[2][0]==i+1 && tab[2][1]==i+1 && tab[2][2]==i+1
		|| tab[0][0]==i+1 && tab[1][1]==i+1 && tab[2][2]==i+1
		|| tab[2][0]==i+1 && tab[1][1]==i+1 && tab[0][2]==i+1)
		{
			return (i+1);
			printf("%d\n" , i+1);
		}
	}
	return 0;
}
void afficherTictactoeclavier (SDL_Surface *screen , tic_tac_toe t)
{
	if(0<=t.select && t.select<=2)
	{
		SDL_BlitSurface(t.img[t.j] , NULL , screen , &t.pos[0][t.select]);
	}
	else if (3<=t.select && t.select<=5)
	{
		SDL_BlitSurface(t.img[t.j] , NULL , screen , &t.pos[1][t.select]-3);
	}
	else 
	{
		SDL_BlitSurface(t.img[t.j] , NULL , screen , &t.pos[2][t.select]-6);
	}
}
void initialiser_back(background *back)
{
	back->img[0]= IMG_Load("image/ttt animation/1.png");
	back->img[1]= IMG_Load("image/ttt animation/2.png");
	back->img[2]= IMG_Load("image/ttt animation/3.png");
	back->img[3]= IMG_Load("image/ttt animation/4.png");
	back->img[4]= IMG_Load("image/ttt animation/5.png");
	back->nbr=5;
	back->p=0;
	back->pos.x=0;
	back->pos.y=0;
	back->pos.w=back->img[0]->w;
	back->pos.h=back->img[0]->h;
}
void afficher_back(SDL_Surface *screen , background back)
{
	SDL_BlitSurface(back.img[back.p] , NULL , screen , &back.pos);
}
void annimer_back(background *back)
{
	back->p++;
	if(back->p==back->nbr)
	{
		back->p=0;
	}
}
void initialiser_texteGood(texte* good)
{
	good->police = TTF_OpenFont("Ubuntu-Bold.ttf" , 10);
	good->color.r=255;good->color.g=255;good->color.b=255;
	strcpy(good->ch ,"good");
	good->txt=TTF_RenderText_Blended(good->police , good->ch ,good->color);
	good->pos.x=0;
	good->pos.y=0;
}
void initialiser_textHardLuck(texte* HardLuck)
{
	HardLuck->police = TTF_OpenFont("Ubuntu-Bold.ttf" , 60);
	HardLuck->color.r=255;HardLuck->color.g=255;HardLuck->color.b=255;
	strcpy(HardLuck->ch ,"HardLuck");
	HardLuck->txt=TTF_RenderText_Blended(HardLuck->police , HardLuck->ch ,HardLuck->color);
	HardLuck->pos.x=0;
	HardLuck->pos.y=0;
	
}
void initialiser_rotozoom(rotozoom *z)
{
	initialiser_texteGood(&z->goodluck);
	initialiser_textHardLuck(&z->hardluck);
	for(int i=0 ; i<10 ; i++)
	{
		z->zoom[i]=rotozoomSurface(z->goodluck.txt, 0, i+1 , 1);
		z->rotation[i]=rotozoomSurface(z->hardluck.txt, 25*i, 1 , 1);
	}
	z->j=0;
	z->i=0;
}
void afficher_rotozoom(SDL_Surface *screen , rotozoom z)
{
	if(z.j==1)
	{
		SDL_BlitSurface(z.zoom[z.i%10] , NULL , screen , &z.goodluck.pos);
	}
	else if(z.j==2)
	{
		SDL_BlitSurface(z.rotation[z.i%10] , NULL , screen , &z.hardluck.pos);
	}
}
void joueur2(int tab[3][3])
{
	int test=0;
	int choix;
	do
	{
		 choix = rand() %9 ;
		if(0<=choix && choix<=2)
		{
			if(tab[0][choix]==0)
			{
				tab[0][choix]=2;
				test=1;
			}
			
		}
		else if (3<=choix && choix<=5)
		{
			if(tab[1][choix-3]==0)
			{
				tab[1][choix-3]=2;
				test=1;
			}
			
		}
		else 
		{
			if(tab[2][choix-6]==0)
			{
				tab[2][choix-6]=2;
				test=1;
			}
		}
	}
	while(test==0);
}
void rejouer(tic_tac_toe *t)
{
	t->nbr++;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			t->tab[i][j]=0;
		}
	}
	t->j=0;
}
