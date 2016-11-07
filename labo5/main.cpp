/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Erick Corazza et Sébastien Saez
 *
 * Created on 7 novembre 2016, 11:12
 */

#include <cstdlib>

using namespace std;

bool estBissextile(int annee);
bool jourValide(int jour);

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
