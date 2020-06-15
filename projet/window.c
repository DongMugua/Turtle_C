#include"callback.h"
#include"robot.h"


/*
  Antécédent: argc,*argv[] et une pointeur void
  Conséquent: void		
  Rôle: réalise les fonctions sous la forme <programme> 
*/
void init_display(int argc,char *argv[],void *d)
{
  Widget FILE,QUIT,AREA,COMTEXT,OK,PROG;
  
  AREA=MakeDrawArea(WIDTH,HEIGHT,area,d);
  QUIT=MakeButton("quit",d_accord,NULL);
  FILE=MakeButton("FILE",file,d);
  COMTEXT=MakeLabel("command:");
  PROG=MakeLabel("programme");
  COMMAND=MakeStringEntry(NULL,LONGUEUR,NULL,NULL);
  OK=MakeButton("enter",ok,d);
  
  SetWidgetPos(PROG,PLACE_RIGHT,FILE,NO_CARE,NULL);
  SetWidgetPos(AREA,PLACE_UNDER,FILE,NO_CARE,NULL);
  SetWidgetPos(COMTEXT,PLACE_UNDER,AREA,NO_CARE,NULL);
  SetWidgetPos(COMMAND,PLACE_UNDER,AREA,PLACE_RIGHT,COMTEXT);
  SetWidgetPos(OK,PLACE_UNDER,AREA,PLACE_RIGHT,COMMAND);
  SetWidgetPos(QUIT,PLACE_RIGHT,OK,PLACE_UNDER,AREA);

  ShowDisplay();
}


/*
  Antécédent: argc,*argv[]
  Conséquent: void		
  Rôle: réalise ce programme
*/
int main(int argc,char *argv[])
{
  location d;
  if(OpenDisplay(argc,argv)==0){
    fprintf(stderr,"Can't open display\n");
    return 1;
  }

  initialiser(&d);
  
  init_display(argc,argv,&d);
  MainLoop();
}
  
