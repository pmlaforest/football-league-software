/**************************************************************************
  classesIOFichiers.cpp -- classes ecriture/lecture dans des fichiers
  pour le logiciel de gestion de ligue de soccer
  Écrit par : Pierre-Marc Laforest
  Date: 20/02/17                  
  A FAIRE: FINIR DE DEBUGGER LA FONCTION SEARCHIDFORCLUB....                    
*************************************************************************** */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include "classeIOFichiers.h"
#include "classesLigue.h"

using namespace std;

GestionFichier::GestionFichier(string nouveauNomFichier) 
{
	nomDuFichier = nouveauNomFichier;
	copieDuFichier = nomDuFichier + '2';
}

GestionFichier::~GestionFichier() {}

bool GestionFichier::ouvrirFichierLecture(void)
{
  if (fichierDonnees.is_open() == true)
    return false;

  fichierDonnees.open(nomDuFichier, std::fstream::in);
  return true;
}

bool GestionFichier::ouvrirFichierEcriture(void)
{
   if (fichierDonnees.is_open() == true)
    return false;

  fichierDonnees.open(nomDuFichier, std::fstream::out | ios::app);
  return true;	
}

bool GestionFichier::ouvrirFichierEcriture2(void)
{
  if (fichierDonnees.is_open() == true)
    return false;

  fichierDonnees.open(nomDuFichier, std::fstream::in | std::fstream::out);
  return true;
}

bool GestionFichier::fermerFichier(void)
{
  fichierDonnees.close();
  return 0;
}

bool GestionFichier::ecrireDonneesFichier(char donneesAEnregistrer[][MAX_CHARS], int nbDonnees)
{
	int  noDonnee;
	
	if (ouvrirFichierEcriture() == false)
		return false;
	
	for (noDonnee = 0; noDonnee	< (nbDonnees - 1); noDonnee++)
		fichierDonnees << donneesAEnregistrer[noDonnee] << ':';
	
	fichierDonnees << donneesAEnregistrer[noDonnee] << '\n';
	
	fermerFichier();
	
	return true;
}

bool GestionFichier::supprimerObjet(long int idObjetASupprimer)
{
	int nouvellePos = 0;
	int anciennePos = 0;
	int idFound;
	int haveFoundId = 0;
	std::string line;  
	std::string idSearched;
	
	if (ouvrirFichierEcriture2() == false)
		return false;
	
	while(std::getline(fichierDonnees, line))
    {
	  nouvellePos = fichierDonnees.tellg();
      std::istringstream iss(line);

      getline(iss, idSearched, ':');
	  idFound  = atol(idSearched.c_str());
 
      if (idFound == idObjetASupprimer)
	  {
			haveFoundId = 1;
			break;
	  }
	  anciennePos = nouvellePos;
    }
	
	if (haveFoundId == 0)
	{
		fermerFichier();
		return false;
	}	

	fichierDonnees.seekp(anciennePos, ios::beg);
	long int idCpy = idObjetASupprimer;
	while (idCpy > 9)
	{
		idCpy /= 10;
		fichierDonnees << '0';
	}
	fichierDonnees << '0';
	
	fermerFichier();
	
	return true;
}

bool GestionFichier::miseAJourFichier(void)
{
	int idFound;
	std::string line;  
	std::string idSearched;
	ofstream nouveaufichierDonnees;
	
	if (ouvrirFichierEcriture2() == false)
		return false;
	
	nouveaufichierDonnees.open(copieDuFichier, std::fstream::out | ios::app); 
	
	while(std::getline(fichierDonnees, line))
    {
      std::istringstream iss(line);
      getline(iss, idSearched, ':');
	  idFound  = atol(idSearched.c_str());
 
      if (idFound != 0)
	  {
		nouveaufichierDonnees << line << endl;
	  }
    }
	
	rename(copieDuFichier.c_str(), nomDuFichier.c_str());
	nouveaufichierDonnees.close();
	fermerFichier();	
	
	return true;
}

string GestionFichier::lectureLigne(int noLigne)
{
	std::string line;
	if (ouvrirFichierLecture() == false)
		return NULL;
	
	while (std::getline(fichierDonnees, line)) 
	{
		if (noLigne == 0)
		{
			fermerFichier();
			return line;
		}		
		noLigne--;
	}
			
	fermerFichier();
		
	return "termine";
}

GestionClub::GestionClub() : GestionFichier("clubs.txt")  { }	
GestionClub::~GestionClub() { }	

bool GestionClub::ajoutNouveauClub(Club& clubAEnregistrer, const long int idOfClub)
{ 
	char clubStr[7][MAX_CHARS];
	int nbStrObjetClub;

	convertClubToStr(clubAEnregistrer, idOfClub, clubStr, &nbStrObjetClub);
	ecrireDonneesFichier(clubStr, nbStrObjetClub);
			  
  return true;	
} 

bool GestionClub::convertClubToStr(Club& clubAConvertir, const long int idOfClub, char clubStr[][MAX_CHARS], int *nbStr)
{
	char idOfClubStr[10];
	char nbJoueursStr[10];
	char nbTitresStr[10];
	
	*nbStr = 0;
	
	sprintf(idOfClubStr, "%ld", idOfClub);
	sprintf(nbJoueursStr, "%u", clubAConvertir.retourneNbJoueurs());
	sprintf(nbTitresStr, "%u", clubAConvertir.retournePalmaresDeChampionnats().retourneNbTitres());
	
	strcpy(clubStr[(*nbStr)++], idOfClubStr);
	strcpy(clubStr[(*nbStr)++], clubAConvertir.retourneNom().c_str());
	strcpy(clubStr[(*nbStr)++], clubAConvertir.retourneHistoire().c_str());
	strcpy(clubStr[(*nbStr)++], clubAConvertir.retourneCouleur().c_str());
	strcpy(clubStr[(*nbStr)++], clubAConvertir.retourneVille().c_str());
	strcpy(clubStr[(*nbStr)++], clubAConvertir.retourneAdresse().c_str());
	strcpy(clubStr[(*nbStr)++], nbJoueursStr);
	strcpy(clubStr[(*nbStr)++], nbTitresStr);
	
	return true;
}

