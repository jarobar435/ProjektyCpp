#pragma once
#include "Zawodnik.h"
#include <fstream>

class Œlimak :public Zawodnik
{
	bool domek;	//true - ma domek, false - ju¿ mu z³e zó³wie popus³y
public:
	Œlimak();
	void wypisz(std::ofstream &fout);
	void z³e¯ó³wieRozgniot³yDomek();
};

