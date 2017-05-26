#pragma once
#include <vector>
#include "Zawodnik.h"
#include "Parametry.h"
#include <fstream>

class Bieg
{
	std::vector<Zawodnik*> zawodnicy;
	int biegTrwa; //warunek pêtli, bieg trwa dopóki chocia¿ 1 uczestnik nadal biegnie
	int grupyZawodników = 10; //pierwsza fala (10 zawodników)
	int iloœæPoleg³ych = 0;
public:
	Bieg(int, char**);
	Zawodnik* losujZawodnika(void);
	void dodajZawodników(Parametry & uruchomieniowe);
	void zwalnianiePamiêci(void);
	void wykonajKrok(Parametry & uruchomieniowe, std::ofstream &fout);
	bool samodzielneUszkodzenieNogi(void);
	bool ¿ó³wieUszkodzenieNogi(void);
	bool spotkanieBezŒwiadków(Parametry & uruchomieniowe, double po³o¿enie);
	bool spotkanieZó³wStonoga(Parametry & uruchomieniowe, double po³o¿enie);
};

