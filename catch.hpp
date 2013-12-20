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
#include <cstdlib>
#include <map>
#include <conio.h>

using namespace std;

typedef vector <char> CVLine;
typedef vector <CVLine> CMatrix;
typedef pair   <unsigned, unsigned> CPosition;

const char KTokenPlayer1 = 'X';
const char KTokenPlayer2 = 'O';
const char KEmpty        = ' ';

const string KReset  = "0";
const string KNoir   = "30";
const string KRouge  = "31";
const string KVert   = "32";
const string KJaune  = "33";
const string KBleu   = "34";
const string KMAgenta= "35";
const string KCyan   = "36";

CPosition PosPlayer1;
CPosition PosPlayer2;

int status;
