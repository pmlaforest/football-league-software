/**************************************************************************
  detailsContrats.h -- Classes for the soccer club software
  Écrit par : Pierre-Marc Laforest                                       
// A FAIRE : AJOUTER LA LISTE DE TITRE GAGNES
*************************************************************************** */

#ifndef CLASSEDETAILSCONTRATS_H
#define CLASSEDETAILSCONTRATS_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include "classesLigue.h"
#include "classesCalendrierMatchs.h"

using namespace std;

class Club;
class Joueur;

class Reglement 
{
private:
	int seuil;
	string descriptionDroit;
	float montantTransfert;
	float montantEncaisseClub;
	float montantEncaisseJoueur;	
public:
	Reglement();
	~Reglement();	 
	void ajoutdescriptionDroit(string descriptionAAjouter);
	void ajoutMontantTransfert(float montantTransfertAAjouter);
	void ajoutMontantEncaisseClub(float montantEncaisseClubAAjouter);
	void ajoutMontantEncaisseJoueur(float montantEncaisseJoueurAAjouter);
	void ajoutSeuil(int seuilAAjouter); 
	int  retourneSeuil(void);
	string retourneDescription(void);
	float retourneMontantTransfert(void);
	float retourneMontantEncaisseClub(void);
	float retourneMontantEncaisseJoueur(void);
	Reglement operator=(Reglement reglement2);
};

class ContratEngagement 
{
private:
	Joueur joueurContractant;
	Club   clubContractant;
	Club   clubLibere;
	int    dureeContrat;
	Date   dateEntree;
	Reglement reglement;
	Date   dateContrat;
public:
	ContratEngagement(Joueur& joueurContractant, Club& clubContractant, Club& clubLibere, int nbAnneesContrat, Date& dateEntree,
					  Date& dateContrat, Reglement& reglementsContrat);
	ContratEngagement();
	~ContratEngagement();
	void ajoutJoueurContractant(Joueur& joueurAAjouter);
	void ajoutClubContractant(Club& clubContractantAAjouter);
	void ajoutClubLibere(Club& clubLibereAAjouter);
	void ajoutdureeContrat(int dureeContratAAjouter);
	void ajoutDateEntree(Date& dateAAjouter);
	void ajoutDateContrat(Date& dateContratAAjouter);
	void ajoutReglement(Reglement reglementContrat);
	Joueur retourneJoueurContractant(void);
	Club   retourneClubContractant(void);
	Club   retourneClubLibere(void);
	int    retourneDureeContrat(void);
	Date   retourneDateEntree(void);
	Date   retourneDateContrat(void);
	Reglement retourneReglementContrat(void); 
	ContratEngagement operator=(ContratEngagement contrat2);
};

class Rupture 
{
private:
	Joueur joueurContractant;
	Club   clubLibere;
	string raisonDepart;
public:
	Rupture();
	~Rupture();
	void ajoutJoueurContractant(Joueur& joueurAAJouter);
	void ajoutClubLibere(Club& clubAAjouter);
	void ajoutRaisonDepart(string raisonAAjouter);
	Joueur retourneJoueurContractant(void);
	Club retourneClubLibere(void);
	string retourneRaisonDepart(void);
	Rupture operator=(Rupture rupture2);
};

class Message
{
private: 
	string nomClubEmetteur;
	string sujetMessage;
	string nomJoueurImplique;
	string prenomJoueurImplique;
	float montantTransaction;
	time_t heureEnvoi;
public:
	Message() { nomClubEmetteur= "aucun"; sujetMessage = "aucun"; montantTransaction = 0; nomJoueurImplique = "aucun"; prenomJoueurImplique = "aucun"; heureEnvoi = time(NULL);}
	Message(string nomClub, string sujetNouveauMessage, string nomJoueurTransaction, string prenomJoueurTransaction, float montantVenteAchat)
	{
		nomClubEmetteur = nomClub;
		sujetMessage = sujetNouveauMessage;
		nomJoueurImplique = nomJoueurTransaction;
		prenomJoueurTransaction = prenomJoueurTransaction;
		montantTransaction = montantVenteAchat;
		time(&heureEnvoi);
	}
	~Message() {}
	void   ajoutEmetteur(string nouvelEmetteur) { nomClubEmetteur = nouvelEmetteur; } 
	void   ajoutSujetMessage(string nouveauSujet) { sujetMessage = nouveauSujet; }
	void   ajoutMontantTransaction(float nouveauMontantTransaction) { montantTransaction = nouveauMontantTransaction; } 
	void   ajoutNomJoueurImplique(string nouveauNom) { nomJoueurImplique = nouveauNom; }
	void   ajoutPrenomJoueurImplique(string nouveauPrenom) { prenomJoueurImplique = nouveauPrenom; }
	string retourneEmetteur(void) { return nomClubEmetteur; }
	string retourneSujetMessage(void) { return sujetMessage; }
	string retourneNomJoueurImplique(void) { return nomJoueurImplique; }
	string retournePrenomJoueurImplique(void) { return prenomJoueurImplique;}
	float  retourneMontantTransaction(void) { return montantTransaction; } 
	time_t retourneHeureEnvoi(void) { return heureEnvoi; }
	void   afficherMessage(void);
};

