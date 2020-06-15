#include"robot.h"


/*
 *Antécédent: une pointeur de struct
 *Conséquent: void		
 *Rôle: initialise tous les variables de struct
 */
void initialiser(location *d)
{
  int j;
  d->x=(WIDTH)/2;
  d->y=(HEIGHT)/2;
  d->angle=0.0;
  d->color='B';
  d->leve_ou_baisse=0;
  d->history[0][0]=(WIDTH)/2;
  d->history[1][0]=(HEIGHT)/2;
  
  for(j=0;j<FOIS;j++)
    d->LineWidth[j]=1;
  
  d->Color[0]='B';
  d->i=1;
  d->cache_ou_montre=1;
}
