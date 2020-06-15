#ifndef _DATAH
#define _DATAH

#include<stdio.h>
#include<stdlib.h>
#include<libsx.h>

#define WIDTH 700
#define HEIGHT 700
#define FOIS 100

typedef struct{
  int x;
  int y;
  double angle;
  int leve_ou_baisse;
  int cache_ou_montre;
  char color;
  int i;
  int history[2][FOIS];
  int LineWidth[FOIS];
  char Color[FOIS];
}location; /*intialise un struct dont le type est <location>*/


extern void initialiser(location*); /*déclare la fonction*/

#endif
