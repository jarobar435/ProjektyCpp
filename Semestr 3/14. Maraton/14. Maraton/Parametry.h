#pragma once
#include <string>

class Parametry
{
	int długośćTrasy;
	int liczbaUczestników;
	std::string nazwaPlikuWyjściowego;
public:
	Parametry(int, char**);
	bool Szukaj_D(int argc, char **argv);
	int Wczytaj_D(int argc, char **argv);
	bool Szukaj_L(int argc, char **argv);
	int Wczytaj_L(int argc, char **argv);
	bool Szukaj_O(int argc, char **argv);
	std::string Wczytaj_O(int argc, char **argv);
	void NiepoprawneParametry();
	bool CzyLiczbaCałkowita(char *ciag);
	int getDługośćTrasy(void);
	int getLiczbaUczestników(void);
	std::string getNazwaPlikuWyjściowego(void);
};