Club GestionClub::convertStrToClub(string strAConvertir, long int *idToReturn)
{
	Club clubARetourner;
	string tmpString;
	int nbJoueurs;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');  
	clubARetourner.ajoutNom(tmpString);
	getline(iss, tmpString, ':');
	clubARetourner.ajoutHistoire(tmpString);
	getline(iss, tmpString, ':');
	clubARetourner.ajoutCouleur(tmpString);
	getline(iss, tmpString, ':');
	clubARetourner.ajoutVille(tmpString);
	getline(iss, tmpString, ':');
	clubARetourner.ajoutAdresse(tmpString);
	getline(iss, tmpString, ':');
	nbJoueurs = atol(tmpString.c_str());
	clubARetourner.ajoutNbJoueurs(nbJoueurs);
	
	return clubARetourner;	
}

Club GestionClub::lectureClub(int noLigne)
{
	string clubStr;
	Club clubLu;
	
	clubStr = lectureLigne(noLigne);
	
	if (clubStr == "termine")
		clubLu = Club();
	else
		clubLu = convertStrToClub(clubStr, NULL);
	
	return clubLu;
}

Club GestionClub::lectureClubAvecId(const long int idClubARetourner)
{
	long int idRead; 
	Club clubARetourner;
	string clubStr;
	int ligneCount = 0;
	
	while( (clubStr = lectureLigne(ligneCount++)) != "termine")
    {
	  clubARetourner = convertStrToClub(clubStr, &idRead); 	
		
      if (idRead == idClubARetourner)
	  {
		return clubARetourner;
	  }
    }
	
	return Club();	
}

long int GestionClub::searchForIdOfClub(const string nameOfClub)
{
  	long int idRead; 
	Club clubARetourner;
	string clubStr;
	int ligneCount = 0;
	  
  while((clubStr = lectureLigne(ligneCount++)) != "termine" )
    {
	  clubARetourner = convertStrToClub(clubStr, &idRead); 
	  
      if (clubARetourner.retourneNom() == nameOfClub)
		return idRead;
    }

	return -1;
} 

GestionStade::GestionStade() : GestionFichier("stades.txt") {}
GestionStade::~GestionStade() {}

bool GestionStade::ajoutNouveauStade(Stade& stadeAEnregistrer, const long int idOfStade, const long int idOfClub)
{ 
	char stadeStr[6][MAX_CHARS];
	int nbStrObjetStade;

	convertStadeToStr(stadeAEnregistrer, idOfStade, idOfClub, stadeStr, &nbStrObjetStade);
	ecrireDonneesFichier(stadeStr, nbStrObjetStade);

  return true;	
} 

bool GestionStade::convertStadeToStr(Stade& stadeAConvertir, const long int idOfStade, const long int idOfClub, char stadeStr[][MAX_CHARS], int *nbStr)
{
	char idOfStadeStr[10];
	char idOfClubStr[10];
	char capaciteStr[10];
	
	*nbStr = 0;
	
	sprintf(idOfStadeStr, "%ld", idOfStade);
	sprintf(idOfClubStr, "%ld", idOfClub);
	sprintf(capaciteStr, "%u", stadeAConvertir.retourneCapacite());
	
	strcpy(stadeStr[(*nbStr)++], idOfStadeStr);
	strcpy(stadeStr[(*nbStr)++], idOfClubStr);
	strcpy(stadeStr[(*nbStr)++], stadeAConvertir.retourneNom().c_str());
	strcpy(stadeStr[(*nbStr)++], stadeAConvertir.retourneAdresse().c_str());
	strcpy(stadeStr[(*nbStr)++], stadeAConvertir.retourneQualiteTerrain().c_str());
	strcpy(stadeStr[(*nbStr)++], capaciteStr);
	
	return true;
}

Stade GestionStade::convertStrToStade(string strAConvertir, long int *idToReturn, long int *id2ToReturn)
{
	Stade stadeARetourner;
	string tmpString;
	int capaciteStade;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	if (id2ToReturn != NULL)
		*id2ToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	stadeARetourner.modifNomStade(tmpString.c_str());
	getline(iss, tmpString, ':');
	stadeARetourner.modifAdresse(tmpString.c_str());
	getline(iss, tmpString, ':');
	stadeARetourner.modifQualiteTerrain(tmpString.c_str());
	getline(iss, tmpString, ':');
	capaciteStade = atol(tmpString.c_str());
	stadeARetourner.modifCapacite(capaciteStade);
	
	return stadeARetourner;	
}

Stade GestionStade::lectureStadeAvecId(const long int idStadeARetourner)
{
	long int idStadeRead = -1; 
	Stade stadeARetourner;
	std::string stadeStr;
	int ligneCount = 0;

	while( (stadeStr = lectureLigne(ligneCount++)) != "termine")
    {
	  stadeARetourner = convertStrToStade(stadeStr, &idStadeRead, NULL); 	
		
      if (idStadeRead == idStadeARetourner)
	  {
		return stadeARetourner;
	  }
    }
	
	return Stade();	
} 

long int GestionStade::returnIdOfStadeWithClubId(const long int clubId)
{
  long int idStadeRead, idClubRead; 
  Stade stadeARetourner;
  string stadeStr;
  int ligneCount = 0;
	  
  while((stadeStr = lectureLigne(ligneCount++)) != "termine" )
    {
	  stadeARetourner = convertStrToStade(stadeStr, &idStadeRead, &idClubRead); 
	  
      if (idClubRead == clubId)
		return idStadeRead;
    }
	
	return -1;
} 

GestionEntraineur::GestionEntraineur() : GestionFichier("entraineurs.txt") {}
GestionEntraineur::~GestionEntraineur() {}

bool GestionEntraineur::ajoutNouvelEntraineur(Entraineur& entraineurAEnregistrer, const long int idOfEntraineur, const long int idOfClub)
{ 
	char entraineurStr[5][MAX_CHARS];
	int nbStrObjetEntraineur;

	convertEntraineurToStr(entraineurAEnregistrer, idOfEntraineur, idOfClub, entraineurStr, &nbStrObjetEntraineur);
	ecrireDonneesFichier(entraineurStr, nbStrObjetEntraineur);
			  
  return true;	
} 

