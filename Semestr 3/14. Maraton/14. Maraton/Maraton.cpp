#include <time.h>
#include "Bieg.h"

void main(int argc, char **argv)
{
	srand(time(NULL));	//punkt startowy rand'a
	setlocale(LC_ALL, "Polish");	//polskie znaki w konsoli - �eby komunikat o b��dnych parametrach �adnie si� wy�wietli�!

	Bieg maratonLe�ny(argc, argv);
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}