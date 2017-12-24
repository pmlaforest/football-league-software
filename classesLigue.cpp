/**************************************************************************
  classesLigue.cpp -- Classes principales de la ligue de soccer
  Écrit par : Pierre-Marc Laforest
  Date: 08/02/17                                        
*************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include "classesLigue.h"
#include "classeIOFichiers.h"

#define ANNEE_PREMIER_CLUB 1850
#define ANNEE_ACTUELLE     2017

using namespace std;

Date::Date(){} 

Date::Date(const short unsigned int anneeAAssigner, const short unsigned int moisAAssigner, const short unsigned jourAAssigner) {

  if ((verifieAnnee(anneeAAssigner) == true) && (verifieMois(moisAAssigner) == true) && (verifieJour(jourAAssigner) == true))
    {
      annee = anneeAAssigner;
      mois = moisAAssigner;
      jour = jourAAssigner;
    }
  else 
    annee = mois = jour = 0;            

} 

Date::Date(string dateFormat1)
{
	string tmpString;
	
	std::istringstream iss(dateFormat1);
	getline(iss, tmpString , '/');
	jour = atol(tmpString.c_str());
	getline(iss, tmpString , '/');
	mois = atol(tmpString.c_str());
	getline(iss, tmpString , '/');
	annee = atol(tmpString.c_str());	
}

Date::~Date() {} 

bool Date::modifAnnee(const short unsigned int nouvelleAnnee)
{
  if (verifieAnnee(nouvelleAnnee) == true)
    {
    annee = nouvelleAnnee;
    return true;
    }
  else
    return false;
} 

bool Date::modifMois(const short unsigned int nouveauMois)
{
  if (verifieMois(nouveauMois) == true)
    {
      mois = nouveauMois;
      return true;
    }
  else
    return false;
} 

bool Date::modifJour(const short unsigned int nouveauJour)
{
  if (verifieJour(nouveauJour) == true)
    {
      jour = nouveauJour;
      return true;
    }
  else
    return false;
}

short int Date::retourneAnnee(void) { return annee; }
short int Date::retourneMois(void) { return mois; } 
short int Date::retourneJour(void) { return jour; }
string Date::retourneDateFormat1(void) { return to_string(jour) + '/' + to_string(mois) + '/' + to_string(annee); }

bool Date::verifieAnnee(const short unsigned int anneeAVerifier)
{
  if (anneeAVerifier < ANNEE_PREMIER_CLUB || anneeAVerifier > ANNEE_ACTUELLE)
    return false;
  return true;
}

bool Date::verifieMois(const short unsigned int moisAVerifier)
{
  if (moisAVerifier < 1 || moisAVerifier > 12)
    return false;
  return true;
} 

bool Date::verifieJour(const short unsigned int jourAVerifier)
{
  if (jourAVerifier < 1 || jourAVerifier > 31)
    return false;
  return true;
}

Date Date::operator=(Date date2)
{
	annee = date2.annee;
	mois = date2.mois;
	jour = date2.jour;
	
	return (*this);
}

Palmares::Palmares()
{
  titresObtenus.resize(0);
  titresObtenus.clear();
  itTitre = titresObtenus.begin();
}
Palmares::~Palmares(){ }

short unsigned int Palmares::retourneNbTitres(void) { return titresObtenus.size();  }

bool Palmares::ajoutTitre(const string titreAAjouter, Date dateDuTitre)
{
  titre titreTmp;
  
  titreTmp.nomDuTitre = titreAAjouter;
  titreTmp.dateDuChampionnat = dateDuTitre;
  
  
  itTitre = titresObtenus.begin();
  itTitre = titresObtenus.insert(itTitre, titreTmp);
 
 return true;
}

bool Palmares::enleverTitre(const string titreAEnlever)
{
   for (unsigned int i = 0; i < titresObtenus.size(); i++)
   {
	  if (titresObtenus.at(i).nomDuTitre == titreAEnlever)
	  {
		  titresObtenus.erase(titresObtenus.begin() + i);
		  return true;
	  }
   }
	return false;
}

bool Palmares::modifierNomTitre(const string titreAModifier, const string nouveauNomTitre)
{
     for (unsigned int i = 0; i < titresObtenus.size(); i++)
	 {
	  if (titresObtenus.at(i).nomDuTitre == titreAModifier)
	  {
		  titresObtenus.at(i).nomDuTitre = nouveauNomTitre;
		  return true;
	  }
	 }
	return false;
}

bool Palmares::modifierAnneeTitre(const string titreAModifier, Date nouvelleDate)
{
     for (unsigned int i = 0; i < titresObtenus.size(); i++)
	 {
	  if (titresObtenus.at(i).nomDuTitre == titreAModifier)
	  {
		  titresObtenus.at(i).dateDuChampionnat = nouvelleDate;
		  return true;
	  }
	 }
  return false;
}

bool Palmares::chercherTitre(short unsigned int dateAChercher, string resultatsTrouvees[],short unsigned int *nbResultats)
{
  *nbResultats = 0;

  for (unsigned int i = 0; i < titresObtenus.size(); i++)
	{
	  if (titresObtenus.at(i).dateDuChampionnat.retourneAnnee() == dateAChercher)
		  resultatsTrouvees[(*nbResultats)++] = titresObtenus.at(i).nomDuTitre;
	  else if (titresObtenus.at(i).dateDuChampionnat.retourneMois() == dateAChercher)
		  resultatsTrouvees[(*nbResultats)++] = titresObtenus.at(i).nomDuTitre;
	  else if (titresObtenus.at(i).dateDuChampionnat.retourneJour() == dateAChercher)
		  resultatsTrouvees[(*nbResultats)++] = titresObtenus.at(i).nomDuTitre;
	  else
		  continue;
	}
 
  if (*nbResultats == 0)
    return false;

  return true;
} 


void Palmares::operator=(Palmares palmares2)
{
	titresObtenus = palmares2.titresObtenus;
	itTitre = palmares2.itTitre;
} 

Stade::Stade()
{
  capacite = 0;
  qualiteTerrain = "aucun";
  nom = "aucun";
  adresse = "aucun";
	
} 

Stade::Stade(const unsigned int capaciteNouveauStade, const string qualiteNouveauStade, const string nomNouveauStade, const string adresseNouveauStade)
{
  capacite       = capaciteNouveauStade;
  qualiteTerrain = qualiteNouveauStade;
  nom            = nomNouveauStade;
  adresse        = adresseNouveauStade;
} 

Stade::~Stade() { }

bool Stade::modifCapacite(const unsigned int nouvelleCapacite) { capacite = nouvelleCapacite; return true; } 
bool Stade::modifQualiteTerrain(const string nouvelleQualite){ qualiteTerrain = nouvelleQualite; return true; } 
bool Stade::modifNomStade(const string nouveauNom) { nom = nouveauNom; return true; }
bool Stade::modifAdresse(const string nouvelleAdresse) { adresse = nouvelleAdresse; return true; } 

unsigned int Stade::retourneCapacite(void){ return capacite; } 
string Stade::retourneQualiteTerrain(void){ return qualiteTerrain; } 
string Stade::retourneNom(void){ return nom;} 
string Stade::retourneAdresse(void){return adresse; } 

void Stade::operator=(const Stade stade2)
{
  capacite = stade2.capacite;
  qualiteTerrain = stade2.qualiteTerrain;
  nom = stade2.nom;
  adresse = stade2.adresse;
} 

Joueur::Joueur(const string nomDuJoueur, const string prenomDuJoueur, const float poidsDuJoueur, const string villeDeNaissanceDuJoueur) : Personne(nomDuJoueur, prenomDuJoueur), Sportif(poidsDuJoueur)
{
  villeDeNaissance = villeDeNaissanceDuJoueur;
}

Joueur::Joueur() : Personne() , Sportif()
{ 
	villeDeNaissance = "non definie";
} 

Joueur::~Joueur() {}

bool Joueur::modifVilleDeNaissance(const string nouvelleVille) { villeDeNaissance = nouvelleVille; return true; }
string Joueur::retourneVilleDeNaissance(void) { return villeDeNaissance; }

Joueur& Joueur::operator=(Joueur joueur2)
{
  (*this).modifNom(joueur2.retourneNom());
  (*this).modifPrenom(joueur2.retournePrenom());
  (*this).modifPoids(joueur2.retournePoids());
  villeDeNaissance = joueur2.villeDeNaissance;
  
  return (*this);
} 

Personne::Personne(const string nomNouvellePersonne , const string prenomNouvellePersonne, const int ageNouvellePersonne, const string nouveauRoleDansLequipe)
{
  nom = nomNouvellePersonne;
  prenom = prenomNouvellePersonne;
  age = ageNouvellePersonne;
  roleDansLequipe = nouveauRoleDansLequipe;
} 

Personne::Personne(const string nomNouvellePersonne , const string prenomNouvellePersonne)
{
  nom = nomNouvellePersonne;
  prenom = prenomNouvellePersonne;
  age = 0;
  roleDansLequipe = "aucun";
} 

Personne::Personne() 
{ 
	nom = "aucun";
	prenom = "aucun";
}
 
Personne::~Personne() {} 
bool Personne::modifNom(const string nouveauNom) { nom = nouveauNom; return true; }
bool Personne::modifPrenom(const string nouveauPrenom) { prenom = nouveauPrenom; return true; } 
bool Personne::modifAge(const int nouvelAge) { age = nouvelAge; return true; }
bool Personne::modifRoleDansLequipe(const string nouveauRole) { roleDansLequipe = nouveauRole; return true; } 

string Personne::retourneNom(void){ return nom; } 
string Personne::retournePrenom(void) { return prenom; } 
int    Personne::retourneAge(void){ return age; } 
string Personne::retourneRole(void){ return roleDansLequipe; } 

Entraineur::Entraineur() : Personne(), Sportif()
{ 
	nbTitres = 0;
	lieuObtentionGrade = "aucun";	
} 

Entraineur::Entraineur(const string nomNouvelEntraineur, const string prenomNouvelEntraineur, const string nouveauLieuObtention) : Personne(nomNouvelEntraineur, prenomNouvelEntraineur), Sportif()
{
  lieuObtentionGrade = nouveauLieuObtention;
  nbTitres = 0; 
}

Entraineur::~Entraineur() {} 

bool Entraineur::modifLieuObtention(const string lieuModifie) { lieuObtentionGrade = lieuModifie; return true; } 
string Entraineur::retourneLieu(void) { return lieuObtentionGrade; } 
Palmares Entraineur::retourneListeTitres(void) { return listeTitresGagnes; } 
unsigned int Entraineur::retourneNbTitres(void) { return nbTitres; }

bool Entraineur::ajoutTitre(const string nomDuTitre, const short unsigned int anneeDuTitre, const short unsigned int moisDuTitre, const short unsigned int jourDuTitre) 
{
   Date nouvelleDate = Date(anneeDuTitre, moisDuTitre, jourDuTitre);
   listeTitresGagnes.ajoutTitre(nomDuTitre, nouvelleDate);
   nbTitres++;
  return true;
} 

Entraineur& Entraineur::operator=(Entraineur entraineur2)
{
  (*this).modifNom(entraineur2.retourneNom());
  (*this).modifPrenom(entraineur2.retournePrenom());
  (*this).modifPoids(entraineur2.retournePoids());
  lieuObtentionGrade = entraineur2.lieuObtentionGrade;
  nbTitres = entraineur2.nbTitres;
  listeTitresGagnes = entraineur2.listeTitresGagnes;
  
  return (*this);
}

Arbitre::Arbitre() : Personne()
{
	lieuObtention = "Aucun";
	experienceArbitrage = 0;
}
Arbitre::~Arbitre() {}

void Arbitre::ajoutLieuObtention(string lieuObtentionAAjouter) { lieuObtention = lieuObtentionAAjouter; }
void Arbitre::ajoutExperience(int experienceAAjouter) { experienceArbitrage = experienceAAjouter; }

string Arbitre::retourneLieuObtention(void) { return lieuObtention; }
int Arbitre::retourneExperience(void) { return experienceArbitrage;}

Club::Club ()
{
  nomDuClub = "aucun";
  couleur   = "aucune";
  ville     = "aucune";
  adresse   = "aucune";
  histoire  = "aucune";
  nbJoueurs = 0;

} 

Club::Club(string nouveauNomDuClub, string nouvelleHistoire, string nouvelleCouleur, string nouvelleVille, string nouvelleAdresse) 
{
  nomDuClub = nouveauNomDuClub;
  histoire  = nouvelleHistoire;
  couleur   = nouvelleCouleur;
  ville     = nouvelleVille;
  adresse   = nouvelleAdresse;
  nbJoueurs = 0;
  

}

Club::~Club() { } 

void Club::ajoutNom(const string nouveauNom) { nomDuClub  = nouveauNom; } 
void Club::ajoutHistoire(const string nouvelleHistoire) { histoire = nouvelleHistoire; } 
void Club::ajoutCouleur(const string nouvelleCouleur) { couleur = nouvelleCouleur; }
void Club::ajoutVille(const string nouvelleVille) { ville = nouvelleVille; } 
bool Club::ajoutStade(Stade& nouveauStade) { stadeDuClub = nouveauStade; return 0;};
void Club::ajoutAdresse(const string nouvelleAdresse) { adresse = nouvelleAdresse; } 
bool Club::ajoutEntraineur(Entraineur nouvelEntraineur) {  entraineurDeLequipe = nouvelEntraineur;  return true; } 
bool Club::ajoutNbJoueurs(unsigned int nouveauNbJoueurs) { nbJoueurs = nouveauNbJoueurs; return true; }

void Club::ajoutJoueur(Joueur nouveauJoueur)
{
  effectif[nbJoueurs++] = nouveauJoueur;
  return;
} 

void Club::copieJoueur(Joueur nouveauJoueur, unsigned int position) { effectif[position] = nouveauJoueur; }
void Club::ajoutTitre(titre nouveauTitre) { palmaresDeChampionnats.ajoutTitre(nouveauTitre.nomDuTitre, nouveauTitre.dateDuChampionnat);}

bool Club::ajoutTrophee(const string nouveauTitre, const short unsigned int anneeDuChampionnat, const short unsigned int moisDuChampionnat, const short unsigned int jourDuChampionnat)
{ 
 Date nouvelleDate = Date(anneeDuChampionnat, moisDuChampionnat, jourDuChampionnat);
 palmaresDeChampionnats.ajoutTitre(nouveauTitre, nouvelleDate);

  return true;
} 

bool Club::ajoutTitreEntraineur(const string nomDuTitre, const short unsigned int anneeDuChampionnat, const short unsigned int moisDuChampionnat, const short unsigned int jourDuChampionnat)
{
  entraineurDeLequipe.ajoutTitre(nomDuTitre, anneeDuChampionnat, moisDuChampionnat, jourDuChampionnat);
  return true;
} 
 bool Club::ajoutContratJoueur(ContratEngagement nouveauContrat) 
{
	itContrats = contrats.begin();
	contrats.emplace(itContrats, nouveauContrat);
	return true;
}

bool Club::ajoutRuptureContrat(Rupture& nouvelleRupture)
{	
	itRuptures =  ruptureContrats.begin();
	ruptureContrats.emplace(itRuptures, nouvelleRupture);

	return true;
}

string Club::retourneNom(void) { return nomDuClub; } 
string Club::retourneHistoire(void) { return histoire; } 
string Club::retourneCouleur(void) { return couleur; } 
string Club::retourneVille(void) { return ville; }
string Club::retourneAdresse(void) { return adresse; } 
Stade Club::retourneStade(void){ return stadeDuClub; }
Palmares Club::retournePalmaresDeChampionnats(void) { return palmaresDeChampionnats; }
unsigned int Club::retourneNbJoueurs(void) { return nbJoueurs; } 
Entraineur Club::retourneEntraineur(void) { return entraineurDeLequipe; }
Joueur Club::retourneJoueurAvecNo(const unsigned int noJoueur) { return effectif[noJoueur - 1]; }  

string Club::retourneStatutContrat(string prenomDuJoueurAChercher, string nomDuClub)
{
	EnregistrementDonnee donneesAEnregistrer;
	
	return donneesAEnregistrer.retourneStatutContractuel(prenomDuJoueurAChercher, nomDuClub);	
}

Club Club::operator=(Club clubAEgaler)
{
  
  nomDuClub = clubAEgaler.nomDuClub;
  histoire  = clubAEgaler.histoire;
  couleur   = clubAEgaler.couleur;
  ville     = clubAEgaler.ville;
  adresse   = clubAEgaler.adresse;
  nbJoueurs = clubAEgaler.nbJoueurs;
  entraineurDeLequipe = clubAEgaler.entraineurDeLequipe;
  stadeDuClub = clubAEgaler.stadeDuClub;
  palmaresDeChampionnats = clubAEgaler.palmaresDeChampionnats;
  for (int noJoueur = 0; noJoueur < (int) clubAEgaler.nbJoueurs; noJoueur++)
    effectif[noJoueur] = clubAEgaler.effectif[noJoueur]; 

  return (*this);
} 

bool Club::enleveJoueurAvecNo(const unsigned int noJoueur)
{
  unsigned int indexJoueur = noJoueur - 1;
  Joueur joueurASupprimer;

  if (indexJoueur < 0 || indexJoueur > nbJoueurs)
    {
      cout << "Erreur aucun joueur ne correspond a ce numero.\n";
      return false;
    }
	
  else if (indexJoueur == NB_JOUEURS_PAR_EQUIPE - 1) return false;
  else
  {
	for (unsigned int joueurAEnlever = indexJoueur; joueurAEnlever < (nbJoueurs - 1); joueurAEnlever++)
      effectif[joueurAEnlever] = effectif[joueurAEnlever + 1];
  }
  
  nbJoueurs--;
  return true;
} 


Ligue::Ligue() 
{ 
    clubDansLaLigue.resize(0);
	clubDansLaLigue.clear();
	itClubDansLaLigue = clubDansLaLigue.begin();
	nom = "aucun";
} 
Ligue::~Ligue() { } 

int Ligue::retourneNbClubs(void) { return clubDansLaLigue.size(); }

void Ligue::ajoutClub(Club& clubAAjouter)
{	
	itClubDansLaLigue = clubDansLaLigue.begin();
	clubDansLaLigue.emplace(itClubDansLaLigue, clubAAjouter);
	return;
}

bool Ligue::supprimeClubAvecNo(int noClubASupprimer)
{
	clubDansLaLigue.erase(clubDansLaLigue.begin()+noClubASupprimer);
	
	return 0;
}

void Ligue::modifClub(const unsigned int noClub, Club nouveauClub)  {  clubDansLaLigue[noClub - 1] = nouveauClub;  return;  }

vector<string> Ligue::retourneListeNomClubs(void)
{
	vector<string> nomsARetourner;
	vector<string>::iterator itClub = nomsARetourner.begin();
	
	for (std::vector<Club>::iterator it = clubDansLaLigue.begin(); it != clubDansLaLigue.end(); ++it)
	{
		itClub = nomsARetourner.insert(itClub, (*it).retourneNom());
	}
	
	return nomsARetourner;
}

vector<string> Ligue::retourneListeNomJoueurs(int noClub)
 {
	vector<string> nomsARetourner;
	vector<string>::iterator itJoueur = nomsARetourner.begin();
	string tmpStr;
	Club clubTmp;
	
	clubTmp = retourneClubAvecNo(noClub);
	int nbJoueurs = clubTmp.retourneNbJoueurs();
	
	for (int noJoueur = 0; noJoueur < nbJoueurs; noJoueur++)
	{
		tmpStr = clubDansLaLigue[noClub - 1].retourneJoueurAvecNo(noJoueur + 1).retournePrenom() + " " 
				 + clubDansLaLigue[noClub - 1].retourneJoueurAvecNo(noJoueur + 1).retourneNom();
		itJoueur = nomsARetourner.insert(itJoueur, tmpStr);
	}
	return nomsARetourner; 	
}

vector<string> Ligue::retourneListeNomEntraineurs(void)
{
	vector<string> nomsARetourner;
	vector<string>::iterator itEntraineur = nomsARetourner.begin();
	string tmpStr;
	Entraineur entraineurTmp;
	
	for (std::vector<Club>::iterator it = clubDansLaLigue.begin() ; it != clubDansLaLigue.end(); ++it)
	{
		entraineurTmp = (*it).retourneEntraineur();	
		tmpStr = entraineurTmp.retournePrenom() + " " + entraineurTmp.retourneNom();
		itEntraineur = nomsARetourner.insert(itEntraineur, tmpStr);
	}
	
	return nomsARetourner;
}

Club Ligue::retourneClubAvecNo(const unsigned int noARechercher)
{
  if (noARechercher <= 0 )
    {
	  Club clubARetourner;	
      cout << "Impossible aucun club ne correspond!" << endl;
      return clubARetourner;
    }

	return clubDansLaLigue[noARechercher - 1];	
} 


Club Ligue::retourneClubAvecNom(string nomDuClub)
{
	Club clubARetourner;
	
  for (std::vector<Club>::iterator it = clubDansLaLigue.begin() ; it != clubDansLaLigue.end(); ++it)
  {
		if ((*it).retourneNom() == nomDuClub)
			return (*it);
  }
	return clubARetourner;
} 


Club Ligue::retourneClubPlusTitre(void)
{
	Club clubPlusTitre;

	// Ne gere pas le cas ou plusieurs club ont le meme nombre de trophees
	
	for (itClubDansLaLigue = clubDansLaLigue.begin(); itClubDansLaLigue < clubDansLaLigue.end(); itClubDansLaLigue++)
	{
		if (itClubDansLaLigue->retournePalmaresDeChampionnats().retourneNbTitres() > clubPlusTitre.retournePalmaresDeChampionnats().retourneNbTitres())
		{
			clubPlusTitre = *itClubDansLaLigue;
		}
	}
	
	return clubPlusTitre; 
}	

void Ligue::lectureDonneesProgramme(void)
{
	EnregistrementDonnee clubsEnregistres;
	
	clubDansLaLigue = clubsEnregistres.lectureDonnees();
	
	return;
}




