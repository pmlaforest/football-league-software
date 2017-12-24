/**************************************************************************
  objetsProgramme.cpp -- Cette classe constitue tous les objets du programme. 
  Ce sont les objets qui sont temporises en memoire pendant lexecution normal du 
  programme.
  Écrit par : Pierre-Marc Laforest
  Date: 28/04/17                                      
*************************************************************************** */


#include "ObjetsSelectionnes.h"


ObjetsProgramme::ObjetsProgramme() { }

ObjetsProgramme::~ObjetsProgramme() {}

void ObjetsProgramme::modifJoueurSelectionne(Joueur& nouveauJoueurSelectionne) { joueurSelectionne = nouveauJoueurSelectionne; return; }
void ObjetsProgramme::modifClubSelectionne(Club& nouveauClubSelectionne, int noClubChoisi) { clubSelectionne = nouveauClubSelectionne; clubChoisi = noClubChoisi; return; }
void ObjetsProgramme::modifEntraineurSelectionne(Entraineur& nouvelEntraineurSelectionne){ entraineurSelectionne = nouvelEntraineurSelectionne; return; } 

bool ObjetsProgramme::initialiseLigue(void) { ligueSelectionnee.lectureDonneesProgramme(); return 0; }

bool ObjetsProgramme::initialiseCalendrier(void) 
{
	EnregistrementDonnee donneesRencontres;
	donneesRencontres.lectureRencontres(calendrierSelectionne.retournePtrTableauRencontre(), calendrierSelectionne.retournePtrNbRencontres());
	return 0;
}

bool ObjetsProgramme::deselectionneJoueur(void) { joueurSelectionne = Joueur(); return 0; }
bool ObjetsProgramme::deselectionneClub(void)  { clubSelectionne = Club(); return 0; }
bool ObjetsProgramme::deselectionneEntraineur(void) { entraineurSelectionne = Entraineur(); return 0; } 

bool ObjetsProgramme::supprimeJoueurDeClub(int noJoueurASupprimer) 
{ 
   Joueur joueurASupprimer;
   	EnregistrementDonnee donneesJoueur;
	
   
   clubSelectionne.enleveJoueurAvecNo(noJoueurASupprimer);
   ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);
   
   joueurASupprimer = clubSelectionne.retourneJoueurAvecNo(noJoueurASupprimer);
   donneesJoueur.supprimerJoueur(clubSelectionne.retourneNom(), joueurASupprimer);
   
   return 0;
}

bool ObjetsProgramme::simulerMatchCalendrier(int noRencontreASimuler)
{ 
	Club clubDomicile, clubEtranger;
	EnregistrementDonnee donneesRencontre;
	Rencontre rencontreAEnregistrer;
	Rencontre rencontreASupprimer;
	
	rencontreASupprimer = calendrierSelectionne.retourneRencontreAvecNo(noRencontreASimuler);
	donneesRencontre.supprimerRencontre(rencontreASupprimer);
	
	clubDomicile = ligueSelectionnee.retourneClubAvecNom(calendrierSelectionne.retourneRencontreAvecNo(noRencontreASimuler).retourneNomClubDomicile());
	clubEtranger = ligueSelectionnee.retourneClubAvecNom(calendrierSelectionne.retourneRencontreAvecNo(noRencontreASimuler).retourneNomClubEtranger());
	
	calendrierSelectionne.simulerMatch2(noRencontreASimuler, clubDomicile, clubEtranger);

	rencontreAEnregistrer = calendrierSelectionne.retourneRencontreAvecNo(noRencontreASimuler);
	donneesRencontre.enregistrerRencontre(rencontreAEnregistrer);
	
	return 0;
}

bool ObjetsProgramme::ajouteEntraineurDansClub(Entraineur& entraineurAAjouter) 
{
	EnregistrementDonnee donneesEntraineur;

	clubSelectionne.ajoutEntraineur(entraineurAAjouter);
    ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);	
		
	donneesEntraineur.enregistrerEntraineur(clubSelectionne.retourneNom(), entraineurAAjouter);

	return 0;
}

bool ObjetsProgramme::ajouteNouveauContratJoueur(unsigned int nbAnneesContrat, Date dateEntree, Date DateContrat, float valeurContrat)
{
	Reglement reglementTmp;
	EnregistrementDonnee nouvelEnregistrement;
	
	
	reglementTmp.ajoutMontantTransfert(valeurContrat);
	reglementTmp.ajoutdescriptionDroit("Aucun");
	
	ContratEngagement contratTmp(joueurSelectionne, clubSelectionne, clubSelectionne, nbAnneesContrat, dateEntree, DateContrat, reglementTmp);
	clubSelectionne.ajoutContratJoueur(contratTmp);
	nouvelEnregistrement.enregistrerContrat( clubSelectionne.retourneNom(), contratTmp);
	
	return 0;
}

