/**************************************************************************
  classesSoccer.h -- Classes for the soccer club software
  Écrit par : Pierre-Marc Laforest
  Date: 30/01/17                                        
// A FAIRE : AJOUTER LA LISTE DE TITRE GAGNES
*************************************************************************** */
#ifndef CLASSESSOCCER_H
#define CLASSESSOCCER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date 
{
 private: 
  short unsigned int annee;
  short unsigned int mois;
  short unsigned int jour;
  bool verifieAnnee(const short unsigned int anneeAVerifier);
  bool verifieMois(const short unsigned int moisAVerifier);
  bool verifieJour(const short unsigned int jourAVerifier);
 public:
  Date();
  Date(const short unsigned int anneeAAssigner, const short unsigned moisAAssigner, const short unsigned jourAAssigner);
  Date(string dateFormat1);
  ~Date();
  bool modifAnnee(const short unsigned int nouvelleAnnee);
  bool modifMois(const short unsigned int nouveauMois);
  bool modifJour(const short unsigned int nouveauJour);
  short int retourneAnnee(void);
  short int retourneMois(void);
  short int retourneJour(void);
  string retourneDateFormat1(void);
  Date operator=(Date date2);
}; // classe Date

typedef struct titre
{
  string nomDuTitre;
  Date dateDuChampionnat;
}titre;

class Palmares 
{
 private: 
  vector<titre> titresObtenus;
  vector<titre>::iterator itTitre;
 public:
  Palmares();
  ~Palmares();
  bool   ajoutTitre(const string titreAAjouter, const Date dateDeChampionnat);
  bool   enleverTitre(const string titreAEnlever);
  bool   modifierNomTitre(const string titreAModifier, const string nouveauNomTitre);
  bool   modifierAnneeTitre(const string titreAModifier,  Date nouvelleDate);
  bool   chercherTitre(short unsigned int dateAChercher, string resultatsTrouvee[], short unsigned int *nbResultats);
  short unsigned int retourneNbTitres(void);
  void   operator=(Palmares palmares2);
}; // classe Palmares

class Stade 
{
 private:
  unsigned int capacite;
  string       qualiteTerrain;
  string       nom;
  string       adresse;
 public:
  Stade();
  Stade(const unsigned int capaciteNouveauStade, const string qualiteTerrainNouveauStade, const string nomNouveauStade, const string adresseNouveauStade);
  ~Stade();
  bool modifCapacite(const unsigned int nouvelleCapacite);
  bool modifQualiteTerrain(const string nouvelleQualite);
  bool modifNomStade(const string nouveauNom);
  bool modifAdresse(const string nouvelleAdresse); 
  unsigned int retourneCapacite(void);
  string retourneQualiteTerrain(void);
  string retourneNom(void);
  string retourneAdresse(void);
  void operator=(const Stade stade2);
};

class Personne {
 private:
  int age;
  string nom;
  string prenom;
  string roleDansLequipe;
 public:
  Personne(const string nomNouvellePersonne, const string prenomNouvellePersonne, const int ageNouvellePersonne, const string nouveauRoleDansLequipe);
  Personne(const string nomNouvellePersonne, const string prenomNouvellePersonne);
  Personne();
  ~Personne();
  bool modifNom(const string nouveauNom);
  bool modifPrenom(const string nouveauPrenom);
  bool modifAge(const int nouvelAge);
  bool modifRoleDansLequipe(const string nouveauRole);
  string retourneNom(void);
  string retournePrenom(void);
  int    retourneAge(void);
  string retourneRole(void);
}; // Personne

class Sportif
{	
private:
	float poids;
	float taille;
public:
	Sportif() { poids = 0; taille = 0;}
	Sportif(const float nouveauPoids) { poids = nouveauPoids; taille = 0;}
	Sportif(float nouveauPoids, float nouvelleTaille) { poids = nouveauPoids; taille = nouvelleTaille; } 
	~Sportif() {};
	bool modifPoids(float nouveauPoids) { poids = nouveauPoids; return true;}
	bool modifTaille(float nouvelleTaille) { taille = nouvelleTaille; return true;}
	float retournePoids(void) { return poids;}
	float retourneTaille(void) { return taille;}
};

class Joueur : public Personne, public Sportif
{
 private:
  typedef struct parcours { 
    string nomDuClub;
    Date passageAuClub;
  }parcours;
  string villeDeNaissance;
  vector<parcours> parcoursDuJoueur;
 public: 
  Joueur(const string nomDuJoueur, const string prenomDuJoueur, const float poidsDuJoueur, const string villeDeNaissanceDuJoueur);
  Joueur();
  ~Joueur();
  bool modifVilleDeNaissance(const string nouvelleVille);
  string retourneVilleDeNaissance(void);		
  Joueur& operator=(Joueur joueur2);
};

