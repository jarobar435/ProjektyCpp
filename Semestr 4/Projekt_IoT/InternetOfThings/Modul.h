#pragma once
#include <string>

class Modul
{
	static int idCounter;
	int IDnumber;
	const std::string Name, Type;
	const int PinsConnection;
public:
	Modul();
	Modul(std::string name, std::string type, int pins);
	~Modul();
	int getID();
	std::string getName();
	std::string getType();
	int getPins();
	virtual void wypiszDane();
	virtual void wypisz();
	virtual double getValue();
	virtual bool getState();
	virtual void changeState();
};

class Przekaznik : public Modul
{
	bool LogicState;
public:
	Przekaznik();
	Przekaznik(bool);
	~Przekaznik();
	bool getState();
	void changeState();
	void wypiszDane();
	void wypisz();
};

class SensorSwiatla : public Modul
{
	double LightValue;
public:
	SensorSwiatla();
	~SensorSwiatla();
	double getValue();
	void setValue(double);
	void simulation(int);
	void wypiszDane();
	void wypisz();
};

class PrzelacznikDrzwi : public Modul
{
	bool LogicState;
public:
	PrzelacznikDrzwi();
	PrzelacznikDrzwi(bool);
	~PrzelacznikDrzwi();
	bool getState();
	void changeState();
	void wypiszDane();
	void wypisz();
};

class PrzelacznikSwiatla : public Modul
{
	bool LogicState;
public:
	PrzelacznikSwiatla();
	PrzelacznikSwiatla(bool);
	~PrzelacznikSwiatla();
	bool getState();
	void changeState();
	void wypiszDane();
	void wypisz();
};