bool ObjetsProgramme::ajoutRencontreCalendrier(int noClubDomicile, int noClubEtranger, Date dateRencontre)
{	
	EnregistrementDonnee donneesRencontre;
	
	Club clubDomicile, clubEtranger;
	Stade stadeRencontre;
	
	clubDomicile = ligueSelectionnee.retourneClubAvecNo(noClubDomicile);
	clubEtranger = ligueSelectionnee.retourneClubAvecNo(noClubEtranger);  
	stadeRencontre = clubDomicile.retourneStade(); 
		
	Rencontre rencontreAAjouter(clubDomicile.retourneNom(), clubEtranger.retourneNom(), stadeRencontre, dateRencontre);
	
	calendrierSelectionne.ajoutRencontre2(rencontreAAjouter);
	donneesRencontre.enregistrerRencontre(rencontreAAjouter);
	
	return 0;
}

bool ObjetsProgramme::enleveRencontreCalendrier(int noRencontreASupprimer)
{
	EnregistrementDonnee donneesRencontre;
	Rencontre rencontreASupprimer;

	rencontreASupprimer = calendrierSelectionne.retourneRencontreAvecNo(noRencontreASupprimer);
	
	calendrierSelectionne.enleverRencontre2(noRencontreASupprimer);
	donneesRencontre.supprimerRencontre(rencontreASupprimer);
	
	return 0;
}

bool ObjetsProgramme::ajouteRuptureContrat(string raisonDepart) 
{
	Rupture ruptureTmp;
	EnregistrementDonnee donneesRupture;
	
	ruptureTmp.ajoutJoueurContractant(joueurSelectionne);
	ruptureTmp.ajoutClubLibere(clubSelectionne);
	
	ruptureTmp.ajoutRaisonDepart(raisonDepart); 
	
	clubSelectionne.ajoutRuptureContrat(ruptureTmp);
	donneesRupture.enregistrerRupture(ruptureTmp.retourneClubLibere().retourneNom(), ruptureTmp.retourneJoueurContractant(), ruptureTmp);
	
	return 0;
}

bool ObjetsProgramme::modifEntraineurDansClub(Entraineur& nouvelEntraineur)
{
	EnregistrementDonnee donneesEntraineur;	
	
	clubSelectionne.ajoutEntraineur(nouvelEntraineur);
    ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);

	donneesEntraineur.modifierEntraineur(clubSelectionne.retourneNom(), nouvelEntraineur);
	
	return 0;
}

bool ObjetsProgramme::modifStadeDansClub(Stade& stadeAModifier)
{
	EnregistrementDonnee donneesStade;
	
	donneesStade.modifierStade(clubSelectionne.retourneNom(), stadeAModifier);
	clubSelectionne.ajoutStade(stadeAModifier);
    ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);
	
	return 0;
}

bool ObjetsProgramme::ajouteStadeDansClub(Stade& stadeAAjouter)
{
	EnregistrementDonnee donneesStade;
	
	donneesStade.enregistrerStade(clubSelectionne.retourneNom(), stadeAAjouter);
	clubSelectionne.ajoutStade(stadeAAjouter);
    ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);

	return 0;
}

bool ObjetsProgramme::ajoutTropheeClub(string nomTrophee, short unsigned int anneeTrophee, short unsigned int moisTrophee, short unsigned int jourTrophee)
{
	EnregistrementDonnee donneesTrophees;
	titre titreTmp;
	Date dateTmp (anneeTrophee, moisTrophee, jourTrophee);
	
	titreTmp.nomDuTitre = nomTrophee;
	titreTmp.dateDuChampionnat = dateTmp;
	
   clubSelectionne.ajoutTrophee(nomTrophee, anneeTrophee, moisTrophee, jourTrophee);
   ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);	
   
	donneesTrophees.enregistrerTitreClub(clubSelectionne.retourneNom(), titreTmp);
   
   return 0;
}

bool ObjetsProgramme::ajoutTropheeEntraineur(string nomTrophee, short unsigned int anneeTrophee, short unsigned int moisTrophee, short unsigned int jourTrophee)
{
	clubSelectionne.ajoutTitreEntraineur(nomTrophee, anneeTrophee, moisTrophee, jourTrophee);
    ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);
	
	return 0;
}

bool ObjetsProgramme::supprimeClubDeLigue(int noClubASupprimer) 
{ 

  EnregistrementDonnee enregistrementASupprimer;
  Club clubASupprimer;
  Stade stadeASupprimer;
  Entraineur entraineurASupprimer;
  
  clubASupprimer = ligueSelectionnee.retourneClubAvecNo(noClubASupprimer);
  stadeASupprimer = clubASupprimer.retourneStade();
  entraineurASupprimer = clubASupprimer.retourneEntraineur();
  
  enregistrementASupprimer.supprimerStade(clubASupprimer.retourneNom(), stadeASupprimer);
  enregistrementASupprimer.supprimerEntraineur(clubASupprimer.retourneNom(), entraineurASupprimer);
 
  for (unsigned int noJoueur = 0; noJoueur < clubASupprimer.retourneNbJoueurs(); noJoueur++)
  {
	  Joueur joueurASupprimer;
	  joueurASupprimer = clubASupprimer.retourneJoueurAvecNo(noJoueur + 1);
      enregistrementASupprimer.supprimerJoueur(clubASupprimer.retourneNom(), joueurASupprimer);  
  }
  enregistrementASupprimer.supprimerClub(clubASupprimer);

  ligueSelectionnee.supprimeClubAvecNo(noClubASupprimer);
  
  return true;	
}

