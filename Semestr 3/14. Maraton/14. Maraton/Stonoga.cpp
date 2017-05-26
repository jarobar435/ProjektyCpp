#include "Stonoga.h"
#include <iostream>
#include <fstream>

using namespace std;

Stonoga::Stonoga() : Zawodnik::Zawodnik(7,0,0,'s'), ilo��N�g(100)
{
	//domy�lnie konstruowane s� Stonogi z kompletem n�g i pr�dko�ci� pocz�tkow� 7m/min
}

void Stonoga::wypisz(std::ofstream &fout)
{
	if (ilo��N�g <= 0)
	{
		fout << "Typ: Stonoga" << endl
			<< "Po�o�enie: " << getPo�o�enie() << endl
			<< "Pr�dko��: " << getPr�dko��() << endl << endl;
	}
	else
	{
		fout << "Typ: Stonoga" << endl
			<< "Ilo�� n�g: " << ilo��N�g << endl
			<< "Po�o�enie: " << getPo�o�enie() << endl
			<< "Pr�dko��: " << getPr�dko��() << endl << endl;
	}
}

bool Stonoga::uszkodzenieN�g(int ilo��) //true je�li stonoga straci�a wszystkie nogi
{
	this->ilo��N�g -= ilo��;
	if (ilo��N�g <= 0)
		return true;
	return false;
}