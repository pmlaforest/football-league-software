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
#include <math.h>
#include "classeIOFichiers.h"
#include "classesCalendrierMatchs.h"
#include "classesLigue.h"
#include "detailsContrats.h"

using namespace std;

Reglement::Reglement() 
{
	seuil = 0;
	descriptionDroit = "Aucun Droit";
	montantTransfert = 0;
	montantEncaisseClub = 0;
	montantEncaisseJoueur = 0;
}

Reglement::~Reglement() {}

void Reglement::ajoutdescriptionDroit(string descriptionAAjouter) { descriptionDroit = descriptionAAjouter; }
void Reglement::ajoutMontantTransfert(float montantTransfertAAjouter) { montantTransfert = montantTransfertAAjouter; }
void Reglement::ajoutMontantEncaisseClub(float montantEncaisseClubAAjouter) { montantEncaisseClub = montantEncaisseClubAAjouter; }
void Reglement::ajoutMontantEncaisseJoueur(float montantEncaisseJoueurAAjouter) { montantEncaisseJoueur = montantEncaisseJoueurAAjouter; }
void Reglement::ajoutSeuil(int seuilAAjouter) { seuil = seuilAAjouter; }

int    Reglement::retourneSeuil(void) { return seuil; }
string Reglement::retourneDescription(void) { return descriptionDroit; }
float  Reglement::retourneMontantTransfert(void) { return montantTransfert; }
float  Reglement::retourneMontantEncaisseClub(void) { return montantEncaisseClub; }
float  Reglement::retourneMontantEncaisseJoueur(void) { return montantEncaisseClub; }

Reglement Reglement::operator=(Reglement reglement2) 
{
	seuil = reglement2.seuil;
	descriptionDroit = reglement2.descriptionDroit;
	montantTransfert = reglement2.montantTransfert;
	montantEncaisseClub = reglement2.montantEncaisseClub;
	montantEncaisseJoueur = reglement2.montantEncaisseJoueur;
	
	return (*this);
}

ContratEngagement::ContratEngagement() { dureeContrat = 0; }
	
ContratEngagement::ContratEngagement(Joueur& nouveauJoueur, Club& nouveauClubContractant, Club& nouveauClubLibere, int nbAnneesContrat, Date& nouvelleDateEntree,
Date& nouvelleDateContrat, Reglement& nouveauReglementsContrat)
{
	joueurContractant = nouveauJoueur;
	clubContractant = nouveauClubContractant;
	clubLibere = nouveauClubLibere;
	dureeContrat = nbAnneesContrat;
	dateEntree = nouvelleDateEntree;
	reglement = nouveauReglementsContrat;
	dateContrat = nouvelleDateContrat; 
	
}

ContratEngagement::~ContratEngagement() {}
void ContratEngagement::ajoutJoueurContractant(Joueur& joueurAAjouter)  { joueurContractant = joueurAAjouter; } 
void ContratEngagement::ajoutClubContractant(Club& clubContractantAAjouter) { clubContractant = clubContractantAAjouter; } 
void ContratEngagement::ajoutClubLibere(Club& clubLibereAAjouter) { clubLibere = clubLibereAAjouter; } 
void ContratEngagement::ajoutdureeContrat(int dureeContratAAjouter) { dureeContrat = dureeContratAAjouter; } 
void ContratEngagement::ajoutDateEntree(Date& dateAAjouter) { dateEntree = dateAAjouter; }
void ContratEngagement::ajoutDateContrat(Date& dateContratAAjouter) { dateContrat = dateContratAAjouter; } 
void ContratEngagement::ajoutReglement(Reglement reglementContrat){ reglement = reglementContrat; }

