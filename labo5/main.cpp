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

 Compilateur : g++ 6.2.1 20160830
 -----------------------------------------------------------------------------------
 */
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

// Enum des mois de l'année avec janvier = 1 et decembre = 12 pour respecter
// les conventions usuelles
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
const int   BORNE_ANNEE_MINIMALE = 1600,
            BORNE_ANNEE_MAXIMALE = 3000,
            BORNE_JOUR_MINIMUM = 1,
            BORNE_JOUR_MAXIMUM = 7,
            LARGEUR_MOIS = 16,
            LARGEUR_COLONNE = 3,
            LARGEUR_MAX = 21,
            ESPACE_AVANT_ANNEE = 12,
            ESPACE_APRES_ANNEE = 9;
          
/**
 L'année est-elle bissextile?
 
 @param n entier >=1600 et <=3000 
 
 @return true or false
 */
bool estBissextile(int annee);

/**
 Demande les valeurs à l'utilisateur et verifie la saisie
 
 @param question(string) demande à l'utilisateur d'entrer une année et un jour de la semaine (1-7)
 @param erreur(string) message d'erreur en cas d'entrée(s) non valide(s)
 @param min(entier) définit le nombre mimimum à entrer
 @param max(entier) définit le nombre maximum à entrer
 @return la saisie correcte
 */
int saisieUtilisateur(string question, string erreur, int min, int max);

/**
 Affiche l'entête de chaque mois avec le nom du mois et l'ordre des jours dans la semaine
 
 @param mois(entier) le mois à afficher
 @param premierJourSemaine(entier) la position du lundi dans les jours de la semaine (1-7)
 */
void affichageCentreMois(int mois, int premierJourSemaine);

/**
 Affiche et centre correctement les jours du mois
 
 @param jour(entier) le jour a afficher
 @param premierJourSemaine(entier) le jour de la semaine par lequel commence chaque semaine sur le calendrier
 */
void affichageCentreJour(int jour, int premierJourSemaine);

/**
 Affiche une unique chaine de manière centrée sur 21 caractères
 
 @param chaîne (string) la chaine qu'on veut centrer 
 */
void affichageCentreChaine(string chaine);

/**
 Affiche le calndrier d'une annee donnee 
 
 @param annee(entier) >=1600 et <=3000 
 @param jour(entier) represente la position du lundi dans la semaine a afficher
 @return l'affichage du calendrier de l'annee
 */
void affichageAnnee(int annee, int jour);


/**
 Premier janvier de chaque année, formule valable pour l'annee 1583 à 9999
 La formule utilisée est la suivante: 
 j = [jour + a + a / 4 - a / 100 + a / 400 + 31 * m / 12] mod 7
 Source: http://tny.im/7na
 
 
 @param annee(entier) >=1600 et <=3000
 @return le jour de la semaine correspondant au premier lundi de l'annee(1-7) avec dim=1, lundi=2, etc
 */
int premierJourJanvier(int annee);


int main()
{
    string question1 = "Quelle annee voulez-vous afficher? (1600-3000) ",
           question2 = "Quel jour de la semaine est le lundi? (1-7) ",
           erreur = "Entree non valide";
    int annee, jour;
    
    annee = saisieUtilisateur(question1, erreur, BORNE_ANNEE_MINIMALE, BORNE_ANNEE_MAXIMALE);
    jour = saisieUtilisateur(question2, erreur, BORNE_JOUR_MINIMUM, BORNE_JOUR_MAXIMUM);   
    affichageAnnee(annee, jour);
    
    
    return EXIT_SUCCESS;
}


bool estBissextile(int annee)
{
    return !(annee % 400) || (!(annee % 4) && (annee % 100));
}


bool jourValide(int jour)
{
    return (jour > 0 && jour <= 7) ? true : false;
}


int saisieUtilisateur(string question, string erreur, int valMin, int valMax)
{
   int valeur;
   bool entree_valide = false;
   cout << question;   
   
   do
   {
      if (entree_valide = (not(cin >> valeur) || (valeur <  valMin ||  valeur > valMax)))
      {
         cout << erreur << endl;
         cin.clear();
         cin.ignore(numeric_limits<int>::max(), '\n');
         cout << question;   
      }      
   } 
   while(entree_valide);   
   
   return valeur;
}


