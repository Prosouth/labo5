/*
 -----------------------------------------------------------------------------------
 Laboratoire : 
 Fichier     : main.cpp
 Auteur(s)   : Corazza Erick, Sebastien Saez
 Date        : Novembre 2016

 But         : 

 Remarque(s) : 

 Compilateur : MinGW-g++ 5.3.0
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

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
 @param min(entier) definit le mimimum
 @param min(entier) definit le maximum
 
 @return true or false
 */
void saisieUtilisateur(string question, string erreur, int min, int max);


/**
 l'annee est elle Bissextile
 
 @param n entier >=1600 et <=3000 
 
 @return true or false
 */
int premierJanvier(int annee);




int main(int argc, char** argv) {

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
    
}