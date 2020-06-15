#include "callback.h"
#include "robot.h"

/*
  Antécédent: void
  Conséquent: une nouvelle zone à peindre après effacer
  Rôle: efface l’écran et revient à la positon (0,0) , construit le système d'axe, 
        revient la couleur tacitee et la largeur de ligne tacitee à la même
*/
static void Nettoie()
{

  ClearDrawArea(); /*efface l'écran*/
  
  SetLineWidth(1); /*revient la largeur de ligne tacitee*/
  SetColor(GetRGBColor(190,190,190)); 

  DrawLine(WIDTH/6,HEIGHT/2,5*WIDTH/6,HEIGHT/2);
  DrawLine(WIDTH/2,5*HEIGHT/6,WIDTH/2,HEIGHT/6);
  DrawLine(121*WIDTH/240,43*HEIGHT/240,WIDTH/2,HEIGHT/6);
  DrawLine(119*WIDTH/240,43*HEIGHT/240,WIDTH/2,HEIGHT/6);
  DrawLine(5*WIDTH/6,HEIGHT/2,197*WIDTH/240,121*HEIGHT/240);
  DrawLine(5*WIDTH/6,HEIGHT/2,197*WIDTH/240,119*HEIGHT/240);
  DrawText("y",57*WIDTH/120,HEIGHT/6);
  DrawText("x",5*WIDTH/6,63*HEIGHT/120); /*construit le système d'axe*/

  SetColor(GetRGBColor(0,0,0)); /*revient la couleur tacitee*/

}


/*
  Antécédent: une pointeur de structure et les coordonnées après et avant
  Conséquent: une ligne qu'on gagne
  Rôle: peint la ligne qui possède la couleur
*/
static void Drawline(location*l,int x1,int y1,int x2,int y2)
{

  GetStandardColors();
 
  switch(l->Color[l->i])
    {
    case 'r': SetColor(RED);   break;
    case 'w': SetColor(WHITE); break;
    case 'y': SetColor(YELLOW);break;
    case 'b': SetColor(BLUE);  break;
    case 'B': SetColor(BLACK); break;
    case 'g': SetColor(GREEN); break;
    }
  DrawLine(x1,y1,x2,y2); /*apple la fonction <DrawLine>*/

}


/*
  Antécédent: une pointeur d'structure 
  Conséquent: un robot qui possède la couleur,la largeur de ligne et la trace		
  Rôle: peint un robot sous tous les conditions
*/
static void robot(location *l)
{
  int j=l->i;						

  Nettoie();

  if(j!=1)
    {
      for(l->i=0;l->i<j-1;l->i++)
	{
	  if(l->Color[l->i]!='X')
	    {
	      SetLineWidth(l->LineWidth[l->i]);/*installe la largeur de ligne*/
	      Drawline(l,l->history[0][l->i],l->history[1][l->i],l->history[0][l->i+1],l->history[1][l->i+1]);/*peint la trace*/
	    }
	}
    }
  l->i=j;

  SetLineWidth(l->LineWidth[l->i-1]);
  if(l->cache_ou_montre==1)
    {
      GetStandardColors();
      switch(l->color)
	{
	case 'r': SetColor(RED);   break;
	case 'w': SetColor(WHITE); break;
	case 'y': SetColor(YELLOW);break;
	case 'b': SetColor(BLUE);  break;
	case 'B': SetColor(BLACK); break;
	case 'g': SetColor(GREEN); break;
	}

      DrawLine(l->x+cos(l->angle*pi/180)*WIDTH/50, l->y-sin(l->angle*pi/180)*WIDTH/50,
	       l->x-cos(l->angle*pi/180)*WIDTH/100-sin(l->angle*pi/180)*WIDTH/100,
	       l->y+sin(l->angle*pi/180)*WIDTH/100-cos(l->angle*pi/180)*WIDTH/100);
      
      DrawLine(l->x+cos(l->angle*pi/180)*WIDTH/50, l->y-sin(l->angle*pi/180)*WIDTH/50,
	       l->x-cos(l->angle*pi/180)*WIDTH/100+sin(l->angle*pi/180)*WIDTH/100,
	       l->y+sin(l->angle*pi/180)*WIDTH/100+cos(l->angle*pi/180)*WIDTH/100);

      DrawLine(l->x-cos(l->angle*pi/180)*WIDTH/100-sin(l->angle*pi/180)*WIDTH/100,
	       l->y+sin(l->angle*pi/180)*WIDTH/100-cos(l->angle*pi/180)*WIDTH/100,
	       l->x-cos(l->angle*pi/180)*WIDTH/100+sin(l->angle*pi/180)*WIDTH/100,
	       l->y+sin(l->angle*pi/180)*WIDTH/100+cos(l->angle*pi/180)*WIDTH/100); /*peint la forme de ce robot*/
}
}


