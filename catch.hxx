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

#define ABS(x)    (x < 0 ? -x : x)
#define MAX(x, y) (x > y ?  x : y)

#include <iostream>
#include <unistd.h>
#include  <fstream>
#include  <cassert>
#include   <string>
#include   <vector>
#include      <map>

#ifdef __unix__
#include <sys/ioctl.h>
#define TERM_SIZE 0x5413

int      rand(void)                __THROW;
void     srand(unsigned int seed)  __THROW;
long int time(long int *timer)     __THROW;
#endif

#ifdef __MINGW32__
#include <windows.h>
#include   <conio.h>
#include    <time.h>
#endif

using namespace std;

typedef vector   <char>             CVLine;
typedef vector <CVLine>            CMatrix;

typedef pair<unsigned, unsigned> CPosition;

int system(const char *command);

/* lin/win.cxx */
void ClearScreen();
char GetKey();
void ShowMatrix(const CMatrix &Mat);
void GetCmdInfo(CPosition &cmdinfo);

/* ai.cxx */
char AILevel0(CPosition &PosPlayer1, CPosition &PosPlayer2);
char AILevel1(CPosition &PosPlayer1, CPosition &PosPlayer2);
int  distance(CPosition &PosPlayer1, CPosition &PosPlayer2);
pair <int, int>   Substract(CPosition arg1, CPosition arg2);

constexpr char p1keys[] = {'A', 'Z', 'E', 'Q', 'D', 'W', 'X', 'C'};
constexpr char p2keys[] = {'R', 'T', 'Y', 'F', 'H', 'V', 'B', 'N'};

#endif