bool GestionEntraineur::convertEntraineurToStr(Entraineur& entraineurAConvertir, const long int idOfEntraineur, const long int idOfClub, char entraineurStr[][MAX_CHARS], int *nbStr)
{
	char idOfClubStr[10];
	char idOfEntraineurStr[10];

	*nbStr = 0;
	
	sprintf(idOfEntraineurStr, "%ld", idOfEntraineur);
	sprintf(idOfClubStr, "%ld", idOfClub);
	
	strcpy(entraineurStr[(*nbStr)++], idOfEntraineurStr);
	strcpy(entraineurStr[(*nbStr)++], idOfClubStr);
	strcpy(entraineurStr[(*nbStr)++], entraineurAConvertir.retourneNom().c_str());
	strcpy(entraineurStr[(*nbStr)++], entraineurAConvertir.retournePrenom().c_str());
	strcpy(entraineurStr[(*nbStr)++], entraineurAConvertir.retourneLieu().c_str());
	
	return true;
}

Entraineur GestionEntraineur::convertStrToEntraineur(string strAConvertir, long int *idToReturn, long int *id2ToReturn)
{
	Entraineur entraineurARetourner;
	string tmpString;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	if (id2ToReturn != NULL)
		*id2ToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	entraineurARetourner.modifNom(tmpString.c_str());
	getline(iss, tmpString, ':');
	entraineurARetourner.modifPrenom(tmpString.c_str());
	getline(iss, tmpString, ':');
	entraineurARetourner.modifLieuObtention(tmpString.c_str());
	
	return entraineurARetourner;	
} 

long int GestionEntraineur::returnIdOfEntraineurWithClubId(const long int clubId)
{
  long int idEntraineurRead, idClubRead; 
  Entraineur entraineurARetourner;
  string entraineurStr;
  int ligneCount = 0;
	  
  while((entraineurStr = lectureLigne(ligneCount++)) != "termine" )
    {
	  entraineurARetourner = convertStrToEntraineur(entraineurStr, &idEntraineurRead, &idClubRead); 
	  
      if (idClubRead == clubId)
		return idEntraineurRead;
    }
	
	return -1;
} 

Entraineur GestionEntraineur::lectureEntraineurAvecId(const long int idEntraineurARetourner)
{
	long int idEntraineurRead = -1; 
	Entraineur entraineurARetourner;
	std::string entraineurStr;
	int ligneCount = 0;

	while( (entraineurStr = lectureLigne(ligneCount++)) != "termine")
    {
	  entraineurARetourner = convertStrToEntraineur(entraineurStr, &idEntraineurRead, NULL); 	
		
      if (idEntraineurRead == idEntraineurARetourner)
	  {
		return entraineurARetourner;
	  }
    }
	
	return Entraineur();	
}

GestionJoueurs::GestionJoueurs() : GestionFichier("joueurs.txt")	{}	
GestionJoueurs::~GestionJoueurs() {}	

bool GestionJoueurs::ajoutNouveauJoueur(Joueur& joueurAEnregistrer, const long int idOfJoueur, const long int idOfClub)
{ 
	char joueurStr[6][MAX_CHARS];
	int nbStrObjetJoueur;

	convertJoueurToStr(joueurAEnregistrer, idOfJoueur, idOfClub, joueurStr, &nbStrObjetJoueur);
	ecrireDonneesFichier(joueurStr, nbStrObjetJoueur);
			  
  return true;	
} 

bool GestionJoueurs::convertJoueurToStr(Joueur& joueurAConvertir, const long int idOfJoueur, const long int idOfClub, char joueurStr[][MAX_CHARS], int *nbStr)
{
	char idOfClubStr[10];
	char idOfJoueurStr[10];
	char poidsStr[10];

	*nbStr = 0;
	
	sprintf(idOfJoueurStr, "%ld", idOfJoueur);
	sprintf(idOfClubStr, "%ld", idOfClub);
	sprintf(poidsStr, "%f", joueurAConvertir.retournePoids());
	
	strcpy(joueurStr[(*nbStr)++], idOfJoueurStr);
	strcpy(joueurStr[(*nbStr)++], idOfClubStr);
	strcpy(joueurStr[(*nbStr)++], joueurAConvertir.retournePrenom().c_str());
	strcpy(joueurStr[(*nbStr)++], joueurAConvertir.retourneNom().c_str());
	strcpy(joueurStr[(*nbStr)++], poidsStr);
	strcpy(joueurStr[(*nbStr)++], joueurAConvertir.retourneVilleDeNaissance().c_str());
	
	return true;
}

Joueur GestionJoueurs::convertStrToJoueur(string strAConvertir, long int *idToReturn, long int *id2ToReturn)
{
	Joueur joueurARetourner;
	string tmpString;
	float poidsJoueur;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	if (id2ToReturn != NULL)
		*id2ToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	joueurARetourner.modifPrenom(tmpString.c_str());
	getline(iss, tmpString, ':');
	joueurARetourner.modifNom(tmpString.c_str());
	getline(iss, tmpString, ':');
	poidsJoueur = atol(tmpString.c_str());
	joueurARetourner.modifPoids(poidsJoueur);
	getline(iss, tmpString, ':');
	joueurARetourner.modifVilleDeNaissance(tmpString.c_str());
	
	return joueurARetourner;	
}

long int GestionJoueurs::returnIdOfJoueurWithClubId(const long int clubId, string prenomDuJoueur)
{
  long int idJoueurRead, idClubRead; 
  Joueur joueurARetourner;
  string joueurStr;
  int ligneCount = 0;
	  
  while((joueurStr = lectureLigne(ligneCount++)) != "termine" )
    {
	  joueurARetourner = convertStrToJoueur(joueurStr, &idJoueurRead, &idClubRead); 
	  
      if (idClubRead == clubId && joueurARetourner.retournePrenom() == prenomDuJoueur)
		return idJoueurRead;
    }
	
	return -1;
}


int GestionJoueurs::lectureJoueursAvecId(long int idOfClub ,Joueur* joueursClub)
{
	long int idJoueurRead = -1; 
	long int idClubRead;
	int unJoueurTrouve = 0;
	Joueur joueurLu;
	std::string joueurStr;
	int ligneCount = 0;
	int nbJoueurs;

	nbJoueurs = 0;
	
	while( (joueurStr = lectureLigne(ligneCount++)) != "termine")
    {
	  joueurLu = convertStrToJoueur(joueurStr, &idJoueurRead, &idClubRead); 	
		
      if (idClubRead == idOfClub)
	  {
		unJoueurTrouve += 1;
		joueursClub[nbJoueurs++] = joueurLu;
	  }
    }
	return unJoueurTrouve;
} 