/*
  Antécédent: un Widget,la location et une pointeur void 
  Conséquent: une nouvelle zone		
  Rôle: peint une nouvelle zone
*/
void area(Widget w,int x,int y,void *d)
{
  location *l=d;
  robot(l);
}


/*
  Antécédent: un Widget et une pointeur void 
  Conséquent: void		
  Rôle: ferme la fenêtre actuelle
*/
void d_accord(Widget w,void *d)
{
  CloseWindow();
}


/*
  Antécédent: un entier x 
  Conséquent: un label		
  Rôle: vérifie les commandes fausses
*/
static void error_format(int x)
{
  Widget TEXT,OK;
  MakeWindow("error",SAME_DISPLAY,EXCLUSIVE_WINDOW);
  if(x==1)
    TEXT=MakeLabel("Importez la commande selon le correct format,s'il vous plaît");
  else if(x==2)
    TEXT=MakeLabel("Importez la correcte commande en majuscules,s'il vous plaît");
  else if(x==3)
     TEXT=MakeLabel("Importez un espace et un nombre après la commande,s'il vous plaît");
  else if(x==4)
    TEXT=MakeLabel("Vous ne pouvez pas importer un nombre après cette commande,s'il vous plaît");
   else if(x==5)
    TEXT=MakeLabel("Vous pouvez importer la commande selon ce format: ALLELRA x y");
   else if(x==6)
     TEXT=MakeLabel("Importez la couleur standard,s'il vous plaît");
   else if(x==7)
    TEXT=MakeLabel("Importez la commande à nouveaux,s'il vous plaît");
  OK=MakeButton("OK",d_accord,NULL);
  SetWidgetPos(OK,PLACE_UNDER,TEXT,NO_CARE,NULL);
  ShowDisplay();
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: ce robot avance n unités
*/
static void avance(char *b,location *l)
{
  char mid;
  if(*b>57 || *b<48)
    error_format(3); /*vérifie si la second partie de commande est un nombre*/
  else
    {
      if((strtod(b,NULL)*cos(l->angle*pi/180) + l->x > WIDTH || strtod(b,NULL)*cos(l->angle*pi/180) + l->x < 0)
	 || (-strtod(b,NULL)*sin(l->angle*pi/180) + l->y > HEIGHT ||-strtod(b,NULL)*sin(l->angle*pi/180) + l->y < 0))

	error_format(7); /*vérifie si la trace est hors de portée*/
      else
	
	{
	  if(l->leve_ou_baisse==1)
	    l->Color[l->i-1]=l->color;
	  else
	    {
	      mid=l->Color[l->i-1];
	      l->Color[l->i-1]='X';
	      l->Color[l->i]=mid;
	    }	      
	  
	  l->x = strtod(b,NULL)*cos(l->angle*pi/180) + l->x;
	  l->y =-strtod(b,NULL)*sin(l->angle*pi/180) + l->y;

	  l->history[0][l->i]=l->x;
	  l->history[1][l->i]=l->y;
	 
	  l->LineWidth[l->i]=l->LineWidth[l->i-1];
	  
	  (l->i)++; /*change la location,la largeur de ligne et la couleur*/

	  robot(l);
       }
    }
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: ce robot recule n unités
*/
static void recule(char *b,location *l)
{
  char mid;
  if(*b>57 || *b<48)
    error_format(3); /*vérifie si la second partie de commande est un nombre*/
  else
    {
      if((-strtod(b,NULL)*cos(l->angle*pi/180) + l->x > WIDTH || -strtod(b,NULL)*cos(l->angle*pi/180) + l->x < 0)
	 || (strtod(b,NULL)*sin(l->angle*pi/180) + l->y > HEIGHT ||strtod(b,NULL)*sin(l->angle*pi/180) + l->y < 0))

	error_format(7); /*vérifie si la trace est hors de portée*/
      else
	{
	  if(l->leve_ou_baisse==1)
	    l->Color[l->i-1]=l->color;
	  else
	    {
	      mid=l->Color[l->i-1];
	      l->Color[l->i-1]='X';
	      l->Color[l->i]=mid;
	    }	  
	  l->x =-strtod(b,NULL)*cos(l->angle*pi/180) + l->x;
	  l->y =strtod(b,NULL)*sin(l->angle*pi/180) + l->y;

	  l->history[0][l->i]=l->x;
	  l->history[1][l->i]=l->y;
	  l->LineWidth[l->i]=l->LineWidth[l->i-1];
	  
	  (l->i)++; /*change la location,la largeur de ligne et la couleur*/
	  
	  robot(l);
	}
    }
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: ce robot tourne sur la gauche de n degrés
*/
static void gauche(char *b,location *l)
{
  if(*b>57 || *b<48)
    error_format(3); /*vérifie si la second partie de commande est un nombre*/
  else
    l->angle=l->angle + strtod(b,NULL); /*change l'angle*/
  robot(l);
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: ce robot tourne sur la droite de n degrés
*/
static void droite(char *b,location *l)
{
  if(*b>57 || *b<48)
    error_format(3); /*vérifie si la second partie de commande est un nombre*/
  else
    l->angle=l->angle - strtod(b,NULL);  /*change l'angle*/
  robot(l);
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: il n'y pas de trace dans l'écran
*/
static void leve_crayon(char *b,location *l)
{
  if(*b!='\0')
    error_format(4); /*vérifie la commande*/
  else
    l->leve_ou_baisse=0;
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: il y a les traces dans l'écran
*/
static void baisse_crayon(char *b,location *l)
{
  if(*b!='\0')
    error_format(4); /*vérifie la commande*/
  else
    l->leve_ou_baisse=1;
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: colore les lignes et le robot
*/
static void couleur(char *b,location *l)
{
 GetStandardColors();
  
  if(strcmp(b,"RED")==0)
    l->color='r';
  else if(strcmp(b,"GREEN")==0)
    l->color='g';
  else if(strcmp(b,"BLUE")==0)
    l->color='b';
  else if(strcmp(b,"YELLOW")==0)
    l->color='y';
  else if(strcmp(b,"BLACK")==0)
    l->color='B';
  else if(strcmp(b,"WHITE")==0)
    l->color='w';
  else
    error_format(6);
  robot(l);
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: efface l’écran et revient à la positon (0,0) , construit le système d'axe, revient la couleur tacitee, 
        la largeur de ligne tacitee,initialise le struct et peint un robot à la même
*/
static void nettoie(char *b,location *l)
{
  if(*b!='\0')
    error_format(4); /*vérifie la commande*/
  else
    {
      Nettoie();
      initialiser(l);
      robot(l);
    }
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: cache le robot
*/
static void cache(char *b,location *l)
{
  if(*b!='\0')
    error_format(4); /*vérifie la commande*/
  else
    {
    l->cache_ou_montre=0;
    robot(l);
    }
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: montre le robot
*/
static void montre(char *b,location *l)
{
  if(*b!='\0')
    error_format(4); /*vérifie la commande*/
  else
    {
    l->cache_ou_montre=1;
    robot(l);
    }
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: une nouvelle location		
  Rôle: place le robot à une nouvelle location
*/
static void allera(char *b,location *l)
{
  char *a=b;
  char mid;
  if((*b>57 || *b<48) && *b!='-')
    error_format(5);
  else
    {
      while(*b!=' ' && *b !='\0')
	b++;      
      if(*b==' ')
	{
	  if( strtod(a,NULL)+WIDTH/2 > WIDTH ||strtod(a,NULL)+WIDTH/2 < 0
	     ||-strtod(b,NULL)+HEIGHT/2 > HEIGHT || -strtod(b,NULL)+HEIGHT/2 < 0 )

	    error_format(7);
	  else
	    {
	      
	      if(l->leve_ou_baisse==1)
		l->Color[l->i-1]=l->color;
	      else
		{
		  mid=l->Color[l->i-1];
		  l->Color[l->i-1]='X';
		  l->Color[l->i]=mid;
		}
	      
	      l->x=strtod(a,NULL)+WIDTH/2;
	      l->y=-strtod(b,NULL)+HEIGHT/2;
	      
	      l->history[0][l->i]=l->x;
	      l->history[1][l->i]=l->y;
	      l->LineWidth[l->i]=l->LineWidth[l->i-1];
	      
	      (l->i)++;
	      
 	      robot(l);
	    }
	}
      else if(*b=='\0')
	error_format(5);      
    }
}


/*
  Antécédent: une pointeur de commande et une pointeur de structure 
  Conséquent: void		
  Rôle: change la largeur de ligne
*/
static void ligne_large(char *b,location *l)
{
  if(*b>57 || *b<48)
    error_format(3);
  else
    {
      l->LineWidth[l->i-1] = strtod(b,NULL);
      robot(l);
    }
}


/*
  Antécédent: une pointeur de commande important dans le cadre et une pointeur de structure 
  Conséquent: void		
  Rôle: réalise la commande par appeler la fonction
*/
static void valide_draw(location *l, char *cd)
{
  char *a=cd,*b=NULL;

  if(*a <65 || *a>90){
    error_format(1);} /*vérifie si la forme de commande est correcte*/
  else
    {
      while(*cd!=' ' && *cd !='\0' )
	cd++;

      if(*cd=='\0')
	b=cd;
      else if(*cd!='\0')
	{*cd='\0';
	  b=++cd;}
	
      if(strcmp(a,"AVANCE")==0)
        avance(b,l);
      else if(strcmp(a,"RECULE")==0)
	recule(b,l);
      else if(strcmp(a,"GAUCHE")==0)
	gauche(b,l);
      else if(strcmp(a,"DROITE")==0)
	droite(b,l);
      else if(strcmp(a,"LEVE_CRAYON")==0)
	leve_crayon(b,l);
      else if(strcmp(a,"BAISSE_CRAYON")==0)
	baisse_crayon(b,l);
      else if(strcmp(a,"COULEUR")==0)
	couleur(b,l);
      else if(strcmp(a,"NETTOIE")==0)
	nettoie(b,l);
      else if(strcmp(a,"ALLERA")==0)
	allera(b,l);
      else if(strcmp(a,"CACHE")==0)
	cache(b,l);
      else if(strcmp(a,"MONTRE")==0)
	montre(b,l);
      else if(strcmp(a,"LIGNE_LARGE")==0)
	ligne_large(b,l); /*choisi la fonction correspondante*/
      else
	error_format(2);
    }
}


/*
  Antécédent: une pointeur void et un Widget
  Conséquent: void		
  Rôle: écrive la commande dans le cadre sous la forme <programme>
*/
void ok(Widget w,void *d)
{
  char *cd=GetStringEntry(COMMAND),*q=NULL,*p=malloc(LONGUEUR);
  location *l=d;
  int i;
  valide_draw(l,cd);
  q=p;
  for(i=0;i<LONGUEUR;i++){
      *p='\0';
      p++;}
  SetStringEntry(COMMAND,q);
  free(q);
}


static Widget TEXT;


/*
  Antécédent: une pointeur void et un Widget
  Conséquent: réalise les commandes de document		
  Rôle: écrive la commande dans le cadre sous la forme <file>
*/
static void file_ok(Widget w,void *d)
{
  int i=0;
  location *l=d;
  FILE *fp;
  char *t=GetStringEntry(TEXT),T[LONGUEUR];

		       
  if( (fp=fopen(t,"r") )==NULL)
    {
      Widget warning,ok;
      MakeWindow("warning",SAME_DISPLAY,EXCLUSIVE_WINDOW);
      warning=MakeLabel("Importez le correct nom de votre document,s'il vous plaît");
      ok=MakeButton("OK",d_accord,NULL);
      SetWidgetPos(ok,PLACE_UNDER,warning,NO_CARE,NULL);
      
      char *q=NULL,*p=malloc(LONGUEUR);
      q=p;
      for(int i=0;i<LONGUEUR;i++){
	*p='\0';
	p++;}
      SetStringEntry(TEXT,q);
      free(q);
      ShowDisplay();
    }
  else
    {      
      while( (fgets(T,LONGUEUR,fp)) !=NULL )
	{
	  for(i=0;i<LONGUEUR;i++)
	    {
	      if(T[i]=='\n')
		{
		  T[i]='\0';
		  break;
		}
		}
	  valide_draw(l,T);
	  for(i=0;i<LONGUEUR;i++)
	  T[i]='0';
       	}
      CloseWindow();
    }
}


/*
  Antécédent: une pointeur void et un Widget
  Conséquent: une fenêtre ou un label		
  Rôle: réalise les fonctions par choisir un document que l'usager défini
*/
void file(Widget w,void *d)
{
  Widget CL,OK,ANNULER;
  MakeWindow("FILE",SAME_DISPLAY,EXCLUSIVE_WINDOW);
  CL=MakeLabel("Importez le nom de votre document,s'il vous plaît");
  TEXT=MakeStringEntry(NULL,LONGUEUR,NULL,NULL);
  OK=MakeButton("OK",file_ok,d);
  ANNULER=MakeButton("Annuler",d_accord,NULL);

  SetWidgetPos(TEXT,PLACE_UNDER,CL,NO_CARE,NULL);
  SetWidgetPos(OK,PLACE_UNDER,TEXT,NO_CARE,NULL);
  SetWidgetPos(ANNULER,PLACE_UNDER,TEXT,PLACE_RIGHT,OK);

  ShowDisplay();
}
