#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Symulacja.h" //w main tylko tworzê obiekt symulacji, jej ca³oœæ zawarta w konstruktorze (tak mieliœmy robiæ na projekcie z 3 semestru), z tego powodu powy¿sze nag³ówki niepotrzebne
#include <time.h>	//dla rand()
#include <iostream>
#include <thread>

using namespace std;

int main()
{
		srand(time(NULL));
		setlocale(LC_ALL, ""); //dla polskich znaków w konsoli

		try
		{
			Symulacja inteligentneMieszkanie;	//bez () - domyslne 4; pusty nawias - brak wartosci
		}
		catch (string _Exception)
		{
			cout << "Wyst¹pi³ b³¹d krytyczny - " << _Exception << endl
				<< "Optymalna iloœæ w¹tków dla procesora u¿ytkownika: " << thread::hardware_concurrency();
		}
		catch (int _Exception)
		{
			cout << "Niestety GUI Symulatora nie mo¿na przeskalowaæ do rozdzielczoœci u¿ytkownika (" << _Exception/1000 << "x" << _Exception%1000 << ")."
				<< endl << "Zalecana rozdzielczoœæ to 1600x800." << endl;
		}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}