int premierJourJanvier(int annee)
{
    // nombre de jours dans une semaine
    const int NB_JOUR_SEMAINE = 7;
    
    // jour represente le jour dans le mois
    int jour = 1;
    
    // m corrrespond à la somme de 1(premier mois de l'annee) et 10 (une constante))
    int m = 11;
    
    // a vaut annee-1 si on calcule le premier jour de mois de janv. ou fev. et annee pour les autres mois
    int a = annee - 1;
    
    // on utilise la formule pour affecter son resultat a la variable premierJour
    int premierJour = (jour + a + a / 4 - a / 100 + a / 400 + 31 * m / 12 ) % NB_JOUR_SEMAINE;
    
    // on retourne le resultat de la formule + 1 car on veut obtenir les indices de 1-7 et non pas de 0-6
    return premierJour + 1; 
}


void affichageCentreChaine(string chaine)
{
   int longueur = chaine.length(),
       milieu = ((LARGEUR_MAX - longueur) / 2) + longueur,
       solde = LARGEUR_MAX - milieu;
   
   cout << setw(milieu) << chaine << setw(solde) << "" << endl;    
}


void affichageCentreMois(int mois, int premierJourSemaine)
{    
 
   // on affiche le mois centré correspondant au numéro de mois donné en parametre
    switch(mois)
    {
       case (int)Mois::JANVIER : 
          affichageCentreChaine("Janvier");
          break;
       case (int)Mois::FEVRIER : 
          affichageCentreChaine("Fevrier");
          break;
       case (int)Mois::MARS : 
          affichageCentreChaine("Mars");
          break;
       case (int)Mois::AVRIL : 
          affichageCentreChaine("Avril");
          break;
       case (int)Mois::MAI : 
          affichageCentreChaine("Mai");
          break;
       case (int)Mois::JUIN : 
          affichageCentreChaine("Juin");
          break;
       case (int)Mois::JUILLET : 
          affichageCentreChaine("Juillet");
          break;
       case (int)Mois::AOUT : 
          affichageCentreChaine("Aout");
          break;
       case (int)Mois::SEPTEMBRE : 
          affichageCentreChaine("Septembre");
          break;
       case (int)Mois::OCTOBRE: 
          affichageCentreChaine("Octobre");
          break;
       case (int)Mois::NOVEMBRE: 
          affichageCentreChaine("Novembre");
          break;
       case (int)Mois::DECEMBRE: 
          affichageCentreChaine("Decembre");
          break;
    }
    
    // on affiche l'ordre des jours de la semaine en fonction de la position du lundi(1-7)
    switch(premierJourSemaine)
    {
        //Lundi en position 1
        case 1:
            cout << setw(LARGEUR_MAX) <<  "  L  M  M  J  V  S  D" << endl;  
            break;
        case 2: // Lundi en position 2, etc...
            cout << setw(LARGEUR_MAX) << "  D  L  M  M  J  V  S"<< endl;
            break;
        case 3:
            cout << setw(LARGEUR_MAX) << "  S  D  L  M  M  J  V"<< endl; 
            break;
        case 4:
            cout << setw(LARGEUR_MAX) << "  V  S  D  L  M  M  J"<< endl;
            break;
        case 5:
            cout << setw(LARGEUR_MAX) << "  J  V  S  D  L  M  M"<< endl;
            break;
        case 6:
            cout << setw(LARGEUR_MAX) << "  M  J  V  S  D  L  M "<< endl; 
            break;
        case 7:
            cout << setw(LARGEUR_MAX) << "  M  M  J  V  S  D  L"<< endl; 
            break;
        default:
            cout << "Il y a un probleme!" << endl;
    }
    
}


