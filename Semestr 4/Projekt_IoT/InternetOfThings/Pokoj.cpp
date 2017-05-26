#include "Pokoj.h"
#include "Mikrokontroler.h"
#include "Modul.h"
#include <iostream>

using namespace std;

int Pokoj::idCounter = 1; //bo deklaracja statyczna nie definiuje

Pokoj::Pokoj(string typ, int ilPrzekaznik, int ilDrzwi, int ilPrzelacznik, int ilKontroler, int ilSens) : typPokoju(typ), IDnumber(idCounter++), iloscPrzekaznik(ilPrzekaznik), iloscPrzelacznikDrzwi(ilDrzwi), iloscPrzelacznikSwiatla(ilPrzelacznik), iloscSensorSwiatla(ilSens)
{
}

Pokoj::~Pokoj()
{
}

void Pokoj::WypiszDane()
{
	cout << "Numer ID: " << getID() << endl
		<< "Typ pokoju: " << getType() << endl
		<< "Iloœæ przekaŸników: " << getIlPrzekaznik() << endl
		<< "Iloœæ prze³¹czników drzwi: " << getIlDrzwi() << endl
		<< "Iloœæ prze³¹czników œwiat³a: " << getIlPrzelacznik() << endl
		<< "Iloœæ sensorów œwiat³a: " << getIlSensorSwiatla() << endl
		<< "Modu³ów ³¹cznie: " << getIlModul() << endl
		<< "Kontrolerów ³¹cznie: " << getIlKontroler() << endl << endl;
	for (int i = 0; i < getIlModul(); i++)
	{
		cout << "Modu³: " << endl;
		Moduly[i]->wypiszDane();
	}
	cout << endl;

	for (int i = 0; i < getIlKontroler(); i++)
	{
		cout << "Kontroler: " << endl;
		Kontrolery[i]->wypiszDane();
	}
	cout << endl << endl;
}

void Pokoj::DodawanieKontrolerow()
{
	//wirtualna
}

void Pokoj::DodawanieModulow()
{
	Modul* dodawany;
	for (int i = 0; i < getIlPrzekaznik(); i++)
	{
		dodawany = new Przekaznik;
		Moduly.push_back(dodawany);
		Kontrolery.back()->takePins(dodawany->getPins());
	}

	for (int i = 0; i < getIlDrzwi(); i++)
	{
		dodawany = new PrzelacznikDrzwi;
		Moduly.push_back(dodawany);
		Kontrolery.back()->takePins(dodawany->getPins());
	}

	for (int i = 0; i < getIlPrzelacznik(); i++)
	{
		dodawany = new PrzelacznikSwiatla;
		Moduly.push_back(dodawany);
		Kontrolery.back()->takePins(dodawany->getPins());
	}

	for (int i = 0; i < getIlSensorSwiatla(); i++)
	{
		dodawany = new SensorSwiatla;
		Moduly.push_back(dodawany);
		Kontrolery.back()->takePins(dodawany->getPins());
	}
}

string Pokoj::getType()
{
	return typPokoju;
}

int Pokoj::getID()
{
	return IDnumber;
}

int Pokoj::getIlPrzekaznik()
{
	return iloscPrzekaznik;
}

int Pokoj::getIlDrzwi()
{
	return iloscPrzelacznikDrzwi;
}

int Pokoj::getIlPrzelacznik()
{
	return iloscPrzelacznikSwiatla;
}

int Pokoj::getIlSensorSwiatla()
{
	return iloscSensorSwiatla;
}

int Pokoj::getIlKontroler()
{
	return int(Kontrolery.size()); //jawnie ¿eby kompilator nie krzycza³
}

int Pokoj::getIlModul()
{
	return int(Moduly.size()); //jawnie ¿eby kompilator nie krzycza³
}

Sypialnia::Sypialnia() : Pokoj::Pokoj("Sypialnia",5, 1, 5, 1, 2)
{
	DodawanieKontrolerow();
	DodawanieModulow();
}

//to powinno daæ radê wzorcem:
void Sypialnia::DodawanieKontrolerow()
{
	Mikrokontroler* dodawany = new ArduinoUno;
	Kontrolery.push_back(dodawany);
}

//void Sypialnia::DodawanieModulow()
//{
//	Modul* dodawany;
//	for (int i = 0; i < getIlPrzekaznik(); i++)
//	{
//		dodawany = new Przekaznik;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlDrzwi(); i++)
//	{
//		dodawany = new PrzelacznikDrzwi;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlPrzelacznik(); i++)
//	{
//		dodawany = new PrzelacznikSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlSensorSwiatla(); i++)
//	{
//		dodawany = new SensorSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//}

Goscinny::Goscinny() : Pokoj::Pokoj("Goœcinny", 3, 2, 3, 1, 2)
{
	DodawanieKontrolerow();
	DodawanieModulow();
}

void Goscinny::DodawanieKontrolerow()
{
	Mikrokontroler* dodawany = new ArduinoMiniPro;
	Kontrolery.push_back(dodawany);
}

//void Goscinny::DodawanieModulow()
//{
//	Modul* dodawany;
//	for (int i = 0; i < getIlPrzekaznik(); i++)
//	{
//		dodawany = new Przekaznik;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlDrzwi(); i++)
//	{
//		dodawany = new PrzelacznikDrzwi;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlPrzelacznik(); i++)
//	{
//		dodawany = new PrzelacznikSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlSensorSwiatla(); i++)
//	{
//		dodawany = new SensorSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//}

Lazienka::Lazienka() : Pokoj::Pokoj("£azienka", 2, 1, 2, 1, 0)
{
	DodawanieKontrolerow();
	DodawanieModulow();
}

void Lazienka::DodawanieKontrolerow()
{
	Mikrokontroler* dodawany = new ArduinoMiniPro;
	Kontrolery.push_back(dodawany);
}

//void Lazienka::DodawanieModulow()
//{
//	Modul* dodawany;
//	for (int i = 0; i < getIlPrzekaznik(); i++)
//	{
//		dodawany = new Przekaznik;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlDrzwi(); i++)
//	{
//		dodawany = new PrzelacznikDrzwi;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlPrzelacznik(); i++)
//	{
//		dodawany = new PrzelacznikSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlSensorSwiatla(); i++)
//	{
//		dodawany = new SensorSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//}

Pakamera::Pakamera() : Pokoj::Pokoj("Pakamera", 1, 1, 1, 1, 0)
{
	DodawanieKontrolerow();
	DodawanieModulow();
}

void Pakamera::DodawanieKontrolerow()
{
	Mikrokontroler* dodawany = new ArduinoMiniPro;
	Kontrolery.push_back(dodawany);
}
//
//void Pakamera::DodawanieModulow()
//{
//	Modul* dodawany;
//	for (int i = 0; i < getIlPrzekaznik(); i++)
//	{
//		dodawany = new Przekaznik;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlDrzwi(); i++)
//	{
//		dodawany = new PrzelacznikDrzwi;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlPrzelacznik(); i++)
//	{
//		dodawany = new PrzelacznikSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//
//	for (int i = 0; i < getIlSensorSwiatla(); i++)
//	{
//		dodawany = new SensorSwiatla;
//		Moduly.push_back(dodawany);
//		Kontrolery.back()->takePins(dodawany->getPins());
//	}
//}