GestionRencontre::GestionRencontre() : GestionFichier("rencontres.txt") {}
GestionRencontre::~GestionRencontre() {}
 
bool GestionRencontre::ajoutNouvelleRencontre(Rencontre& rencontreAEnregistrer, const long int idOfRencontre)
{ 
	char rencontreStr[6][MAX_CHARS];
	int nbStrObjetRencontre;

	convertRencontreToStr(rencontreAEnregistrer, idOfRencontre, rencontreStr, &nbStrObjetRencontre);
	ecrireDonneesFichier(rencontreStr, nbStrObjetRencontre);
			  
  return true;	
} 

bool GestionRencontre::convertRencontreToStr(Rencontre& rencontreAConvertir, const long int idOfRencontre, char rencontreStr[][MAX_CHARS], int *nbStr)
{
	char idOfRencontreStr[10];
	char nbButsEquipeLocaleStr[10];
	char nbButsEquipeAdverseStr[10];
	
	*nbStr = 0;
	
	sprintf(idOfRencontreStr, "%ld", idOfRencontre);
	sprintf(nbButsEquipeLocaleStr, "%d", rencontreAConvertir.retourneResultatMatch().retourneNbTotalButsEquipeLocale());
	sprintf(nbButsEquipeAdverseStr, "%d", rencontreAConvertir.retourneResultatMatch().retourneNbTotalButsEquipeAdverse());
	
	strcpy(rencontreStr[(*nbStr)++], idOfRencontreStr);
	strcpy(rencontreStr[(*nbStr)++], rencontreAConvertir.retourneNomClubDomicile().c_str());
	strcpy(rencontreStr[(*nbStr)++], rencontreAConvertir.retourneNomClubEtranger().c_str());
	strcpy(rencontreStr[(*nbStr)++], rencontreAConvertir.retourneDateRencontre().retourneDateFormat1().c_str());
	strcpy(rencontreStr[(*nbStr)++], nbButsEquipeLocaleStr);
	strcpy(rencontreStr[(*nbStr)++], nbButsEquipeAdverseStr);
	
	return true;
}

Rencontre GestionRencontre::convertStrToRencontre(string strAConvertir, long int *idToReturn)
{
	Rencontre rencontreARetourner;
	Resultat resultatTmp;
	string tmpString;
	int nbButsEquipeLocale, nbButsEquipeAdverse;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	rencontreARetourner.ajoutNomClubDomicile(tmpString.c_str());
	getline(iss, tmpString, ':');
	rencontreARetourner.ajoutNomClubEtranger(tmpString.c_str());
	getline(iss, tmpString, ':');
	Date dateTmp(tmpString);
	rencontreARetourner.ajoutDateRencontre(dateTmp);
	getline(iss, tmpString, ':');
	nbButsEquipeLocale = atol(tmpString.c_str());
	resultatTmp.ajoutnbTotalButsEquipeLocale(nbButsEquipeLocale);
	getline(iss, tmpString, ':');
	nbButsEquipeAdverse = atol(tmpString.c_str());
	resultatTmp.ajoutnbTotalButsEquipeAdverse(nbButsEquipeAdverse);
	rencontreARetourner.ajoutResultatMatch(resultatTmp);
	
	return rencontreARetourner;	
}


long int GestionRencontre::searchForIdOfRencontre(const string nameOfEquipeDomicile, const string nameOfEquipeAdverse, const string DateRencontre)
 {
	string rencontreStr;
	long int idRencontreRead;
	Rencontre rencontreARetourner;
	int ligneCount = 0;
	  
  while((rencontreStr = lectureLigne(ligneCount++)) != "termine" )
    {
	  rencontreARetourner = convertStrToRencontre(rencontreStr, &idRencontreRead); 
	  
      if (rencontreARetourner.retourneNomClubDomicile() == nameOfEquipeDomicile &&
		  rencontreARetourner.retourneNomClubEtranger() == nameOfEquipeAdverse &&
		  rencontreARetourner.retourneDateRencontre().retourneDateFormat1() == DateRencontre)
		{
			return idRencontreRead;
		}
    }
	
	return -1;
 } 
 
bool GestionRencontre::lectureRencontres(Rencontre* tableauRencontres, int *nbRencontres)
{
	Rencontre rencontreLu;
	std::string rencontreStr;
	int ligneCount = 0;

	*nbRencontres = 0;
	
	while( (rencontreStr = lectureLigne(ligneCount++)) != "termine")
    {
	  rencontreLu = convertStrToRencontre(rencontreStr, NULL); 	
	  tableauRencontres[*nbRencontres] = rencontreLu;
	  *nbRencontres = *nbRencontres + 1;
		
    }
	return true;
} 

GestionContrats::GestionContrats() : GestionFichier("contrats.txt") {}
GestionContrats::~GestionContrats() {}
 
bool GestionContrats::ajoutContrat(ContratEngagement& nouveauContrat, const long idOfContrats, const long idOfClub)
{ 
	char contratStr[11][MAX_CHARS];
	int nbStrObjetContrat;

	convertContratToStr(nouveauContrat, idOfContrats, idOfClub, contratStr, &nbStrObjetContrat);
	ecrireDonneesFichier(contratStr, nbStrObjetContrat);
			  
  return true;	
} 

bool GestionContrats::convertContratToStr(ContratEngagement& contratAConvertir, const long int idOfContrat, const long int idOfClub, char contratStr[][MAX_CHARS], int *nbStr)
{
	char idOfContratStr[10];
	char idOfClubStr[10];
	char dureeContratStr[10];
	char montantTransferStr[10];
	char montantEncaisseClubStr[10];
	char montantEncaisseJoueurStr[10];
	
	*nbStr = 0;
	
	sprintf(idOfContratStr, "%ld", idOfContrat);
	sprintf(idOfClubStr, "%ld", idOfClub);
	sprintf(dureeContratStr, "%d", contratAConvertir.retourneDureeContrat());
	sprintf(montantTransferStr, "%f", contratAConvertir.retourneReglementContrat().retourneMontantTransfert());
	sprintf(montantEncaisseClubStr, "%f", contratAConvertir.retourneReglementContrat().retourneMontantEncaisseClub());
	sprintf(montantEncaisseJoueurStr, "%f", contratAConvertir.retourneReglementContrat().retourneMontantEncaisseJoueur());
	 
	strcpy(contratStr[(*nbStr)++], idOfContratStr);
	strcpy(contratStr[(*nbStr)++], idOfClubStr);
	strcpy(contratStr[(*nbStr)++], contratAConvertir.retourneJoueurContractant().retournePrenom().c_str());
	strcpy(contratStr[(*nbStr)++], contratAConvertir.retourneJoueurContractant().retourneNom().c_str());
	strcpy(contratStr[(*nbStr)++], contratAConvertir.retourneClubContractant().retourneNom().c_str());
	strcpy(contratStr[(*nbStr)++], dureeContratStr);
	strcpy(contratStr[(*nbStr)++], contratAConvertir.retourneDateContrat().retourneDateFormat1().c_str());
	strcpy(contratStr[(*nbStr)++], contratAConvertir.retourneDateEntree().retourneDateFormat1().c_str());
	strcpy(contratStr[(*nbStr)++], montantTransferStr);
	strcpy(contratStr[(*nbStr)++], montantEncaisseClubStr);
	strcpy(contratStr[(*nbStr)++], montantEncaisseJoueurStr);
	
	return true;
}

