/**************************************************************************
  classesEcran.cpp -- classes d'affichage pour le logiciel de gestion du club de soccer
  Écrit par : Pierre-Marc Laforest
  Date: 30/01/17                                        
*************************************************************************** */

#include <iostream>
#include <climits>
#include <stdio.h>
#include <string>
#include <vector>
#include "classesLigue.h"
#include "classesEcran.h"
#include "classesCalendrierMatchs.h"
#include "ObjetsSelectionnes.h"

ObjetsProgramme objetsEnMemoire; 

using namespace std;

MenuPrincipal::MenuPrincipal()
{ 
	menuPrincipalOptionChoisie = 0;
	menuLigueOptionChoisie = 0;
	menuClubOptionChoisie = 0;
	menuJoueurOptionChoisie = 0;
	menuCalendrierOptionChoisie = 0;
	menuEntraineurOptionChoisie = 0;
	menuTropheeOptionChoisie = 0;
}

MenuPrincipal::~MenuPrincipal() { }

int  MenuPrincipal::retourneOptionChoisie(void) { return menuPrincipalOptionChoisie; }
int  MenuPrincipal::retourneLigueOptionChoisie(void) { return menuLigueOptionChoisie; }
int  MenuPrincipal::retourneClubOptionChoisie(void) { return menuClubOptionChoisie; }
int  MenuPrincipal::retourneJoueurOptionChoisie(void) { return menuJoueurOptionChoisie; }
int  MenuPrincipal::retourneCalendrierOptionChoisie(void) { return menuCalendrierOptionChoisie; }
int  MenuPrincipal::retourneEntraineurOptionChoisie(void) { return menuEntraineurOptionChoisie; }
int  MenuPrincipal::retourneTropheeOptionChoisie(void) { return menuTropheeOptionChoisie; }

void MenuPrincipal::affichage(void)
{		
  cout << "*******************************\n";
  cout << "*        Menu Principal       *\n";
  cout << "*******************************\n\n";
  cout << "1) Aller au menu de la ligue\n";
  cout << "2) Aller au menu des clubs\n";
  cout << "3) Aller au menu des joueurs\n";
  cout << "4) Aller au menu des entraineurs\n";
  cout << "5) Aller au calendrier de la ligue\n";
  cout << "6) Aller au menu des trophees\n";
  cout << "7) Simuler un achat/vente dun joueur\n";
  cout << "8) Quitter\n\n";
  
  cout << "Choisissez une option: ";
  cin >> menuPrincipalOptionChoisie;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  cout << '\n';
  return;
}

void MenuPrincipal::appelleFonctionChoisie(void)
{
	switch(menuPrincipalOptionChoisie)
	{
		case 1: 
		 do 
		{
			menuLigue.affichage();
			menuLigue.appelleFonctionChoisie();
			menuLigueOptionChoisie = menuLigue.retourneOptionChoisie();
		} while (menuLigueOptionChoisie != 4 && menuLigueOptionChoisie != 5);
		break;
		
		case 2:
		  do 
		{
			if (!objetsEnMemoire.testClubSelectionne())
			{
				if (!selectionClub()) break;
			}
			menuClub.affichage();	
			menuClub.appelleFonctionChoisie();
			menuClubOptionChoisie = menuClub.retourneOptionChoisie();
		} while (menuClubOptionChoisie != 13 && menuClubOptionChoisie != 14); 
		break;
		
		case 3:
		  do
		{
			if (!objetsEnMemoire.testClubSelectionne())
			{
				if (!selectionClub()) break;
			}
			if (!objetsEnMemoire.testJoueurSelectionne())
			{
				if (!selectionJoueur()) break;
			}
			menuJoueur.affichage();
			menuJoueur.appelleFonctionChoisie();
			menuJoueurOptionChoisie = menuJoueur.retourneOptionChoisie();
		} while( menuJoueurOptionChoisie != 4 && menuJoueurOptionChoisie != 5); 
		break;
		
		case 4:
			do 
		{
			if (!objetsEnMemoire.testEntraineurSelectionne())
			{
				if (!selectionEntraineur()) break;
			}
			menuEntraineur.affichage();
			menuEntraineur.appelleFonctionChoisie();
			menuEntraineurOptionChoisie = menuEntraineur.retourneOptionChoisie();
		}	while( menuEntraineurOptionChoisie != 8 && menuEntraineurOptionChoisie != 9);
		break;
		case 5:
			do
			{
			menuCalendrier.affichage();
			menuCalendrier.appelleFonctionChoisie();
			menuCalendrierOptionChoisie = menuCalendrier.retourneOptionChoisie();
			} while( menuCalendrierOptionChoisie != 6 && menuCalendrierOptionChoisie != 7);					
		break;
		case 6: 
			do
			{
			menuTrophee.affichage();
			menuTrophee.appelleFonctionChoisie();
			menuTropheeOptionChoisie = menuTrophee.retourneOptionChoisie();
			} while (menuTropheeOptionChoisie != 3 && menuTropheeOptionChoisie != 4);
		break;
		case 7: 
			if (!objetsEnMemoire.testClubSelectionne())
			{
				if (!selectionClub()) break;
			}
			if (!objetsEnMemoire.testJoueurSelectionne())
			{
				if (!selectionJoueur()) break;
			}
			simulationAchatVenteJoueur();
		break;
		case 8: break;
		default: cout << "Cette option ne fait pas partie des choix !\n";
	}
	return;
}

bool MenuPrincipal::selectionClub(void) 
{

  vector<string> listeClubs;
  vector<string>::iterator it;
  int noClub = 0;
  int clubChoisi;
  
  listeClubs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomClubs();
  it = listeClubs.end();
  
  cout << "Choix d'un club\n";
  cout << "***************\n";
  
  if (!listeClubs.empty())
  {
	for (it--; it >= listeClubs.begin(); it--)
		std::cout << ++noClub << ") " << *it << '\n';
  }
  else
  {
	cout << "Actuellement, il n'y a aucun club dans la ligue\n\n";
	cin.ignore(INT_MAX, '\n');
	return false;
  }
    
  do
  {
  cout << "\nChoisissez un club (0 pour retourner au menu): ";
  cin >> clubChoisi;
  cout << '\n';
	if (clubChoisi > noClub || clubChoisi < 0)
		cout << "Aucun numero de club ne correspond!\n";
  }while(clubChoisi > noClub || clubChoisi < 0);
  
  
  if (clubChoisi == 0)
    return false;
  
  Club clubAModifier;
  clubAModifier = objetsEnMemoire.retourneLigueSelectionnee().retourneClubAvecNo(clubChoisi);
  objetsEnMemoire.modifClubSelectionne(clubAModifier, clubChoisi);
  
  return true;
} 

