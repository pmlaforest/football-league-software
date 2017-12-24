/**************************************************************************
  classesEcran.h -- classes ecran pour le logiciel du club de soccer
  Écrit par : Pierre-Marc Laforest
  Date: 30/01/17                                        
// A FAIRE : AJOUTER LA LISTE DE TITRE GAGNES
*************************************************************************** */
#include <iostream>
#include <string>
#include <vector>

#ifndef CLASSESECRAN_H
#define CLASSESECRAN_H

class MenuLigue {
 private:
  int optionChoisie;
 public:
  MenuLigue();
  ~MenuLigue();
  void affichage(void);
  void appelleFonctionChoisie(void);
  bool ajoutClub(void);
  bool enleverClub(void);
  void afficheListeClubs(void);
  int  retourneOptionChoisie(void);
}; //classe MenuLigue

class MenuClub 
{
 private:
  int optionChoisie;
 public:
  MenuClub();
  ~MenuClub();
  void affichage(void);
  void choixOptions(void);
  bool ajoutEntraineur(void);
  bool modifInfosClub(void);
  bool enleveJoueurClub(void);
  bool ajoutJoueurClub(void);
  void afficheListeJoueurs(void);
  void afficheInfosClub(void);
  int  retourneOptionChoisie(void);
  void appelleFonctionChoisie(void);
  bool modifEntraineur(void);
  bool modifStade(void);
  bool ajoutStade(void);
  bool modifStaffTechnique(void);
  bool ajoutTrophee(void);
  bool ajoutTitreEntraineur(void);				
  void affichageRencontres(void);
  void affichageResultatsMatch(void);
};

class MenuJoueur
{
private:
	int optionChoisie;
public:
	MenuJoueur();
	~MenuJoueur();
	void affichage(void);
	void appelleFonctionChoisie(void);
	bool negocierNouveauContrat(void);
	bool afficheStatutContractuel(void);
	bool ruptureContrat(void);
	int  retourneOptionChoisie(void);
};

class MenuEntraineur
{
private:
	int optionChoisie;
public:
	MenuEntraineur();
	~MenuEntraineur();
	void affichage(void);
	void appelleFonctionChoisie(void);
	void afficheInfosEntraineur(void);
	bool modifInfosEntraineur(void);
	bool negocierNouveauContrat(void);
	void afficheStatutContractuel(void);
	bool ruptureContrat(void);
	bool ajoutTrophee(void);
	bool modifierPalmares(void);
	int retourneOptionChoisie(void);
};


class MenuCalendrier
{
private:
	int optionChoisie;
public:
	MenuCalendrier();
	~MenuCalendrier();
	void affichage(void);
	void appelleFonctionChoisie(void);
	int  retourneOptionChoisie(void);
	bool ajoutRencontreCalendrier(void);
	bool enleveRencontreCalendrier(void);
	void afficheRencontresCalendrier(void);
	void afficheResultatsMatch(void);
	void  simulerUnMatch(void);  
};

class MenuTrophee
{
private:
	int optionChoisie;
public:
	MenuTrophee();
	~MenuTrophee();
	void affichage(void);
	void appelleFonctionChoisie(void);
	int  retourneOptionChoisie(void); 
	void afficheClubPlusTitre(void);
	void afficheEntraineurPlusTitre(void);
};

class MenuPrincipal
{
private:
	int menuLigueOptionChoisie;
	int menuClubOptionChoisie;
	int menuJoueurOptionChoisie;
	int menuPrincipalOptionChoisie;
	int menuCalendrierOptionChoisie;
	int menuEntraineurOptionChoisie;
	int menuTropheeOptionChoisie;
	MenuLigue menuLigue;
	MenuClub  menuClub;
	MenuJoueur menuJoueur;
	MenuCalendrier menuCalendrier;
	MenuEntraineur menuEntraineur;
	MenuTrophee menuTrophee;
public:
	MenuPrincipal();
	~MenuPrincipal();
	void affichage();
	void appelleFonctionChoisie(void);
	void appelleMenuLigue(void);
	void appelleMenuClub(void);
	void appelleMenuJoueur(void);
	void appelleMenuEntraineur(void);
	void simulationAchatVenteJoueur(void);
	bool selectionClub(void);
	bool selectionJoueur(void);
	bool selectionEntraineur(void);
	int  retourneOptionChoisie(void);
	int  retourneLigueOptionChoisie(void);
	int retourneClubOptionChoisie(void);
	int retourneJoueurOptionChoisie(void);
	int retourneCalendrierOptionChoisie(void);
	int retourneEntraineurOptionChoisie(void);
	int retourneTropheeOptionChoisie(void);
};

#endif
