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

#ifndef DEBUG
#define NDEBUG
#endif

#include "catch.hpp"



namespace Jesuss
{

#ifdef __unix__

    void ClearScreen()
    {
        cout << "\033[2J\033[1;1H";//outputs a reset escape code for VT-100 terminals
    }// ClearScreen()

    char GetKey()
    {
        char c;
        system("stty cbreak -echo"); // disables stdin buffering and echoing
        c = getchar();
        assert('A' <= toupper(c) && toupper(c) <= 'Z');
        system("stty cooked echo"); // restores the terminal in its normal state
        return c;
    }// GetKey()

    void  ShowMatrix(const CMatrix &Mat)
    {
        ClearScreen();
        cout << "\033[0m"; //sets the normal color
        /* color codes for the two players */
        unsigned ColorPlayer1 = 31;
        unsigned ColorPlayer2 = 34;
        for (CVLine i : Mat)
        {
            for (char j : i)
            {
                if (j == KTokenPlayer1)
                    cout << "\033[" << ColorPlayer1 << "m" << j << "\033[0m";
                else if (j == KTokenPlayer2)
                    cout << "\033[" << ColorPlayer2 << "m" << j << "\033[0m";
                else
                    cout << ' ';
                cout << '|';//grid delimiter
            }
            cout << endl;
        }
        cout << endl;
    }// ShowMatrix()

    void GetCmdInfo(CPosition &cmdinfo)
    {
        unsigned short cmd[2];     // abstraction of the ttysize struct
        ioctl(1, TIOCGWINSZ, cmd);
        assert(cmd[0] >= 5 && cmd[1] >= 5);
        //5x5 are the minimal dimensions
        cmdinfo.first = cmd[1] >= 5 ? cmd[1] : 5;
        cmdinfo.second = cmd[0] >= 5 ? cmd[0] : 5;
    }// GetCmdInfo()

#endif

#ifdef __MINGW32__

    void ClearScreen()
    {
        system("cls");
    }// ClearScreen()

    void ShowMatrix(const CMatrix &Mat)
    {
        ClearScreen();
        for (CVLine i : Mat)
        {
            for (char j : i)
            {
                cout << j << '|';
            }

            cout << '\n';
        }
    }// ShowMatrix()

    char GetKey()
    {
        return getch();
    }// GetKey()

