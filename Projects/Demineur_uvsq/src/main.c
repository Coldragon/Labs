#include "hdr/graphics.h"

int t[20][20]; // MINES
int m[20][20]; // POINTS
int v[20][20]; // DECOUVERT
int h[20][20]; // MARQUEUR

 //       FONCTION       //

void remplir_tableaux() // Iinitialise tableaux et remplis mines
{
	int aleax, aleay;
	int i, j;
	for(i=0; i<20; i++) // Initialise tableaux mines
	{
		for(j=0; j<20; j++)
			{
		t[i][j]=0;
			}
	}
	for(i=0; i<30; i++) // 30 = nombres de mines
	{
		aleax=alea_int(20);
		aleay=alea_int(20);
		while(t[aleax][aleay]==1)
		{
			aleax=alea_int(20);
			aleay=alea_int(20);
		}
		t[aleax][aleay]=1;
	}

	for(i=0; i<20; i++) // Initialise tableaux découverte
	{
		for(j=0; j<20; j++)
			{
		v[i][j]=0;
			}
	}

	for(i=0; i<20; i++) // Initialise tableaux marqueur
	{
		for(j=0; j<20; j++)
			{
		h[i][j]=0;
			}
	}
}

void quadrillage() // Graphismes
{
	fill_screen(gris);
	int i;
	POINT p1, p2;
	COULEUR c;

	for(i=0; i<25; i++) // Dégradé moitié haut
	{
		c=couleur_RGB(0, 0, 127+i*3);
		p1.x=0;
		p1.y=650-i;
		p2.x=600;
		p2.y=650-i;
		draw_fill_rectangle(p1, p2, c);
	}

	for(i=0; i<25; i++) // Dégradé moitié bas
	{
		c=couleur_RGB(0, 0, 202-i*3);
		p1.x=0;
		p1.y=625-i;
		p2.x=600;
		p2.y=625-i;
		draw_fill_rectangle(p1, p2, c);
	}

	for(i=0; i<21; i++) //Lignes Horizontale
	{
		p1.x=0; p1.y=i*30;
		p2.x=600; p2.y=i*30;
		draw_line(p1, p2, blanc);
	}

	for(i=0; i<20; i++) // Lignes Vertical
	{
		p1.x=i*30; p1.y=0;
		p2.x=i*30; p2.y=600;
		draw_line(p1, p2, blanc);
	}

	p1.x=599; p1.y=600;
	p2.x=599; p2.y=0;
	draw_line(p1, p2, blanc);

	//Carré mode recherche
	p1.x=8; p1.y=608;
	p2.x=42; p2.y=642;
	draw_fill_rectangle(p1, p2, noir);
	p1.x=10; p1.y=610;
	p2.x=40; p2.y=640;
	draw_fill_rectangle(p1, p2, blanc);
	p1.x = 50; p1.y= 639;
	aff_pol("Mode recherche", 20, p1, blanc);

	//Rectangle score
	p1.x=488; p1.y=608;
	p2.x=552; p2.y=642;
	draw_fill_rectangle(p1, p2, noir);
	p1.x=490; p1.y=610;
	p2.x=550; p2.y=640;
	draw_fill_rectangle(p1, p2, blanc);
	p1.x=500; p1.y=640;
	aff_int(0, 20, p1, rouge);
}

POINT trouver_dans_tableau(POINT clic)
{
	POINT coord;
	coord.x=clic.x/30;
	coord.y=clic.y/30;
	return coord;
}

void dessiner_mine() // DEBUG et dessine les mines en fin de partie
{
	POINT p1, p2;
	int i, j;
	for(i=0; i<20; i++)
	{
		for(j=0; j<20; j++)
			{
				if(t[i][j]==1)
				{
					p1.x=i*30; p1.y=j*30;
					p2.x=i*30+30; p2.y=j*30+30;
					draw_fill_rectangle(p1, p2, blanc);
					p1.x=i*30+15; p1.y=j*30+15;
					draw_fill_circle(p1, 10, rouge);
				}
			}
	}
}

