#include "Parametry.h"
#include <string>
#include <iostream>

using namespace std;

Parametry::Parametry(int argc, char **argv)
{
	if (Szukaj_D(argc, argv))	//sprawdz czy jest prze��cznik -d i czy jego wartosc jest prawidlowa
		d�ugo��Trasy = Wczytaj_D(argc, argv);	//je�li tak, wczytaj -d
	else
	{
		NiepoprawneParametry();
	}

	if (Szukaj_L(argc, argv))	//sprawdz, czy jest prze��cznik -l i czy jego wartosc jest prawidlowa
		liczbaUczestnik�w = Wczytaj_L(argc, argv);		//je�li tak, wczytaj -l
	else
	{
		NiepoprawneParametry();
	}

	if (Szukaj_O(argc, argv))	//sprawdz, czy jest prze��cznik -o i czy jego wartosc jest prawidlowa
		nazwaPlikuWyj�ciowego = Wczytaj_O(argc, argv);		//je�li tak, to wczytaj -o
	else
	{
		NiepoprawneParametry();
	}
}

bool Parametry::Szukaj_D(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) //od 1, bo [9] to nazwa programu; do argc-1 (u mnie jako warunek imniejsze, a nie mniejsze r�wne) bo prze��cznik musi by� poprzednikiem warto�ci
	{
		if (argv[i] == string("-d"))
			if (CzyLiczbaCa�kowita(argv[i + 1]))		//je�li kolejna jest liczba - zwr�� true
				return true;
	}
	return false;
}

int Parametry::Wczytaj_D(int argc, char ** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == string("-d"))
			return atoi(argv[i + 1]);
	}
	return 0;
}

bool Parametry::Szukaj_L(int argc, char ** argv)
{
	for (int i = 1; i < argc; i++)//od 1, bo [9] to nazwa programu; do argc-1 (u mnie jako warunek imniejsze, a nie mniejsze r�wne) bo prze��cznik musi by� poprzednikiem warto�ci
	{
		if (argv[i] == string("-l"))
			if (CzyLiczbaCa�kowita(argv[i + 1]))	//je�li kolejna jest liczba - zwr�� true
				return true;
	}
	return false;
}

int Parametry::Wczytaj_L(int argc, char ** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == string("-l"))
			return atoi(argv[i + 1]);
	}
	return 0;
}

bool Parametry::Szukaj_O(int argc, char ** argv)
{
	for (int i = 1; i < argc; i++) //od 1, bo [9] to nazwa programu; do argc-1 (u mnie jako warunek imniejsze, a nie mniejsze r�wne) bo prze��cznik musi by� poprzednikiem warto�ci
	{
		if (argv[i] == string("-o"))
			//if (argv[i+1]!="")    nie trzeba tego sprawdza� - skoro sprawdzam do argc-1, to na nast�pnym miejscu musi co� wyst�powa�
			return true;
	}
	return false;
}

string Parametry::Wczytaj_O(int argc, char ** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == string("-o"))
			return (argv[i + 1]);
	}
	return "to sie nigdy nie zdarzy!"; //bo metod� Wczytaj_ wywo�uj� ju� po sprawdzeniu, �e prze��cznik istnieje, i warto�� za nim jest odpowiednia
}

void Parametry::NiepoprawneParametry()
{
	cout << "Niestety, podane parametry nie spe�niaj� wymaga�.\n"
		"Parametry -d -l -o s� OBLIGATORYJNE, warto�ci musz� nast�powa� po nich.\n"
		"Przyk�adowe PRAWID�OWE wywo�anie programu:\n"
		"\t\"14. Maraton.exe\" -d 30 -l 10 -o statystyki.txt\n";
	exit(EXIT_FAILURE);
}

bool Parametry::CzyLiczbaCa�kowita(char *ciag)
{
	string ciagTestowany = ciag;
	for (int i = 0; i < ciagTestowany.length(); i++)
	{
		if (!isdigit(ciagTestowany[i]))
			return false;
	}
	return true;
}

int Parametry::getD�ugo��Trasy(void)
{
	return d�ugo��Trasy;
}

int Parametry::getLiczbaUczestnik�w(void)
{
	return liczbaUczestnik�w;
}

string Parametry::getNazwaPlikuWyj�ciowego(void)
{
	return nazwaPlikuWyj�ciowego;
}

