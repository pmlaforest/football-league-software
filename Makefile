GCC=g++
CFLAGS=-g -std=c++11 -Wall
DOSSIER_BIN = ./bin
DOSSIER_BUILD = ./build

all: main

main: main.o classesLigue.o classesEcran.o classeIOFichiers.o classesCalendrierMatchs.o   objetsSelectionnes.o detailsContrats.o
	$(GCC) $(CFLAGS) $(DOSSIER_BUILD)/main.o $(DOSSIER_BUILD)/classesLigue.o $(DOSSIER_BUILD)/classesCalendrierMatchs.o $(DOSSIER_BUILD)/classesEcran.o $(DOSSIER_BUILD)/classeIOFichiers.o $(DOSSIER_BUILD)/objetsSelectionnes.o $(DOSSIER_BUILD)/detailsContrats.o -o $(DOSSIER_BIN)/main

main.o: main.cpp classesLigue.h
	$(GCC) $(CFLAGS) -c main.cpp -o $(DOSSIER_BUILD)/main.o

classesCalendrierMatchs.o: classesCalendrierMatchs.cpp classesCalendrierMatchs.h classesLigue.h
	$(GCC) $(CFLAGS) -c classesCalendrierMatchs.cpp -o $(DOSSIER_BUILD)/classesCalendrierMatchs.o
	
classesLigue.o: classesLigue.cpp classesLigue.h
	$(GCC) $(CFLAGS) -c classesLigue.cpp -o $(DOSSIER_BUILD)/classesLigue.o

classesEcran.o: classesEcran.cpp classesLigue.h
	$(GCC) $(CFLAGS) -c classesEcran.cpp -o $(DOSSIER_BUILD)/classesEcran.o

classeIOFichiers.o : classeIOFichiers.cpp  classeIOFichiers.h classesLigue.h
	$(GCC) $(CFLAGS) -c classeIOFichiers.cpp -o $(DOSSIER_BUILD)/classeIOFichiers.o
	
objetsSelectionnes.o : objetsSelectionnes.cpp objetsSelectionnes.h classesCalendrierMatchs.h classesLigue.h classeIOFichiers.h
	$(GCC) $(CFLAGS) -c objetsSelectionnes.cpp -o $(DOSSIER_BUILD)/objetsSelectionnes.o
	
detailsContrats.o : detailsContrats.cpp detailsContrats.h	classeIOFichiers.h  classesCalendrierMatchs.h
	$(GCC) $(CFLAGS) -c detailsContrats.cpp -o $(DOSSIER_BUILD)/detailsContrats.o
	
clean: 
	rm $(DOSSIER_BUILD)/*.o $(DOSSIER_BUILD)/*.*~ $(DOSSIER_BUILD)/*~
