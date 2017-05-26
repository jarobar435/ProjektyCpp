#include "Modul.h"
#include "Symulacja.h"
#include <iostream>
#include <string>
#include <thread>

using namespace std;

const int zakresNocy = 10; //zmienna {0,20} dostosowywana do u�ytkownika - je�li pokuj jest oszklony i jasny - mniej; bez okien - max;
int dayTime = 0; //dzie� = 86400s; powiedzmy �e krok symulacji to 5s, wi�c zakres zmiennej 17280
int Modul::idCounter = 1; //zmienna od inkrementacji ID modu��w //definicja z deklaracji statycznej w .h


Modul::Modul() : IDnumber(idCounter++), Name("NoName"), Type("NoType"), PinsConnection(NULL)
{

}

Modul::Modul(std::string name, std::string type, int pins) : IDnumber(idCounter++), Name(name), Type(type), PinsConnection(pins)
{
}

Modul::~Modul()
{
}

int Modul::getID()
{
	return IDnumber;
}

string Modul::getName()
{
	return Name;
}

string Modul::getType()
{
	return Type;
}

int Modul::getPins()
{
	return PinsConnection;
}

void Modul::wypiszDane()
{
	//wirtualna
}

void Modul::wypisz()
{
	//wirtualna
}

double Modul::getValue()
{
	//wirtualna dla sensora�wiat�a
	return -1;
}

bool Modul::getState()
{
	//wirtualna
	return false;
}

void Modul::changeState()
{
	//wirtualna
}

void Modul::setChanged()
{
	//virtual
}

bool Modul::getChanged()
{
	//virtual
	return false;
}

void Modul::simulation(int)
{
	//virtual
}


Przekaznik::Przekaznik() : Modul("Przekaznik", "Wyjsciowy", 1)
{
	LogicState = false; //domy�lnie wy�aczony
}

Przekaznik::Przekaznik(bool stan) : Modul("Przekaznik", "Wyjsciowy", 1)
{
	LogicState = stan;
}

Przekaznik::~Przekaznik()
{

}

bool Przekaznik::getState()
{
	return LogicState;
}

void Przekaznik::wypiszDane()
{
	cout << "Numer ID: " << getID() << endl
		<< "Nazwa: " << getName() << endl
		<< "Typ urz�dzenia: " << getType() << endl
		<< "Ilo�� pin�w do komunikacji: " << getPins() << endl
		<< "Obecny stan: ";
		if (getState())
		{
			cout << "w��czony." << endl;
		}
		else
		{
			cout << "wy��czony." << endl;
		};
}

void Przekaznik::wypisz()
{
	cout << getName() << " ID = " << getID() << " : ";
	if (getState() ? cout << "ON." << endl : cout << "OFF." << endl);
}

void Przekaznik::changeState()
{
	LogicState = !LogicState;
}

SensorSwiatla::SensorSwiatla() : Modul("Sensor natezenia swiatla", "Wejsciowe", 2)
{
	LightValue = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (4)))+13;
}
SensorSwiatla::~SensorSwiatla()
{

}
double SensorSwiatla::getValue()
{
	return LightValue;
}
void SensorSwiatla::setValue(double newVal)
{
	LightValue = newVal;
}
void SensorSwiatla::simulation(int pauseTime)
{
	int godzina = Symulacja::getGodzina();
	bool zmiana = false;
	while (!Symulacja::getZakonczenieWatkow())
	{
		if (godzina != Symulacja::getGodzina())
			zmiana = true;
		else
			zmiana = false;

		godzina = Symulacja::getGodzina();
		
		if (godzina < 5 || godzina > 16)//je�li przed godzina 5, lub po godzinie 16 - niech si� �ciemnia
		{
			//je�li zesz�a poni�ej 0:
			if (LightValue < 0)
				LightValue = 0;

			if(zmiana)
				LightValue -= (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1)) + 0.75);
			else
				LightValue = (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.05*LightValue)) + LightValue);

		}
		else //niech si� rozja�nia
		{
			//je�li wesz�a powy�ej 20:
			if (LightValue > 20)
				LightValue = 20;

			if (zmiana)
				LightValue += (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1)) + 0.75);
			else
				LightValue = (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.05*LightValue)) + LightValue);
		}
		this_thread::sleep_for(chrono::seconds(pauseTime));
	}
}