bool ObjetsProgramme::ajouteClubDansLigue(string nouveauNomDuClub, string nouvelleHistoire, string nouvelleCouleur, string nouvelleVille, string nouvelleAdresse) 
{
	EnregistrementDonnee sauvegardeClub;
	
	Club clubAAjouter(nouveauNomDuClub, nouvelleHistoire, nouvelleCouleur, nouvelleVille, nouvelleAdresse);
	sauvegardeClub.enregistrerClub(clubAAjouter);

	ligueSelectionnee.ajoutClub(clubAAjouter);
	
	return 0; 
}

bool ObjetsProgramme::modifClubLigue(Club& ancienClub, Club& nouveauClub)
{
	EnregistrementDonnee sauvegardeClub;
	sauvegardeClub.modifierClub(ancienClub, nouveauClub);

	ligueSelectionnee.modifClub(clubChoisi, nouveauClub);
	
	return 0;
}

bool ObjetsProgramme::ajouteJoueurDansClub(string nomJoueurAAJouter, string prenomJoueurAAJouter, float poidsJoueurAAJouter, string villeJoueurAAjouter)
{
    EnregistrementDonnee sauvegardeClub;
	EnregistrementDonnee donneesJoueur;
	Club ancienClub;
	
	ancienClub = clubSelectionne;
	
	Joueur joueurAAjouter(nomJoueurAAJouter, prenomJoueurAAJouter, poidsJoueurAAJouter, villeJoueurAAjouter);	 
	donneesJoueur.enregistrerJoueur(clubSelectionne.retourneNom(), joueurAAjouter);
	clubSelectionne.ajoutJoueur(joueurAAjouter);

	sauvegardeClub.modifierClub(ancienClub, clubSelectionne);
	
	ligueSelectionnee.modifClub(clubChoisi, clubSelectionne);

	return 0;
}

Joueur ObjetsProgramme::retourneJoueurSelectionne(void)  { return joueurSelectionne; }
Club  ObjetsProgramme::retourneClubSelectionne(void) { return clubSelectionne; }
Entraineur ObjetsProgramme::retourneEntraineurSelectionne(void) { return entraineurSelectionne; } 
Ligue ObjetsProgramme::retourneLigueSelectionnee(void) { return ligueSelectionnee; }
Calendrier ObjetsProgramme::retourneCalendrierSelectionne(void) { return calendrierSelectionne; }
int        ObjetsProgramme::retourneNoClubChoisi(void) { return clubChoisi; } 


bool ObjetsProgramme::testJoueurSelectionne(void) { return ( joueurSelectionne.retourneNom() != "aucun"); }
bool ObjetsProgramme::testClubSelectionne(void) { return (clubSelectionne.retourneNom() != "aucun"); }
bool ObjetsProgramme::testEntraineurSelectionne(void) { return (entraineurSelectionne.retourneNom() != "aucun"); }
bool ObjetsProgramme::testEntraineurClubSelectionne(void) {  return !(clubSelectionne.retourneEntraineur().retourneNom() == "aucun"); }
bool ObjetsProgramme::testStadeClubSelectionne(void) { return !(clubSelectionne.retourneStade().retourneNom() == "aucun"); }

bool ObjetsProgramme::simulationAchat(float montantAchat, float montantMax,  float dureeMax,   float margeAcceptable)
{
	Club clubTmp;
	
	NegoAcheteur simulationAcheteur(montantAchat, montantMax, dureeMax, margeAcceptable, clubSelectionne);
	NegoVendeur  simulationVendeur(montantAchat*5, montantMax/2, dureeMax, margeAcceptable, clubTmp);
	
	Negociation negoVendeurAcheteur(simulationAcheteur, simulationVendeur);
	negoVendeurAcheteur.simulationNegotiations('a', joueurSelectionne.retourneNom(), joueurSelectionne.retournePrenom());
	
	return true;
}

bool ObjetsProgramme::simulationVente(float montantVente, float montantMin,  float dureeMax, float margeAcceptable)
{
	Club clubTmp;
	
	NegoVendeur  simulationVendeur(montantVente, montantMin, dureeMax, margeAcceptable, clubSelectionne);
	NegoAcheteur simulationAcheteur(montantVente/5, montantMin*2, dureeMax, margeAcceptable, clubTmp);
	
	Negociation negoVendeurAcheteur(simulationAcheteur, simulationVendeur);
	negoVendeurAcheteur.simulationNegotiations('v', joueurSelectionne.retourneNom(), joueurSelectionne.retournePrenom());

	return true;
}



