#include <iostream>

using namespace std;

#ifdef __unix__
int hello()
{
	cout << "hello linux" << endl;
	return 0;
}
#endif

#ifdef __MINGW32__
int hello()
{
	cout << "hello windows" << endl;
	return 0;
}
#endif


int main ()
{
	return hello();
}

