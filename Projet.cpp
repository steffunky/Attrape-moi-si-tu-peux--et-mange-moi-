/**
 *
 *@file : InitMat.cxx
 *
 *@author : Mickael BRUNEL
 *
 *@date : 18/12/2013
 *
 *@brief : InitMatsvp
 *
**/


#include "catch.hpp"


namespace Jesuss
{
                
#ifdef __unix__
        
	void ClearScreen()
	{
		cout << "\033[2J\033[1;1H";
	}
	
	char GetKey()
	{
		char c;
		system("stty cbreak -echo");
		c = getchar();
		system("stty cooked echo");
		return c;
	}

	void  ShowMatrix(const CMatrix &Mat)
	{
		ClearScreen();
		write(1, "\033[0m",4);
		unsigned ColorPlayer1 = 31;
		unsigned ColorPlayer2 = 34;
		for (CVLine i : Mat)
		{
			for (char &j : i)
			{
				if (j == KTokenPlayer1)
					cout << "\033[" << ColorPlayer1 << "m" << j << "\033[0m";
				else if (j == KTokenPlayer2)
					cout << "\033[" << ColorPlayer2 << "m" << j << "\033[0m";
				else
					cout << ' ';
				cout << '|';
			}
			cout << endl;
		}
		cout << endl;
	}

#endif

#ifdef __MINGW32__
        
	void ClearScreen()
	{
		system("cls");
	}
	
	void ShowMatrix(const CMatrix &Mat)
	{
		ClearScreen();
		for (CVLine i : Mat)
		{
			for (char &j : i)
			{
					cout << j << '|';
			}

			cout << endl;
		}
	}

	char GetKey()
	{
		return getch();
	}
#endif

	void InitMat (CMatrix &Mat, unsigned NbLine, unsigned NbColumn, CPosition &PosPlayer1, CPosition &PosPlayer2)
	{
		Mat.resize(NbLine);
		for (CVLine &i : Mat)
		{
			i.resize(NbColumn);
			for (char &j : i)
			{
				j = ' ';
			}
		}
		Mat[PosPlayer1.second][PosPlayer1.first] = KTokenPlayer1;
		Mat[PosPlayer2.second][PosPlayer2.first] = KTokenPlayer2;                
	}

	void clamp(const CMatrix &Mat, CPosition &Pos)
	{
		Pos.first = Pos.first == ~0U ? 0 : Pos.first;
		Pos.first = Pos.first >= Mat[0].size() ? Mat[0].size() - 1 : Pos.first;
		Pos.second = Pos.second == ~0U ? 0 : Pos.second;
		Pos.second = Pos.second >= Mat.size() ? Mat.size() - 1 : Pos.second;
	}

	void MoveTokenPlayer1 (CMatrix &Mat, char Move, CPosition &Pos)
	{
		CPosition OldPos = Pos;
		switch (toupper(Move))
		{
			case 'A':
				--Pos.second;
				--Pos.first;
				break;
			case 'Z':
				--Pos.second;
				break;
			case 'E':
				--Pos.second;
				++Pos.first;
				break;
			case 'Q':
				--Pos.first;
				break;
			case 'D':
				++Pos.first;
				break;
			case 'W':
				++Pos.second;
				--Pos.first;
				break;
			case 'X':
				++Pos.second;
				break;
			case 'C':
				++Pos.first;
				++Pos.second;
				break;
		}

		clamp(Mat, Pos);
			/*if (Pos == PosPlayer1 || Pos == PosPlayer2)
			{
					Mat[Pos.second][Pos.first] = ' ';
			}
			else
			{*/
		swap(Mat[OldPos.second][OldPos.first], Mat[Pos.second][Pos.first]);
					//}
	}
	