bool MenuPrincipal::selectionJoueur(void)
{
  int noJoueur;
  int listeNoJoueur = 0;
  vector<string> listeJoueurs;
  vector<string>::iterator itJoueur;
	
  cout << "Selection Joueur\n";
  cout << "****************\n";
  
  if (objetsEnMemoire.retourneClubSelectionne().retourneNbJoueurs() == 0)
    {
      cout << "Actuellement, il n'y a aucun joueur dans lequipe!\n\n";
	  cin.ignore(INT_MAX, '\n');
      return false;
    }

  listeJoueurs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomJoueurs(objetsEnMemoire.retourneNoClubChoisi());
  itJoueur = listeJoueurs.end();
  
  if(!listeJoueurs.empty())
  {
  for (itJoueur--; itJoueur >= listeJoueurs.begin(); itJoueur--)
	std::cout << ++listeNoJoueur << ") " << *itJoueur << '\n';
  }
  else
  {
	 cout << "Actuellement il n'y aucun joueur dans la ligue\n";
	 cin.ignore(INT_MAX, '\n');
	 return false;
  }
  
  do {
	cout << "\nChoisissez un joueur (0 pour retourner au menu): ";
	cin >> noJoueur;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << '\n';
	if (noJoueur > listeNoJoueur || noJoueur < 0)
		cout << "Aucun joueur ne correspond a ce numero\n";
  } while (noJoueur > listeNoJoueur || noJoueur < 0);
  
  if (noJoueur == 0)
	return false;

  Joueur joueurAModifier;
  joueurAModifier = objetsEnMemoire.retourneClubSelectionne().retourneJoueurAvecNo(noJoueur);
  objetsEnMemoire.modifJoueurSelectionne(joueurAModifier);
   
   return true;

} 

bool MenuPrincipal::selectionEntraineur(void)
{
  int noEntraineur;
  int listeNoEntraineur = 0;
  vector<string> listeEntraineurs;
  vector<string>::iterator itEntraineur;
	
  cout << "Selection Entraineur\n";
  cout << "********************\n";
  
  if (objetsEnMemoire.retourneLigueSelectionnee().retourneNbClubs() == 0)
    {
      cout << "Actuellement, il n'y a aucun entraineur dans la ligue!\n\n";
	  cin.ignore(INT_MAX, '\n');
      return false;
    }

  listeEntraineurs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomEntraineurs();
  itEntraineur = listeEntraineurs.end();
  
   if(!listeEntraineurs.empty())
  {
	for (itEntraineur--; itEntraineur >= listeEntraineurs.begin(); itEntraineur--)
		std::cout << ++listeNoEntraineur << ") " << *itEntraineur << '\n';
  }
  else
  {
	 cout << "Actuellement il n'y aucun entraineur dans la ligue\n";
	 cin.ignore(INT_MAX, '\n');
	 return false;
  }
  
  do
  {
  cout << "\nChoisissez un entraineur (0 pour retourner au menu): ";
  cin >> noEntraineur;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << '\n';
	if (noEntraineur > listeNoEntraineur || noEntraineur < 0)
		cout << "Aucun entraineur ne correspond a ce numero!\n";
  }while(noEntraineur > listeNoEntraineur || noEntraineur < 0);
  
  if (noEntraineur == 0)
	return false;

   Entraineur entraineurAModifier;
   entraineurAModifier = objetsEnMemoire.retourneLigueSelectionnee().retourneClubAvecNo(noEntraineur).retourneEntraineur();
   objetsEnMemoire.modifEntraineurSelectionne(entraineurAModifier);

   
   return true;
 
} 

void MenuPrincipal::simulationAchatVenteJoueur(void)
{
   char achatOuVente;
	
  cout << "Simulation dun achat/vente dun joueur\n";
  cout << "*************************************\n";

  cout << "Souhaitez-vous simuler un achat ou une vente ?\n\n";
  cout << "Entrez a pour un achat ou v pour une vente: ";

  cin >> achatOuVente;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  cout << "\n\n";
  
  if (achatOuVente == 'a')
  {
	  float montantAchat;
	  float montantMax;
	  float dureeMax;
	  float margeAcceptable;
	  
	 cout << "Entrer le montant de depart que vous etes pret a payer: ";
	 cin >> montantAchat;
	 cout << "Entrer le montant maximum que vous etes pret a payer: ";
	 cin >> montantMax;
	 cout << "Entrer la duree de la simulation: ";
	 cin >> dureeMax;
	 cout << "Entrer la marge de jeu acceptable: ";
	 cin >> margeAcceptable;
	  
	  objetsEnMemoire.simulationAchat(montantAchat, montantMax, dureeMax, margeAcceptable);
	  
  }
  else if (achatOuVente == 'v')
  {
	 float montantAchat;
	 float montantMin;
	  float dureeMax;
	  float margeAcceptable;
	  
	 cout << "Entrer le montant de depart que vous etes pret a accepter: ";
	 cin >> montantAchat;
	 cout << "Entrer le montant minimum que vous etes pret a accepter: ";
	 cin >> montantMin;
	 cout << "Entrer la duree de la simulation: ";
	 cin >> dureeMax;
	 cout << "Entrer la marge de jeu acceptable: ";
	 cin >> margeAcceptable;
	
	  objetsEnMemoire.simulationVente(montantAchat, montantMin, dureeMax, margeAcceptable);
  }
  else 
	  cout << "Cette entree ne fait pas partie des choix!\n";
  
  return;
}


MenuLigue::MenuLigue()  { optionChoisie = 0; }
MenuLigue::~MenuLigue() {}

int MenuLigue::retourneOptionChoisie(void) { return optionChoisie;}

void MenuLigue::affichage(void)
{
  cout << "*******************************\n";
  cout << "*        Menu Ligue           *\n";
  cout << "*******************************\n\n";
  cout << "1) Ajouter un club a la ligue\n";
  cout << "2) Enlever un club a la ligue\n";
  cout << "3) Afficher tous les clubs de la ligue\n";
  cout << "4) Retourner au menu principal\n";
  cout << "5) Quitter\n\n";
  
  cout << "Choisissez une option: ";
  cin >> optionChoisie;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  cout << '\n';
  return;
} 

void MenuLigue::appelleFonctionChoisie(void) {

  switch(optionChoisie)
    {
 
    case 1: ajoutClub(); break;
 
    case 2: enleverClub(); break;
     
    case 3: afficheListeClubs(); break;
	  
	case 4: break;
	case 5: break;
    default: cout << "Erreur cette option nest pas dans le menu\n";
      break;
    }
	
  return;
} 

bool MenuLigue::ajoutClub(void)
{
  string nomTmp, histoireTmp, couleurTmp, villeTmp, adresseTmp;
  char  ajoutOk;

  cout << "Ajout d'un club\n";
  cout << "***************\n";
  cout << "Entrer le nom du club: ";
  getline(cin,nomTmp);
  cout << "Entrer son histoire: ";
  getline(cin,histoireTmp);
  cout << "Entrer la couleur du club: ";
  getline(cin,couleurTmp);
  cout << "Entrer la ville du club: ";
  getline(cin,villeTmp);
  cout << "Entrer ladresse du club: ";
  getline(cin,adresseTmp);

  cout << "\nEtes-vous sur de vouloir ajouter le club (O ou N) ? ";
  cin >> ajoutOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');

  if (ajoutOk == 'O' || ajoutOk == 'o')
    { 
	  objetsEnMemoire.ajouteClubDansLigue(nomTmp, histoireTmp, couleurTmp, villeTmp, adresseTmp);
      cout << "Le club a été ajouté avec succes !\n\n";
      return true;
    }

  cout << "Le club n'a pas ete ajoute!\n\n";
  return false;
} 