void point_par_case() // Iinitialise tableau point par case (Chiant a faire !)
{
	int i, j;

	for(i=0; i<20; i++)
	{
		for(j=0; j<20; j++)
		{
			m[i][j]=0;
		}
	}

	for(i=0; i<20; i++)
	{
		for(j=0; j<20; j++)
		{
			if(t[i][j]==1)
			{	if(t[i+1][j+1]==0 && i+1<20 && j+1<20)
				m[i+1][j+1]=m[i+1][j+1]+1;

				if(t[i][j+1]==0 && j+1<20)
				m[i][j+1]=m[i][j+1]+1;

				if(t[i+1][j]==0 && i+1<20)
				m[i+1][j]=m[i+1][j]+1;

				if(t[i-1][j-1]==0 && i-1>=0 && j-1>=0)
				m[i-1][j-1]=m[i-1][j-1]+1;

				if(t[i-1][j+1]==0 && i-1>=0 && j+1<20)
				m[i-1][j+1]=m[i-1][j+1]+1;

				if(t[i-1][j]==0 && i-1>=0)
				m[i-1][j]=m[i-1][j]+1;

				if(t[i][j-1]==0 && j-1>=0)
				m[i][j-1]=m[i][j-1]+1;

				if(t[i+1][j-1]==0 && i+1<20 && j-1>=0)
				m[i+1][j-1]=m[i+1][j-1]+1;
			}
		}
	}
}

void afficher_nombre() //DEBUG et Affichage en fin de partie
{
	int i, j;
	POINT p, pp;
	for(i=0; i<20; i++)
	{
		for(j=0; j<20; j++)
		{

			if (m[i][j]!=0)
			{
				p.x=i*30; p.y=j*30;
				pp.x=i*30+30; pp.y=j*30+30;
				draw_fill_rectangle(p, pp, blanc);
				p.x=i*30+10; p.y=j*30+30;
				aff_int(m[i][j],25, p, bleu);
			}
		}
	}
}

//    FONCTION MAIN     //

#ifdef main
#undef main
#endif