	void MoveTokenPlayer1 (CMatrix &Mat, char Move, CPosition &Pos)
	{
		CPosition OldPos = Pos;
		switch (toupper(Move))
		{
			case 'Y':
				--Pos.second;
				--Pos.first;
				break;
			case 'U':
				--Pos.second;
				break;
			case 'I':
				--Pos.second;
				++Pos.first;
				break;
			case 'G':
				--Pos.first;
				break;
			case 'J':
				++Pos.first;
				break;
			case 'V':
				++Pos.second;
				--Pos.first;
				break;
			case 'B':
				++Pos.second;
				break;
			case 'N':
				++Pos.first;
				++Pos.second;
				break;
		}

		clamp(Mat, Pos);
			/*if (Pos == PosPlayer1 || Pos == PosPlayer2)
			{
					Mat[Pos.second][Pos.first] = ' ';
			}
			else
			{*/
		swap(Mat[OldPos.second][OldPos.first], Mat[Pos.second][Pos.first]);
					//}
	}
        
    void ReadParamaters (map <string, unsigned> &Params)
	{ 
		unsigned NbConfig;
		ifstream ifs("config.txt");
		string LineConfig;
		while (!ifs.eof())
		{
			ifs >> LineConfig;
			LineConfig = LineConfig.substr (0, LineConfig.size() - 1);
			ifs >> NbConfig;
			Params[LineConfig] = NbConfig;
		}
    }
    
    int Run()
    {
        CMatrix Mat;
		map <string, unsigned> Params;
            /* Default values */
            /*
            Params["NbLine"] = /* console width */;
            /*Params["NbCol"] = /* console height*/;

            /*        Params["XPosPlay1"] = Params["NbLine"] - 1;
            Params["YPosPlay2"] = Params["NbCol"] - 1;

            Params["YPosPlay1"] = 0;
            Params["XPosPlay2"] = 0;*/
		ReadParamaters (Params);
		PosPlayer1.first = Params["XPosPlay1"];
		PosPlayer1.second = Params["YPosPlay1"];
		PosPlayer2.first = Params["XPosPlay2"];
		PosPlayer2.second = Params["YPosPlay2"];
		InitMat (Mat, Params["NbLine"], Params["NbCol"], PosPlayer1,PosPlayer2);
		cout << "Voulez-vous que le jeu ce passe en plusieurs tours ou en ilimité ?" << endl;
		cout << "Appuyer sur \'Y\' pour accepter" << endl;
		char MoreTurn;
		cin >> MoreTurn;
		if (toupper(MoreTurn) == 'Y')
		{
			unsigned NbTurn;
			cout << "Saisissez le nombre de tour que chaque personne peut avoir" << endl;
			cin >> NbTurn;					
			for (unsigned i = 0; i < NbTurn * 2; ++i)
			{
				char MovePlayer1;
				char MovePlayer2;
				ShowMatrix (Mat);
				cout << "X1: " << PosPlayer1.first << " Y1: " << PosPlayer1.second << endl;
				cout << "X2: " << PosPlayer2.first << " Y2: " << PosPlayer2.second << endl;                        
				MovePlayer1 = GetKey();
				MoveToken (Mat, MovePlayer1, PosPlayer1);
				ShowMatrix (Mat);                        
				cout << "X1: " << PosPlayer1.first << " Y1: " << PosPlayer1.second << endl;
				cout << "X2: " << PosPlayer2.first << " Y2: " << PosPlayer2.second << endl;
				MovePlayer2 = GetKey();
				MoveToken (Mat, MovePlayer2, PosPlayer2);
			}
		}
		else
		{
			for (;;)
			{
				char MovePlayer1;
				char MovePlayer2;
				ShowMatrix (Mat);
				cout << "X1: " << PosPlayer1.first << " Y1: " << PosPlayer1.second << endl;
				cout << "X2: " << PosPlayer2.first << " Y2: " << PosPlayer2.second << endl;                        
				MovePlayer1 = GetKey();
				MoveTokenPlayer1 (Mat, MovePlayer1, PosPlayer1);
				ShowMatrix (Mat);                        
				cout << "X1: " << PosPlayer1.first << " Y1: " << PosPlayer1.second << endl;
				cout << "X2: " << PosPlayer2.first << " Y2: " << PosPlayer2.second << endl;
				MovePlayer2 = GetKey();
				MoveTokenPlayer2 (Mat, MovePlayer2, PosPlayer2);
			} 
			return 0;
		}
    }
}



using namespace Jesuss;        

int main()
{
        return Run();
}