bool MenuLigue::enleverClub(void)
{
  char supprimeOk = 'n';
  unsigned int noClubASupprimer;
  Club clubASupprimer;
  vector<string> listeClubs;
  vector<string>::iterator it;
  int noClub = 0;
  
  listeClubs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomClubs();
  it = listeClubs.end();
  
  cout << "\nSupression d'un club\n";
  cout << "********************\n";
  if (!listeClubs.empty())
  {
	for (it--; it >= listeClubs.begin(); it--)
		std::cout << ++noClub << ") " << *it << '\n';
  }
  else
  {
	cout << "Actuellement, il n'y a aucun club dans la ligue\n";
	cin.ignore(INT_MAX, '\n');
	return false;
  }
  cout << '\n';
  
  cout <<"Entrer le no du club a supprimer (0 pour retourner au menu): ";
  cin >> noClubASupprimer;
  if (noClubASupprimer == 0) return true;
  
  cout << "\nEtes-vous sur de vouloir supprimer le club (O ou N) ? ";
  cin >> supprimeOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');

  if (supprimeOk == 'O' || supprimeOk == 'o')
  {	  
	  objetsEnMemoire.supprimeClubDeLigue(noClubASupprimer);	  
      cout << "Le club a été supprime avec succes!\n\n";	  
      return true;
    }

  cout << "Le club n'a pas ete supprime!\n\n";
  return false;
}

void MenuLigue::afficheListeClubs(void)
{
  vector<string> listeClubs;
  vector<string>::iterator it;
  int noClub = 0;
  
  listeClubs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomClubs();
  it = listeClubs.end();
  
  cout << "\nListe des clubs\n";
  cout << "*****************\n";
  if (!listeClubs.empty())
  {
	for (it--; it >= listeClubs.begin(); it--)
		std::cout << ++noClub << ") " << *it << '\n';
  }
  else
  {
	cout << "Actuellement, il n'y a aucun club dans la ligue\n";
  }
 
  cin.ignore(INT_MAX, '\n');
  return;

}

MenuClub::MenuClub() { optionChoisie = 0; }
MenuClub::~MenuClub() { } 

int MenuClub::retourneOptionChoisie(void) { return optionChoisie; } 
 
void MenuClub::affichage(void) {
  cout << "******************************\n";
  cout << "*        Menu Clubs          *\n";
  cout << "******************************\n\n";
  cout << "Club selectionne: " << objetsEnMemoire.retourneClubSelectionne().retourneNom() << "\n\n";
  cout << "1) Modifier les informations du club (nom, histoire, couleur, etc)\n";
  cout << "2) Afficher les informations du club\n";
  cout << "3) Ajouter un joueur\n";
  cout << "4) Enlever un joueur\n";
  cout << "5) Afficher la liste des joueurs\n";
  if (objetsEnMemoire.testEntraineurClubSelectionne())
	cout << "6) Changer d'entraineur\n";
  else
	cout << "6) Ajouter un entraineur\n";
  cout << "7) Ajouter un titre a lentraineur actuel\n";
  if (objetsEnMemoire.testStadeClubSelectionne())
	cout << "8) Changer de stade\n";
  else
	cout << "8) Ajouter un stade\n";  
  cout << "9) Changer les infos du personnel technique\n";
  cout << "10) Ajouter un trophee\n";
  cout << "11) Afficher les rencontres du club\n";
  cout << "12) Afficher les resultats du club\n";
  cout << "13) Retourner au menu principal\n";
  cout << "14) Quitter\n\n";

  cout << "Choisissez une option: ";
  cin >> optionChoisie;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << '\n';
  
  return;
} //MenuClub::affichage

void MenuClub::appelleFonctionChoisie(void)
{
	
  switch(optionChoisie)
    {
    case 1: modifInfosClub(); break;
   
    case 2: afficheInfosClub(); break;      
     
	case 3: ajoutJoueurClub(); break;

	case 4: enleveJoueurClub(); break;
	
	case 5: afficheListeJoueurs(); break;
	
    case 6: if (objetsEnMemoire.testEntraineurClubSelectionne()) modifEntraineur();
			else ajoutEntraineur(); 
			break;
      
    case 7: ajoutTitreEntraineur(); break;
      
    case 8:  if (objetsEnMemoire.testStadeClubSelectionne()) modifStade();
			 else ajoutStade();
			break; 
	
    case 9: break;
      
    case 10: ajoutTrophee(); break;
	  
    case 11: affichageRencontres(); break; 
	
	case 12: affichageResultatsMatch(); break;
	   
    case 13: objetsEnMemoire.deselectionneClub(); break;
      
    case 14: break;
	
    default: cout << "Cette option ne fait pas partie des choix!"; break;
    }
	return;
}

bool MenuClub::modifInfosClub(void)
{
  string tmpStr;
  Club   clubTemporaire;
  char modifOk;

  clubTemporaire = objetsEnMemoire.retourneClubSelectionne();
  
  cout << "\nModif info du club\n";
  cout << "********************\n";
  cout << "ENTER pour garder linformation\n\n";
  cout << "Entrer le nom du club: ";
  getline(cin, tmpStr);
  if (tmpStr != "") clubTemporaire.ajoutNom(tmpStr);
  cout << "Entrer l'histoire du club: ";
  getline(cin, tmpStr);
  if (tmpStr != "") clubTemporaire.ajoutHistoire(tmpStr);
  cout << "Entrer la couleur du club: ";
  getline(cin, tmpStr);
  if (tmpStr != "") clubTemporaire.ajoutCouleur(tmpStr);
  cout << "Entrer la ville du club: ";
  getline(cin, tmpStr);
  if (tmpStr != "") clubTemporaire.ajoutVille(tmpStr);
  cout << "Entrer l'adresse du club: ";
  getline(cin, tmpStr);
  if (tmpStr != "") clubTemporaire.ajoutAdresse(tmpStr);
  
  cout << '\n';
  cout << "nom du club: " << clubTemporaire.retourneNom() << '\n';
  cout << "histoire du club: " << clubTemporaire.retourneHistoire() << '\n';
  cout << "couleur: " << clubTemporaire.retourneCouleur() << '\n';
  cout << "ville: " << clubTemporaire.retourneVille() << '\n';
  cout << "adresse: " << clubTemporaire.retourneAdresse() << "\n\n";
  
  cout << "Etes vous sur de vouloir modifer le club (O ou N) ? ";
  cin  >> modifOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (modifOk == 'O' || modifOk == 'o')
    {	  
	  Club clubAModifier;
	  clubAModifier = objetsEnMemoire.retourneClubSelectionne();
	  objetsEnMemoire.modifClubLigue(clubAModifier, clubTemporaire);
	  objetsEnMemoire.modifClubSelectionne(clubTemporaire, objetsEnMemoire.retourneNoClubChoisi());
	  
      cout << "Le club a ete mis-a-jour!\n\n";
      return true;
    }

  cout << "Le club n'a pas ete mis-a-jour!\n\n";
  return false;
}