void affichageAnnee(int annee, int jour)
{
    //variable contenant l'indice de la colonne du dernier jour du mois
    int dernierePos;
    //variable contenant le nombre maximum de jours par mois initialisé à 31 pour Janvier
    int maxJours = 31;
    
    //on affiche l'année entrée par l'utilisateur suivi d'une ligne vide
    cout << endl << setw(ESPACE_AVANT_ANNEE) << annee << setw(ESPACE_APRES_ANNEE) << "" << endl;
    cout << setw(LARGEUR_MAX) << "" << endl;
    
    //on itère sur tous les mois de l'année
    for(int i = (int)Mois::JANVIER ; i <= (int)Mois::DECEMBRE; i++)
    {
        //on affiche le nom du mois en cours
        affichageCentreMois(i, jour);
        //on initialise à 1 une variable contenant le numéro des jours du mois
        int numeroJour = 1;
        //variable booléenne indiquant si on se trouve à la première ligne
        bool premiereLigne = false;
        //variable booléenne nous permettant de savoir s'il faut rajouter une ligne vide à la fin du mois 
        bool rajoutLigne = false;
        
        // on affecte à maxJours le nombre de jours correspondant aux mois
        if(i == (int)Mois::FEVRIER)
        {
            //maxJours vaudra 29 si c'est une année bissextile et 28 sinon
            maxJours = estBissextile(annee) ? (int)JourParMois::FEVRIER + 1 : (int)JourParMois::FEVRIER;
        }//sinon maxJours vaudra 30 pour les mois d'avril, mai, juin et septembre
        else if(i==(int)Mois::AVRIL || i==(int)Mois::JUIN || i==(int)Mois::SEPTEMBRE || i==(int)Mois::NOVEMBRE)
        {
            maxJours = 30;
        }// sinon pour tous les autres mois maxjours vaut 31
        else
        {
            maxJours = 31;
        }
        
        //on itère de la première à la sixième ligne
        for(int li = 1 ; li <= 6; li++)
        {
            //on affecte true à premiereLigne si on est dans la ligne n°1
            premiereLigne = (li==1);
            
            //on itère sur les 7 colonnes des jours de la semaine
            for(int co = 1 ; co <= 7 ; co++)
            {   
                //on déclare un indice de position qui contient le numéro de la position du lundi pour janvier
                int indicePosition;
               
                //on calcule l'indice de la position pour le premier janvier
                if(i == (int)Mois::JANVIER)
                {
                    indicePosition = premierJourJanvier(annee) - 1;
                }
                else //sinon on reprend la derniere position du dernier jour du mois précédant
                {
                    indicePosition = dernierePos + 1;
                }
                
                //on test si l'indice de position vaut 0, alors cela veut dire que l'indice doit être à 7
                if(!indicePosition)
                {
                    indicePosition = 7;
                }
                
                //on déclare une nouvelle variable servant à indiquer le numéro de colonne du premier du mois
                // en fonction de indicePosition
                int indiceColonne = (i == (int)Mois::JANVIER)? (indicePosition + jour - 1) % 7 : indicePosition;
                
                //on doit tester si la valeur égale 0, alors on doit la mettre à 7
                if(!indiceColonne)
                {
                    indiceColonne = 7;
                }
                    
                //si on se trouve dans la 1ère ligne et que le numéro de colonne est plus petit que l'indice
                //de la colonne où le premier jour doit être affiché, alors on affiche un blanc
                if((premiereLigne && co < indiceColonne) )
                {
                    cout << setw(LARGEUR_COLONNE) << "";
                }
                else//sinon, on doit écrire le jour, ou afficher des blancs après la fin du dernier jour
                {
                    //si on a pas atteint le nombre de jours max du mois
                    if(numeroJour <= maxJours)
                    {
                        //on affecte true à rajoutLigne si on est dans la 6ème ligne
                        rajoutLigne = (li == 6);
                        // on affiche le jour avec la largeur adaptée et on incrémente le jour
                        cout << setw(LARGEUR_COLONNE) << numeroJour;
                        numeroJour++;
                        //si on atteint le nombre de jours max, on retient l'indice de la colonne suivante
                        if(numeroJour == maxJours)
                        {
                            //on utilise modulo 7 car on doit numéroter sur 7 colonnes
                            dernierePos = (co + 1) % 7;
                        }
                    }
                    else //sinon, on affiche des blancs jusqu'à la fin de la ligne
                    {
                        cout << setw(LARGEUR_COLONNE) << "";
                    }
                }                   
                
                //si on est à la fin des 7 colonnes
                if(co == 7)
                {
                    //on teste si on doit rajouter une ligne à la fin du mois
                    if(rajoutLigne)
                    {
                        cout << endl << setw(LARGEUR_MAX) << "" << endl;
                    }
                    else // ou simplement retourner à la ligne 
                    {
                        cout << endl;
                    }
                    //si on est à la fin de la première ligne on doit mettre premiereLigne à false
                    premiereLigne = !premiereLigne;
                }   
            }
        }
    }
}