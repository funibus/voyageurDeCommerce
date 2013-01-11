SRC=main.c interface_utilisateur.c test_interface_utilisateur.c prim_TSP.c structure_arbre_couvrant.c structure_matrice.c structure_ville.c tas_min.c test_prim.c lecture_fichier.c tests_lecture_fichier.c villes_traversees.c test_tas_min.c
DEP= ${SRC:.c=.dep}
OBJ= ${SRC:.c=.o}

SRCG=main.c interface_utilisateur.c test_interface_utilisateur.c prim_TSP.c structure_arbre_couvrant.c structure_matrice.c structure_ville.c tas_min.c test_prim.c lecture_fichier.c tests_lecture_fichier.c villes_traversees.c gui.c test_tas_min.c
DEPG= ${SRCG:.c=.dep}
OBJG= ${SRCG:.c=.o}
CXX	 = gcc
LFLAGS   = 
CXXFLAGS = -Wall


all: depend exe Makefile exe_gui

exe: $(OBJ) $(HDR) 
	${CXX} $(CXXFLAGS) -o $@ $(OBJ) $(LFLAGS)  $(LIB) -lm -U GUI_ENABLE

	
exe_gui: $(OBJG) $(HDR) 
	${CXX} $(CXXFLAGS) -o $@ $(OBJG) $(LFLAGS) -D GUI_ENABLE  $(LIB) -lm -lSDL -lSDL_gfx 

clean: 
	rm -f $(OBJ) $(DEP)

destroy: clean
	rm -f exe 

depend: ${DEP}

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

%.dep: %.c
	$(CXX) $(CXXFLAGS) -MM -MF $@ $<

-include ${DEP}