bool MenuClub::ajoutJoueurClub(void)
{
  float nouveauPoids;
  string prenomTmp, nomTmp, villeTmp;
  char ajoutOk = 'n';
  
  cout << "Ajout d'un Joueur\n";
  cout << "*****************\n";
  cout << "Entrer le prenom du joueur: ";
  getline(cin,prenomTmp);
  cout << "Entrer le nom du joueur: ";
  getline(cin,nomTmp);
  cout << "Entrer le poids du joueur: ";
  cin >> nouveauPoids;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  cout << "Entrer la ville de naissance du joueur: ";
  getline(cin,villeTmp);

  cout << "\n\nEtes-vous sur de vouloir ajouter le joueur au club (O ou N) ? ";
  cin >> ajoutOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');

  if (ajoutOk == 'O' || ajoutOk == 'o')
    {
	  objetsEnMemoire.ajouteJoueurDansClub(nomTmp, prenomTmp, nouveauPoids, villeTmp);
      cout << "Le joueur a été ajouté avec succes !\n\n";
      return true;
    }

  cout << "Le joueur n'a pas ete ajoute!\n\n";
  return false;
} 
 
bool MenuClub::enleveJoueurClub(void) 
{

  int noJoueur;
  char enleveOk;
  Joueur joueurASupprimer;
  vector<string> listeJoueurs;
  vector<string>::iterator itJoueur;
  int listeNoJoueur = 0;

  if (objetsEnMemoire.retourneClubSelectionne().retourneNbJoueurs() == 0)
    {
      cout << "Actuellement, il n'y a aucun joueur dans lequipe!\n";
	  cin.clear();
	  cin.ignore(INT_MAX, '\n');
	  return false;
    }

  listeJoueurs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomJoueurs(objetsEnMemoire.retourneNoClubChoisi());
  itJoueur = listeJoueurs.end();
  
  for (itJoueur--; itJoueur >= listeJoueurs.begin(); itJoueur--)
	std::cout << ++listeNoJoueur << ") " << *itJoueur << '\n';
  cout << '\n';
  
  cout << "Choissisez un joueur: ";
  cin >> noJoueur;
  cin.clear();
  cin.ignore(INT_MAX, '\n');	
  
  cout << "Etes-vous sur de vouloir enlever ce joueur (O ou N) ? ";
  cin >> enleveOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (enleveOk == 'o' || enleveOk == 'O')
    {
	  objetsEnMemoire.supprimeJoueurDeClub(noJoueur);
      cout << "Le joueur a ete enleve avec succes!\n";
      return true;
    }

  cout << "Le joueur na pas ete enlevee du club\n";
  return false;
}

void MenuClub::afficheListeJoueurs(void)
{
  vector<string> listeJoueurs;
  vector<string>::iterator itJoueur;
  int listeNoJoueur = 0;
	
  cout << "Liste des joueurs\n";
  cout << "*****************\n";

  if (objetsEnMemoire.retourneClubSelectionne().retourneNbJoueurs() == 0)
    {
      cout << "Actuellement, il n'y a aucun joueur dans lequipe!\n";
	  cin.clear();
	  cin.ignore(INT_MAX, '\n');
      return;
    }

  listeJoueurs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomJoueurs(objetsEnMemoire.retourneNoClubChoisi());
  itJoueur = listeJoueurs.end();
  
  for (itJoueur--; itJoueur >= listeJoueurs.begin(); itJoueur--)
	std::cout << ++listeNoJoueur << ") " << *itJoueur << '\n';
  cout << '\n';	  
	
  getchar();

  return;
}

void MenuClub::afficheInfosClub(void)
{
  Entraineur entraineurDeLequipe;
  Stade stadeDeLequipe;
  Club clubAAfficher;
  
  clubAAfficher = objetsEnMemoire.retourneClubSelectionne();
  entraineurDeLequipe = clubAAfficher.retourneEntraineur();  
  stadeDeLequipe = clubAAfficher.retourneStade();

  cout << "\nInformation sur le club\n";
  cout << "*************************\n";
  
  cout << "nom du club: " << clubAAfficher.retourneNom() << '\n';
  cout << "histoire du club: " << clubAAfficher.retourneHistoire() << '\n';
  cout << "couleur: " << clubAAfficher.retourneCouleur() << '\n';
  cout << "ville: " << clubAAfficher.retourneVille() << '\n';
  cout << "adresse: " << clubAAfficher.retourneAdresse() << "\n";
  
  cout << "Entraineur\n";
  cout << "\tnom: " << entraineurDeLequipe.retourneNom() << '\n';
  cout << "\tprenom: " << entraineurDeLequipe.retournePrenom() << '\n';
  cout << "\tlieu dobtention: " << entraineurDeLequipe.retourneLieu() << '\n';
  cout << "\tNb de titres: " << entraineurDeLequipe.retourneListeTitres().retourneNbTitres() << "\n";
  
  cout << "Stade\n";
  cout << "\tNom: " << stadeDeLequipe.retourneNom() << '\n';
  cout << "\tcapacite: " << stadeDeLequipe.retourneCapacite() << '\n';
  cout << "\tQualite du Terrain: " << stadeDeLequipe.retourneQualiteTerrain() << '\n';
  cout << "\tAdresse: " << stadeDeLequipe.retourneAdresse() << '\n';
  
  getchar();
} 

bool MenuClub::ajoutEntraineur(void)
{
  string tmpStr;
  char modifOk = 'n';
  Entraineur nouvelEntraineur;

  cout << "\nAjout nouvel entraineur\n";
  cout << "*************************\n";
  cout << "Entrer le nom de lentraineur: ";
  getline(cin,tmpStr);
  nouvelEntraineur.modifNom(tmpStr);
  cout << "Entrer le prenom de lentraineur: ";
  getline(cin,tmpStr);
  nouvelEntraineur.modifPrenom(tmpStr);
  cout << "Entrer le lieu dobtention des grade: ";
  getline(cin,tmpStr);
  nouvelEntraineur.modifLieuObtention(tmpStr);

  cout << "\nEtes vous sur de vouloir ajouter cet entraineur (O ou N) ? ";
  cin  >> modifOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (modifOk == 'o' || modifOk == 'O')
    {		  
	  objetsEnMemoire.ajouteEntraineurDansClub(nouvelEntraineur);
      cout << "Lentraineur a ete ajoute avec succes!\n\n";
      return true;
    }

  cout << "Lentraineur na pas ete ajoute\n\n";
  return false;

}

