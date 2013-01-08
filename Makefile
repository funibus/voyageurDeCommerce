SRC=main.c interface_utilisateur.c interface_utilisateur_test.c prim.c structure_arbre_couvrant.c structure_matrice.c structure_ville.c tas_min.c test_prim.c TSP.c TSP_tests.c villes_traversees.c
DEP= ${SRC:.c=.dep}
OBJ= ${SRC:.c=.o}
CXX	 = gcc
LFLAGS   = 
CXXFLAGS = -Wall


all: depend exe Makefile

exe: $(OBJ) $(HDR) 
	${CXX} $(CXXFLAGS) -o $@ $(OBJ) $(LFLAGS)  $(LIB) -lm

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
