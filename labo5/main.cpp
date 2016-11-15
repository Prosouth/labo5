/*
 -----------------------------------------------------------------------------------
 Laboratoire : 5 - Calendrier
 Fichier     : labo5_corazza_saez.cpp
 Auteur(s)   : Corazza Erick, Sebastien Saez
 Date        : 7 Novembre 2016

 But         : Le but de ce laboratoire est d'afficher dans la console le calendrier 
 *             d'une année. Vous demandez à l'utilisateur de rentrer une année entre
 *             1600 et 3000, et la place du lundi dans l'ordre des 7 jours de la 
 *             semaine (entre 1 et 7). En sortie, vous affichez par exemple pour 2016 
 *             et le lundi en position 1.

 Remarque(s) : 

 Compilateur : g++ 
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// on crée une énumération des jours de la semaine avec dimanche ayant la valeur de 1 
// jusqu'a 7 pour samedi
enum class JourDeLaSemaine 
{
   DIMANCHE = 1, LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI
};

enum class Mois 
{
   JANVIER = 1, FEVRIER, MARS, AVRIL, MAI, JUIN, JUILLET, AOUT, SEPTEMBRE, 
   OCTOBRE, NOVEMBRE, DECEMBRE
};

enum class JourParMois 
{
   JANVIER = 31, FEVRIER = 28, MARS = 31, AVRIL = 30, MAI = 31, JUIN = 30, 
   JUILLET = 31, AOUT = 31, SEPTEMBRE = 30, OCTOBRE = 31, NOVEMBRE = 30,
   DECEMBRE = 31
};

// Constantes 
const int BORNE_ANNEE_MINIMALE = 1600,
          BORNE_ANNEE_MAXIMALE = 3000,
          LARGEUR_MOIS = 16,
          LARGEUR_JOUR_SEMAINE = 3,
          LARGEUR_COLONNE = 21;

/**
 l'annee est elle Bissextile
 
 @param n entier >=1600 et <=3000 
 
 @return true or false
 */
bool estBissextile(int annee);


/**
 demande les valeurs a l'utilisateur et verifie la saisie
 
 @param question(string) demande a l'utilisateur d'entrer une annnee et un jour de la semaine (1-7)
 @param erreur(string) message d'erreur en cas d'entree(s) non valide
 @param min(entier) definit le nombre mimimum a entrer
 @param min(entier) definit le nombre maximum a entrer
 @return la saisie correcte
 */
int saisieUtilisateur(string question, string erreur, int min, int max);


/**
 Affiche l'entete de chaque mois avec le nom du mois et l'ordre des jours dans la semaine
 @param mois(entier) le mois à afficher
 @param premierJourSemaine(entier) le jour de la semaine par lequel commence chaque semaine sur le calendrier
 */
void affichageCentreMois(int mois, int premierJourSemaine);


/**
 Affiche et centre correctement les jours du mois
 @param jour(entier) le jour a afficher
 @param premierJourSemaine(entier) le jour de la semaine par lequel commence chaque semaine sur le calendrier
 */
void affichageCentreJour(int jour, int premierJourSemaine);


/**
 Premier janvier de chaque annee
 
 * formule valable pour l'annee 1583 a 9999
 @param annee(entier) >=1600 et <=3000 
 
 @return le jour de la semaine correspondant au premier lundi de l'annee(1-7) avec dim=1, lundi=2, etc
 */
int premierJourJanvier(int annee);

/**
 * Affiche le calndrier d'une annee donnee 
 * 
 @param annee(entier) >=1600 et <=3000 
 @return l'affichage de l'annee
 */
void affichageAnnee(int annee, int jour);



int main(int argc, char** argv)
{
    string question1 = "Quelle annee voulez.vous afficher? (1600-3000)";
    string question2 = "Quel jour de la semaine est le lundi? (1-7)";
    string erreur = "Entree non valide";
    int annee = saisieUtilisateur(question1, erreur, BORNE_ANNEE_MINIMALE, BORNE_ANNEE_MAXIMALE);
    int jour = saisieUtilisateur(question2, erreur, 1, 7);
    
    affichageAnnee(annee, jour);
    
    
    return 0;
}


bool estBissextile(int annee)
{
    return (annee % 400 == 0) || ((annee % 4 == 0) && ((annee % 100) != 0));
}

bool jourValide(int jour)
{
    return (jour > 0 && jour <= 7) ? true : false;
}


int saisieUtilisateur(string question, string erreur, int valMin, int valMax)
{
   int valeur;
   bool entree_valide = false;
   cout << question << endl;   
   
   do
   {
      if (entree_valide = (not(cin >> valeur) || (valeur <  valMin ||  valeur > valMax)))
      {
         cout << erreur << endl;
         cin.clear();
         cin.ignore(numeric_limits<int>::max(), '\n');
         cout << question << endl;   
      }      
   } while(entree_valide);    
   return valeur;
}


