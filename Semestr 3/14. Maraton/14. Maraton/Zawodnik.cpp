#include "Zawodnik.h"
#include <fstream>
#include <iostream>

Zawodnik::Zawodnik(double prêdkoœæ, double po³o¿enie, int status, char typ)
{
	this->prêdkoœæ = prêdkoœæ;
	this->po³o¿enie = po³o¿enie;
	this->status = status;
	this->typ = typ;
}

double Zawodnik::getPrêdkoœæ()
{
	return prêdkoœæ;
}

double Zawodnik::getPo³o¿enie()
{
	return po³o¿enie;
}

int Zawodnik::getStatus()
{
	return status;
}

char Zawodnik::getTyp()
{
	return typ;
}

void Zawodnik::wypisz(std::ofstream &fout)
{
	//f.polimorficzna - virtual w *.h
}

bool Zawodnik::uszkodzenieNóg(int iloœæ)
{
	//virtual
	return false;
}

void Zawodnik::z³e¯ó³wieRozgniot³yDomek()
{
	//virtual
}

void Zawodnik::setPredkoœæ(double newPrêdkoœæ)
{
	this->prêdkoœæ = newPrêdkoœæ;
}

void Zawodnik::setPo³o¿enie(double newPo³o¿enie)
{
	this->po³o¿enie = newPo³o¿enie;
}

void Zawodnik::setStatus(int newStatus)
{
	this->status = newStatus;
}