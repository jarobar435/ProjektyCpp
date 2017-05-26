#pragma once
#include <fstream>

class Zawodnik
{
	double prêdkoœæ;
	double po³o¿enie;
	int status; //czy jeszcze biegnie = 0, czy ju¿ skoñczy³ = 1, czy odpad³ = -1
	char typ;
public:
	Zawodnik(double prêdkoœæ, double po³o¿enie, int status, char typ);
	virtual ~Zawodnik() = default;
	double getPrêdkoœæ();
	double getPo³o¿enie();
	int getStatus();
	char getTyp();
	void setPredkoœæ(double newPrêdkoœæ);
	void setPo³o¿enie(double newPo³o¿enie);
	void setStatus(int newStatus);
	virtual void wypisz(std::ofstream &fout);
	virtual bool uszkodzenieNóg(int iloœæ);
	virtual void z³e¯ó³wieRozgniot³yDomek();
};