class Entraineur : public Personne, public Sportif
{ 
 private:
  unsigned int nbTitres;
  string lieuObtentionGrade;
  Palmares listeTitresGagnes;
 public:
  Entraineur(const string nomNouvelEntraineur, const string prenomNouvelEntraineur, const string nouveauLieuObtention);
  Entraineur();
  ~Entraineur();
  bool ajoutLieuObtention(const string nouveauLieu);
  bool ajoutTitre(const string nomDuTitre, const short unsigned int anneeDuTitre, const short unsigned int moisDuTitre, const short unsigned int jourDuTitre);
  bool modifLieuObtention(const string lieuModifie);
  string retourneLieu(void);
  unsigned int retourneNbTitres(void); 
  Palmares retourneListeTitres(void);
  Entraineur& operator=(Entraineur entraineur2);
};

class Arbitre : public Personne
{
private:
	string lieuObtention;
	int experienceArbitrage;
public:
	Arbitre();
	~Arbitre();
	void ajoutLieuObtention(string lieuObtentionAAjouter);
	void ajoutExperience(int experienceAAjouter);
	string retourneLieuObtention(void);
	int retourneExperience(void);
};

class ContratEngagement;
class Rupture;

class Club {
#define NB_JOUEURS_PAR_EQUIPE 50
private:
  unsigned int nbJoueurs;
  string nomDuClub;
  string histoire;
  string couleur;
  Date anneeCreation;
  string ville;
  string adresse;
  Palmares palmaresDeChampionnats;
  Stade stadeDuClub;
  Joueur effectif[NB_JOUEURS_PAR_EQUIPE];
  vector<ContratEngagement> contrats;
  vector<ContratEngagement>::iterator itContrats;
  vector<Rupture> ruptureContrats;
  vector<Rupture>::iterator itRuptures;
  Personne staffTechnique;
  Entraineur entraineurDeLequipe;
 public:
  Club(string nouveauNomDuClub, string nouvelleHistoire, string nouvelleCouleur, string nouvelleVille, string nouvelleAdresse);
  Club();
  ~Club();
  void ajoutNom(const string nouveauNom);
  void ajoutHistoire(const string nouvelleHistoire);
  void ajoutCouleur(const string nouvelleCouleur);
  void ajoutVille(const string nouvelleVille);
  void ajoutAdresse(const string nouvelleAdresse);
  void ajoutJoueur(Joueur nouveauJoueur);
  void copieJoueur(Joueur nouveauJoueur, unsigned int position);
  void ajoutTitre(titre nouveauTitre);
  bool ajoutEntraineur(Entraineur nouvelEntraineur);
  bool ajoutStade(Stade& nouveauStade);
  bool ajoutTrophee(const string nomDuTitre, const short unsigned int anneeDuChampionnat, const short unsigned int moisDuChampionnat, const short unsigned int jourDuChampionnat);
  bool ajoutTitreEntraineur(const string nomDuTitre, const short unsigned int anneeDuChampionnat, const short unsigned int moisDuChampionnat, const short unsigned int jourDuChampionnat);
  bool ajoutContratJoueur(ContratEngagement nouveauContrat);
  bool ajoutRuptureContrat(Rupture& nouvelleRupture);
  bool ajoutNbJoueurs(unsigned int nbJoueurs);
  string retourneNom(void);
  string retourneHistoire(void);
  string retourneCouleur(void);
  string retourneVille(void);
  string retourneAdresse(void);
  Joueur retourneJoueurAvecNo(const unsigned int noJoueur);
  unsigned int retourneNbJoueurs(void);	
  Entraineur retourneEntraineur(void);
  Stade retourneStade(void);
  Palmares retournePalmaresDeChampionnats(void);
  string retourneStatutContrat(string prenomDuJoueurAChercher, string nomDuClub);
  bool enleveJoueurAvecNo(const unsigned int noJoueur);
  Club operator=(Club ClubAEgaler);
}; // classe Club

class Ligue {
 private:
  string nom;
  vector<Club> clubDansLaLigue;
  vector<Club>::iterator itClubDansLaLigue;
 public:
  Ligue();
  ~Ligue();
  void ajoutClub(Club& clubAAjouter);
  void ajoutJoueur(int noClubAModifier, Joueur joueurAAjouter);
  int retourneNbClubs(void);
  Club retourneClubAvecNo(const unsigned int noARechercher);
  Club retourneClubAvecNom(string nomDuClub);
  vector<string> retourneListeNomClubs(void);
  vector<string> retourneListeNomJoueurs(int noClub);
  vector<string> retourneListeNomEntraineurs(void);
  bool supprimeClubAvecNo(int noClubASupprimer);
  void modifClub(const unsigned int noClub, Club nouveauClub);
  Club retourneClubPlusTitre(void);
  void lectureDonneesProgramme(void);
}; //classe Ligue

class Equipe
{
private:
	Club clubEquipe;
	int  nbJoueursPresentsTerrain;
	int  nbGardiens;
	Joueur capitaineEquipe;
public:
	Equipe();
	~Equipe();
	void ajoutClubEquipe(Club& clubAAjouter);
	void ajoutNbJoueursPresentsTerrain(int nbJoueursPresentsAAjouter);
	void ajoutNbGardiens(int nbGardiensAAjouter);
	void ajoutCapitaine(Joueur& capitaineAAjouter);
	Club retourneclubEquipe(void);
	int retourneNbJoueursPresents(void);
	int retourneNbGardiens(void);
	Joueur retourneCapitaine(void);
};

#endif