class NegoVendeur
{	
private:
	float montantDesire;
	float montantMin;
	double dureeMax;
	time_t heureDebutTransaction;
	float margeAcceptable;
	Club representantClub;
	void calculMontantDesire(void);
public:
	NegoVendeur();
	NegoVendeur(float nouveauMontantDesire, float nouveauMontantMin, float nouvelleDureeMax, float nouvelleMarge, Club nouveauRepresentantClub);
	~NegoVendeur() {}
	string retourneNomDuClubVendeur(void) { return representantClub.retourneNom(); }
	float retourneMontantDesire(void)  { calculMontantDesire(); return montantDesire; }
	float retourneMontantMin(void) { return montantMin; }
	double retourneDureeMax(void)  { return dureeMax; }
	float retourneMargeAcceptable(void) { return margeAcceptable; }
	void   ajoutHeureDebutTransaction(time_t heureDebut) { heureDebutTransaction = heureDebut; }
	time_t retourneHeureDebutTransaction(void) { return heureDebutTransaction; }
	Club  retourneRepresentantClub(void) { return representantClub; }
	Message faitProposition(string sujetMessage, string nomJoueurImplique, string prenomJoueurImplique);
	int reponseAProposition(Message& proposition);
	NegoVendeur& operator=(NegoVendeur& vendeur2);
};

class NegoAcheteur
{
private:
	float montantAchat;
	float montantMax;
	double dureeMax;
	float margeAcceptable;
	time_t heureDebutTransaction;
	Club representantClub;
	void calculMontantAchat(void);
public:
	NegoAcheteur();
	NegoAcheteur(float nouveauMontantAchat, float nouveauMontantMax, float nouvelleDureeMax, float nouvelleMarge, Club nouveauRepresentantClub);
	~NegoAcheteur() {}
	string retourneNomDuClubAcheteur(void) { return representantClub.retourneNom(); }
	float retourneMontantAchat(void) { calculMontantAchat(); return montantAchat; }
	float retourneMontantMax(void) { return montantMax; }
		float retourneMargeAcceptable(void) { return margeAcceptable; }
	void   ajoutHeureDebutTransaction(time_t heureDebut) { heureDebutTransaction = heureDebut; }
	double retourneDureeMax(void) { return dureeMax; }
	Club  retourneRepresentantClub(void) { return representantClub; }
	time_t retourneHeureDebutTransaction(void) { return heureDebutTransaction; }
	Message faitProposition(string sujetMessage, string nomJoueurImplique, string prenomJoueurImplique);
	int reponseAProposition(Message& proposition);
	NegoAcheteur& operator=(NegoAcheteur& acheteur2);
};

class Negociation
{
private:
	queue<Message> messagesAcheteur;
	queue<Message> messagesVendeur;
	NegoAcheteur acheteur;
	NegoVendeur  vendeur;
	double dureeMax;
	stack<char> alertesMessages;
	char tourAcheteurOuVendeur;
public:
	Negociation() {}
	Negociation(NegoAcheteur nouvelAcheteur, NegoVendeur nouveauVendeur);
	~Negociation() {}
	void propositionVenteJoueur(Message& messageVenteJoueur);
	void propositionAchatJoueur(Message& messageAchatJoueur);
	bool contreProposition(Message& contreProposition);
	int simulationNegotiations(char venteOuAchat, string nomJoueurImplique, string prenomJoueurImplique);
	void accepterOffre(Message& MessageRecu);
	void refuserOffre(Message& MessageRecu);
	Message lectureMessageAcheteur(void);
	Message lectureMessageVendeur(void);
	void traiteProposition(void);
};

#endif
