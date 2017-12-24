/**************************************************************************
  classesCalendrierMatchs.h -- Classes for the soccer club software
  Écrit par : Pierre-Marc Laforest
  Date: 15/03/17                                        
// A FAIRE : AJOUTER LA LISTE DE TITRE GAGNES
*************************************************************************** */

#ifndef CLASSECALENDRIER_H
#define CLASSECALENDRIER_H

#include <iostream>
#include <string>
#include "classesLigue.h"
#include "detailsContrats.h"

using namespace std;

class Club;
class Joueur;

class Resultat 
{
private:
	int nbTotalButsEquipeLocale;
	int nbTotalButsEquipeAdverse;
public:
	Resultat();
	~Resultat();
	void ajoutnbTotalButsEquipeLocale(int butsEquipeLocaleAAJouter);
	void ajoutnbTotalButsEquipeAdverse(int butsEquipeAdverseAAjouter);
	int  retourneNbTotalButsEquipeLocale(void);
	int  retourneNbTotalButsEquipeAdverse(void);
	Resultat operator=(Resultat resultat2);
};

class Rencontre 
{
private:
	string nomClubDomicile;
	string nomClubEtranger;
	Stade  lieuRencontre;
	Date   dateRencontre;
	Resultat resultatMatch;
public:
	Rencontre();
	Rencontre(string nomClubDomicileAAjouter, string nomClubEtrangerAAjouter, Stade& lieuRencontreAAjouter, Date& dateRencontreAAjouter);
	~Rencontre();
	void ajoutNomClubDomicile(string nomClubAAjouter);
	void ajoutNomClubEtranger(string nomClubAAjouter);
	void ajoutLieuRencontre(Stade& lieuRencontreAAjouter);
	void ajoutDateRencontre(Date& dateAAjouter);
	void ajoutResultatMatch(Resultat& resultatAAjouter);
	string retourneNomClubDomicile(void);
	string retourneNomClubEtranger(void);
	Stade retourneLieuRencontre(void);
	Date retourneDateRencontre(void);
	Resultat retourneResultatMatch(void);
	Rencontre operator=(Rencontre rencontre2);
};

class Calendrier
{
#define NB_MAX_RENCONTRES 50
private:
	Rencontre rencontresPrevues[NB_MAX_RENCONTRES];
	int	nbRencontres;
public:
	Calendrier();
	~Calendrier();
	bool ajoutRencontre2(Rencontre& rencontreAAjouter);
	bool enleverRencontre2(unsigned int noRencontreAEnlever);
	Rencontre* retourneRencontresPrevues(void);
	int retourneNbRencontres(void);
	vector<string> retourneListeRencontres(void);
	vector<string> retourneListeRencontresEquipe(string nomClub);
	Rencontre retourneRencontreAvecNo(int noRencontre);
	vector<string> retourneResultatsRencontres(void);
	vector<string> retourneResultatsRencontresEquipe(string nomClub);
	Rencontre* retournePtrTableauRencontre(void);
	int* retournePtrNbRencontres(void);
	void afficherRencontres(void);
	void afficherRencontresAvecNo(void);
	void afficherRencontreAvecNomClub(string nomClub);
	void lectureRencontresFichier(void);
	void simulerMatch2(int noRencontre, Club& clubDomicile, Club& clubEtranger);
};

class Periode 
{
private:
	int dureePeriode;
	int nbButsEquipeLocale;
	int nbButsEquipeAdverse;
public:
	Periode();
	~Periode();
	void ajoutDureePeriode(int dureeAAjouter);
	void ajoutNbButsEquipeLocale(int nbButsAAJouter);
	void ajoutNbButsEquipeAdverse(int nbButsAAjouter);
	int retourneDureePeriode(void);
	int retourneNbButsEquipeLocale(void);
	int retourneNbButsEquipeAdverse(void);
};

class Match 
{
private:
	Equipe equipeLocale;
	Equipe equipeInvitee;
	Periode listePeriodes[2];
public:
	Match();
	~Match();
	void ajoutEquipeLocale( Equipe& equipeAAjouter);
	void ajoutEquipeInvitee( Equipe& equipeAAjouter);
	Equipe retourneEquipeLocale(void);
	Equipe retourneEquipeInvitee(void);
	Resultat simulationRencontre(Club& clubADomicile, Club& clubAEtranger);
};

#endif
