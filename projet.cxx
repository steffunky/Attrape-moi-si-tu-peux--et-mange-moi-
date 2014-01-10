/**
 *
 *@file : projet.cxx
 *
 *@author : Mickael BRUNEL, Anthony ALEGRE, Nabil BOUTEMEUR, Stéphen ABELLO
 *
 *@date : 18/12/2013
 *
 *@brief : Funny and functionnal game
 *
 **/



#ifndef DEBUG
#define NDEBUG
#endif

#include "catch.hxx"

namespace Jesuss
{
	/**
	 *
	 *@brief : Initializes the matrix.
	 *
	 **/
    void InitMat (CMatrix &Mat, unsigned NbLine, unsigned NbColumn, CPosition &PosPlayer1, CPosition &PosPlayer2)
    {
		const char KTokenPlayer1 = 'X';
		const char KTokenPlayer2 = 'O';

        Mat.resize(NbLine);
        for (CVLine &i : Mat)
        {
            i.resize(NbColumn);
            for (char &j : i)
				j = ' ';
        }

        /* Sets the tokens on the board */
        assert(PosPlayer1.second < Mat.size() && PosPlayer2.second < Mat.size());
        assert(PosPlayer1.first < Mat[0].size() && PosPlayer2.first < Mat[0].size());

        Mat[PosPlayer1.second][PosPlayer1.first] = KTokenPlayer1;
        Mat[PosPlayer2.second][PosPlayer2.first] = KTokenPlayer2;
    }// InitMat()

	/**
	 *
	 *@brief : Prevents a player from going outside the board
	 *
	 **/
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

	/**
	 *
	 *@brief : Move the player's token according to the pressed key (Used in Turn Based mod).
	 *
	 **/
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

        if(OldPos != Pos)//Prevents the player of deleting himself in case of his position got clamped
        {
            Mat[Pos.second][Pos.first] = Mat[OldPos.second][OldPos.first];
            Mat[OldPos.second][OldPos.first] = ' ';
        }
    }

	/**
	 *
	 *@brief : Checks if the char is in the char tab.
	 *
	 **/
    bool Contains(const char Tab[], unsigned size, char value)
    {
        for (unsigned i = 0; i < size; ++i)
        {
            if (Tab[i] == value)
                return true;
        }

        return false;
    }

	/**
	 *
	 *@brief : Move the players' token according to the pressed key (Used in dynamic mod).
	 *
	 **/
    unsigned MoveTokenPlayers(CMatrix &Mat, char Move, CPosition &PosPlayer1, CPosition &PosPlayer2)
    {
        CPosition NewPos;
        CPosition players[2];

        /* The move is player 1... */
        unsigned currentP = 0;

        /* ... unless the pressed key belongs to player 2*/
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

        if (NewPos != players[currentP])
        {
            Mat[NewPos.second][NewPos.first] = Mat[players[currentP].second][players[currentP].first];
            Mat[players[currentP].second][players[currentP].first] = ' ';
        }

        currentP == 0 ? PosPlayer1 = NewPos : PosPlayer2 = NewPos;
        return currentP;
    }// MoveTokenPlayers()

	/**
	 *
	 *@brief : Set basical parameters and if they are not in the config file, they wont be replaced.
	 *
	 **/	
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
        Params["tpt"] = 1;
		Params["menu"] = 0;
		Params["ai"] = 0; //disabled
		Params["ailevel"] = 0;//0 = easy, 1 = impossible

    }// SetDefaultParameters()

	/**
	 *
	 *@brief : Determinate if the input char is a digit or not, return boolean.
	 *
	 **/	
    bool isdigit(char c)
    {
        return ('0' <= c && c <= '9');
    }// isdigit()
	

	/**
	 *
	 *@brief : Read through the config file, read the parameter name and its value, put them into the map Params.
	 *
	 **/	
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
            if(LineConfig[0] == '#' || isdigit(LineConfig[0]))//isdigit because after we ignore the name of the param, the stream will be probably positionned on its value
                continue;

            LineConfig = LineConfig.substr (0, LineConfig.size() - 1); // remove the : at end of para's name
            ifs >> NbConfig;//reads the param value
            Params[LineConfig] = NbConfig;
        }
    }// ReadParameters()

	/**
	 *
	 *@brief : Menu to choose Game mode.
	 *
	 **/
	void GameMenu(map <string,unsigned> &Params)
    {
        cout << "     WELCOME \n  IN THE ARENA\n\n";
		cout << "Select a game mod\nT : Turn based game\nD : Dynamic game\nOther : Exit" << endl;

		switch(toupper(GetKey()))
		{
		case 'T':
			Params["tpt"] = 1;
			break;
		case 'D':
			Params["tpt"] = 0;
			break;
		default:
			exit(-1);
		}
		
    }

	/**
	 *
	 *@brief : Main function of the game, call the function in the right order to make run the game, return the number of winner player.
	 *
	 **/	
    int Run()
    {
        CMatrix Mat;
		CPosition PosPlayer1;
		CPosition PosPlayer2;

        char Move;
        map <string, unsigned> Params;
		int status;
        int i = 0;

		srand(time((long int *)0));
        SetDefaultParameters(Params);
        ReadParameters(Params);

		if(Params["menu"]) GameMenu(Params);
	
        PosPlayer1.first = Params["XPosPlay1"];
        PosPlayer1.second = Params["YPosPlay1"];

        PosPlayer2.first = Params["XPosPlay2"];
        PosPlayer2.second = Params["YPosPlay2"];

        InitMat(Mat, Params["NbLine"], Params["NbCol"], PosPlayer1, PosPlayer2);

        ShowMatrix(Mat);

        for (Params["nb_turns"] *= 2; PosPlayer1 != PosPlayer2 && Params["nb_turns"]; ShowMatrix(Mat))
        {
            if (Params["tpt"])
            {
				if(Params["ai"] && i % 2 == 1)
					Move = Params["ailevel"] == 0 ? AILevel0(PosPlayer1, PosPlayer2) : AILevel1(PosPlayer1, PosPlayer2);
				else
					while((Move = GetKey()) && !Contains(p1keys, 8, toupper(Move)));
                MoveToken(Mat, Move, ++i % 2 == 0 ? PosPlayer2 : PosPlayer1);
            }
            else
                (Move = GetKey()) && (status = MoveTokenPlayers(Mat, Move, PosPlayer1, PosPlayer2));
            Params["nb_turns"] -= Params["inf_turns"] != 0 && PosPlayer1 != PosPlayer2;
        }

        status = Mat[PosPlayer1.second][PosPlayer1.first] == 'O'; /*status = 1 if p2 wins otherwise 0 */

        if(Params["NbCol"] >= 4)
            cout << string(Params["NbCol"] - 4, ' ');/* outputs spaces minus half the space "Bravo JX"
														take to align in the bottom center of the board */
		if(Params["nb_turns"])
            cout << "Bravo J" << (char)((status) + '1')
                 << '!' << endl;
        else
            cout << "Egalite!" << endl;

        GetKey();// prevent from exiting brutally
        //ClearScreen();
        return status;
    }
}

using namespace Jesuss;

/**
 *
 *@brief : Call the main function of the game.
 *
 **/	
int main()
{
    return Run();
}