bool MenuClub::modifEntraineur(void)
{
  string tmpStr;
  char modifOk = 'n';
  Entraineur nouvelEntraineur;
  
  nouvelEntraineur = objetsEnMemoire.retourneClubSelectionne().retourneEntraineur();

  cout << "\nChanger d'entraineur\n";
  cout << "***********************\n";
  cout << "Entrer le nom de lentraineur: ";
  getline(cin,tmpStr);
  nouvelEntraineur.modifNom(tmpStr);
  cout << "Entrer le prenom de lentraineur: ";
  getline(cin,tmpStr);
  nouvelEntraineur.modifPrenom(tmpStr);
  cout << "Entrer le lieu dobtention des grade: ";
  getline(cin,tmpStr);
  nouvelEntraineur.modifLieuObtention(tmpStr);

  cout << "\nEtes vous sur de vouloir modifier lentraineur (O ou N) ? ";
  cin  >> modifOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (modifOk == 'o' || modifOk == 'O')
    {	  
	  objetsEnMemoire.modifEntraineurDansClub(nouvelEntraineur);	  
      cout << "Lentraineur a ete modifie avec succes!\n\n";
      return true;
    }

  cout << "Lentraineur na pas ete modifie\n\n";
  return false;

}

bool MenuClub::modifStade(void)
{
  string tmpStr;
  char modifOk = 'n';
  Stade nouveauStade;

  nouveauStade = objetsEnMemoire.retourneClubSelectionne().retourneStade(); 
  
  cout << "Modifier le stade\n";
  cout << "*****************\n";
  cout << "Entrer le nom du stade: ";
  getline(cin,tmpStr);
  nouveauStade.modifNomStade(tmpStr);
  cout << "Entrer ladresse du stade: ";
  getline(cin,tmpStr);
  nouveauStade.modifAdresse(tmpStr);
  cout << "Entrer la qualite du terrain: ";
  getline(cin,tmpStr);
  nouveauStade.modifQualiteTerrain(tmpStr);

  cout << "\nEtes vous sur de vouloir modifier les informations sur le stade (O ou N) ? ";
  cin  >> modifOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (modifOk == 'o' || modifOk == 'O')
    { 
	  objetsEnMemoire.modifStadeDansClub(nouveauStade);
      cout << "Le stade a ete modifie avec succes!\n\n";
      return true;
    }

  cout << "Le stade na pas ete modifie\n\n";
  return false;

} //MenuClub::modifStade

bool MenuClub::ajoutStade(void)
{
  string tmpStr;
  char modifOk = 'n';
  Stade nouveauStade;
  
  cout << "Ajouter un stade\n";
  cout << "*****************\n";
  cout << "Entrer le nom du stade: ";
  getline(cin,tmpStr);
  nouveauStade.modifNomStade(tmpStr);
  cout << "Entrer ladresse du stade: ";
  getline(cin,tmpStr);
  nouveauStade.modifAdresse(tmpStr);
  cout << "Entrer la qualite du terrain: ";
  getline(cin,tmpStr);
  nouveauStade.modifQualiteTerrain(tmpStr);

  cout << "\nEtes vous sur de vouloir modifier les informations sur le stade (O ou N) ? ";
  cin  >> modifOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (modifOk == 'o' || modifOk == 'O')
    {	  
	  objetsEnMemoire.ajouteStadeDansClub(nouveauStade);	  
      cout << "Le stade a ete ajoute avec succes!\n\n";
      return true;
    }

  cout << "Le stade na pas ete ajoute\n\n";
  return false;

} //MenuClub::modifStade

bool MenuClub::modifStaffTechnique(void){ return true; } //menuClub::modifStaffTechnique

bool MenuClub::ajoutTrophee(void)
{
  char ajoutOk = 'n';
  string nomTmp;
  short unsigned int anneeTmp, moisTmp, jourTmp;

  cout << "\nAjout dun trophee\n";
  cout << "*****************\n";
  cout << "Entrer le nom du titre a ajouter: ";
  getline(cin,nomTmp);
  cout << "Entrer lannee que vous avez gagne ce titre: ";
  cin >> anneeTmp;
  cout << "Entrer le mois que vous avez gagne ce titre: ";
  cin >> moisTmp;
  cout << "Entrer le jour que vous avez gagne ce titre: ";
  cin >> jourTmp;

  cout << "\nEtes vous sur de vouloir ajouter ce titre (O ou N) ? ";
  cin  >> ajoutOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (ajoutOk == 'o' || ajoutOk == 'O')
    {	  
	  objetsEnMemoire.ajoutTropheeClub(nomTmp, anneeTmp, moisTmp, jourTmp);
      cout << "Le trophee a ete ajoute avec succes!\n\n";
      return true;
    }

  cout << "Le trophee na pas ete ajoute\n\n";
  return false;
} //MenuClub::AjoutTrophee

bool MenuClub::ajoutTitreEntraineur(void)
{
  char ajoutOk = 'n';
  string nomTmp;
  short unsigned int anneeTmp, moisTmp, jourTmp;

  cout << "\nAjout d'un titre a lentraineur\n";
  cout << "******************************\n";
  cout << "Entrer le nom du titre a ajouter: ";
  getline(cin,nomTmp);
  cout << "Entrer lannee que cet entraineur a gagne ce titre: ";
  cin >> anneeTmp;
  cout << "Entrer le mois que cet entraineur a gagne ce titre: ";
  cin >> moisTmp;
  cout << "Entrer le jour que cet entraineur a gagne ce titre: ";
  cin >> jourTmp;

  cout << "\nEtes vous sur de vouloir ajouter ce titre (O ou N) ? ";
  cin  >> ajoutOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (ajoutOk == 'o' || ajoutOk == 'O')
    {	  
	  objetsEnMemoire.ajoutTropheeEntraineur(nomTmp, anneeTmp, moisTmp, jourTmp);	  
      cout << "Le trophee de lentraineur a ete ajoute avec succes!\n\n";
      return true;
    }

  cout << "Le trophee n'a pas ete ajoute\n\n";
  return false;
} //MenuClub::ajoutTitreEntraineur

void MenuClub::affichageRencontres(void)
{
  string nomDuClub = objetsEnMemoire.retourneClubSelectionne().retourneNom();
  vector<string> listeRencontres;
  vector<string>::iterator it;
	
  cout << "Affichage des rencontres de lequipe\n";
  cout << "***********************************\n";

  listeRencontres = objetsEnMemoire.retourneCalendrierSelectionne().retourneListeRencontresEquipe(nomDuClub);
  it = listeRencontres.end();

  if (listeRencontres.empty())
  {
	cout << "Aucune rencontre de prevues pour ce club!\n\n";
	return;
  }

  for (it--; it >= listeRencontres.begin(); it--)
	std::cout << *it << '\n';
  cout << '\n';
	
  cin.ignore(INT_MAX, '\n');
} //MenuClub::affichageRencontres

