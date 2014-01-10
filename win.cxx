#ifdef __MINGW32__
#include "catch.hxx"

/**
 *
 *@brief : Clears the terminal
 *
 **/
void ClearScreen()
{
	system("cls");
}// ClearScreen()

/**
 *
 *@brief : Displays the board on windows.
 *
 **/
void ShowMatrix(const CMatrix &Mat)
{
	ClearScreen();
	string matrixTxt;
	for (CVLine i : Mat)
	{
		for (char j : i)
			matrixTxt += j + '|';
		matrixTxt += '\n';
	}
	/* 
	   The matrix is cached in a string before being displayed
	   to reduce print time.
	*/
	cout << matrixTxt;
}// ShowMatrix()

/**
 *
 *@brief : Return the pressed key without having to press enter on windows.
 *
 **/
char GetKey()
{
	return getch();
}// GetKey()

/**
 *
 *@brief : Get the terminal's size's information and use it to dimension the arena on windows. 
 *
 **/
void GetCmdInfo(CPosition &cmd)
{
	CONSOLE_SCREEN_BUFFER_INFO cmdinfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmdinfo);

	cmd.first = cmdinfo.srWindow.Right - cmdinfo.srWindow.Left + 1;
	cmd.second = cmdinfo.srWindow.Bottom - cmdinfo.srWindow.Top + 1;
	assert(cmd.first >= 5 && assert cmd.second >= 5);

	cmd.second = cmd.second >= 5 ? cmd.second : 5;
	cmd.first = cmd.first >= 5 ? cmd.first : 5;
}// GetCmdInfo()

#endif
