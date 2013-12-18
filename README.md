Attrape-moi-si-tu-peux--et-mange-moi-
=====================================

Le projet trop génial de la mort

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

namespace
{
	
	void ClearScreen ()
	{
		cout << "\033[H\x1B[2J";
	}
	
	/*void  ShowMatrix (const CMatrix & Mat)
	{
		ClearScreen();
		cout << "\033[0m";
		unsigned ColorPlayer1 = 31;
		unsigned ColorPlayer2 = 34;
		for (CVLine i : Mat)
		{
			for (char &j : i)
			{
				if (j == KTokenPlayer1) cout << "\033[" << ColorPlayer1 << "m" << j;
				if (j == KTokenPlayer2) cout << "\033[" << ColorPlayer2 << "m" << j;
				else cout << KEmpty;
				cout << '|';
			}
		    cout << endl;
		}
	}
	*/
	
	void ShowMatrix (const CMatrix & Mat)
	{
		for (CVLine i : Mat)
		{
			for (char &j : i)
			{
				cout << j << '|';
			}
			cout << endl;
		}
	}
	
	void InitMat (CMatrix & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2)
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
	
	void MoveToken (CMatrix & Mat, char Move, CPosition  & Pos)
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
		swap(Mat[OldPos.second][OldPos.first], Mat[Pos.second][Pos.first]);
	}
	
	void ReadParamaters (map <string , unsigned> &Params)
	{
		unsigned NbConfig;
        ifstream ifs("config.txt");
		string LineConfig;
        while (!ifs.eof ())
        {
			ifs >> LineConfig;
			LineConfig = LineConfig.substr (0, LineConfig.size () - 1);
			ifs >> NbConfig;
			Params["LineConfig"] = NbConfig;
        }
	}
	
	int Run ()
	{
	    CMatrix Mat;
		// map <string , unsigned> Params;
		// ReadParamaters (Params);
		unsigned NbLine;
		cin >> NbLine;
		unsigned NbColumn;
		cin >> NbColumn;
		CPosition PosPlayer1;
		cin >> PosPlayer1.first;
		cin >> PosPlayer1.second;
		CPosition PosPlayer2;
		cin >> PosPlayer2.first;
		cin >> PosPlayer2.second;
		InitMat (Mat, NbLine, NbColumn, PosPlayer1, PosPlayer2);
		for (;;)
		{
			ShowMatrix (Mat);
			char MovePlayer1;
			cin >> MovePlayer1;
			MoveToken (Mat, MovePlayer1, PosPlayer1);
			if (
			ShowMatrix (Mat);
			char MovePlayer2;
			cin >> MovePlayer2;
			MoveToken (Mat, MovePlayer2, PosPlayer2);
		}
		return 0;
	} 
	

}
	/*int Run ()
	{
	    CMatrix Mat;
		// map <string , unsigned> Params;
		// ReadParamaters (Params);
		unsigned NbLine;
		cin >> NbLine;
		unsigned NbColumn;
		cin >> NbColumn;
		CPosition PosPlayer1;
		cin >> PosPlayer1.first;
		cin >> PosPlayer1.second;
		CPosition PosPlayer2;
		cin >> PosPlayer2.first;
		cin >> PosPlayer2.second;
		InitMat (Mat, NbLine, NbColumn, PosPlayer1, PosPlayer2);
		for (;;)
		{
			ShowMatrix (Mat);
			char MovePlayer1;
			cin >> MovePlayer1
			MoveToken (Mat, MovePlayer1, PosPlayer1);
			ShowMatrix (Mat);
			char MovePlayer2;
			cin >> MovePlayer2;
			MoveToken (Mat, MovePlayer2, PosPlayer2);
			ShowMatrix (Mat);
		}
		return 0;
	 */  

	    
	// initmatrix
	
	//showmatrix..
	
	/*tant qu'on peut jouer && non victoire
	    */
	 
	// }

int main ()
{
	Run ();
}