void MenuClub::affichageResultatsMatch(void)
{
  string nomDuClub = objetsEnMemoire.retourneClubSelectionne().retourneNom();
  vector<string> listeResultats;
  vector<string>::iterator it;
	
  cout << "Affichage des resultats de lequipe\n";
  cout << "***********************************\n";

  listeResultats = objetsEnMemoire.retourneCalendrierSelectionne().retourneResultatsRencontresEquipe(nomDuClub);
  it = listeResultats.end();

  if (listeResultats.empty())
  {
	cout << "Aucune rencontre de prevues pour ce club!\n\n";
	return;
  }

  for (it--; it >= listeResultats.begin(); it--)
	std::cout << *it << '\n';
  cout << '\n';
	
  cin.ignore(INT_MAX, '\n');
} //MenuClub::affichageRencontres */


MenuJoueur::MenuJoueur() { }
MenuJoueur::~MenuJoueur() { }

int MenuJoueur::retourneOptionChoisie(void) { return optionChoisie;}

void MenuJoueur::affichage(void)
{

  cout << "******************************\n";
  cout << "*        Menu Joueurs        *\n";
  cout << "******************************\n\n";
 
  if (objetsEnMemoire.testJoueurSelectionne())
	cout << "Joueur selectione: " << objetsEnMemoire.retourneJoueurSelectionne().retournePrenom() << " " << objetsEnMemoire.retourneJoueurSelectionne().retourneNom() << "\n\n";
  //cout << 1) afficher les informations/statistiques du joueur
  cout << "1) Negocier un nouveau contrat\n";
  cout << "2) Rupture de contrat\n";
  cout << "3) Afficher le statut contractuel\n";
  cout << "4) Retour au menu Club\n";
  cout << "5) Quitter\n\n";

  cout << "Choisissez une option: ";
  cin >> optionChoisie;
  cin.clear();
  cin.ignore(INT_MAX, '\n');

  return;
}

void MenuJoueur::appelleFonctionChoisie(void)
{	
  switch(optionChoisie)
    {
    case 1: negocierNouveauContrat(); break;
	
    case 2: ruptureContrat(); break;
	
	case 3: afficheStatutContractuel();  break;
	
	case 4: objetsEnMemoire.deselectionneClub();
			objetsEnMemoire.deselectionneJoueur();
	break;
	
	case 5: break;
    default: cout << "Cette option ne fait pas partie de la liste\n"; break;
    }

	return;
} 

bool MenuJoueur::negocierNouveauContrat(void)
{
	string tmpStr;
	Reglement reglementTmp;
	char ajoutContratOk = 'n';
	int nbAnneesContrat;
	float valeurContrat;
	Date dateTmp1, dateTmp2;

	cout << "Negocier nouveau contrat\n";
	cout << "************************\n\n";
	
	cout << "Entrer la duree du contrat en annees: ";
	cin >> nbAnneesContrat;
	cout << "Entrer la valeur du contrat: ";
	cin >> valeurContrat;
	cout << "Entrer la date dentree en vigueur du contrat (AAAA/MM/JJ): ";
	cin >> tmpStr;
	dateTmp1 = Date(tmpStr);
	cout << "Entrer la date de signature du contrat (AAAA/MM/JJ):  ";
	cin >> tmpStr;
	dateTmp2 = Date(tmpStr);
	
	cout << "\nEtes vous sur de vouloir ajouter ce contrat (O ou N) ? ";
	cin  >> ajoutContratOk;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
  
	if (ajoutContratOk == 'o' || ajoutContratOk == 'O')
    {	  
	  objetsEnMemoire.ajouteNouveauContratJoueur(nbAnneesContrat, dateTmp1, dateTmp2, valeurContrat);		  
      cout << "Le contrat de ce joueur a ete ajoute avec succes!\n\n";
      return true;
    }
	
	return false;
}

bool MenuJoueur::afficheStatutContractuel(void)
{
	string statutCont;
	
	cout << "Affichage du statut contractuel\n";
	cout << "*******************************\n";

	statutCont = objetsEnMemoire.retourneClubSelectionne().retourneStatutContrat(objetsEnMemoire.retourneJoueurSelectionne().retournePrenom(), objetsEnMemoire.retourneClubSelectionne().retourneNom());
	 
	cout << statutCont << "\n\n"; 
	
	return true;
}	

bool MenuJoueur::ruptureContrat(void)
{
	string raisonDepart;
	Rupture ruptureTmp;
	char ajoutOk = 'n';
	
	cout << "Rupture du contrat actuel\n";
	cout << "*************************\n\n";
	
	cout << "Entrer la raison pour laquelle vous voulez rompre le contrat avec ce joueur: ";
	cin  >> raisonDepart;
	
	cout << "\nEtes vous sur de vouloir rompre le contrat (O ou N) ? ";
	cin  >> ajoutOk;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
  
	if (ajoutOk == 'o' || ajoutOk == 'O')
    {	
	  objetsEnMemoire.ajouteRuptureContrat(raisonDepart);	  
      cout << "Le contrat a ete rompu avec succes.\n\n";
      return true;
    }
	return false;
}

MenuCalendrier::MenuCalendrier() 
{ 
 optionChoisie = 0;
}

MenuCalendrier::~MenuCalendrier() {}

int MenuCalendrier::retourneOptionChoisie(void) { return optionChoisie;}

void MenuCalendrier::affichage(void)
{
  cout << "*******************************\n";
  cout << "*        Menu Calendrier      *\n";
  cout << "*******************************\n\n";
  cout << "1) Ajouter une rencontre au calendrier de la ligue\n";
  cout << "2) Enlever une rencontre au calendrier de la ligue\n";
  cout << "3) Afficher les rencontres prevues au calendrier de la ligue\n";
  cout << "4) Afficher les resultats des rencontres\n";
  cout << "5) Simuler un match prevu au calendrier\n";
  cout << "6) Retourner au menu principal\n";
  cout << "7) Quitter\n\n";
  
  cout << "Choisissez une option: ";
  cin >> optionChoisie;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  cout << '\n';
  return;
} //Menu::afficherClubs

void MenuCalendrier::appelleFonctionChoisie(void) {

  switch(optionChoisie)
    {
	
    case 1: ajoutRencontreCalendrier(); break;
	
	case 2: enleveRencontreCalendrier(); break;
	
	case 3: afficheRencontresCalendrier(); break;

	case 4: afficheResultatsMatch(); break;
	
	case 5: simulerUnMatch(); break;
	  
	case 6: break;
			
	case 7: break;
    default: cout << "Erreur cette option nest pas dans le menu\n";
      break;
    }
	
  return;
} 

