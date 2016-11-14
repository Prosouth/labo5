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
#include <cmath>
#include <limits>

using namespace std;

// on cree une enumeration des jours de la semaine avec dimanche ayant la valeur de 1 jusqu'a 7 pour samedi
enum class JourDeLaSemaine {DIMANCHE = 1, LUNDI, MARDI, MERCREDI, JEUDI, VENDREDI, SAMEDI};

enum class Mois {JANVIER=1, FEVRIER, MARS, AVRIL, MAI, JUIN, JUILLET, AOUT, SEPTEMBRE, OCTOBRE, NOVEMBRE, DECEMBRE};

// Constatntes 
const int BORNE_ANNEE_MINIMALE = 1600,
          BORNE_ANNEE_MAXIMALE = 3000;

/**
 l'annee est elle Bissextile
 
 @param n entier >=1600 et <=3000 
 
 @return true or false
 */
bool estBissextile(int annee);


/**
 l'annee est elle valide
 
 @param n entier >=1600 et <=3000 
 
 @return true or false
 */
bool anneeValide(int annee);


/**
 demande les valeurs a l'utilisateur et verifie la saisie
 
 @param question(string) demande a l'utilisateur d'entrer une annnee et un jour de la semaine (1-7)
 @param erreur(string) message d'erreur en cas d'entree(s) non valide
 @param min(entier) definit le nombre mimimum a entrer
 @param min(entier) definit le nombre maximum a entrer
 */
void saisieUtilisateur(string question, string erreur, int min, int max);


/**
 Premier janvier de chaque annee
 
 * formule valable pour l'annee 1583 a 9999
 @param annee(entier) >=1600 et <=3000 
 
 @return le jour de la semaine correspondant au premier lundi de l'annee(1-7) avec dim=1, lundi=2, etc
 */
int premierJourJanvier(int annee);

/**
 * Affiche le mois dans une annee donnee 

 @param mois(entier)   compris entre 1 et 12
 @param annee(entier) >=1600 et <=3000 
 @return l'affichage du mois
 */
void affichageMois(int mois, int annee);



int main(int argc, char** argv)
{
    int annee ;
    cout << "entrez une annee :  ";
    cin >> annee ;
    
    
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


void saisieUtilisateur(string question, string erreur, int min, int max)
{
   int valeur;
   bool entree_valide = false;
   cout << question << endl;   
   
   do
   {
      if (entree_valide = (not(cin >> valeur) || (valeur <  min ||  valeur > max)))
      {
         cout << erreur << endl;
         cin.clear();
         cin.ignore(numeric_limits<int>::max(), '\n');
      }      
   } while(entree_valide);    
}

bool anneeValide(int annee)
{
    if(BORNE_ANNEE_MINIMALE > annee || annee > BORNE_ANNEE_MAXIMALE )
    {
        cout << "Entree non valide" << endl;
        return false;
    }
    
    return true;
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


void affichageMois(int mois, int annee)
{
   
}
