#include "¯ó³w.h"
#include <iostream>
#include <fstream>

using namespace std;

¯ó³w::¯ó³w() : Zawodnik::Zawodnik(4,0,0,'¿')
{
	//domyœlnie konstruowane s¹ ¿ó³wie z prêdkoœci¹ pocz¹tkow¹ 4m/min
}

void ¯ó³w::wypisz(std::ofstream &fout)
{
	fout << "Typ: ¯ó³w" << endl
	  	 << "Po³o¿enie: " << getPo³o¿enie() << endl
		 << "Prêdkoœæ: " << getPrêdkoœæ() << endl << endl;
}