ContratEngagement GestionContrats::convertStrToContrat(string strAConvertir, long int *idToReturn, long int *id2ToReturn)
{
	ContratEngagement contratARetourner;
	Reglement reglementTmp;
	Joueur joueurTmp;
	Club clubContractantTmp;
	string tmpString;
	int dureeContrat;
	int montantTransferTmp, montantEncaisseClubTmp, montantEncaisseJoueurTmp;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	if (id2ToReturn != NULL)
		*id2ToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	joueurTmp.modifPrenom(tmpString);
	getline(iss, tmpString, ':');
	joueurTmp.modifNom(tmpString);
	contratARetourner.ajoutJoueurContractant(joueurTmp);
	getline(iss, tmpString, ':');
	clubContractantTmp.ajoutNom(tmpString);
	contratARetourner.ajoutClubContractant(clubContractantTmp);
	getline(iss, tmpString, ':');
	dureeContrat = atol(tmpString.c_str());
	contratARetourner.ajoutdureeContrat(dureeContrat);
	getline(iss, tmpString, ':');
	Date dateContratTmp(tmpString);
	contratARetourner.ajoutDateContrat(dateContratTmp);
	getline(iss, tmpString, ':');
	Date dateEntreeTmp(tmpString);
	contratARetourner.ajoutDateEntree(dateContratTmp);
	getline(iss, tmpString, ':');
	montantTransferTmp =  atol(tmpString.c_str());
	reglementTmp.ajoutMontantTransfert(montantTransferTmp);
	getline(iss, tmpString, ':');
	montantEncaisseClubTmp =  atol(tmpString.c_str());
	reglementTmp.ajoutMontantEncaisseClub(montantEncaisseClubTmp);
	getline(iss, tmpString, ':');
	montantEncaisseJoueurTmp = atol(tmpString.c_str());
	reglementTmp.ajoutMontantEncaisseJoueur(montantEncaisseJoueurTmp);
	contratARetourner.ajoutReglement(reglementTmp);
	
	return contratARetourner;
}


 string GestionContrats::lectureContratAvecId(const long int idContratARetourner)
 {
	long int idContratRead = -1; 
	ContratEngagement contratARetourner;
	std::string contratStr;
	int ligneCount = 0;

	while( (contratStr = lectureLigne(ligneCount++)) != "termine")
    {
	  contratARetourner = convertStrToContrat(contratStr, &idContratRead, NULL); 	
		
      if (idContratRead == idContratARetourner)
	  {
		 Joueur joueurTmp;
		 Date dateEntreeTmp, dateContratTmp;
		 Reglement reglementTmp;
		 string tmpString;
		 char dureeContratStr[10];
		 char valeurContratStr[10];
		 
		 
		 joueurTmp = contratARetourner.retourneJoueurContractant();
		 reglementTmp = contratARetourner.retourneReglementContrat();
		 dateEntreeTmp = contratARetourner.retourneDateEntree();
		 dateContratTmp = contratARetourner.retourneDateContrat();
		 
		 sprintf(dureeContratStr, "%d", contratARetourner.retourneDureeContrat());
		 sprintf(valeurContratStr, "%f", reglementTmp.retourneMontantTransfert());
		 
		 
		 tmpString = joueurTmp.retournePrenom() + joueurTmp.retourneNom() + dureeContratStr + " ans " + dateEntreeTmp.retourneDateFormat1() + valeurContratStr + '$';
		 return tmpString;
	  }
    }
	
	return "aucun Contrat";	
 }

 long int GestionContrats::returnIdOfContrat(long int idOfClub, string prenomDuJoueurContractant)
 {
	string contratStr;
	long int idContratRead, idClubRead;
	ContratEngagement contratLu;
	int ligneCount = 0;
	  
	while((contratStr = lectureLigne(ligneCount++)) != "termine" )
    {
	  contratLu = convertStrToContrat(contratStr, &idContratRead, &idClubRead);  
      if (idClubRead == idOfClub && contratLu.retourneJoueurContractant().retournePrenom() == prenomDuJoueurContractant)
		{
			return idContratRead;
		}
    }
	
	return -1;
 }
 
GestionRuptures::GestionRuptures() : GestionFichier("ruptures.txt") {}
GestionRuptures::~GestionRuptures() {}
  
bool GestionRuptures::ajoutRupture(Rupture& nouvelleRupture, const long idOfRuptures, const long idOfClub)
{ 
	char ruptureStr[6][MAX_CHARS];
	int nbStrObjetRupture;

	convertRuptureToStr(nouvelleRupture, idOfRuptures, idOfClub, ruptureStr, & nbStrObjetRupture);
	ecrireDonneesFichier(ruptureStr,  nbStrObjetRupture);
			  
  return true;	
} 

bool GestionRuptures::convertRuptureToStr(Rupture& ruptureAConvertir, const long int idOfRupture,  const long int idOfClub, char ruptureStr[][MAX_CHARS], int *nbStr)
{
	char idOfRuptureStr[10];
	char idOfClubStr[10];
	
	*nbStr = 0;
	
	sprintf(idOfRuptureStr, "%ld", idOfRupture);
	sprintf(idOfClubStr, "%ld", idOfClub);
	
	strcpy(ruptureStr[(*nbStr)++], idOfRuptureStr);
	strcpy(ruptureStr[(*nbStr)++], idOfClubStr);
	strcpy(ruptureStr[(*nbStr)++], ruptureAConvertir.retourneJoueurContractant().retournePrenom().c_str());
	strcpy(ruptureStr[(*nbStr)++], ruptureAConvertir.retourneClubLibere().retourneNom().c_str());
	strcpy(ruptureStr[(*nbStr)++], ruptureAConvertir.retourneRaisonDepart().c_str());

	return true;
}

