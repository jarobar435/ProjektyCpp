#pragma once
#include "Zawodnik.h"
#include <fstream>

class �limak :public Zawodnik
{
	bool domek;	//true - ma domek, false - ju� mu z�e z�wie popus�y
public:
	�limak();
	void wypisz(std::ofstream &fout);
	void z�e��wieRozgniot�yDomek();
};

