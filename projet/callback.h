#ifndef _CALLBACKH
#define _CALLBACKH

#include <math.h>
#include "robot.h"

#define LONGUEUR 200
#define pi (4*atan(1))

Widget COMMAND;

extern void area(Widget,int,int,void*);
extern void ok(Widget,void *);
extern void file(Widget,void*);
extern void d_accord(Widget,void*); /*déclare les fonctions*/

#endif
  
