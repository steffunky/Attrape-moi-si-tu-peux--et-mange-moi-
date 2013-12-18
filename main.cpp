/**
 *
 *@file : main.cpp
 *
 *@author : Mickael BRUNEL, Anthony ALEGRE, Nabil BOUTEMEUR, Stéphen ABELLO
 *
 *@date : 18/12/2013
 *
 *@brief : Projet C++ semestre 1, "catch me if you can"
 *
**/

#include "catch.hpp"
int Run();


namespace Jesuss
{
	
	void ClearScreen ()
	{
		cout << "\033[H\x1B[2J";
	}
	
	void Color (const string & col)
    {
        cout << "\033[" << col <<"m";
    }
	
	void  ShowMatrix (const CMatrix & Mat)
	{
		ClearScreen();
		Color(KReset);
		for (CVLine i : Mat)
		{
			for (char &j : i)
			{
				if (j == KTokenPlayer1) cout << "\033[" << KRouge << "m" << j;
				if (j == KTokenPlayer2) cout << "\033[" << KBleu << "m" << j;
				else cout << KEmpty;
				cout << '|';
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
	

}

    void ReadParameters()
    {
        unsigned i = 0;
        vector<pair<string, int>> params;
        ifstream ifs("config.txt"); 
        for(; !ifs.eof(); ifs >> params[i].first && ifs >> params[i].second )
        {
            ++i;
            cout << params[i].first << params[i].second << endl;
        }
    }

	int Run ()
	{
	    CMatrix Mat;
	    
	    

	    
	// initmatrix
	
	//showmatrix..
	
	/*tant qu'on peut jouer && non victoire
	    */
	   return 0; 
	}
int main (int argc, char **argv)
{
	return Run ();
}