Joueur ContratEngagement::retourneJoueurContractant(void) { return joueurContractant; } 
Club   ContratEngagement::retourneClubContractant(void) { return clubContractant; }
Club   ContratEngagement::retourneClubLibere(void) { return clubLibere; }
int    ContratEngagement::retourneDureeContrat(void) { return dureeContrat; }
Date   ContratEngagement::retourneDateEntree(void) { return dateEntree; } 
Date   ContratEngagement::retourneDateContrat(void) { return dateContrat; }
Reglement ContratEngagement::retourneReglementContrat(void) { return reglement; }

ContratEngagement ContratEngagement::operator=(ContratEngagement contrat2)
{
	joueurContractant = contrat2.joueurContractant;
	clubContractant = contrat2.clubContractant;
	clubLibere = contrat2.clubLibere;
	dureeContrat = contrat2.dureeContrat;
	dateEntree = contrat2.dateEntree;
	reglement = contrat2.reglement;
	dateContrat	= contrat2.dateContrat;
	
	return (*this);
}

Rupture::Rupture() { raisonDepart = "Aucune";}
Rupture::~Rupture() {}

void Rupture::ajoutJoueurContractant(Joueur& joueurAAJouter) { joueurContractant = joueurAAJouter; }
void Rupture::ajoutClubLibere(Club& clubAAjouter) { clubLibere = clubAAjouter; }
void Rupture::ajoutRaisonDepart(string raisonAAjouter) { raisonDepart = raisonAAjouter; }

Joueur Rupture::retourneJoueurContractant(void) { return joueurContractant; }
Club Rupture::retourneClubLibere(void) { return clubLibere; }
string Rupture::retourneRaisonDepart(void) { return raisonDepart; }

Rupture Rupture::operator=(Rupture rupture2)
{
	joueurContractant = rupture2.joueurContractant;
	clubLibere = rupture2.clubLibere;
	raisonDepart = rupture2.raisonDepart;
	
	return (*this);
}

void Message::afficherMessage(void)
{
	cout << "nom du Club Emetteur: " << nomClubEmetteur << '\n';
	cout << "sujet du message: " << sujetMessage << '\n';
	cout << "joueur implique: " << prenomJoueurImplique << nomJoueurImplique << '\n';
	cout << "montant transaction: " << montantTransaction << "\n\n";
	
	return;
}

NegoVendeur::NegoVendeur() 
{
	montantDesire = 0;
	montantMin = 0;
	dureeMax = 100;
	margeAcceptable = 0;
	time(&heureDebutTransaction);
}

NegoVendeur::NegoVendeur(float nouveauMontantDesire, float nouveauMontantMin, float nouvelleDureeMax, float nouvelleMarge, Club nouveauRepresentantClub)
{
	montantDesire = nouveauMontantDesire;
	montantMin = nouveauMontantDesire;
	dureeMax = nouvelleDureeMax;
	margeAcceptable = nouvelleMarge;
	representantClub = nouveauRepresentantClub;
	time(&heureDebutTransaction);
}


NegoVendeur& NegoVendeur::operator=(NegoVendeur& vendeur2)
{
	montantDesire = vendeur2.retourneMontantDesire();
	montantMin = vendeur2.retourneMontantMin();
	dureeMax = vendeur2.retourneDureeMax();
	heureDebutTransaction = vendeur2.retourneHeureDebutTransaction();
	representantClub = vendeur2.retourneRepresentantClub();
	margeAcceptable = vendeur2.retourneMargeAcceptable();
	
	return (*this);
}

void NegoVendeur::calculMontantDesire(void) 
{ 

	float montantCalcule = montantDesire - (0.01*montantDesire)*difftime(time(NULL), heureDebutTransaction); 

	if (montantCalcule > montantMin)
		montantDesire = montantCalcule;
	else
		montantDesire = montantMin;
	
	return;
}
 
Message NegoVendeur::faitProposition(string sujetMessage, string nomJoueurImplique, string prenomJoueurImplique)
{
	calculMontantDesire();
	float montantTransaction = montantDesire;
	Message propositionAEnvoyer = Message(retourneRepresentantClub().retourneNom(), sujetMessage, nomJoueurImplique, prenomJoueurImplique, montantTransaction);
	
	return propositionAEnvoyer;
}