// la formule a utiliser est la suivante : j = [ jour + a + a/4 - a/100 + a/400 + 31*m/12 ] mod 7
int premierJourJanvier(int annee)
{
    // nombre de jours dans une semaine
    const int nbJourSemaine = 7;
    
    // jour represente le jour dans le mois
    int jour = 1;
    
    // m corrrespond à la somme de 1(premier mois de l'annee) et 10 (une constante))
    int m = 11;
    
    // a vaut annee-1 si on calcule le premier jour de mois de janv. ou fev. et annee pour les autres mois
    int a = annee - 1;
    
    // on utilise la formule pour affecter son resultat a la variable premierJour
    int premierJour = (jour + a + a / 4 - a / 100 + a / 400 + 31 * m / 12 ) % nbJourSemaine;
    
    // on retourne le resultat de la formule + 1 car on veut obtenir les indices de 1-7 et non pas de 0-6
    return premierJour + 1; 
}


void affichageCentreMois(int mois, int premierJourSemaine)
{
    cout << setw(LARGEUR_MOIS);
    switch(mois)
    {
       case (int)Mois::JANVIER : 
           cout << "Janvier" << endl;
           break;
        case (int)Mois::FEVRIER : 
           cout << "Fevrier" << endl;
           break;
        case (int)Mois::MARS : 
           cout << "Mars" << endl;
           break;
        case (int)Mois::AVRIL : 
           cout << "Avril" << endl; 
           break;
        case (int)Mois::MAI : 
           cout << "Mai" << endl; 
           break;
        case (int)Mois::JUIN : 
           cout << "Juin"  << endl; 
           break;
        case (int)Mois::JUILLET : 
           cout << "Juillet" << endl; 
           break;
        case (int)Mois::AOUT : 
           cout << "Aout" << endl; 
           break;
        case (int)Mois::SEPTEMBRE : 
           cout << "Septembre" << endl; 
           break;
        case (int)Mois::OCTOBRE: 
           cout << "Octobre" << endl; 
           break;
        case (int)Mois::NOVEMBRE: 
           cout << "Novembre" << endl; 
           break;
        case (int)Mois::DECEMBRE: 
           cout << "Decembre" << endl; 
           break;
    }
    
    
    switch(premierJourSemaine)
    {
        case (int)JourDeLaSemaine::LUNDI - 1:
            cout << setw(LARGEUR_COLONNE) <<  "  L  M  M  J  V  S  D" << endl;  
            break;
        case (int)JourDeLaSemaine::MARDI - 1:
            cout << setw(LARGEUR_COLONNE) << "  D  L  M  M  J  V  S"<< endl;
            break;
        case (int)JourDeLaSemaine::MERCREDI - 1:
            cout << setw(LARGEUR_COLONNE) << "  S  D  L  M  M  J  V"<< endl; 
            break;
        case (int)JourDeLaSemaine::JEUDI - 1:
            cout << setw(LARGEUR_COLONNE) << "  V  S  D  L  M  M  J"<< endl;
            break;
        case (int)JourDeLaSemaine::VENDREDI - 1:
            cout << setw(LARGEUR_COLONNE) << "  J  V  S  D  L  M  M"<< endl;
            break;
        case (int)JourDeLaSemaine::SAMEDI - 1:
            cout << setw(LARGEUR_COLONNE) << "  M  J  V  S  D  L  M "<< endl; 
            break;
        case (int)JourDeLaSemaine::DIMANCHE + 6:
            cout << setw(LARGEUR_COLONNE) << "  M  M  J  V  S  D  L"<< endl; 
            break;
        default:
            cout << "Il y a un probleme!" << endl;
    }
    
}


void affichageAnnee(int annee, int jour)
{
    int dernierePos;
    int maxJours = 31;
    int positionPremierJanvier = premierJourJanvier(annee);
    
    
    for(int i = 1 ; i <= 12; i++)
    {
        affichageCentreMois(i, jour);
        int lol = 1;
        bool premiereLigne = false;
        
        
        if(estBissextile(annee) && i == 2)
        {
            maxJours = (int)JourParMois::FEVRIER + 1;
        }
        else if(i==(int)Mois::AVRIL || i==(int)Mois::JUIN || i==(int)Mois::SEPTEMBRE || 
                i==(int)Mois::NOVEMBRE )
        {
            maxJours = 30;
        }
        else
        {
            maxJours = 31;
        }
        
        for(int li=1 ; li<= 6; li++)
        {
            if(li == 1)
            {
                premiereLigne = true;
            }
            for(int co=1; co<=7; co++)
            {
                if(premiereLigne && (co < (positionPremierJanvier+6)) || co < dernierePos)
                {
                    cout << setw(LARGEUR_JOUR_SEMAINE) << "";
                }
                else
                {
                    if(lol <= maxJours)
                    {
                        cout << setw(LARGEUR_JOUR_SEMAINE) << lol;
                        lol++;
                        premiereLigne = false;
                        dernierePos = co;
                    }
                    else
                    {
                        cout << setw(LARGEUR_JOUR_SEMAINE) << "";
                    }
                   
                }  
                
                if(co == 7)
                {
                    cout << endl;
                }   
            }
            
            
                
        }

        
    }
}
