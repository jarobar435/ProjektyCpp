#include "Modul.h"
#include <iostream>
#include <string>

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
	if (getState())
	{
		cout << "ON." << endl;
	}
	else
	{
		cout << "OFF." << endl;
	};
}

void Przekaznik::changeState()
{
	LogicState = !LogicState;
}

SensorSwiatla::SensorSwiatla() : Modul("Sensor natezenia swiatla", "Wejsciowe", 2)
{
	LightValue = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (2)))+8;
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
void SensorSwiatla::simulation(int timeStep)
{
	if (dayTime < 18000 || dayTime>39600) //je�li przed godzina 5, lub po godzinie 12 - niech si� �ciemnia
	{
		if (getValue() == 0) //je�li ju� ciemniej by� nie mo�e
		{
			wypisz();

			dayTime += timeStep;
			if (dayTime > 86400)
				dayTime -= 86400;
			cout << "\nGodzina " << dayTime / timeStep << "." << endl;

			return;
		}
		setValue(getValue() - (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 1))+0.75));
		if (getValue() < 0) //je�li b�dzie mniejsze od 0 (poziom kompletnego braku �wiat�a, w�a�ciwie niedopuszczalny, ale na potrzeby projektu powiedzmy �e mo�liwy
			setValue(0);

		wypisz();
	}
	else //je�li ma si� rozja�nia�
	{
		if (getValue() == 20)
		{
			wypisz();

			dayTime += timeStep;
			if (dayTime > 86400)
				dayTime -= 86400;
			cout << "\nGodzina " << dayTime / timeStep << "." << endl;

			return;
		}
		setValue(getValue() + (static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 2))+2));
		if (getValue() > 20) //je�li b�dzie mniejsze od 0 (poziom kompletnego braku �wiat�a, w�a�ciwie niedopuszczalny, ale na potrzeby projektu powiedzmy �e mo�liwy
			setValue(20);

		wypisz();
	}
	dayTime += timeStep;
	if (dayTime > 86400)
		dayTime -= 86400;
	cout << "\nGodzina " << dayTime/timeStep << ":" << endl;
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
	cout << getName() << " ID = " << getID() << " : " << getValue() << " (";
	if (getValue() > 10)
		cout << "DZIE�).";
	else
		cout << "NOC).";
	cout << endl;
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