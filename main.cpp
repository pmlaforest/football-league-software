/**************************************************************************
  main.cpp -- main for the soccer club software
  Écrit par : Pierre-Marc Laforest
  Date: 30/01/17                                        
*************************************************************************** */

#include <iostream>
#include <string>
#include "classesLigue.h"
#include "classesEcran.h"
#include "classesCalendrierMatchs.h"
#include "classeIOFichiers.h"
#include "ObjetsSelectionnes.h"

extern ObjetsProgramme objetsEnMemoire;

int main(void) 
{ 
  MenuPrincipal menuPrincipal;
  objetsEnMemoire.initialiseLigue();
  objetsEnMemoire.initialiseCalendrier(); 
   
  do
  {
	menuPrincipal.affichage();
	menuPrincipal.appelleFonctionChoisie();
	
  } while(menuPrincipal.retourneOptionChoisie() != 8 &&
		  menuPrincipal.retourneLigueOptionChoisie() != 5 &&
		  menuPrincipal.retourneClubOptionChoisie() != 14 && 
		  menuPrincipal.retourneJoueurOptionChoisie() != 5 &&
		  menuPrincipal.retourneCalendrierOptionChoisie() != 7 &&
		  menuPrincipal.retourneEntraineurOptionChoisie() != 9 &&
		  menuPrincipal.retourneTropheeOptionChoisie() != 4);

  return 0;
}