Rupture GestionRuptures::convertStrToRupture(string strAConvertir, long int *idToReturn, long int *id2ToReturn)
{
	Rupture ruptureARetourner;
	Joueur joueurContractantTmp;
	Club clubLibereTmp;
	string tmpString;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	if (id2ToReturn != NULL)
		*id2ToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	joueurContractantTmp.modifPrenom(tmpString.c_str());
	ruptureARetourner.ajoutJoueurContractant(joueurContractantTmp);
	getline(iss, tmpString, ':');
	clubLibereTmp.ajoutNom(tmpString.c_str());
	ruptureARetourner.ajoutClubLibere(clubLibereTmp);
	getline(iss, tmpString, ':');
	ruptureARetourner.ajoutRaisonDepart(tmpString.c_str());

	return ruptureARetourner;	
}

string GestionRuptures::lectureRuptureAvecId(const long int idRuptureAChercher)
 {
	long int idRuptureRead; 
	Rupture ruptureLu;
	string ruptureStr;
	int ligneCount = 0;
	
	while((ruptureStr = lectureLigne(ligneCount++)) != "termine")
    {
	  ruptureLu = convertStrToRupture(ruptureStr, &idRuptureRead, NULL); 	
		
      if (idRuptureRead == idRuptureAChercher)
	  {
		return ruptureLu.retourneJoueurContractant().retournePrenom() + ruptureLu.retourneClubLibere().retourneNom() + ruptureLu.retourneRaisonDepart();
	  }
    }
	
	return "aucune Rupture";		
 }
 
long int GestionRuptures::returnIdOfRupture(long int idOfClub, string prenomDuJoueurContractant)
 {
  long int idRuptureRead, idClubRead; 
  Rupture ruptureLu;
  string ruptureStr;
  int ligneCount = 0;
	  
  while((ruptureStr = lectureLigne(ligneCount++)) != "termine" )
    {
	   ruptureLu = convertStrToRupture(ruptureStr, &idRuptureRead, &idClubRead); 
	  
      if (idClubRead == idOfClub && ruptureLu.retourneJoueurContractant().retournePrenom() == prenomDuJoueurContractant)
		return idRuptureRead;
    }
	
	return -1;
 }
 
GestionTitresClubs::GestionTitresClubs()  : GestionFichier("titresClubs.txt") {}
GestionTitresClubs::~GestionTitresClubs() {}

bool GestionTitresClubs::ajoutTitreClub(titre titreAEnregistrer, const long int idOfTitre, const long int idOfClub)
{
   char titreStr[4][MAX_CHARS];
   int nbStrObjetTitre;

   convertTitreClubToStr(titreAEnregistrer, idOfTitre, idOfClub, titreStr, &nbStrObjetTitre);
   ecrireDonneesFichier(titreStr, nbStrObjetTitre);
			  
   return true;
}

bool GestionTitresClubs::convertTitreClubToStr(titre titreAConvertir, const long int idOfTitre, const long int idOfClub, char titreStr[][MAX_CHARS], int *nbStr)
{
	char idOfTitreStr[10];
	char idOfClubStr[10];
	
	*nbStr = 0;
	
	sprintf(idOfTitreStr, "%ld", idOfTitre);
	sprintf(idOfClubStr, "%ld", idOfClub);
	
	strcpy(titreStr[(*nbStr)++], idOfTitreStr);
	strcpy(titreStr[(*nbStr)++], idOfClubStr);
	strcpy(titreStr[(*nbStr)++], titreAConvertir.nomDuTitre.c_str());
	strcpy(titreStr[(*nbStr)++], titreAConvertir.dateDuChampionnat.retourneDateFormat1().c_str());

	return true;
}

titre GestionTitresClubs::convertStrToTitre(string strAConvertir, long int *idToReturn, long int *id2ToReturn)
{
	titre titreARetourner;
	string tmpString;
	
	std::istringstream iss(strAConvertir);

	getline(iss, tmpString, ':');
	if (idToReturn != NULL)
		*idToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	if (id2ToReturn != NULL)
		*id2ToReturn = atol(tmpString.c_str());
	getline(iss, tmpString, ':');
	titreARetourner.nomDuTitre = tmpString;
	getline(iss, tmpString, ':');
	Date dateTmp(tmpString);
	titreARetourner.dateDuChampionnat = dateTmp; 
	
	return titreARetourner;	
}

int  GestionTitresClubs::lectureTitresAvecClubId(long int idOfClub, titre *tableauTitres, int *nbTitresTableau)
{
	long int idTitreRead = -1; 
	long int idClubRead;
	int unTitreTrouve = 0;
	titre titreLu;
	std::string titreStr;
	int ligneCount = 0;

	*nbTitresTableau = 0;
	
	while( (titreStr = lectureLigne(ligneCount++)) != "termine")
    {
	  titreLu = convertStrToTitre(titreStr, &idTitreRead, &idClubRead); 
 
      if (idClubRead == idOfClub)
	  {
		unTitreTrouve += 1;
		tableauTitres[*nbTitresTableau] = titreLu;
		*nbTitresTableau += 1;
	  }
    }
	return unTitreTrouve;
}

EnregistrementDonnee::EnregistrementDonnee()  {}
EnregistrementDonnee::~EnregistrementDonnee() {}

int EnregistrementDonnee::enregistrerClub(Club& clubAEnregistrer)
{
	long int idOfClub = generateId("club");
	enregistrementClub.ajoutNouveauClub(clubAEnregistrer, idOfClub);
	
	return 0;
}

int EnregistrementDonnee::enregistrerRencontre(Rencontre& rencontreAEnregistrer)
{
	long int idOfRencontre = generateId("rencontre");	
	enregistrementRencontre.ajoutNouvelleRencontre(rencontreAEnregistrer, idOfRencontre);
	
	return 0;
}

