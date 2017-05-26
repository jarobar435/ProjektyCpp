#pragma once
#include <vector>
#include "Zawodnik.h"
#include "Parametry.h"
#include <fstream>

class Bieg
{
	std::vector<Zawodnik*> zawodnicy;
	int biegTrwa; //warunek p�tli, bieg trwa dop�ki chocia� 1 uczestnik nadal biegnie
	int grupyZawodnik�w = 10; //pierwsza fala (10 zawodnik�w)
	int ilo��Poleg�ych = 0;
public:
	Bieg(int, char**);
	Zawodnik* losujZawodnika(void);
	void dodajZawodnik�w(Parametry & uruchomieniowe);
	void zwalnianiePami�ci(void);
	void wykonajKrok(Parametry & uruchomieniowe, std::ofstream &fout);
	bool samodzielneUszkodzenieNogi(void);
	bool ��wieUszkodzenieNogi(void);
	bool spotkanieBez�wiadk�w(Parametry & uruchomieniowe, double po�o�enie);
	bool spotkanieZ�wStonoga(Parametry & uruchomieniowe, double po�o�enie);
};