bool MenuCalendrier::ajoutRencontreCalendrier(void) 
{
  int noClubDomicile, noClubEtranger;
  int noClub = 0;
  string dateStr;
  char  ajoutOk;
  vector<string> listeClubs;
  vector<string>::iterator it;
  
  listeClubs = objetsEnMemoire.retourneLigueSelectionnee().retourneListeNomClubs();
  it = listeClubs.end();

  cout << "Ajout d'une rencontre\n";
  cout << "*********************\n";
  
  for (it--; it >= listeClubs.begin(); it--)
	std::cout << ++noClub << ") " << *it << '\n';
  cout << '\n';
    
  cout << "Entrer le no du club a domicile (0 pour retourner au menu) : ";
  cin >> noClubDomicile;
  
  if (noClubDomicile == 0)
    return true;
  
  cout << "Entrer le no du club a letranger (0 pour retourner au menu): ";
  cin >> noClubEtranger;
  
  if (noClubEtranger == 0)
    return true;
  
  cout << "Entrer la date de la rencontre (AAAA/MM/JJ): ";
  cin >> dateStr;

  cout << "\nEtes-vous sur de vouloir ajouter cette rencontre (O ou N) ? ";
  cin >> ajoutOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');

  if (ajoutOk == 'O' || ajoutOk == 'o')
    {
	  Date dateRencontre = Date(dateStr);
	  objetsEnMemoire.ajoutRencontreCalendrier(noClubDomicile, noClubEtranger, dateRencontre);
      cout << "La rencontre a été ajoutée avec succes !\n\n";
      return true;
    }

  cout << "La rencontre na pas ete ajoute avec succes !\n\n";
  return false;

} 

bool MenuCalendrier::enleveRencontreCalendrier(void)
{
	char supprimeOk = 'n';
	unsigned int noRencontreASupprimer;
	vector<string> listeRencontres;
	vector<string>::iterator it;
	unsigned int noRencontre = 0;
			
	listeRencontres = objetsEnMemoire.retourneCalendrierSelectionne().retourneListeRencontres();
	
	it = listeRencontres.end();
	
	cout << "\nSupression d'une rencontre\n";
	cout << "**************************\n";
	
	if (!listeRencontres.empty())
	{		
		for (it--; it >= listeRencontres.begin(); it--)
		std::cout << ++noRencontre << ") " << *it << '\n';
		cout << '\n';
	}
	else
	{
		cout << "Actuellement, il n'y a aucune rencontre de prevues au calendrier\n";
		cin.ignore(INT_MAX, '\n');
		return false;
	}

	cout <<"Entrer le no de la rencontre a supprimer (0 pour retourner au menu): ";
	cin >> noRencontreASupprimer;

  if (noRencontreASupprimer == 0)
    return true;
  
  cout << "\nEtes-vous sur de vouloir supprimer cette rencontre (O ou N) ? ";
  cin >> supprimeOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');

  if (supprimeOk == 'O' || supprimeOk == 'o')
  { 
	  objetsEnMemoire.enleveRencontreCalendrier(noRencontreASupprimer);
	  
	  cout << "La rencontre a été supprime avec succes!\n\n";
 
      return true;
  }

  cout << "La rencontre n'a pas ete supprime!\n\n";
  return false;
}

void MenuCalendrier::afficheRencontresCalendrier(void)
{
	vector<string> listeRencontres;
	vector<string>::iterator it;
	
	listeRencontres = objetsEnMemoire.retourneCalendrierSelectionne().retourneListeRencontres();
	it = listeRencontres.end();
	
	cout << "\nListe des rencontres\n";
	cout << "********************\n";

	if (!listeRencontres.empty())
	{		
		for (it--; it >= listeRencontres.begin(); it--)
		std::cout << *it << '\n';
		cout << '\n';
	}
	else
	{
		cout << "Actuellement, il n'y a aucune rencontre de prevue au calendrier\n";
	}
	
	cin.ignore(INT_MAX, '\n');
} //MenuLigue::afficheRencontreCalendrier

void MenuCalendrier::afficheResultatsMatch(void)
{
	vector<string> listeResultats;
	vector<string>::iterator it;

	listeResultats = objetsEnMemoire.retourneCalendrierSelectionne().retourneResultatsRencontres();

	it = listeResultats.end();
	
	cout << "\nListe des resultats des Rencontres\n";
	cout << "************************************\n";

	if (!listeResultats.empty())
	{		
		for (it--; it >= listeResultats.begin(); it--)
		std::cout << *it << '\n';
		cout << '\n';
	}
	else
	{
		cout << "Actuellement, il n'y a aucune rencontre de prevue au calendrier\n";
	}
	
	cin.ignore(INT_MAX, '\n');
} //MenuLigue::afficheRencontreCalendrier */

void MenuCalendrier::simulerUnMatch(void)
{
	int noRencontreASimuler;
	Rencontre rencontreASimuler;
	Club clubDomicile, clubEtranger;
	char simulerOk = 'n';
	Match nouveauMatch;
	Resultat resultatMatch;
	vector<string> listeRencontres;
	vector<string>::iterator it;
	int noRencontre = 0;
	
	listeRencontres = objetsEnMemoire.retourneCalendrierSelectionne().retourneListeRencontres();
	it = listeRencontres.end();
	
	cout << "\nSimulation d'un match\n";
	cout << "********************\n";
	
	if (!listeRencontres.empty())
	{		
		for (it--; it >= listeRencontres.begin(); it--)
		std::cout << ++noRencontre << ") " << *it << '\n';
		cout << '\n';
	}
	else
	{
		cout << "Actuellement, il n'y a aucune rencontre de prevues au calendrier\n";
		cin.ignore(INT_MAX, '\n');
		return;
	}
		
	cout <<"\nQuel match desirez-vous simuler (0 pour retourner au menu): ";
	cin >> noRencontreASimuler;

  if (noRencontreASimuler == 0)
    return;

  cout << "\nEtes-vous sur de vouloir simuler cette rencontre (O ou N) ? ";
  cin >> simulerOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');

  if (simulerOk == 'O' || simulerOk == 'o')
  { 
	objetsEnMemoire.simulerMatchCalendrier(noRencontreASimuler);
	
	cout << "Le match a ete simule avec succes !\n";
	
	return;
  }
  return;	
}

MenuEntraineur::MenuEntraineur()  { optionChoisie = 0; }
MenuEntraineur::~MenuEntraineur() {}

int MenuEntraineur::retourneOptionChoisie(void) { return optionChoisie;}


void MenuEntraineur::affichage(void)
{
  cout << "*******************************\n";
  cout << "*        Menu Entraineurs      *\n";
  cout << "*******************************\n\n";
  if (objetsEnMemoire.testEntraineurClubSelectionne())
	cout << "Entraineur selectione: " << objetsEnMemoire.retourneEntraineurSelectionne().retournePrenom() << " " << objetsEnMemoire.retourneEntraineurSelectionne().retourneNom() << "\n\n";
  cout << "1) Afficher les informations personnels\n";
  cout << "2) Modifier les informations personnels de cet entraineur\n";
  cout << "3) Afficher le statut contractuel\n";
  cout << "4) Negocier un nouveau contrat\n";
  cout << "5) Mettre a la porte cet entraineur\n";
  cout << "6) Ajouter un trophee a cet entraineur\n";
  cout << "7) Modifier le palmares de cet entraineur\n";
  cout << "8) Retourner au menu principal\n";
  cout << "9) Quitter\n\n";
  
  cout << "Choisissez une option: ";
  cin >> optionChoisie;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  cout << '\n';
  return;
} //MenuEntraineur::affichage()


