#include "Mikrokontroler.h"
#include "Pokoj.h"
#include "Symulacja.h"
#include <iostream>
#include <string>

using namespace std;

int Mikrokontroler::idCounter = 1;

Mikrokontroler::Mikrokontroler(string name, double vcc, double memory, int pins, int clock) : Name(name), IDnumber(idCounter++), Vcc(vcc), FlashMemory(memory), IOpins(pins), Clock(clock)
{
}

Mikrokontroler::~Mikrokontroler()
{
}

//sprawdzaj po kolei modu�y i je�li co� si� zmienia, zmieniaj stan przekaznika
void Mikrokontroler::symulujKontroler()
{
	while (!Symulacja::getZakonczenieWatkow())
	{

	}
}


int Mikrokontroler::getID()
{
	return IDnumber;
}

string Mikrokontroler::getName()
{
	return Name;
}

double Mikrokontroler::getVcc()
{
	return Vcc;
}

double Mikrokontroler::getMemory()
{
	return FlashMemory;
}

int Mikrokontroler::getClock()
{
	return Clock;
}

int Mikrokontroler::getPins()
{
	return IOpins;
}

void Mikrokontroler::takePins(int numberOfPins)
{
	IOpins -= numberOfPins;
}

void Mikrokontroler::wypiszDane()
{
	cout << "Numer ID: " << getID() << endl
		<< "Nazwa: " << getName() << endl
		<< "Napicie zasilania: " << getVcc() << endl
		<< "Ilo�� pami�ci: " << getMemory() << endl
		<< "Cz�stotliwo�� taktowania: " << getClock() << endl
		<< "Ilo�� dost�pnych pin�w do komunikacji: " << getPins() << endl << endl;
}

void Mikrokontroler::takeMemory(double sizeOfCode)
{
	FlashMemory -= sizeOfCode;
}

void Mikrokontroler::Loop()
{
	//virtual
}

ArduinoUno::ArduinoUno() : Mikrokontroler("Arduino Uno", 5, 31.5, 20, 16)
{
}

ArduinoUno::~ArduinoUno()
{
}

ArduinoMiniPro::ArduinoMiniPro() : Mikrokontroler("Arduino MiniPro", 5, 15.5, 14, 16)
{
}

ArduinoMiniPro::~ArduinoMiniPro()
{
}
