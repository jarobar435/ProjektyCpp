#include "�limak.h"
#include <iostream>
#include <fstream>
#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
using namespace std;

�limak::�limak() : Zawodnik::Zawodnik(5,0,0,'�'), domek(true)
{
	//domy�lnie konstruowane s� �limaki z niezepsutym domkiem i pr�dko�ci� pocz�tkow� 5m/min
}

void �limak::wypisz(std::ofstream &fout)
{
	fout << "Typ: �limak" << endl
		 << "Po�o�enie: " << getPo�o�enie() << endl 
		 << "Pr�dko��: " << getPr�dko��() << endl << endl;
}

void �limak::z�e��wieRozgniot�yDomek()
{
	domek = false;
}

