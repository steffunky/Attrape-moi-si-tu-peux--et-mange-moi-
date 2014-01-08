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

#ifndef __CATCH_HPP__
#define __CATCH_HPP__

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <unistd.h>

#ifdef __unix__
#include <sys/ioctl.h>
#define TERM_SIZE 0x5413
#endif

#ifdef __MINGW32__
#include <windows.h>
int getch();
#endif

#include <cassert>

using namespace std;

typedef vector <char> CVLine;
typedef vector <CVLine> CMatrix;
typedef pair   <unsigned, unsigned> CPosition;


constexpr char p1keys[] = {'A', 'Z', 'E', 'Q', 'D', 'W', 'X', 'C'};
constexpr char p2keys[] = {'R', 'T', 'Y', 'F', 'H', 'V', 'B', 'N'};

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

int system(const char *command);

CPosition PosPlayer1;
CPosition PosPlayer2;

int status;

#endif