int main(int argc, char** argv)
{
init_graphics(600, 650);
affiche_auto_off;
POINT coord, clic; //coord pour transferer coordonnee de la fonction (pour retourner deux valeurs)
POINT p1, p2; // Pour dessiner
int loose, x, y, total, mode, cont; // total = score
cont=0;
while(cont==0) // Boucloue pour relancer partie
{
total=0;
loose=0;
mode=0;

remplir_tableaux();
quadrillage();
point_par_case();
// dessiner_mine();  //DEBUG
// afficher_nombre();  //DEBUG

while(loose==0) // La boucle contenant le jeux
{
	clic=wait_clic();

	coord=trouver_dans_tableau(clic);  // Savoir on on clic
	x=coord.x;
	y=coord.y;

	if (clic.x>10 && clic.x<40 && clic.y>610 && clic.y<640) // Changement de mode
	{
		if (mode%2==0)
		{
			p1.x=15; p1.y=615;
			p2.x=35; p2.y=635;
			draw_fill_rectangle(p1, p2, vert);
		}
		if (mode%2==1)
		{
			p1.x=10; p1.y=610;
			p2.x=40; p2.y=640;
			draw_fill_rectangle(p1, p2, blanc);
		}
		mode++;
	}

	if(clic.y<600 && v[x][y]==0) // Si clic dans plateau de jeux et case pas découverte
	{
		if (mode%2==0) // Mode découverte
		{
			if(m[x][y]!=0) // Nombres
			{
				total=total+(m[x][y]);
				p1.x=x*30; p2.y=y*30;
				p2.x=x*30+30; p1.y=y*30+30;
				draw_fill_rectangle(p1, p2, blanc);
				p1.x=x*30+10; p1.y=y*30+30;
				aff_int(m[x][y],25, p1, bleu);
				p1.x=490; p1.y=610;
				p2.x=550; p2.y=640;
				draw_fill_rectangle(p1, p2, blanc);
				p1.x=500; p1.y=640;
				aff_int(total, 20, p1, rouge);
				v[x][y]=1;
			}

			if(t[x][y]==1) // Mine
			{
				dessiner_mine();
				afficher_nombre();
				p1.x=500; p1.y=640;
				aff_int(total, 20, p1, rouge);
				loose=1;
			}

			if(t[x][y]==0 && m[x][y]==0) // Case vide
			{
				p1.x=x*30; p1.y=y*30;
				p2.x=x*30+30; p2.y=y*30+30;
				draw_fill_rectangle(p1, p2, blanc);
				v[x][y]=1;

				if(v[x][y+1]==0 && x+1<20 && y+1<20 && t[x][y+1]==0 && m[x][y+1]==0)
				{
				p1.x=x*30; p1.y=(y+1)*30;
				p2.x=x*30+30; p2.y=(y+1)*30+30;
				draw_fill_rectangle(p1, p2, blanc);
				v[x][y+1]=1;
				}

				if(v[x][y-1]==0 && y-1>=0 && t[x][y-1]==0 && m[x][y-1]==0)
				{
				p1.x=x*30; p1.y=(y-1)*30;
				p2.x=x*30+30; p2.y=(y-1)*30+30;
				draw_fill_rectangle(p1, p2, blanc);
				v[x][y-1]=1;
				}

				if(v[x+1][y]==0 && x+1<20 && t[x+1][y]==0 && m[x+1][y]==0)
				{
				p1.x=(x+1)*30; p1.y=(y)*30;
				p2.x=(x+1)*30+30; p2.y=(y)*30+30;
				draw_fill_rectangle(p1, p2, blanc);
				v[x+1][y]=1;
				}

				if(v[x-1][y]==0 && x-1>=0 && t[x-1][y]==0 && m[x-1][y]==0)
				{
				p1.x=(x-1)*30; p1.y=(y)*30;
				p2.x=(x-1)*30+30; p2.y=(y)*30+30;
				draw_fill_rectangle(p1, p2, blanc);
				v[x-1][y]=1;
				}
			}
		}

		if (mode%2==1) // Mode recherche
		{
				p1.x=x*30+5; p1.y=y*30+5;
				p2.x=x*30+25; p2.y=y*30+25;
				if(h[x][y]%2==0)
				draw_fill_rectangle(p1, p2, vert);
				if(h[x][y]%2==1)
				draw_fill_rectangle(p1, p2, gris);
				h[x][y]++;
		}
	}
}

// RELANCER LA PARTIE ?

COULEUR c;
int i;
// Redésine dégradé pour enlevée mode recherche
for(i=0; i<25; i++) // Dégradé moitié haut
{
		c=couleur_RGB(0, 0, 127+i*3);
		p1.x=0;
		p1.y=650-i;
		p2.x=400;
		p2.y=650-i;
		draw_fill_rectangle(p1, p2, c);
}

for(i=0; i<25; i++) // Dégradé moitié bas
{
		c=couleur_RGB(0, 0, 202-i*3);
		p1.x=0;
		p1.y=625-i;
		p2.x=400;
		p2.y=625-i;
		draw_fill_rectangle(p1, p2, c);
}
p1.x = 20; p1.y= 639;
aff_pol("Perdu(e) ! Veux tu rejouer ?", 20, p1, blanc);

p1.x = 317; p1.y= 639;
aff_pol("Oui", 20, p1, blanc);
p1.x=362; p1.y=613;
p2.x=386; p2.y=637;
draw_fill_rectangle(p1, p2, noir);
p1.x=364; p1.y=615;
p2.x=384; p2.y=635;
draw_fill_rectangle(p1, p2, blanc);

p1.x = 397; p1.y= 639;
aff_pol("Non", 20, p1, blanc);
p1.x=442; p1.y=613;
p2.x=466; p2.y=637;
draw_fill_rectangle(p1, p2, noir);
p1.x=444; p1.y=615;
p2.x=464; p2.y=635;
draw_fill_rectangle(p1, p2, blanc);

clic=wait_clic();
while(clic.x<362 || clic.x>466 || (clic.x>386 && clic.x<442) || clic.y>637 || clic.y<613 )
{
clic=wait_clic();
}
if (clic.x>362 && clic.x<386)
cont=0;
if (clic.x>397 && clic.x<466)
cont=1;
} // Fin boucle relance partie

exit(0);
}

 //       FIN CODE       //
