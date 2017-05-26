#pragma once
#include <string>

class Parametry
{
	int d³ugoœæTrasy;
	int liczbaUczestników;
	std::string nazwaPlikuWyjœciowego;
public:
	Parametry(int, char**);
	bool Szukaj_D(int argc, char **argv);
	int Wczytaj_D(int argc, char **argv);
	bool Szukaj_L(int argc, char **argv);
	int Wczytaj_L(int argc, char **argv);
	bool Szukaj_O(int argc, char **argv);
	std::string Wczytaj_O(int argc, char **argv);
	void NiepoprawneParametry();
	bool CzyLiczbaCa³kowita(char *ciag);
	int getD³ugoœæTrasy(void);
	int getLiczbaUczestników(void);
	std::string getNazwaPlikuWyjœciowego(void);
};

