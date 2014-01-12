/**
 *
 *@file : 
 *
 *@author : Mickael BRUNEL, Anthony ALEGRE, Nabil BOUTEMEUR, Stéphen ABELLO
 *
 *@date : 08/01/2014
 *
 *@brief : Specifics functions used for windows.
 *
**/

#ifdef __MINGW32__
#include "catch.hxx"
namespace Jesuss
{

void ClearScreen()
{
	system("cls");
}// ClearScreen()


void ShowMatrix(const CMatrix &Mat)
{
	ClearScreen();
	string matrixTxt;
	for (CVLine i : Mat)
	{
		for (char j : i)
		{
			matrixTxt += j;
			matrixTxt += '|';
		}
		matrixTxt += '\n';
	}
	/* 
	   The matrix is cached in a string before being displayed
	   to reduce print time.
	*/
	cout << matrixTxt;
}// ShowMatrix()


char GetKey()
{
	return getch();
}// GetKey()


void GetCmdInfo(CPosition &cmd)
{
	CONSOLE_SCREEN_BUFFER_INFO cmdinfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cmdinfo);

	cmd.first = cmdinfo.srWindow.Right - cmdinfo.srWindow.Left + 1;
	cmd.second = cmdinfo.srWindow.Bottom - cmdinfo.srWindow.Top + 1;
	assert(cmd.first >= 5 && cmd.second >= 5);

	cmd.second = cmd.second >= 5 ? cmd.second : 5;
	cmd.first = cmd.first >= 5 ? cmd.first : 5;
}// GetCmdInfo()
}
#endif
