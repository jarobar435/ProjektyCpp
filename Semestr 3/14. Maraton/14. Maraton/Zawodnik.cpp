#include "Zawodnik.h"
#include <fstream>
#include <iostream>

Zawodnik::Zawodnik(double pr�dko��, double po�o�enie, int status, char typ)
{
	this->pr�dko�� = pr�dko��;
	this->po�o�enie = po�o�enie;
	this->status = status;
	this->typ = typ;
}

double Zawodnik::getPr�dko��()
{
	return pr�dko��;
}

double Zawodnik::getPo�o�enie()
{
	return po�o�enie;
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

bool Zawodnik::uszkodzenieN�g(int ilo��)
{
	//virtual
	return false;
}

void Zawodnik::z�e��wieRozgniot�yDomek()
{
	//virtual
}

void Zawodnik::setPredko��(double newPr�dko��)
{
	this->pr�dko�� = newPr�dko��;
}

void Zawodnik::setPo�o�enie(double newPo�o�enie)
{
	this->po�o�enie = newPo�o�enie;
}

void Zawodnik::setStatus(int newStatus)
{
	this->status = newStatus;
}