int EnregistrementDonnee::supprimerRencontre(Rencontre& rencontreASupprimer)
 {
	GestionRencontre enregistrementRencontre;
	 
	long int idRencontreASupprimer = enregistrementRencontre.searchForIdOfRencontre(rencontreASupprimer.retourneNomClubDomicile(), rencontreASupprimer.retourneNomClubEtranger(), rencontreASupprimer.retourneDateRencontre().retourneDateFormat1());
	
	if (idRencontreASupprimer == -1)
	{
		cout << "La rencontre en question n'a pas ete supprime!\n";
		return -1;
	}
	
	enregistrementRencontre.supprimerObjet(idRencontreASupprimer);
	enregistrementRencontre.miseAJourFichier();
	
	return 0; 
 }
 
int EnregistrementDonnee::supprimerClub(Club& clubASupprimer)
{
	long int idClubASupprimer;
	
	idClubASupprimer = enregistrementClub.searchForIdOfClub(clubASupprimer.retourneNom());
	
	if (idClubASupprimer == -1)
	{
		cout << "Le club en question n'a pas ete trouve!\n";
		return -1;
	}

	enregistrementClub.supprimerObjet(idClubASupprimer);
	enregistrementClub.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::enregistrerStade(string nomDuClub, Stade& stadeAAjouter)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int nouveauIdOfStade = generateId("stade");
	
	enregistrementStade.ajoutNouveauStade(stadeAAjouter, nouveauIdOfStade, idClub);
	return 1;
}

int EnregistrementDonnee::modifierStade(string nomDuClub, Stade& stadeAModifier)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idStade = enregistrementStade.returnIdOfStadeWithClubId(idClub);
	
	if (idStade == -1)
	{
		cout << "Le stade du club en question n'a pas ete supprime!\n";
		return -1;
	}
	enregistrementStade.supprimerObjet(idStade);
	enregistrementStade.ajoutNouveauStade(stadeAModifier, idStade, idClub);
	enregistrementStade.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::modifierClub(Club& ancienClub, Club& nouveauClub)
{
  long int idClub = enregistrementClub.searchForIdOfClub(ancienClub.retourneNom());
  
  	if (idClub == -1)
	{
		cout << "Le club en question na pas ete modifie!\n";
		return -1;
	}
   
   enregistrementClub.supprimerObjet(idClub);
   enregistrementClub.miseAJourFichier();
   enregistrementClub.ajoutNouveauClub(nouveauClub, idClub);
  
  return 0;
}

int EnregistrementDonnee::enregistrerEntraineur(string nomDuClub, Entraineur& entraineurAAjouter)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int nouveauIdOfEntraineur = generateId("entraineur");
	
	enregistrementEntraineur.ajoutNouvelEntraineur(entraineurAAjouter, nouveauIdOfEntraineur, idClub);
	
	return 0;
}

int EnregistrementDonnee::modifierEntraineur(string nomDuClub, Entraineur& entraineurAModifier)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idEntraineurAModifier = enregistrementEntraineur.returnIdOfEntraineurWithClubId(idClub);
	long int nouveauIdOfEntraineur = generateId("entraineur");
	
	if (idEntraineurAModifier == -1)
	{
		cout << "Lentraineur du club en question  n'a pas ete supprime!\n";
		return -1;
	}
	
	enregistrementEntraineur.supprimerObjet(idEntraineurAModifier);	
	enregistrementEntraineur.ajoutNouvelEntraineur(entraineurAModifier, nouveauIdOfEntraineur, idClub);
	enregistrementEntraineur.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::supprimerEntraineur(string nomDuClub, Entraineur& entraineurAModifier)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idEntraineurAModifier = enregistrementEntraineur.returnIdOfEntraineurWithClubId(idClub);
	
	if (idEntraineurAModifier == -1)
	{	
		cout << "Lentraineur du club en question n'a ete supprime!\n";
		return -1;
	}
	
	enregistrementEntraineur.supprimerObjet(idEntraineurAModifier);
	enregistrementEntraineur.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::supprimerStade(string nomDuClub, Stade& stadeASupprimer)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idStadeASupprimer = enregistrementStade.returnIdOfStadeWithClubId(idClub);
	
	if (idStadeASupprimer == -1)
	{
		cout << "Le stade du club en question n'a pas ete supprime!\n";
		return -1;
	}
	
	enregistrementStade.supprimerObjet(idStadeASupprimer);
	enregistrementStade.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::enregistrerJoueur(string nomDuClub, Joueur& joueurAEnregistrer)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idOfNouveauJoueur = generateId("joueur");
	
	enregistrementJoueurs.ajoutNouveauJoueur(joueurAEnregistrer, idOfNouveauJoueur, idClub);
	enregistrementJoueurs.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::supprimerJoueur(string nomDuClub, Joueur& joueurASupprimer)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idJoueurASupprimer = enregistrementJoueurs.returnIdOfJoueurWithClubId(idClub, joueurASupprimer.retournePrenom());
	
	if (idJoueurASupprimer == -1)
	{
		cout << "Le joueur du club en question n'a pas ete supprime!\n";
		return -1;
	}
	
	enregistrementJoueurs.supprimerObjet(idJoueurASupprimer);
	enregistrementJoueurs.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::enregistrerContrat(string nomDuClub, ContratEngagement& contratAEnregistrer)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idOfNouveauContrat = generateId("contrat");
	
	enregistrementContrat.ajoutContrat(contratAEnregistrer, idOfNouveauContrat, idClub);
	enregistrementContrat.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::enregistrerRupture(string nomDuClub, Joueur joueurContractant, Rupture& ruptureContrat)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idContratASupprimer = enregistrementContrat.returnIdOfContrat(idClub, joueurContractant.retournePrenom());
	long int idOfNouvelleRupture = generateId("rupture");
	
	if (idContratASupprimer == -1)
	{
		cout << "Ce joueur n'est pas sous contrat!\n";
		return -1;
	}
	
	enregistrementContrat.supprimerObjet(idContratASupprimer);
	enregistrementContrat.miseAJourFichier();
	
	enregistrementRupture.ajoutRupture(ruptureContrat, idOfNouvelleRupture, idClub);
	enregistrementRupture.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::enregistrerTitreClub(string nomDuClub, titre titreAEnregistrer)
{
	long int idOfClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idOfNouveauTitre = generateId("titresClub");
	
	enregistrementTitreClub.ajoutTitreClub(titreAEnregistrer, idOfNouveauTitre, idOfClub);
	
	return 0;
}

