#pragma once
#include <string>

class Mikrokontroler
{
	const std::string Name;
	static int idCounter;
	int IDnumber;
	const double Vcc;
	double FlashMemory;
	const int Clock;
	int IOpins;
public:
	Mikrokontroler(std::string name, double vcc, double memory, int pins, int clock);
	~Mikrokontroler(); 
	void symulujKontroler();
	int getID();
	std::string getName();
	double getVcc();
	double getMemory();
	int getClock();
	int getPins();
	void takeMemory(double);
	void takePins(int);
	void wypiszDane();
	virtual void Loop();
};

class ArduinoUno : public Mikrokontroler
{
public:
	ArduinoUno();
	~ArduinoUno();
};

class ArduinoMiniPro : public Mikrokontroler
{
public:
	ArduinoMiniPro();
	~ArduinoMiniPro();
};
