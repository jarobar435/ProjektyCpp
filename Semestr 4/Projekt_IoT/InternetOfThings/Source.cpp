#include <iostream>
#include "Symulacja.h" //w main tylko tworz� obiekt symulacji, jej ca�o�� zawarta w konstruktorze (tak mieli�my robi� na projekcie z 3 semestru), z tego powodu powy�sze nag��wki niepotrzebne
#include <time.h>	//dla rand()
#include <Windows.h> //dla Sleep()

using namespace std;

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, ""); //dla polskich znak�w w konsoli
	//cout << thread::hardware_concurrency() << endl;

	cout << "Projekt zaliczeniowy!" << endl << endl;

	Symulacja inteligentneMieszkanie;	//bez () - domyslne 4; pusty nawias - brak wartosci

	system("PAUSE");
	return 0;
}