#pragma once
#include "Zawodnik.h"
#include <fstream>

class Stonoga :
	public Zawodnik
{
	int ilo��N�g;
public:
	Stonoga();
	bool uszkodzenieN�g(int ilo��);
	void wypisz(std::ofstream &fout);
};