    void GetCmdInfo(CPosition &cmd)
    {
        CONSOLE_SCREEN_BUFFER_INFO cmdinfo;
        /*
           We can't abstract the CSBI struct here because GCSBI
           expects a pointer to the struct, not a void *
        */
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmdinfo);
        cmd.first = cmdinfo.srWindow.Right - cmdinfo.srWindow.Left + 1;
        cmd.second = cmdinfo.srWindow.Bottom - cmdinfo.srWindow.Top + 1;
        assert(cmd.first >= 5 && cmd.second >= 5);
        cmd.second = cmd.second >= 5 ? cmd.second : 5;
        cmd.first = cmd.first >= 5 ? cmd.first : 5;
    }// GetCmdInfo 

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
        /* Sets the tokens on the board */
        assert(PosPlayer1.second < Mat.size() && PosPlayer2.second < Mat.size());
        assert(PosPlayer1.first < Mat[0].size() && PosPlayer2.first < Mat[0].size());

        Mat[PosPlayer1.second][PosPlayer1.first] = KTokenPlayer1;
        Mat[PosPlayer2.second][PosPlayer2.first] = KTokenPlayer2;
    }// InitMat()

    void clamp(const CMatrix &Mat, CPosition &Pos)
    {

        /*
          ~OU: ~ is a NOT operator, which toggles the bit of the unary expression 0,
          which returns the maximum value for an unsigned integrer. The U specifies
          this integrer is unsigned.
        */
        Pos.first = Pos.first == ~0U ? 0 : Pos.first;
        Pos.first = Pos.first >= Mat[0].size() ? Mat[0].size() - 1 : Pos.first;
        Pos.second = Pos.second == ~0U ? 0 : Pos.second;
        Pos.second = Pos.second >= Mat.size() ? Mat.size() - 1 : Pos.second;
    }// clamp()

    void MoveToken(CMatrix &Mat, char Move, CPosition &Pos)
    {
        CPosition OldPos = Pos; //We save the old position

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

        /*
          Checks if the newly calculated position Pos is invalid.
          eg: Out of bounds
        */
        clamp(Mat, Pos);

/*      if (OldPos != Pos)
            Mat[Pos.second][Pos.first] = ' ';

        swap (Mat[Pos.second][Pos.first] ,Mat[OldPos.second][OldPos.first]);
*/
        if(OldPos != Pos)//Prevents the player of deleting himself in case of his position got clamped
        {
            Mat[Pos.second][Pos.first] = Mat[OldPos.second][OldPos.first];
            Mat[OldPos.second][OldPos.first] = ' ';
        }
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

        /* The move is player 1... */
        unsigned currentP = 0;

        /* ... unless the key pressed belong to player 2*/
        if(Contains(p2keys, 8, toupper(Move)))
            ++currentP;

        players[0] = PosPlayer1;
        players[1] = PosPlayer2;

        // Here we decide whose position is gonna change
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
/*      if (NewPos != players[currentP])
            Mat[NewPos.second][NewPos.first] = ' ';
        swap(Mat[players[currentP].second][players[currentP].first], Mat[NewPos.second][NewPos.first]);
*/

        if (NewPos != players[currentP])
        {
            Mat[NewPos.second][NewPos.first] = Mat[players[currentP].second][players[currentP].first];
            Mat[players[currentP].second][players[currentP].first] = ' ';
        }

        currentP == 0 ? PosPlayer1 = NewPos : PosPlayer2 = NewPos;
        return currentP;
    }// MoveTokenPlayers()

    void SetDefaultParameters (map <string, unsigned> &Params)
    {
        CPosition cmdDims;

        GetCmdInfo(cmdDims);
        --cmdDims.first /= 2; //Columns, divided by two
                              //because of the delimiter | taking half the space
        ------cmdDims.second; //removes 3 lines to make enough space for the "Bravo" to prevent scrolling

        /* Default parameters */
        Params["NbLine"] = cmdDims.second;
        Params["NbCol"] = cmdDims.first;
        Params["XPosPlay1"] = 0;
        Params["YPosPlay1"] = Params["NbLine"] - 1;
        Params["XPosPlay2"] = Params["NbCol"] - 1;
        Params["YPosPlay2"] = 0;
        Params["nb_turns"] = 1;
        Params["inf_turns"] = 0;
        Params["tpt"] = 0;
        /* If they are not in the config file, they wont be replaced*/
    }// SetDefaultParameters()

    bool isdigit(char c)
    {
        return ('0' <= c && c <= '9');
    }// isdigit()

    void ReadParameters (map <string, unsigned> &Params)
    {
        unsigned NbConfig;
        ifstream ifs("config.txt");
        string LineConfig;

        if(!ifs.is_open())
            return;

        while (!ifs.eof())
        {
            ifs >> LineConfig;//reads the param name

            // ignore comments in config file
            if(LineConfig[0] == '#' || isdigit(LineConfig[0]))//isdigit because after we ignore the name of the param, the stream will be probably positionned on its value
                continue;

            LineConfig = LineConfig.substr (0, LineConfig.size() - 1); // remove the : at end of para's name
            ifs >> NbConfig;//reads the param value
            Params[LineConfig] = NbConfig;
        }
    }// ReadParameters()

	void GameMenu(map <string,unsigned> &Params, bool &Exit)
    {
    	char GameMod;
		cout << "Select a game mod" << endl
			 << "T : Turn based game" << endl
			 << "D : Dynamic game" << endl
			 << "Other : Exit" << endl;
		GameMod=GetKey();
		switch(toupper(GameMod))
		{
			case 'T':
				Params["tpt"]=1;
				break;
			case 'D':
				Params["tpt"]=0;
				break;
			default:
				Exit=true;
				break;	
		}
		
    }
	

    int Run()
    {
        CMatrix Mat;
        char Move;
        int i = 0;
        map <string, unsigned> Params;

        SetDefaultParameters(Params);
        ReadParameters(Params);

		bool Exit = false;
		GameMenu(Params, Exit);	
		if (Exit) return 0;

        PosPlayer1.first  = Params["XPosPlay1"];
        PosPlayer1.second = Params["YPosPlay1"];

        PosPlayer2.first  = Params["XPosPlay2"];
        PosPlayer2.second = Params["YPosPlay2"];

        InitMat(Mat, Params["NbLine"], Params["NbCol"], PosPlayer1, PosPlayer2);

        ShowMatrix(Mat);

        for (Params["nb_turns"] *= 2; PosPlayer1 != PosPlayer2 && Params["nb_turns"]; ShowMatrix(Mat))
        {
            if (Params["tpt"])
            {
                while((Move = GetKey()) && !Contains(p1keys, 8, toupper(Move)));
                MoveToken(Mat, Move, ++i % 2 == 0 ? PosPlayer2 : PosPlayer1);
            } //Given the number of turns elapsed, we move p2 or p1
            else
			{
                Move = GetKey();
				status = MoveTokenPlayers(Mat, Move);
            }
			Params["nb_turns"] -= Params["inf_turns"] && PosPlayer1 != PosPlayer2;
        }

        status = Mat[PosPlayer1.second][PosPlayer1.first] == 'O'; //status = 1 if p2 wins otherwise 0 

        if(Params["NbCol"] >= 4)
            cout << string(Params["NbCol"] - 4, ' ');/* outputs spaces minus half the space "Bravo JX"
                                                        take to align in the bottom center of the board */
        if(Params["nb_turns"])
            cout << "Bravo J" << (char)((status) + '1')
                 << '!' << endl;
        else
            cout << "Egalite!" << endl;

        GetKey();// prevent from exiting brutally
        return status;
    }

}

using namespace Jesuss;

int main()
{
    return Run();
}
