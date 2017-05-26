#include "Stonoga.h"
#include <iostream>
#include <fstream>

using namespace std;

Stonoga::Stonoga() : Zawodnik::Zawodnik(7,0,0,'s'), iloœæNóg(100)
{
	//domyœlnie konstruowane s¹ Stonogi z kompletem nóg i prêdkoœci¹ pocz¹tkow¹ 7m/min
}

void Stonoga::wypisz(std::ofstream &fout)
{
	if (iloœæNóg <= 0)
	{
		fout << "Typ: Stonoga" << endl
			<< "Po³o¿enie: " << getPo³o¿enie() << endl
			<< "Prêdkoœæ: " << getPrêdkoœæ() << endl << endl;
	}
	else
	{
		fout << "Typ: Stonoga" << endl
			<< "Iloœæ nóg: " << iloœæNóg << endl
			<< "Po³o¿enie: " << getPo³o¿enie() << endl
			<< "Prêdkoœæ: " << getPrêdkoœæ() << endl << endl;
	}
}

bool Stonoga::uszkodzenieNóg(int iloœæ) //true jeœli stonoga straci³a wszystkie nogi
{
	this->iloœæNóg -= iloœæ;
	if (iloœæNóg <= 0)
		return true;
	return false;
}