#pragma once
#include <fstream>

class Zawodnik
{
	double pr�dko��;
	double po�o�enie;
	int status; //czy jeszcze biegnie = 0, czy ju� sko�czy� = 1, czy odpad� = -1
	char typ;
public:
	Zawodnik(double pr�dko��, double po�o�enie, int status, char typ);
	virtual ~Zawodnik() = default;
	double getPr�dko��();
	double getPo�o�enie();
	int getStatus();
	char getTyp();
	void setPredko��(double newPr�dko��);
	void setPo�o�enie(double newPo�o�enie);
	void setStatus(int newStatus);
	virtual void wypisz(std::ofstream &fout);
	virtual bool uszkodzenieN�g(int ilo��);
	virtual void z�e��wieRozgniot�yDomek();
};