int NegoVendeur::reponseAProposition(Message& propositionRecu)
{
	int dureeActuelle = difftime(propositionRecu.retourneHeureEnvoi(), retourneHeureDebutTransaction());
	int differencePrixJoueur = propositionRecu.retourneMontantTransaction() - montantDesire;
	
	if (dureeActuelle > dureeMax) 
		return -1;
	else 
	{
		if ( differencePrixJoueur >= 0)
			return 1; 						// accepter loffre dachat	
		else if ( differencePrixJoueur < 0 && abs((int)differencePrixJoueur) >= abs((int)margeAcceptable))
			return 0;						// refuser, avec une contre-offre
		else	
			return -1;						// refuser
	}
}

NegoAcheteur::NegoAcheteur()
{
	montantAchat = 0;
	montantMax = 0;
	dureeMax = 0;
	time(&heureDebutTransaction);
}

NegoAcheteur::NegoAcheteur(float nouveauMontantAchat, float nouveauMontantMax, float nouvelleDureeMax, float nouvelleMarge, Club nouveauRepresentantClub)
{
	montantAchat = nouveauMontantAchat;
	montantMax = nouveauMontantMax;
	dureeMax = nouvelleDureeMax;
	margeAcceptable = nouvelleMarge;
	representantClub = nouveauRepresentantClub;
	time(&heureDebutTransaction);
}

void NegoAcheteur::calculMontantAchat(void) 
{ 
	float montantCalcule = montantAchat + (0.01*montantAchat)*difftime(time(NULL), heureDebutTransaction); 

	if (montantCalcule < montantMax)
		montantAchat = montantCalcule;
	else
		montantAchat = montantMax;
	
	return;
} 

NegoAcheteur& NegoAcheteur::operator=(NegoAcheteur& acheteur2)
{
	montantAchat = acheteur2.retourneMontantAchat();
	montantMax = acheteur2.retourneMontantMax();
	dureeMax = acheteur2.retourneDureeMax();
	heureDebutTransaction = acheteur2.retourneHeureDebutTransaction();
	representantClub = acheteur2.retourneRepresentantClub();
	
	return (*this);
}

Message NegoAcheteur::faitProposition(string sujetMessage, string nomJoueurImplique, string prenomJoueurImplique)
{
	calculMontantAchat();
	float montantTransaction = montantAchat; 
	Message propositionAEnvoyer = Message(retourneRepresentantClub().retourneNom(), sujetMessage, nomJoueurImplique, prenomJoueurImplique, montantTransaction);
	
	return propositionAEnvoyer;
}

int NegoAcheteur::reponseAProposition(Message& propositionRecu)
{
	int dureeActuelle = difftime(propositionRecu.retourneHeureEnvoi(), retourneHeureDebutTransaction());
	int differencePrixJoueur = montantAchat - propositionRecu.retourneMontantTransaction();
	
	if (dureeActuelle > dureeMax) 
		return -1;							// refuser
	else 
	{
		if ( differencePrixJoueur >= 0)
			return 1; 						// accepter loffre dachat	
		else if ( differencePrixJoueur < 0 && abs((int)differencePrixJoueur) >= abs((int)margeAcceptable))
			return 0;						// refuser, avec une contre-offre
		else	
			return -1;						// refuser
	}
}

Negociation::Negociation(NegoAcheteur nouvelAcheteur, NegoVendeur nouveauVendeur)
{
	acheteur = nouvelAcheteur;
	acheteur.ajoutHeureDebutTransaction(time(NULL));
	vendeur  = nouveauVendeur;
	vendeur.ajoutHeureDebutTransaction(time(NULL));
	dureeMax = 10;
}

void Negociation::propositionVenteJoueur(Message& messageVenteJoueur)
{
	messagesAcheteur.push(messageVenteJoueur);
	alertesMessages.push('a');			
}

