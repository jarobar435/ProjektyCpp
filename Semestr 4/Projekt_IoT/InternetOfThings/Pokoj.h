#pragma once
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include "Mikrokontroler.h"
#include "Modul.h"
#include <vector>
#include <string>

class Pokoj
{
	static int idCounter; //deklaracja statyczna NIE DEFINIUJE zmiennej! trzeba powtórzyæ w .cpp
	int IDnumber,
		iloscPrzekaznik,
		iloscPrzelacznikDrzwi,
		iloscPrzelacznikSwiatla,
		iloscSensorSwiatla;
	const std::string typPokoju;

public:
	std::vector <Mikrokontroler*> Kontrolery;
	std::vector <Modul*> Moduly;
	Pokoj(std::string typ = "UNKNOWN", int ilPrzekaznik = 2, int ilDrzwi = 1, int ilPrzelacznik = 2, int ilKontroler = 1, int iloscSensorSwiatla = 0);
	~Pokoj();
	void WypiszDane();
	virtual void DodawanieKontrolerow();
	//virtual void DodawanieModulow();
	void DodawanieModulow();
	std::string getType();
	int getID();
	int getIlPrzekaznik();
	int getIlDrzwi();
	int getIlPrzelacznik();
	int getIlSensorSwiatla();
	int getIlKontroler();
	int getIlModul();
};

//zastosowaæ wzorce (w przypaku pokojów szczególnie) 
class Sypialnia : public Pokoj
{
public:
	Sypialnia();
	void DodawanieKontrolerow();
	//void DodawanieModulow();
};

class Goscinny : public Pokoj
{
public:
	Goscinny();
	void DodawanieKontrolerow();
	//void DodawanieModulow();
};

class Lazienka : public Pokoj
{
public:
	Lazienka();
	void DodawanieKontrolerow();
	//void DodawanieModulow();
};

class Pakamera : public Pokoj
{
public:
	Pakamera();
	void DodawanieKontrolerow();
	//void DodawanieModulow();
};