int EnregistrementDonnee::supprimerContrat(string nomDuClub, ContratEngagement& contratASupprimer)
{
	long int idClub = enregistrementClub.searchForIdOfClub(nomDuClub);
	long int idContratASupprimer = enregistrementContrat.returnIdOfContrat(idClub, contratASupprimer.retourneJoueurContractant().retournePrenom());
	
	if (idContratASupprimer == -1)
	{
		cout << "Le joueur du club en question n'a pas ete supprime!\n";
		return -1;
	}
	
	enregistrementContrat.supprimerObjet(idContratASupprimer);
	enregistrementContrat.miseAJourFichier();
	
	return 0;
}

int EnregistrementDonnee::lectureRencontres(Rencontre *tableauRencontres, int *nbRencontres)
{
	GestionRencontre rencontreAEcrire;
	
	rencontreAEcrire.lectureRencontres(tableauRencontres, nbRencontres);
	
	return 0;
}

vector<Club> EnregistrementDonnee::lectureDonnees(void)
{
	vector<Club> clubsDansLigueARetourner;
	vector<Club>::iterator itClubDansLigueARetourner = clubsDansLigueARetourner.begin();
	long int idOfClub;
	long int idOfStade;
	long int idOfEntraineur;
	int clubCount = 0;
	Stade stadeDuClub;
	Entraineur entraineurDuClub;
	
	Joueur joueursClub[50];
	unsigned int nbJoueurs;
	
	titre titresClub[20];
	int nbTitres;
		
	while (1)
	{
		Club clubLu;
		
		clubLu = enregistrementClub.lectureClub(clubCount);
		clubCount += 1;
		if (clubLu.retourneNom() == "aucun")
			break;
		
		idOfClub = enregistrementClub.searchForIdOfClub(clubLu.retourneNom());
		if (idOfClub != -1)
		{
			idOfStade = enregistrementStade.returnIdOfStadeWithClubId(idOfClub);
			idOfEntraineur = enregistrementEntraineur.returnIdOfEntraineurWithClubId(idOfClub);
			stadeDuClub = enregistrementStade.lectureStadeAvecId(idOfStade);
			entraineurDuClub = enregistrementEntraineur.lectureEntraineurAvecId(idOfEntraineur);
			enregistrementJoueurs.lectureJoueursAvecId(idOfClub,joueursClub);
			enregistrementTitreClub.lectureTitresAvecClubId(idOfClub, titresClub, &nbTitres);
			
			if (idOfStade != -1)
				clubLu.ajoutStade(stadeDuClub);
			if (idOfEntraineur != -1)
				clubLu.ajoutEntraineur(entraineurDuClub);
		
			
			nbJoueurs = clubLu.retourneNbJoueurs();
			for (int joueurNo = 0; joueurNo < (int) nbJoueurs; joueurNo++)
				clubLu.copieJoueur(joueursClub[joueurNo], joueurNo);	
			
			for (int titreNo = 0; titreNo < (int) nbTitres; titreNo++)
			{
				clubLu.ajoutTitre(titresClub[titreNo]);
			}
			
			itClubDansLigueARetourner = clubsDansLigueARetourner.insert( itClubDansLigueARetourner, clubLu);
		}
	}
		
	return clubsDansLigueARetourner;
}

string EnregistrementDonnee::retourneStatutContractuel(string prenomJoueur, string nomDuClub)
{
	GestionContrats contratARechercher;
	GestionClub clubARechercher;
	string contratRetourne;
	long int idOfContrat;
	long int idOfClub;
	string tmpStr;
	
	idOfClub = clubARechercher.searchForIdOfClub(nomDuClub);
	idOfContrat = contratARechercher.returnIdOfContrat(idOfClub, prenomJoueur);
	
	if (idOfContrat == -1)
		return "Aucun contrat";
	
	contratRetourne = contratARechercher.lectureContratAvecId(idOfContrat);	
	
	return contratRetourne;
}

long int EnregistrementDonnee::generateId(string typeId)
{
   long int idClub, idEntraineur, idJoueur, idStade, idContrat, idRencontre, idRupture, idTitresClub;
   string line, idClubStr, idEntraineurStr, idJoueurStr, idStadeStr, idContratStr, idRencontreStr, idRuptureStr, idTitresClubStr;
   long int idARetourner;
   
   fichierId.close();
   fichierId.open( "Ids.txt", std::fstream::in);
  
   getline(fichierId, line);
   
   std::istringstream iss(line);
   
   getline(iss, idClubStr, ':');
   idClub = atol(idClubStr.c_str());
   getline(iss, idEntraineurStr, ':');
   idEntraineur = atol(idEntraineurStr.c_str());
   getline(iss, idStadeStr, ':');
   idStade = atol(idStadeStr.c_str());
   getline(iss, idJoueurStr, ':');
   idJoueur = atol(idJoueurStr.c_str());
   getline(iss, idContratStr, ':');
   idContrat = atol(idContratStr.c_str());
   getline(iss, idRencontreStr, ':');
   idRencontre = atol(idRencontreStr.c_str());
   getline(iss, idRuptureStr, ':');
   idRupture = atol(idRuptureStr.c_str());
   getline(iss, idTitresClubStr, ':');
   idTitresClub = atol(idTitresClubStr.c_str());
   
  if (fichierId.fail() == true) 
    idClub = idEntraineur = idJoueur = idStade = idContrat = idRencontre = idRupture = idTitresClub = 0;
 
  if (typeId == "club") idARetourner = ++idClub;
  else if (typeId == "entraineur") idARetourner = ++idEntraineur;
  else if (typeId == "stade") idARetourner = ++idStade;
  else if (typeId == "joueur") idARetourner = ++idJoueur;
  else if (typeId == "contrat") idARetourner = ++idContrat;
  else if (typeId == "rencontre") idARetourner = ++idRencontre;
  else if (typeId == "rupture") idARetourner = ++idRupture; 
  else if (typeId == "titresClub") idARetourner = ++idTitresClub;
  else ;
 
  fichierId.close();
  fichierId.open( "Ids.txt", std::fstream::out);
  fichierId << idClub << ':' << idEntraineur << ':' << idStade << ':' << idJoueur << ':' << idContrat << ':'
			<< idRencontre << ':' << idRupture << ':' << idTitresClub;
  fichierId.close(); 
  
  return idARetourner;
}



