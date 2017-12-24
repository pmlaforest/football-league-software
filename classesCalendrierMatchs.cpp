/**************************************************************************
  classesCalendrierMatchs.cpp -- Classes for the soccer club software
  Écrit par : Pierre-Marc Laforest
  Date: 15/03/17                                        
*************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "classeIOFichiers.h"
#include "classesCalendrierMatchs.h"
#include "classesLigue.h"

using namespace std;

Resultat::Resultat() 
{
	nbTotalButsEquipeLocale = -1;
	nbTotalButsEquipeAdverse = -1;
}
Resultat::~Resultat() {}

void Resultat::ajoutnbTotalButsEquipeLocale(int butsEquipeLocaleAAJouter) { nbTotalButsEquipeLocale = butsEquipeLocaleAAJouter; }
void Resultat::ajoutnbTotalButsEquipeAdverse(int butsEquipeAdverseAAjouter) { nbTotalButsEquipeAdverse = butsEquipeAdverseAAjouter; } 

int  Resultat::retourneNbTotalButsEquipeLocale(void) { return nbTotalButsEquipeLocale; }
int  Resultat::retourneNbTotalButsEquipeAdverse(void) { return nbTotalButsEquipeAdverse; }

Resultat Resultat::operator=(Resultat resultat2)
{
	nbTotalButsEquipeLocale = resultat2.nbTotalButsEquipeLocale;
	nbTotalButsEquipeAdverse = resultat2.nbTotalButsEquipeAdverse;
	
	return (*this);
}

Rencontre::Rencontre() 
{
	nomClubDomicile = "Aucun";
	nomClubEtranger = "Aucun";
};

Rencontre::Rencontre(string nomClubDomicileAAjouter, string nomClubEtrangerAAjouter, Stade& lieuRencontreAAjouter, Date& dateRencontreAAjouter) 
{
	nomClubDomicile = nomClubDomicileAAjouter;
	nomClubEtranger = nomClubEtrangerAAjouter;
	lieuRencontre = lieuRencontreAAjouter;
	dateRencontre = dateRencontreAAjouter;
};
Rencontre::~Rencontre() {};

void Rencontre::ajoutNomClubDomicile(string nomClubAAjouter) { nomClubDomicile = nomClubAAjouter; }
void Rencontre::ajoutNomClubEtranger(string nomClubAAjouter) { nomClubEtranger = nomClubAAjouter; }
void Rencontre::ajoutLieuRencontre(Stade& lieuRencontreAAjouter) { lieuRencontre = lieuRencontreAAjouter; }
void Rencontre::ajoutDateRencontre(Date& dateAAjouter) { dateRencontre = dateAAjouter; }
void Rencontre::ajoutResultatMatch(Resultat& resultatAAjouter) {  resultatMatch = resultatAAjouter; }

string Rencontre::retourneNomClubDomicile(void) { return nomClubDomicile; }
string Rencontre::retourneNomClubEtranger(void) { return nomClubEtranger; }
Stade Rencontre::retourneLieuRencontre(void) { return lieuRencontre; }
Date Rencontre::retourneDateRencontre(void) { return dateRencontre; }
Resultat Rencontre::retourneResultatMatch(void) { return resultatMatch; }

Rencontre Rencontre::operator=(Rencontre rencontre2)
{
	nomClubDomicile = rencontre2.nomClubDomicile;
	nomClubEtranger = rencontre2.nomClubEtranger;
	lieuRencontre = rencontre2.lieuRencontre;
	dateRencontre = rencontre2.dateRencontre;
	resultatMatch = rencontre2.resultatMatch;
	
	return (*this);
}

Calendrier::Calendrier() 
{
	nbRencontres = 0;
}
Calendrier::~Calendrier() {}

int Calendrier::retourneNbRencontres(void) {return nbRencontres;}
Rencontre* Calendrier::retourneRencontresPrevues(void) { return rencontresPrevues;}
Rencontre Calendrier::retourneRencontreAvecNo(int noRencontre) { return rencontresPrevues[noRencontre - 1];}

Rencontre* Calendrier::retournePtrTableauRencontre(void){ return rencontresPrevues;}
int* Calendrier::retournePtrNbRencontres(void) { return &nbRencontres;}

vector<string> Calendrier::retourneListeRencontres(void)
{
	vector<string> rencontresARetourner;
	vector<string>::iterator itRencontre = rencontresARetourner.begin();
	string strTmp;
	
	for (int noRencontre = 0; noRencontre < nbRencontres; noRencontre++)
	{
		strTmp = rencontresPrevues[noRencontre].retourneDateRencontre().retourneDateFormat1()
			+ ": " + rencontresPrevues[noRencontre].retourneNomClubDomicile() + " Vs " +
			rencontresPrevues[noRencontre].retourneNomClubEtranger();
		
		itRencontre = rencontresARetourner.insert(itRencontre, strTmp);
	}
	
	return rencontresARetourner;
}

vector<string> Calendrier::retourneListeRencontresEquipe(string nomClub)
{
	vector<string> rencontresARetourner;
	vector<string>::iterator itRencontre = rencontresARetourner.begin();
	string strTmp;
	
	for (int noRencontre = 0; noRencontre < nbRencontres; noRencontre++)
	{
		if (rencontresPrevues[noRencontre].retourneNomClubDomicile() == nomClub)
		{
			strTmp = rencontresPrevues[noRencontre].retourneDateRencontre().retourneDateFormat1()
			+ ": " + rencontresPrevues[noRencontre].retourneNomClubDomicile() + " Vs " +
			rencontresPrevues[noRencontre].retourneNomClubEtranger() + "(A Domicile)";
		
			itRencontre = rencontresARetourner.insert(itRencontre, strTmp);
		}
		else if (rencontresPrevues[noRencontre].retourneNomClubEtranger() == nomClub)
		{
			strTmp = rencontresPrevues[noRencontre].retourneDateRencontre().retourneDateFormat1()
			+ ": " + rencontresPrevues[noRencontre].retourneNomClubDomicile() + " Vs " +
			rencontresPrevues[noRencontre].retourneNomClubEtranger() + "(A Letranger)";
		
			itRencontre = rencontresARetourner.insert(itRencontre, strTmp);	
		}
		else
			continue;
	}
	
	return rencontresARetourner;
}

vector<string> Calendrier::retourneResultatsRencontresEquipe(string nomClub)
{
	vector<string> rencontresARetourner;
	vector<string>::iterator itRencontre = rencontresARetourner.begin();
	string strTmp;
	Resultat resultatTmp;
		
	for (int noRencontre = 0; noRencontre < nbRencontres; noRencontre++)
	{
		resultatTmp = rencontresPrevues[noRencontre].retourneResultatMatch();
		string nbButsEquipeLocale = to_string(resultatTmp.retourneNbTotalButsEquipeLocale());
		string nbButsEquipeAdverse = to_string(resultatTmp.retourneNbTotalButsEquipeAdverse());
		
		if (resultatTmp.retourneNbTotalButsEquipeLocale() != -1)
		{
			if (rencontresPrevues[noRencontre].retourneNomClubDomicile() == nomClub)
			{
				strTmp = rencontresPrevues[noRencontre].retourneDateRencontre().retourneDateFormat1()
				+ ": " + rencontresPrevues[noRencontre].retourneNomClubDomicile() + " Vs " +
				rencontresPrevues[noRencontre].retourneNomClubEtranger() + " " +
				nbButsEquipeLocale + " - " + nbButsEquipeAdverse;
			
				itRencontre = rencontresARetourner.insert(itRencontre, strTmp);
			}
			else if (rencontresPrevues[noRencontre].retourneNomClubEtranger() == nomClub)
			{
				strTmp = rencontresPrevues[noRencontre].retourneDateRencontre().retourneDateFormat1()
				+ ": " + rencontresPrevues[noRencontre].retourneNomClubDomicile() + " Vs " +
				nbButsEquipeLocale + " - " + nbButsEquipeAdverse;
			
				itRencontre = rencontresARetourner.insert(itRencontre, strTmp);	
			}
			else
				continue;
		}
	}
	
	return rencontresARetourner;
}

vector<string> Calendrier::retourneResultatsRencontres(void)
{
	vector<string> rencontresARetourner;
	vector<string>::iterator itRencontre = rencontresARetourner.begin();
	string strTmp;
	Resultat resultatTmp;
	
	for (int noRencontre = 0; noRencontre < nbRencontres; noRencontre++)
	{
		resultatTmp = rencontresPrevues[noRencontre].retourneResultatMatch();
		string nbButsEquipeLocale = to_string(resultatTmp.retourneNbTotalButsEquipeLocale());
		string nbButsEquipeAdverse = to_string(resultatTmp.retourneNbTotalButsEquipeAdverse());
		
		if (resultatTmp.retourneNbTotalButsEquipeLocale() != -1)
		{
			strTmp = rencontresPrevues[noRencontre].retourneDateRencontre().retourneDateFormat1()
			+ ": " + rencontresPrevues[noRencontre].retourneNomClubDomicile() + " Vs " +
			rencontresPrevues[noRencontre].retourneNomClubEtranger() + " " +
			nbButsEquipeLocale + " - " + nbButsEquipeAdverse;
			
			itRencontre = rencontresARetourner.insert(itRencontre, strTmp);
		}
		else
			continue;
	}
	
	return rencontresARetourner;
}

bool Calendrier::ajoutRencontre2(Rencontre& rencontreAAjouter)
{	
	rencontresPrevues[nbRencontres] = rencontreAAjouter;
	nbRencontres += 1;
	
	return true;
}

bool Calendrier::enleverRencontre2(unsigned int noRencontreAEnlever)
{
	if (nbRencontres == 0 || noRencontreAEnlever > (unsigned int) nbRencontres)
		return false;
		
	for (int indexR = (noRencontreAEnlever - 1); indexR < (nbRencontres - 1); indexR++)
		rencontresPrevues[indexR] = rencontresPrevues[indexR + 1];
	
	nbRencontres -= 1;
		
	return true;
}

void Calendrier::simulerMatch2(int noRencontre, Club& clubDomicile, Club& clubEtranger)
{
	Resultat resultatMatch;
	Match nouveauMatch;
		
	resultatMatch = nouveauMatch.simulationRencontre(clubDomicile, clubEtranger);	
	rencontresPrevues[noRencontre - 1].ajoutResultatMatch(resultatMatch);
	
	return;
}

void Calendrier::lectureRencontresFichier(void)
{
	EnregistrementDonnee donneesRencontres;
	
	donneesRencontres.lectureRencontres(rencontresPrevues, &nbRencontres);
}

Periode::Periode() 
{
	dureePeriode = 45;
	nbButsEquipeLocale = 0;
	nbButsEquipeAdverse = 0;
}
Periode::~Periode() {}

void Periode::ajoutDureePeriode(int dureeAAjouter) { dureePeriode = dureeAAjouter; }
void Periode::ajoutNbButsEquipeLocale(int nbButsAAJouter) { nbButsEquipeLocale = nbButsAAJouter; }
void Periode::ajoutNbButsEquipeAdverse(int nbButsAAjouter) { nbButsEquipeAdverse = nbButsAAjouter; }

int Periode::retourneDureePeriode(void) { return dureePeriode; }
int Periode::retourneNbButsEquipeLocale(void) { return nbButsEquipeLocale; }
int Periode::retourneNbButsEquipeAdverse(void) { return nbButsEquipeAdverse; }


Equipe::Equipe() 
{
	nbJoueursPresentsTerrain = 0;
	nbGardiens  = 0;
}
Equipe::~Equipe() {}

void Equipe::ajoutClubEquipe(Club& clubAAjouter) { clubEquipe = clubAAjouter;}
void Equipe::ajoutNbJoueursPresentsTerrain(int nbJoueursPresentsAAjouter) { nbJoueursPresentsTerrain = nbJoueursPresentsAAjouter; }
void Equipe::ajoutNbGardiens(int nbGardiensAAjouter) { nbGardiens = nbGardiensAAjouter;}
void Equipe::ajoutCapitaine(Joueur& capitaineAAjouter) { capitaineEquipe = capitaineAAjouter; }

Club Equipe::retourneclubEquipe(void) { return clubEquipe; }
int Equipe::retourneNbJoueursPresents(void) { return nbJoueursPresentsTerrain; }
int Equipe::retourneNbGardiens(void) { return nbGardiens; }
Joueur Equipe::retourneCapitaine(void) { return capitaineEquipe; }

Match::Match() {}
Match::~Match() {}

void Match::ajoutEquipeLocale( Equipe& equipeAAjouter) { equipeLocale =  equipeAAjouter; }
void Match::ajoutEquipeInvitee( Equipe& equipeAAjouter) { equipeInvitee = equipeAAjouter; }

Equipe Match::retourneEquipeLocale(void) { return equipeLocale; }
Equipe Match::retourneEquipeInvitee(void) { return equipeInvitee; }

Resultat Match::simulationRencontre(Club& clubADomicile, Club& clubAEtranger)
{	
	Resultat resultatMatch;
	
	srand(time(NULL));

	listePeriodes[0].ajoutNbButsEquipeLocale(rand() % 2);
	listePeriodes[0].ajoutNbButsEquipeAdverse(rand() % 2);
	listePeriodes[1].ajoutNbButsEquipeLocale(rand() % 2);
	listePeriodes[1].ajoutNbButsEquipeAdverse(rand() % 2);
		
	resultatMatch.ajoutnbTotalButsEquipeLocale(listePeriodes[0].retourneNbButsEquipeLocale() + listePeriodes[1].retourneNbButsEquipeLocale());
	resultatMatch.ajoutnbTotalButsEquipeAdverse(listePeriodes[0].retourneNbButsEquipeAdverse() + listePeriodes[1].retourneNbButsEquipeAdverse());
	
	return resultatMatch;
} 