void SensorSwiatla::wypiszDane()
{
	cout << "Numer ID: " << getID() << endl
		<< "Nazwa: " << getName() << endl
		<< "Typ urz�dzenia: " << getType() << endl
		<< "Ilo�� pin�w do komunikacji: " << getPins() << endl
		<< "Obecny poziom �wiat�a s�onecznego: " << getValue() << endl
		<< "Wnioskowanie wg poziomu: ";
	if (getValue() > zakresNocy)
		cout << "DZIE�.";
	else
		cout << "NOC.";
	cout << endl;
}
void SensorSwiatla::wypisz()
{
	cout << getName() << " ID = " << getID() << " : " << getValue() << endl;
}

PrzelacznikDrzwi::PrzelacznikDrzwi() : Modul("Przelacznik drzwi", "Wejsciowy", 1)
{
	LogicState = false; //domy�lnie wy�aczony
}

PrzelacznikDrzwi::PrzelacznikDrzwi(bool stan) : Modul("Przelacznik drzwi", "Wejsciowy", 1)
{
	LogicState = stan;
}

PrzelacznikDrzwi::~PrzelacznikDrzwi()
{

}

bool PrzelacznikDrzwi::getState()
{
	return LogicState;
}

void PrzelacznikDrzwi::wypiszDane()
{
	cout << "Numer ID: " << getID() << endl
		<< "Nazwa: " << getName() << endl
		<< "Typ urz�dzenia: " << getType() << endl
		<< "Ilo�� pin�w do komunikacji: " << getPins() << endl
		<< "Obecny stan: ";
	if (getState())
	{
		cout << "w��czony." << endl;
	}
	else
	{
		cout << "wy��czony." << endl;
	};
}

void PrzelacznikDrzwi::wypisz()
{
	cout << getName() << " ID = " << getID() << " : ";
	if (getState())
	{
		cout << "ON." << endl;
	}
	else
	{
		cout << "OFF." << endl;
	};
}

void PrzelacznikDrzwi::changeState()
{
	LogicState = !LogicState;
}

PrzelacznikSwiatla::PrzelacznikSwiatla() : Modul("Przelacznik swiatla", "Wejsciowy", 1)
{
	LogicState = false; //domy�lnie wy�aczony
}

PrzelacznikSwiatla::PrzelacznikSwiatla(bool stan) : Modul("Przelacznik swiat�a", "Wejsciowy", 1)
{
	LogicState = stan;
}

PrzelacznikSwiatla::~PrzelacznikSwiatla()
{

}

bool PrzelacznikSwiatla::getState()
{
	return LogicState;
}

void PrzelacznikSwiatla::wypiszDane()
{
	cout << "Numer ID: " << getID() << endl
		<< "Nazwa: " << getName() << endl
		<< "Typ urz�dzenia: " << getType() << endl
		<< "Ilo�� pin�w do komunikacji: " << getPins() << endl
		<< "Obecny stan: ";
	if (getState() == true)
	{
		cout << "w��czony." << endl;
	}
	else
	{
		cout << "wy��czony." << endl;
	};
}

void PrzelacznikSwiatla::wypisz()
{
	cout << getName() << " ID = " << getID() << " : ";
	if (getState())
	{
		cout << "ON." << endl;
	}
	else
	{
		cout << "OFF." << endl;
	};
}

void PrzelacznikSwiatla::changeState()
{
	LogicState = !LogicState;
}

bool PrzelacznikSwiatla::getChanged()
{
	return HasBeenRecentlyChanged;
}

void PrzelacznikSwiatla::setChanged()
{
	HasBeenRecentlyChanged = !HasBeenRecentlyChanged;
}
