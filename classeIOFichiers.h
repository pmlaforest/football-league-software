/**************************************************************************
  classesIOFichiers.h -- classes ecriture/lecture dans des fichiers
  pour le logiciel de gestion de ligue de soccer
  Écrit par : Pierre-Marc Laforest
  Date: 20/02/17                                        
*************************************************************************** */

#ifndef IO_FICHIERS_H
#define IO_FICHIERS_H

#include <iostream>
#include <fstream>
#include <string>
#include "classesCalendrierMatchs.h"
#include "classesLigue.h"
#include "detailsContrats.h"

#define MAX_CHARS 1000

using namespace std;

class GestionFichier 
{
private:
	string nomDuFichier;
	string copieDuFichier;
	fstream fichierDonnees;
public:
    GestionFichier(string nomDuFichier);																
	~GestionFichier();																	
	bool ouvrirFichierLecture(void);													
	bool ouvrirFichierEcriture(void);												
	bool ouvrirFichierEcriture2(void);													
	bool ecrireDonneesFichier(char donneesAEnregistrer[][MAX_CHARS], int nbDonnees);	
	string lectureLigne(int noLigne);													
	bool supprimerObjet(long int idObjetASupprimer);									
	bool miseAJourFichier(void);													
	bool fermerFichier(void);															
};

class GestionClub : public GestionFichier 
{
private:
	bool convertClubToStr(Club& clubAConvertir, const long int idOfClub, char clubStr[][MAX_CHARS], int *nbStr);	
public:	
	GestionClub();																									
	~GestionClub();																								
	bool ajoutNouveauClub(Club& clubAEnregistrer, const long int idOfClub);											
	long int searchForIdOfClub(const string nameOfClub);															
	Club lectureClubAvecId(const long int idClubARetourner);														
	bool lectureClubs(Club* tableauClub, int *nbClubs);																
	Club lectureClub(int noLineClub);																				
	Club convertStrToClub(string strAConvertir, long int *idToReturn);												
};

class GestionStade : public GestionFichier 
{
private:
	bool convertStadeToStr(Stade& stadeAConvertir, const long int idOfStade, const long int idOfClub, char stadeStr[][MAX_CHARS], int *nbStr);	
public:
	GestionStade();																																
	~GestionStade();																																
	bool ajoutNouveauStade(Stade& stadeAEnregistrer, const long int idOfStade, const long int idOfClub);										
	Stade lectureStadeAvecId(const long int idStadeARetourner);																					
	long int returnIdOfStadeWithClubId(const long int clubId);																				
	Stade convertStrToStade(string strAConvertir, long int *idToReturn, long int *id2ToReturn);													
};

class GestionEntraineur : public GestionFichier 
{
private:
	bool convertEntraineurToStr(Entraineur& entraineurAConvertir, const long int idOfEntraineur, const long int idOfClub, char entraineurStr[][MAX_CHARS], int *nbStr);		
public:
	GestionEntraineur();																																					
	~GestionEntraineur();																																					
	bool ajoutNouvelEntraineur(Entraineur& entraineurAEnregistrer, const long int idOfEntraineur, const long int idOfClub);												
	long int returnIdOfEntraineurWithClubId(const long int clubId);																											
	Entraineur convertStrToEntraineur(string strAConvertir, long int *idToReturn, long int *id2ToReturn);
	Entraineur lectureEntraineurAvecId(const long int idEntraineurARetourner);
};

class GestionJoueurs : public GestionFichier 
{
private:
	bool convertJoueurToStr(Joueur& joueurAConvertir, const long int idOfJoueur, const long int idOfClub, char joueurStr[][MAX_CHARS], int *nbStr);
public:
	GestionJoueurs();
	~GestionJoueurs();
	long int returnIdOfJoueurWithClubId(const long int clubId, string prenomJoueur);
	int lectureJoueursAvecId( long int idOfClub, Joueur *tableauJoueurs);
	bool ajoutNouveauJoueur(Joueur& JoueurAEnregistrer, const long int idOfJoueurs, const long int idOfClub);
	Joueur convertStrToJoueur(string strAConvertir, long int *idToReturn, long int *id2ToReturn);
};

class GestionRencontre : public GestionFichier 
{
private:
	bool convertRencontreToStr(Rencontre& rencontreAConvertir, const long int idOfRencontre, char rencontreStr[][MAX_CHARS], int *nbStr);
public:
	GestionRencontre();
	~GestionRencontre();
	bool ajoutNouvelleRencontre(Rencontre& rencontreAEnregistrer, const long int idOfRencontre);
	long int searchForIdOfRencontre(const string nameOfEquipeDomicile, const string nameOfEquipeAdverse, const string DateRencontre);
	bool lectureRencontres(Rencontre* tableauRencontres, int *nbRencontres);
	Rencontre convertStrToRencontre(string strAConvertir, long int *idToReturn);
};

