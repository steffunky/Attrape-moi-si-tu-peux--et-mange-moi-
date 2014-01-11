/**
 *
 *@file : ai.cxx
 *
 *@author : Mickael BRUNEL, Anthony ALEGRE, Nabil BOUTEMEUR, Stéphen ABELLO
 *
 *@date : 09/01/2014
 *
 *@brief : Two AI for the game.
 *
**/

#include "catch.hxx"
/**
 *
 *@brief : Substracts 2 positions
 *
 **/
pair<int, int> Substract(CPosition arg1, CPosition arg2)
{
	pair<int, int> tmp;
	tmp.first = int(arg1.first - arg2.first);
	tmp.second = int(arg1.second - arg2.second);
	return tmp;
}

/**
 *
 *@brief : Computes the minimal number of key presses required to end the game
 *
 **/
int distance(CPosition &PosPlayer1, CPosition &PosPlayer2)
{
	usleep(300000);
	pair <int, int> tmp = Substract(PosPlayer2, PosPlayer1);
	return MAX(ABS(tmp.first), ABS(tmp.second));
}

/**
 *
 *@brief : Noob AI
 *
 **/
char AILevel0(CPosition &PosPlayer1, CPosition &PosPlayer2)
{
	int steps = distance(PosPlayer1, PosPlayer2);
	pair <int, int>tmp = Substract(PosPlayer2, PosPlayer1);
	int loc = ((tmp.second < 0) << 1) + (tmp.first < 0);

	if(steps % 2)
	{
		switch(loc)
		{
		case 0:
			return 'A';
		case 1:
			return 'E';
		case 2:
			return 'W';
		case 3:
			return 'C';
		}
	}
	else
	{
		switch(loc)
		{
		case 0:
			return tmp.second == 0 ? 'D': 'Q';
		case 1:
			return 'Q';
		case 2:
			return tmp.first == 0 ? 'Z': 'X';
		case 3:
			return 'D';
		}
	}

	/* Should never reach here */
	return p1keys[rand() % 8];
}// AILevel0()

/**
 *
 *@brief : Unbeatable AI
 *
 **/
char AILevel1(CPosition &PosPlayer1, CPosition &PosPlayer2)
{
	int steps = distance(PosPlayer1, PosPlayer2);
	pair <int, int>tmp = Substract(PosPlayer2, PosPlayer1);
	int loc = ((tmp.second < 0) << 1) + (tmp.first < 0);
	if (steps != 2) //we kill him
	{
		switch(loc)
		{
		case 0:
			if (tmp.first == 0)return 'Z';
			else if (tmp.second == 0) return 'Q';
			else return 'A';
		case 1:
			if (tmp.first == 0)return 'Z';
			else if (tmp.second == 0) return 'D';
			else return 'E';
		case 2:
			if (tmp.first == 0)return 'X';
			else if (tmp.second == 0) return 'Q';
			else return 'W';
		case 3:
			if (tmp.first == 0)return 'X';
			else if (tmp.second == 0) return 'D';
			else return 'C';
		}
	}
	else // tries to survive
	{
		switch(loc)
		{
		case 0:
			if (ABS(tmp.first) == ABS(tmp.second))
				return rand() % 2 ? 'Z' : 'Q';
			else if (ABS(tmp.first) > ABS(tmp.second))
				return rand() % 2 ? 'Z' : 'X';
			else
				return rand() % 2 ? 'D' : 'Q';
		case 1:
			if (ABS(tmp.first) == ABS(tmp.second))
				return rand() % 2 ? 'Z' : 'D';
			else if (ABS(tmp.first) > ABS(tmp.second))
				return rand() % 2 ? 'Z' : 'X';
			else
				return rand() % 2 ? 'D' : 'Q';
		case 2:
			if (ABS(tmp.first) == ABS(tmp.second))
				return rand() % 2 ? 'X' : 'Q';
			else if (ABS(tmp.first) > ABS(tmp.second))
				return rand() % 2 ? 'Z' : 'X';
			else
				return rand() % 2 ? 'D' : 'Q';
		case 3:
			if (ABS(tmp.first) == ABS(tmp.second))
				return rand() % 2 ? 'X' : 'D';
			else if (ABS(tmp.first) > ABS(tmp.second))
				return rand() % 2 ? 'Z' : 'X';
			else
				return rand() % 2 ? 'D' : 'Q';
		}
	}

	/* Should never reach here */
	return p1keys[rand() % 8];
}// AILevel1()