void Negociation::propositionAchatJoueur(Message& messageAchatJoueur)
{
	messagesVendeur.push(messageAchatJoueur);
	alertesMessages.push('v');	
}

bool Negociation::contreProposition(Message& contreProposition)
{		
	if (tourAcheteurOuVendeur == 'v')
	{		
		alertesMessages.push('a');	
		messagesAcheteur.push(contreProposition);
	}
	else if (tourAcheteurOuVendeur == 'a')
	{
		alertesMessages.push('v');
		messagesVendeur.push(contreProposition);
	}
	else
		return -1;
	
	return 0;
}

Message Negociation::lectureMessageAcheteur(void)
{ 
	Message messageARetourner;
	messageARetourner = messagesAcheteur.front();
	messagesAcheteur.pop();	

	return messageARetourner;
}
Message Negociation::lectureMessageVendeur(void)  
{ 
	Message messageARetourner;
 
	messageARetourner = messagesVendeur.front(); 
	messagesVendeur.pop();
	
	return messageARetourner;
 }

void Negociation::accepterOffre(Message& messageRecu)
{
	cout << "L'offre a ete accepte!\n";
	cout << "Voici les details: \n\n";
	
	messageRecu.afficherMessage();
	
	return;	
}
void Negociation::refuserOffre(Message& messageRecu) 
{
	cout << "L'offre a ete refusee!\n";
	cout << "Voici les details: \n\n";
	
	messageRecu.afficherMessage();
	
	return;
}

int Negociation::simulationNegotiations(char venteOuAchat, string nomJoueurImplique, string prenomJoueurImplique)
{	
	if (venteOuAchat == 'v')
	{
		Message propositionInitiale;
		propositionInitiale = vendeur.faitProposition("vente", nomJoueurImplique, prenomJoueurImplique);
		propositionVenteJoueur(propositionInitiale);
	}
	else if (venteOuAchat == 'a')
	{
		Message propositionInitiale;
		propositionInitiale = acheteur.faitProposition("achat", nomJoueurImplique, prenomJoueurImplique);
		propositionAchatJoueur(propositionInitiale);
	}
	else
		return -1;
	
	while(1)
	{
		if(alertesMessages.empty())
			return 0;
		
		Message messageRecu;
		int reponseVendeur, reponseAcheteur;
		
		tourAcheteurOuVendeur = alertesMessages.top();
		alertesMessages.pop();
		
		if (tourAcheteurOuVendeur == 'v')
		{
			messageRecu = lectureMessageVendeur();
			reponseVendeur = vendeur.reponseAProposition(messageRecu);
			
			if (reponseVendeur > 0)
			{
				accepterOffre(messageRecu);
				return 1;
			}
			else if (reponseVendeur == 0)
			{
				Message contreOffre;
				contreOffre = vendeur.faitProposition(messageRecu.retourneSujetMessage(), messageRecu.retournePrenomJoueurImplique(), messageRecu.retourneNomJoueurImplique());
				alertesMessages.push('a');
				contreProposition(contreOffre);
				continue;
			}
			else 
			{
				refuserOffre(messageRecu);
				return -1;
			}
		}
		else if (tourAcheteurOuVendeur == 'a')
		{
			messageRecu = lectureMessageAcheteur();
			reponseAcheteur = acheteur.reponseAProposition(messageRecu);
			
			if (reponseAcheteur > 0)
			{
				accepterOffre(messageRecu);
				return 1;
			}
			else if (reponseVendeur == 0)
			{
				Message contreOffre;
				contreOffre = acheteur.faitProposition(messageRecu.retourneSujetMessage(), messageRecu.retournePrenomJoueurImplique(), messageRecu.retourneNomJoueurImplique());
				alertesMessages.push('v');
				contreProposition(contreOffre);
				continue;
			}
			else
			{
				refuserOffre(messageRecu);
				return -1;
			}
		}
		else 
		{
			cout << "erreur!\n"; 
			return -1;
		}
	}
}