void MenuEntraineur::appelleFonctionChoisie(void) {

  switch(optionChoisie)
    {
 
    case 1: afficheInfosEntraineur(); break;
     
    case 2: modifInfosEntraineur(); break;
     
    case 3: afficheStatutContractuel(); break;
	
	case 4: negocierNouveauContrat(); break;
	  
	case 5: ruptureContrat(); break;
	
	case 6: ajoutTrophee(); break;
	
	case 7: modifierPalmares(); break;
	
	case 8: objetsEnMemoire.deselectionneEntraineur(); break; 
	case 9: break;
    default: cout << "Erreur cette option nest pas dans le menu\n";
      break;
    }
		
  return;
} 


void MenuEntraineur::afficheInfosEntraineur(void)
{ 
  Entraineur entraineurAAfficher;
  
  entraineurAAfficher = objetsEnMemoire.retourneEntraineurSelectionne();

  cout << "\nInformation sur l'entraineur\n";
  cout << "******************************\n\n";

  cout << "\tprenom: " << entraineurAAfficher.retournePrenom() << '\n';
  cout << "\tnom: " << entraineurAAfficher.retourneNom() << '\n';
  cout << "\tlieu dobtention: " << entraineurAAfficher.retourneLieu() << '\n';
  cout << "\tNb de titres: " << entraineurAAfficher.retourneListeTitres().retourneNbTitres() << "\n";

  return;
}

bool MenuEntraineur::modifInfosEntraineur(void)
{ 
  cout << "\nModif info de l'entraineur\n";
  cout << "****************************\n";
  cout << "ENTER pour garder linformation\n\n";

  string tmpStr;
  Entraineur entraineurTmp;
  char modifOk;

  entraineurTmp = objetsEnMemoire.retourneEntraineurSelectionne();

  cout << "Entrer le prenom de l'entraineur: ";
  getline(cin, tmpStr);
  if (tmpStr != "") entraineurTmp.modifPrenom(tmpStr);
  cout << "Entrer le nom de l'entraineur: ";
  getline(cin, tmpStr);
  if (tmpStr != "") entraineurTmp.modifNom(tmpStr);
  cout << "Entrer le lieu d'obtention : ";
   getline(cin, tmpStr);
  if (tmpStr != "") entraineurTmp.modifLieuObtention(tmpStr);

  cout << "\tprenom: " << entraineurTmp.retournePrenom() << '\n';
  cout << "\tnom: " << entraineurTmp.retourneNom() << '\n';
  cout << "\tlieu dobtention: " << entraineurTmp.retourneLieu() << '\n';

  cout << "Etes vous sur de vouloir modifer l'entraineur (O ou N) ? ";
  cin  >> modifOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (modifOk == 'O' || modifOk == 'o')
    { 
	  objetsEnMemoire.modifEntraineurDansClub(entraineurTmp);
	  objetsEnMemoire.modifEntraineurSelectionne(entraineurTmp);
      cout << "L'entraineur a ete mis-a-jour!\n\n";
      return true;
    }

  cout << "L'entraineur n'a pas ete mis-a-jour!\n\n";
  return false;
  
  return 0; 
}
void MenuEntraineur::afficheStatutContractuel(void) { return; }
bool MenuEntraineur::negocierNouveauContrat(void) { return 0; }
bool MenuEntraineur::ruptureContrat(void) { return 0; }

bool MenuEntraineur::ajoutTrophee(void)
{
  char ajoutOk = 'n';
  string nomTmp;
  short unsigned int anneeTmp, moisTmp, jourTmp;

  cout << "\nAjout d'un titre a lentraineur\n";
  cout << "******************************\n";
  cout << "Entrer le nom du titre a ajouter: ";
  getline(cin,nomTmp);
  cout << "Entrer lannee que cet entraineur a gagne ce titre: ";
  cin >> anneeTmp;
  cout << "Entrer le mois que cet entraineur a gagne ce titre: ";
  cin >> moisTmp;
  cout << "Entrer le jour que cet entraineur a gagne ce titre: ";
  cin >> jourTmp;

  cout << "\nEtes vous sur de vouloir ajouter ce titre (O ou N) ? ";
  cin  >> ajoutOk;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  if (ajoutOk == 'o' || ajoutOk == 'O')
    {  
	  objetsEnMemoire.ajoutTropheeEntraineur(nomTmp, anneeTmp, moisTmp, jourTmp);	  
      cout << "Le trophee de lentraineur a ete ajoute avec succes!\n\n";
      return true;
    }

  cout << "Le trophee n'a pas ete ajoute\n\n";
  return false;	
  
}
bool MenuEntraineur::modifierPalmares(void) { return 0; }

MenuTrophee::MenuTrophee() {optionChoisie = 0;}
MenuTrophee::~MenuTrophee() { }
	
int  MenuTrophee::retourneOptionChoisie(void) { return optionChoisie;}	
	
void MenuTrophee::affichage(void)
{
  cout << "*******************************\n";
  cout << "*        Menu Trophee         *\n";
  cout << "*******************************\n\n";
  cout << "1) Afficher le club le plus titre\n";
  cout << "2) Afficher lentraineur le plus titre\n";
  cout << "3) Retourner au menu principal\n";
  cout << "4) Quitter\n\n";
  
  cout << "Choisissez une option: ";
  cin >> optionChoisie;
  cin.clear();
  cin.ignore(INT_MAX, '\n');
  
  cout << '\n';
}

void MenuTrophee::appelleFonctionChoisie(void){ 

 switch(optionChoisie)
    {
 
    case 1: afficheClubPlusTitre(); break;
 
    case 2: afficheEntraineurPlusTitre(); break;
     	  
	case 3: break;
	case 4: break;
    default: cout << "Erreur cette option nest pas dans le menu\n";
      break;
    }
	
	return;
}

void MenuTrophee::afficheClubPlusTitre(void)  
{ 
  Club clubPlusTitre;
  
  cout << "Affiche Club le plus titre\n";
  cout << "**************************\n";

  clubPlusTitre = objetsEnMemoire.retourneLigueSelectionnee().retourneClubPlusTitre();
  
  cout << "Voici le club le plus titre:\n" ;
  cout << "nom du club: " << clubPlusTitre.retourneNom() << '\n';
  cout << "histoire du club: " << clubPlusTitre.retourneHistoire() << '\n';
  cout << "couleur: " << clubPlusTitre.retourneCouleur() << '\n';
  cout << "ville: " << clubPlusTitre.retourneVille() << '\n';
  cout << "adresse: " << clubPlusTitre.retourneAdresse() << "\n\n";

  return; 
}

void MenuTrophee::afficheEntraineurPlusTitre(void) { return ;}
