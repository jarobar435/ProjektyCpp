#pragma once
#include "Zawodnik.h"
#include <fstream>

class Stonoga :
	public Zawodnik
{
	int iloœæNóg;
public:
	Stonoga();
	bool uszkodzenieNóg(int iloœæ);
	void wypisz(std::ofstream &fout);
};