class GestionContrats : public GestionFichier
{
private: 
	bool convertContratToStr(ContratEngagement& contratAConvertir, const long int idOfContrat, const long int idOfClub, char contratStr[][MAX_CHARS], int *nbStr);
public:
	GestionContrats();
	~GestionContrats();
	bool ajoutContrat(ContratEngagement& nouveauContrat, const long idOfContrats, const long idOfClub);
	long int returnIdOfContrat(long int idOfClub, string prenomDuJoueurContractant);
	string lectureContratAvecId(const long int idContratARetourner);	
	ContratEngagement convertStrToContrat(string strAConvertir, long int *idToReturn, long int *id2ToReturn);
};

class GestionRuptures : public GestionFichier
{
private: 
	bool convertRuptureToStr(Rupture& ruptureAConvertir, const long int idOfRupture,  const long int idOfClub, char ruptureStr[][MAX_CHARS], int *nbStr);
public:
	GestionRuptures();
	~GestionRuptures();
	bool ajoutRupture(Rupture& nouvelleRupture, const long int idOfRuptures, const long int idOfClub);
	long int returnIdOfRupture(long int idOfClub, string prenomDuJoueurContractant);
	string lectureRuptureAvecId(const long int idRuptureAChercher);
	Rupture convertStrToRupture(string strAConvertir, long int *idToReturn, long int *id2ToReturn);
};

/*
class GestionTitresEntraineurs : public GestionFichier
{
private: 
	bool convertTitreEntraineurToStr();
public:

	GestionTitresEntraineurs();
	~GestionTitresEntraineurs();
	bool ajoutTitreEntraineur();
	string lectureTitreAvecEntraineurId(const long int idTitreEntraineur);
	Titre convertStrToTitre(string stringAConvertir, long int *idToReturn, long int *id2ToReturn);	
};
*/

class GestionTitresClubs : public GestionFichier
{
private: 
	bool convertTitreClubToStr(titre titreAConvertir, const long int idOfTitre, const long int idOfClub, char titreStr[][MAX_CHARS], int *nbStr);
public:
	GestionTitresClubs();
	~GestionTitresClubs();
    bool ajoutTitreClub(titre nouveauTitre, const long int idOfTitre, const long int idOfClub);
	int  lectureTitresAvecClubId(long int idOfClub, titre *tableauTitres, int *nbTitresTableau);
	titre convertStrToTitre(string strAConvertir, long int *idToReturn, long int *id2ToReturn);
};

class EnregistrementDonnee {
 private:
	fstream	fichierId;
	GestionClub enregistrementClub;
	GestionStade enregistrementStade;
	GestionContrats enregistrementContrat; 
	GestionRuptures enregistrementRupture;
	GestionEntraineur enregistrementEntraineur;
	GestionRencontre enregistrementRencontre;
	GestionJoueurs enregistrementJoueurs;
	GestionTitresClubs enregistrementTitreClub;
	//GestionTitresEntraineurs enregistrementTitreEntraineur;
	long int generateId(string typeId);
public: 
	EnregistrementDonnee();
	~EnregistrementDonnee();
	int enregistrerClub(Club& clubAEnregistrer);
	int enregistrerRencontre(Rencontre& rencontreAEnregistrer);
	int enregistrerStade(string nomDuClub, Stade& stadeAAjouter);
	int enregistrerEntraineur(string nomDuClub, Entraineur& entraineurAAjouter);
	int enregistrerJoueur(string nomDuClub, Joueur& joueurAEnregistrer);
	int enregistrerRupture(string nomDuClub, Joueur joueurContractant, Rupture& ruptureContrat);
	int enregistrerContrat(string nomDuClub, ContratEngagement& contratAEnregistrer);
	int enregistrerTitreClub(string nomDuClub, titre titreAEnregistrer); 
	// int enregistrerTitreEntraineur(string nomEntraineur, Titre titreAEnregistrer); 
	int modifierClub(Club& ancienClub, Club& nouveauClub);
	int modifierStade(string nomDuClub, Stade& stadeAModifier);
	int modifierEntraineur(string nomDuClub, Entraineur& entraineurAModifier);
	int supprimerClub(Club& clubASupprimer);
	int supprimerRencontre(Rencontre& rencontreASupprimer);
	int supprimerJoueur(string nomDuClub, Joueur& joueurASupprimer);
	int supprimerEntraineur(string nomDuClub, Entraineur& entraineurASupprimer);
	int supprimerStade(string nomDuClub, Stade& stadeASupprimer);
	int supprimerContrat(string nomDuClub, ContratEngagement& contratASupprimer); 
	vector<Club> lectureDonnees(void);
	int lectureRencontres(Rencontre *tableauRencontres, int *nbRencontres);
	string retourneStatutContractuel(string prenomDuJoueurAChercher, string nomDuClub);
};

#endif 