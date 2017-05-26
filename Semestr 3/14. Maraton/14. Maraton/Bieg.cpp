#include "Bieg.h"
#include "Parametry.h"
#include "Zawodnik.h"
#include "Stonoga.h"
#include "�limak.h"
#include "��w.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;

Bieg::Bieg(int argc, char **argv)
{
	Parametry uruchomieniowe(argc, argv);
	dodajZawodnik�w(uruchomieniowe);
	biegTrwa = uruchomieniowe.getLiczbaUczestnik�w();

	ofstream fout(uruchomieniowe.getNazwaPlikuWyj�ciowego(), ios::out);
	if (fout.good() == true)
	{
		while (biegTrwa)
		{
			wykonajKrok(uruchomieniowe, fout);
		}
		while (ilo��Poleg�ych)
		{
			for (int i = 0; i < zawodnicy.size(); i++)
			{
				if (zawodnicy[i]->getStatus() == -1)
				{
					fout << "W BOJU POLEG�: " << endl;
					zawodnicy[i]->wypisz(fout);
					--ilo��Poleg�ych;
				}
			}

		}
		fout.close();
	}
	else
	{
		cout << "Nie uda�o si� uzyska� dost�pu do pliku." << endl;
	}
	zwalnianiePami�ci();
}

void Bieg::dodajZawodnik�w(Parametry & uruchomieniowe)
{
	for (int i = 0; i < uruchomieniowe.getLiczbaUczestnik�w(); i++)
	{
		zawodnicy.push_back(losujZawodnika());
	}
}

void Bieg::zwalnianiePami�ci(void)
{
	Zawodnik * wskTemp;
	for (int i = 0; i < this->zawodnicy.size(); i++) 
	{
		wskTemp = this->zawodnicy[i];
		delete wskTemp;
	}
}

Zawodnik* Bieg::losujZawodnika(void)
{
	int los = (rand() % 3) + 1;
	switch (los)
	{
	case 1:
		return new Stonoga();
		break;
	case 2:
		return new �limak();
		break;
	case 3:
		return new ��w();
		break;
	}
}

bool Bieg::samodzielneUszkodzenieNogi(void)
{
	int los = (rand() % 10) + 1;
	switch (los)
	{
	case 1:
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool Bieg::��wieUszkodzenieNogi(void)
{
	int los = (rand() % 4) + 1;
	switch (los)
	{
	case 1:
		return false;
		break;
	default:
		return true;
		break;
	}
}

bool Bieg::spotkanieBez�wiadk�w(Parametry & uruchomieniowe, double po�o�enie)
{
	int ilo��Zawodnik�w = 0, ilo���wi = 0;
	for (int i = 0; i < zawodnicy.size() && grupyZawodnik�w; i++)
	{
		if (zawodnicy[i]->getPo�o�enie() == po�o�enie)
		{
			ilo��Zawodnik�w++;
			if (zawodnicy[i]->getTyp() == '�')
				ilo���wi++;
		}
	}
	if(ilo��Zawodnik�w==4 && ilo���wi==3)
		return true;
	
	return false;
}

bool Bieg::spotkanieZ�wStonoga(Parametry & uruchomieniowe, double po�o�enie)
{
	for (int i = 0; i < zawodnicy.size() && grupyZawodnik�w; i++)
	{
		if (zawodnicy[i]->getPo�o�enie() == po�o�enie)//je�li jaki� zawodnik mija stonog�
		{
			if (zawodnicy[i]->getTyp() == '�')//je�li jest ��wiem
				return true;
		}
	}
	return false;
}

void Bieg::wykonajKrok(Parametry & uruchomieniowe, ofstream &fout)
{
	double nowePo�o�enie;
	for (int i = 0; i < zawodnicy.size() && grupyZawodnik�w; i++, grupyZawodnik�w+=10) //ca�o�� operacji kroku wykonuj� je�li nie przeszed�em przez wszystkich zawodnik�w w tym kroku i nie wyczerpa�em limitu ilo�ci grupy, kt�ry powi�ksza si� co 10, tak wi�c w 1-wszym kroku b�dzie to 10, w drugim 20, itd.
	{
		nowePo�o�enie = zawodnicy[i]->getPo�o�enie() + zawodnicy[i]->getPr�dko��();
		if (nowePo�o�enie < uruchomieniowe.getD�ugo��Trasy()) //je�li zawodnik jeszcze nie dobieg� do mety
		{
			//to najpierw sprawdzam, co mu si� przytrafi

			if (zawodnicy[i]->getTyp() == '�')		//WARUNEK 1/5
				zawodnicy[i]->setPredko��(/*zawodnicy[i]->getPr�dko��()*/5 + 0.1 * min(biegTrwa , grupyZawodnik�w)); 

			if (spotkanieBez�wiadk�w(uruchomieniowe, zawodnicy[i]->getPo�o�enie()))				//WARUNEK 4/5  je�li 3 ��wie spotkaj� samotnego �limaka i nie ma �wiadk�w tego zdarzenia, to rozgniot� mu domek
			{
				zawodnicy[i]->setStatus(-1);
				biegTrwa--;
				ilo��Poleg�ych++;
				zawodnicy[i]->z�e��wieRozgniot�yDomek();
			}

			if (zawodnicy[i]->getTyp() == 's')		//WARUNEK 2/5 i 3/5
			{
				if (samodzielneUszkodzenieNogi())
				{
					if (zawodnicy[i]->uszkodzenieN�g(1))
					{
						zawodnicy[i]->setStatus(-1);
						biegTrwa--;
						ilo��Poleg�ych++;
					}
					zawodnicy[i]->setPredko��(zawodnicy[i]->getPr�dko��()*0.95);
				}
				
				if (spotkanieZ�wStonoga(uruchomieniowe, zawodnicy[i]->getPo�o�enie()))		//WARUNEK 5/5
				{
					if (��wieUszkodzenieNogi())
					{
						if (zawodnicy[i]->uszkodzenieN�g(3))
						{
							zawodnicy[i]->setStatus(-1);
							biegTrwa--;
							ilo��Poleg�ych++;
						}
						zawodnicy[i]->setPredko��(zawodnicy[i]->getPr�dko��()*0.95);
					}
				}
			}

			zawodnicy[i]->setPo�o�enie(nowePo�o�enie); //a potem inkrementuj� jego po�o�enie
		}
		else
		{
			if(zawodnicy[i]->getStatus() == 0) //je�li dobieg�
			{
				zawodnicy[i]->setPo�o�enie(nowePo�o�enie);
				zawodnicy[i]->setStatus(1);
				fout << uruchomieniowe.getLiczbaUczestnik�w() - (--biegTrwa) << ". miejsce zajmuje: " << endl;
				zawodnicy[i]->wypisz(fout);
			}
		}
	}

}
