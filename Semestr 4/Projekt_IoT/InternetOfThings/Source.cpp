#include <iostream>
#include "Symulacja.h" //w main tylko tworzê obiekt symulacji, jej ca³oœæ zawarta w konstruktorze (tak mieliœmy robiæ na projekcie z 3 semestru), z tego powodu powy¿sze nag³ówki niepotrzebne
#include <time.h>	//dla rand()
#include <Windows.h> //dla Sleep()

using namespace std;

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, ""); //dla polskich znaków w konsoli
	//cout << thread::hardware_concurrency() << endl;

	cout << "Projekt zaliczeniowy!" << endl << endl;

	Symulacja inteligentneMieszkanie;	//bez () - domyslne 4; pusty nawias - brak wartosci

	system("PAUSE");
	return 0;
}