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
		system("stty cbreak -echo"); // enleve la mise en tampon des caracteres et leur affichage dans le terminal quand on les tapes
		c = getchar();
		system("stty cooked echo"); // restore dans l'etat normal
		return c;
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
    
	void GetCmdInfo(CPosition &cmdinfo)
	{
		unsigned short cmd[2];
		ioctl(1, TIOCGWINSZ, cmd);
		cmdinfo.first = cmd[1];
		cmdinfo.second = cmd[0];
	}
	
#endif
	
#ifdef __MINGW32__
    
	void ClearScreen()
	{
		system("cls");
	}
	
    /* A faire*/
    /* Optimiser l'affichage de la matrice*/
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
	
	void GetCmdInfo(CPosition &cmd)
	{	
		CONSOLE_SCREEN_BUFFER_INFO cmdinfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmdinfo);
		cmd.first = cmdinfo.srWindow.Right - cmdinfo.srWindow.Left + 1;
		cmd.second = cmdinfo.srWindow.Bottom - cmdinfo.srWindow.Top + 1;
		
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
	
	void MoveToken(CMatrix &Mat, char Move, CPosition &Pos)
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
		}
		
		clamp(Mat, Pos);
		if (OldPos != Pos) Mat[Pos.second][Pos.first] = ' ';
		swap (Mat[Pos.second][Pos.first] , Mat[OldPos.second][OldPos.first]);
	}
	
	bool Contains(const char Tab[], unsigned size, char value)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			if (Tab[i] == value)
				return true;
		}
		
		return false;
	}
	
	unsigned MoveTokenPlayers(CMatrix &Mat, char Move)
	{
		CPosition NewPos;
		CPosition players[2];
		unsigned currentP = 0;

		players[0] = PosPlayer1;
		players[1] = PosPlayer2;
		
		if(Contains(p2keys, 8, toupper(Move)))
			++currentP;

		NewPos = currentP == 0 ? PosPlayer1 : PosPlayer2;
		switch (toupper(Move))
		{
		case p1keys[0]:
		case p2keys[0]:
			--NewPos.second;
			--NewPos.first;
			break;
		case p1keys[1]:
		case p2keys[1]:
			--NewPos.second;
			break;
		case p1keys[2]:
		case p2keys[2]:
			--NewPos.second;
			++NewPos.first;
			break;
		case p1keys[3]:
		case p2keys[3]:
			--NewPos.first;
			break;
		case p1keys[4]:
		case p2keys[4]:
			++NewPos.first;
			break;
		case p1keys[5]:
		case p2keys[5]:
			++NewPos.second;
			--NewPos.first;
			break;
		case p1keys[6]:
		case p2keys[6]:
			++NewPos.second;
			break;
		case p1keys[7]:
		case p2keys[7]:
			++NewPos.first;
			++NewPos.second;
		}
		
		clamp(Mat, NewPos);
		if (NewPos != players[currentP])
			Mat[NewPos.second][NewPos.first] = ' ';
		swap(Mat[players[currentP].second][players[currentP].first], Mat[NewPos.second][NewPos.first]);
		currentP == 0 ? PosPlayer1 = NewPos : PosPlayer2 = NewPos;

		return currentP;
}
	
	void SetDefaultParameters (map <string, unsigned> &Params)
	{
		CPosition cmdDims;

		GetCmdInfo(cmdDims);
		--cmdDims.first /= 2;
		----cmdDims.second;
          
		Params["NbLine"] = cmdDims.second;
		Params["NbCol"] = cmdDims.first;
		Params["XPosPlay1"] = 0;
		Params["YPosPlay1"] = Params["NbLine"] - 1;
		Params["XPosPlay2"] = Params["NbCol"] - 1;
		Params["YPosPlay2"] = 0;
		Params["nb_turns"] = 1;
		Params["inf_turns"] = 0;
		Params["tpt"] = 1;
	}
	
	bool isdigit(char c)
	{
		return ('0' <= c && c <= '9');
	}
	
	void ReadParameters (map <string, unsigned> &Params)
	{ 
		unsigned NbConfig;
		ifstream ifs("config.txt");
		string LineConfig;

		if(!ifs.is_open())
			return;

		while (!ifs.eof())
		{
			ifs >> LineConfig;
			
			/* ignore comments in config file */
			if(LineConfig[0] == '#' || isdigit(LineConfig[0]))
				continue;

			LineConfig = LineConfig.substr (0, LineConfig.size() - 1);
			ifs >> NbConfig;
			Params[LineConfig] = NbConfig;
		}
    }
    
    int Run()
    {
        CMatrix Mat;
		char Move;
		int i = 0;
		map <string, unsigned> Params;

		SetDefaultParameters(Params);
		ReadParameters (Params);

		PosPlayer1.first = Params["XPosPlay1"];
		PosPlayer1.second = Params["YPosPlay1"];
		PosPlayer2.first = Params["XPosPlay2"];
		PosPlayer2.second = Params["YPosPlay2"];
		
		InitMat (Mat, Params["NbLine"], Params["NbCol"], PosPlayer1, PosPlayer2);
		
		ShowMatrix (Mat);

		for (Params["nb_turns"] *= 2;cout << i << endl && (Move = GetKey()) && Params["nb_turns"] != 0; ShowMatrix (Mat))
		{
			if (Params["tpt"])
			{
				CPosition &currPlayer = ++i % 2 == 0 ? PosPlayer2 : PosPlayer1;
				MoveToken (Mat, Move, currPlayer);
			}
			else
				status = MoveTokenPlayers (Mat, Move);

			if (PosPlayer1 == PosPlayer2 || !Params["nb_turns"])
			{
				ShowMatrix (Mat);
				status = Mat[PosPlayer1.second][PosPlayer1.first] == 'O';
				break;
			}

			Params["nb_turns"] -= Params["inf_turns"] != 0 && PosPlayer1 != PosPlayer2;
		}

		cout << string(Params["NbCol"] - 4, ' ');

		if(Params["nb_turns"])
			cout << "Bravo J" << (char)((status) + '1') 
				 << '!' << endl;
		else
			cout << "Egalite!" << endl;

		GetKey();
		return status;
    }
}

using namespace Jesuss;        

int main()
{
	return Run();
}

