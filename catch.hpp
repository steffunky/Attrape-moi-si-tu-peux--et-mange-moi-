/**
 *
 *@file : catch.hpp
 *
 *@author : Mickael BRUNEL, Anthony ALEGRE, Nabil BOUTEMEUR, Stéphen ABELLO
 *
 *@date : 18/12/2013
 *
 *@brief : Initialisation pour main.cpp
 *
**/


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille
typedef pair   <unsigned, unsigned> CPosition; // un type représentant une coordonnée dans la grille
const char KTokenPlayer1 = 'X';
const char KTokenPlayer2 = 'O';
const char KEmpty        = ' ';
const string KReset   ("0");
const string KNoir    ("30");
const string KRouge   ("31");
const string KVert    ("32");
const string KJaune   ("33");
const string KBleu    ("34");
const string KMAgenta ("35");
const string KCyan    ("36");
