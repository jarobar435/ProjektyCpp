#include "��w.h"
#include <iostream>
#include <fstream>

using namespace std;

��w::��w() : Zawodnik::Zawodnik(4,0,0,'�')
{
	//domy�lnie konstruowane s� ��wie z pr�dko�ci� pocz�tkow� 4m/min
}

void ��w::wypisz(std::ofstream &fout)
{
	fout << "Typ: ��w" << endl
	  	 << "Po�o�enie: " << getPo�o�enie() << endl
		 << "Pr�dko��: " << getPr�dko��() << endl << endl;
}
