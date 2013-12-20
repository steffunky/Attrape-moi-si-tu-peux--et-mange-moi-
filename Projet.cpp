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
		cout << "\033[H\x1B[2J";
	}
	

	void  ShowMatrix(const CMatrix &Mat)
	{
		ClearScreen();
		cout << "\033[0m";
		unsigned ColorPlayer1 = 31;
		unsigned ColorPlayer2 = 34;
		for (CVLine i : Mat)
		{
			for (char &j : i)
			{
				if (j == KTokenPlayer1)
					cout << "\033[" << ColorPlayer1 << "m" << j;
				if (j == KTokenPlayer2) 
					cout << "\033[" << ColorPlayer2<< "m" << j;
				else
					cout << KEmpty;
				cout << '|';
			}

		    cout << endl;
		}
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

#endif

	void InitMat (CMatrix &Mat, unsigned NbLine, unsigned NbColumn,
				  CPosition &PosPlayer1,
				  CPosition &PosPlayer2)
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
		Pos.first = Pos.first >= Mat[0].size() ? Mat[0].size() - 1 : Pos.first;
		Pos.first = Pos.first <= 0 ? 0 : Pos.first;
		Pos.second = Pos.second >= Mat.size() ? Mat.size() - 1 : Pos.second;
		Pos.second = Pos.second <= 0 ? 0 : Pos.second;
		
	}
	
	void MoveToken (CMatrix &Mat, char Move, CPosition &Pos)
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
	
	void ReadParamaters (map <string, unsigned> &Params)
	{ 
		unsigned NbConfig;
        ifstream ifs("config.txt");
		string LineConfig;
        while (!ifs.eof())
        {
			//cout << "Coucou" << endl;
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

		/*	Params["XPosPlay1"] = Params["NbLine"] - 1;
		Params["YPosPlay2"] = Params["NbCol"] - 1;

		Params["YPosPlay1"] = 0;
		Params["XPosPlay2"] = 0;*/

		ReadParamaters (Params);
		// unsigned NbLine;
		// cin >> NbLine;
		// unsigned NbColumn;
		// cin >> NbColumn;
		// CPosition PosPlayer1;
		// cin >> PosPlayer1.first;
		// cin >> PosPlayer1.second;
		// CPosition PosPlayer2;
		// cin >> PosPlayer2.first;
		// cin >> PosPlayer2.second;
		
		PosPlayer1.first = Params["XPosPlay1"];
		PosPlayer1.second = Params["YPosPlay1"];
		PosPlayer2.first = Params["XPosPlay2"];
		PosPlayer2.second = Params["YPosPlay2"];
		
		InitMat (Mat,
				 Params["NbLine"],
				 Params["NbCol"],
				 PosPlayer1,
				 PosPlayer2);
		for (;;)
		{
			char MovePlayer1;
			char MovePlayer2;

			ShowMatrix (Mat);
			cout << "X1: " << PosPlayer1.first << " Y1: " << PosPlayer1.second << endl;
			cout << "X2: " << PosPlayer2.first << " Y2: " << PosPlayer2.second << endl;
			MovePlayer1 = getch();
			MoveToken (Mat, MovePlayer1, PosPlayer1);

			ShowMatrix (Mat);			
			cout << "X1: " << PosPlayer1.first << " Y1: " << PosPlayer1.second << endl;
			cout << "X2: " << PosPlayer2.first << " Y2: " << PosPlayer2.second << endl;
			MovePlayer2 = getch();
			MoveToken (Mat, MovePlayer2, PosPlayer2);
		} 
		return 0;
	}
	

}



using namespace Jesuss;	

int main()
{
	return Run();
}