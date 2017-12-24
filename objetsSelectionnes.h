/**************************************************************************
  objetsProgramme.h -- Cette classe constitue tous les objets du programme. 
  Ce sont les objets qui sont temporises en memoire pendant lexecution normal du 
  programme.
  Écrit par : Pierre-Marc Laforest
  Date: 28/04/17                                     
*************************************************************************** */

#include <iostream>
#include <climits>
#include <stdio.h>
#include <string>
#include <vector>
#include "classesLigue.h"
#include "classesCalendrierMatchs.h"
#include "classeIOFichiers.h"
#include "detailsContrats.h"


#ifndef CLASSESObjetsProgramme_H
#define CLASSESObjetsProgramme_H

class ObjetsProgramme
{
private:
Joueur joueurSelectionne;
Club   clubSelectionne;
Ligue  ligueSelectionnee;
Calendrier calendrierSelectionne;
Entraineur entraineurSelectionne;
int    clubChoisi;
public:
ObjetsProgramme();
~ObjetsProgramme();
void       modifJoueurSelectionne(Joueur& nouveauJoueurSelectionne);
void       modifClubSelectionne(Club& nouveauClubSelectionne, int noClubChoisi);
void       modifEntraineurSelectionne(Entraineur& nouvelEntraineurSelectionne);
bool       initialiseLigue(void);
bool       initialiseCalendrier(void);
bool       deselectionneJoueur(void);
bool       deselectionneEntraineur(void);
bool       deselectionneClub(void); 
bool       testJoueurSelectionne(void);
bool       testClubSelectionne(void);
bool       testEntraineurClubSelectionne(void);
bool       testStadeClubSelectionne(void);
bool       testEntraineurSelectionne(void);
bool       ajouteClubDansLigue(string nouveauNomDuClub, string nouvelleHistoire, string nouvelleCouleur, string nouvelleVille, string nouvelleAdresse);
bool       ajouteJoueurDansClub(string nomJoueurAAJouter, string prenomJoueurAAJouter, float poidsJoueurAAJouter, string villeJoueurAAjouter);
bool       ajouteEntraineurDansClub(Entraineur& entraineurAAjouter);
bool       modifEntraineurDansClub(Entraineur& entraineurAModifier);
bool       ajoutTropheeClub(string nomTrophee, short unsigned int anneeTrophee, short unsigned int moisTrophee, short unsigned int jourTrophee);
bool       ajoutTropheeEntraineur(string nomTrophee, short unsigned int anneeTrophee, short unsigned int moisTrophee, short unsigned int jourTrophee);
bool       ajouteNouveauContratJoueur(unsigned int nbAnneesContrat, Date dateEntree, Date DateContrat, float valeurContrat);
bool       ajoutRencontreCalendrier(int noClubDomicile, int noClubEtranger, Date dateRencontre);
bool       enleveRencontreCalendrier(int noRencontreASupprimer);
bool       ajouteRuptureContrat(string raisonDepart);
bool       modifStadeDansClub(Stade& stadeAModifier);
bool       ajouteStadeDansClub(Stade& stadeAAjouter);
bool       supprimeJoueurDeClub(int noJoueurASupprimer);
bool   	   supprimeClubDeLigue(int noClubASupprimer);
bool       simulerMatchCalendrier(int noRencontreASimuler);
bool       modifClubLigue(Club& ancienClub, Club& nouveauClub);
bool   	   ajouteEntraineurDansClub(void);
bool       simulationAchat(float montantAchat, float montantMax,  float dureeMax,   float margeAcceptable);
bool	   simulationVente(float montantAchat, float montantMax,  float dureeMax,   float margeAcceptable);
Joueur     retourneJoueurSelectionne(void);
Club       retourneClubSelectionne(void);
Entraineur retourneEntraineurSelectionne(void);
Ligue      retourneLigueSelectionnee(void);
Calendrier retourneCalendrierSelectionne(void);
int 	   retourneNoClubChoisi(void);
};

#endif