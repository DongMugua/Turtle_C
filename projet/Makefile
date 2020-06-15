CC = gcc             # le compilateur à utiliser
CFLAGS = -Wall -pedantic  # les options du compilateur
LDFLAGS = -lsx -lm      # les options pour l'éditeur de liens
SRC = window.c callback.c robot.c # les fichiers sources
PROG = DrawRobot          # nom de l'exécutable
OBJS =  $(SRC:.c=.o) # les .o qui en découlent
.SUFFIXES: .c .o     # lien entre les suffixes

all: $(PROG)

# étapes de compilation et d'édition de liens
# $@ la cible  $^ toutes les dépendances	
$(PROG): $(OBJS)
	$(CC)  -o $@ $^ $(LDFLAGS)

callback.o: callback.h robot.h
robot.o: robot.h 
window.o: callback.h robot.h
# le lien entre .o et .c
# $< dernière dépendance	
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# pour faire propre
.PHONY: clean
clean:
	rm -f *.o *~ core $(PROG)

