#ifdef __unix__
#include "catch.hxx"

/**
 *
 *@brief : Outputs a reset escape code for VT-100 terminals.
 *
 **/
void ClearScreen()
{
	cout << "\033[2J\033[1;1H";

}// ClearScreen()

/**
 *
 *@brief : Returns the pressed key without having to press enter on unix.
 *
 **/
char GetKey()
{
	char c;
	int i; // W:ignoring return value... when compiling with -Wall -Wextra -pedantic
	i = system("stty cbreak -echo"); // disables stdin buffering and echoing
	c = getchar();
	i = system("stty cooked echo"); // restores the terminal in its normal state
	(void)i;
	return c;
}// GetKey()

/**
 *
 *@brief : Display the arena on the terminal.
 *
 **/
void ShowMatrix(const CMatrix &Mat)
{
	const char KTokenPlayer1 = 'X';
	const char KTokenPlayer2 = 'O';

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
}// ShowMatrix()

/**
 *
 *@brief : Get the terminal's size.
 *
 **/
void GetCmdInfo(CPosition &cmdinfo)
{
	unsigned short cmd[2]; // abstraction of the ttysize struct
	ioctl(1, TERM_SIZE, cmd);
	assert(cmd[0] >= 5 && cmd[1] >= 5);
	//5x5 are the minimal dimensions
	cmdinfo.first = cmd[1] >= 5 ? cmd[1] : 5;
	cmdinfo.second = cmd[0] >= 5 ? cmd[0] : 5;
}// GetCmdInfo()

#endif
