#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Symulacja.h" //w main tylko tworz� obiekt symulacji, jej ca�o�� zawarta w konstruktorze (tak mieli�my robi� na projekcie z 3 semestru), z tego powodu powy�sze nag��wki niepotrzebne
#include <time.h>	//dla rand()
#include <iostream>
#include <thread>

using namespace std;

int main()
{
		srand(time(NULL));
		setlocale(LC_ALL, ""); //dla polskich znak�w w konsoli

		try
		{
			Symulacja inteligentneMieszkanie;	//bez () - domyslne 4; pusty nawias - brak wartosci
		}
		catch (string _Exception)
		{
			cout << "Wyst�pi� b��d krytyczny - " << _Exception << endl
				<< "Optymalna ilo�� w�tk�w dla procesora u�ytkownika: " << thread::hardware_concurrency();
		}
		catch (int _Exception)
		{
			cout << "Niestety GUI Symulatora nie mo�na przeskalowa� do rozdzielczo�ci u�ytkownika (" << _Exception/1000 << "x" << _Exception%1000 << ")."
				<< endl << "Zalecana rozdzielczo�� to 1600x800." << endl;
		}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}