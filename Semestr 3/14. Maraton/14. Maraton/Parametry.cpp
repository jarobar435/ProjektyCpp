#include "Parametry.h"
#include <string>
#include <iostream>

using namespace std;

Parametry::Parametry(int argc, char **argv)
{
	if (Szukaj_D(argc, argv))	//sprawdz czy jest prze³¹cznik -d i czy jego wartosc jest prawidlowa
		d³ugoœæTrasy = Wczytaj_D(argc, argv);	//jeœli tak, wczytaj -d
	else
	{
		NiepoprawneParametry();
	}

	if (Szukaj_L(argc, argv))	//sprawdz, czy jest prze³¹cznik -l i czy jego wartosc jest prawidlowa
		liczbaUczestników = Wczytaj_L(argc, argv);		//jeœli tak, wczytaj -l
	else
	{
		NiepoprawneParametry();
	}

	if (Szukaj_O(argc, argv))	//sprawdz, czy jest prze³¹cznik -o i czy jego wartosc jest prawidlowa
		nazwaPlikuWyjœciowego = Wczytaj_O(argc, argv);		//jeœli tak, to wczytaj -o
	else
	{
		NiepoprawneParametry();
	}
}

bool Parametry::Szukaj_D(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) //od 1, bo [9] to nazwa programu; do argc-1 (u mnie jako warunek imniejsze, a nie mniejsze równe) bo prze³¹cznik musi byæ poprzednikiem wartoœci
	{
		if (argv[i] == string("-d"))
			if (CzyLiczbaCa³kowita(argv[i + 1]))		//jeœli kolejna jest liczba - zwróæ true
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
	for (int i = 1; i < argc; i++)//od 1, bo [9] to nazwa programu; do argc-1 (u mnie jako warunek imniejsze, a nie mniejsze równe) bo prze³¹cznik musi byæ poprzednikiem wartoœci
	{
		if (argv[i] == string("-l"))
			if (CzyLiczbaCa³kowita(argv[i + 1]))	//jeœli kolejna jest liczba - zwróæ true
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
	for (int i = 1; i < argc; i++) //od 1, bo [9] to nazwa programu; do argc-1 (u mnie jako warunek imniejsze, a nie mniejsze równe) bo prze³¹cznik musi byæ poprzednikiem wartoœci
	{
		if (argv[i] == string("-o"))
			//if (argv[i+1]!="")    nie trzeba tego sprawdzaæ - skoro sprawdzam do argc-1, to na nastêpnym miejscu musi coœ wystêpowaæ
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
	return "to sie nigdy nie zdarzy!"; //bo metodê Wczytaj_ wywo³ujê ju¿ po sprawdzeniu, ¿e prze³¹cznik istnieje, i wartoœæ za nim jest odpowiednia
}

void Parametry::NiepoprawneParametry()
{
	cout << "Niestety, podane parametry nie spe³niaj¹ wymagañ.\n"
		"Parametry -d -l -o s¹ OBLIGATORYJNE, wartoœci musz¹ nastêpowaæ po nich.\n"
		"Przyk³adowe PRAWID£OWE wywo³anie programu:\n"
		"\t\"14. Maraton.exe\" -d 30 -l 10 -o statystyki.txt\n";
	exit(EXIT_FAILURE);
}

bool Parametry::CzyLiczbaCa³kowita(char *ciag)
{
	string ciagTestowany = ciag;
	for (int i = 0; i < ciagTestowany.length(); i++)
	{
		if (!isdigit(ciagTestowany[i]))
			return false;
	}
	return true;
}

int Parametry::getD³ugoœæTrasy(void)
{
	return d³ugoœæTrasy;
}

int Parametry::getLiczbaUczestników(void)
{
	return liczbaUczestników;
}

string Parametry::getNazwaPlikuWyjœciowego(void)
{
	return nazwaPlikuWyjœciowego;
}

