#pragma once
#include <string>

class Parametry
{
	int d�ugo��Trasy;
	int liczbaUczestnik�w;
	std::string nazwaPlikuWyj�ciowego;
public:
	Parametry(int, char**);
	bool Szukaj_D(int argc, char **argv);
	int Wczytaj_D(int argc, char **argv);
	bool Szukaj_L(int argc, char **argv);
	int Wczytaj_L(int argc, char **argv);
	bool Szukaj_O(int argc, char **argv);
	std::string Wczytaj_O(int argc, char **argv);
	void NiepoprawneParametry();
	bool CzyLiczbaCa�kowita(char *ciag);
	int getD�ugo��Trasy(void);
	int getLiczbaUczestnik�w(void);
	std::string getNazwaPlikuWyj�ciowego(void);
};

