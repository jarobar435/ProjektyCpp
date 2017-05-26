#include "Œlimak.h"
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

Œlimak::Œlimak() : Zawodnik::Zawodnik(5,0,0,'œ'), domek(true)
{
	//domyœlnie konstruowane s¹ œlimaki z niezepsutym domkiem i prêdkoœci¹ pocz¹tkow¹ 5m/min
}

void Œlimak::wypisz(std::ofstream &fout)
{
	fout << "Typ: Œlimak" << endl
		 << "Po³o¿enie: " << getPo³o¿enie() << endl 
		 << "Prêdkoœæ: " << getPrêdkoœæ() << endl << endl;
}

void Œlimak::z³e¯ó³wieRozgniot³yDomek()
{
	domek = false;
}

