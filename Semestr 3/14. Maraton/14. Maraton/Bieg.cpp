#include "Bieg.h"
#include "Parametry.h"
#include "Zawodnik.h"
#include "Stonoga.h"
#include "Œlimak.h"
#include "¯ó³w.h"
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
	dodajZawodników(uruchomieniowe);
	biegTrwa = uruchomieniowe.getLiczbaUczestników();

	ofstream fout(uruchomieniowe.getNazwaPlikuWyjœciowego(), ios::out);
	if (fout.good() == true)
	{
		while (biegTrwa)
		{
			wykonajKrok(uruchomieniowe, fout);
		}
		while (iloœæPoleg³ych)
		{
			for (int i = 0; i < zawodnicy.size(); i++)
			{
				if (zawodnicy[i]->getStatus() == -1)
				{
					fout << "W BOJU POLEG£: " << endl;
					zawodnicy[i]->wypisz(fout);
					--iloœæPoleg³ych;
				}
			}

		}
		fout.close();
	}
	else
	{
		cout << "Nie uda³o siê uzyskaæ dostêpu do pliku." << endl;
	}
	zwalnianiePamiêci();
}

void Bieg::dodajZawodników(Parametry & uruchomieniowe)
{
	for (int i = 0; i < uruchomieniowe.getLiczbaUczestników(); i++)
	{
		zawodnicy.push_back(losujZawodnika());
	}
}

void Bieg::zwalnianiePamiêci(void)
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
		return new Œlimak();
		break;
	case 3:
		return new ¯ó³w();
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

bool Bieg::¿ó³wieUszkodzenieNogi(void)
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

bool Bieg::spotkanieBezŒwiadków(Parametry & uruchomieniowe, double po³o¿enie)
{
	int iloœæZawodników = 0, iloœæ¯ó³wi = 0;
	for (int i = 0; i < zawodnicy.size() && grupyZawodników; i++)
	{
		if (zawodnicy[i]->getPo³o¿enie() == po³o¿enie)
		{
			iloœæZawodników++;
			if (zawodnicy[i]->getTyp() == '¿')
				iloœæ¯ó³wi++;
		}
	}
	if(iloœæZawodników==4 && iloœæ¯ó³wi==3)
		return true;
	
	return false;
}

bool Bieg::spotkanieZó³wStonoga(Parametry & uruchomieniowe, double po³o¿enie)
{
	for (int i = 0; i < zawodnicy.size() && grupyZawodników; i++)
	{
		if (zawodnicy[i]->getPo³o¿enie() == po³o¿enie)//jeœli jakiœ zawodnik mija stonogê
		{
			if (zawodnicy[i]->getTyp() == '¿')//jeœli jest ¿ó³wiem
				return true;
		}
	}
	return false;
}

void Bieg::wykonajKrok(Parametry & uruchomieniowe, ofstream &fout)
{
	double nowePo³o¿enie;
	for (int i = 0; i < zawodnicy.size() && grupyZawodników; i++, grupyZawodników+=10) //ca³oœæ operacji kroku wykonujê jeœli nie przeszed³em przez wszystkich zawodników w tym kroku i nie wyczerpa³em limitu iloœci grupy, który powiêksza siê co 10, tak wiêc w 1-wszym kroku bêdzie to 10, w drugim 20, itd.
	{
		nowePo³o¿enie = zawodnicy[i]->getPo³o¿enie() + zawodnicy[i]->getPrêdkoœæ();
		if (nowePo³o¿enie < uruchomieniowe.getD³ugoœæTrasy()) //jeœli zawodnik jeszcze nie dobieg³ do mety
		{
			//to najpierw sprawdzam, co mu siê przytrafi

			if (zawodnicy[i]->getTyp() == 'œ')		//WARUNEK 1/5
				zawodnicy[i]->setPredkoœæ(/*zawodnicy[i]->getPrêdkoœæ()*/5 + 0.1 * min(biegTrwa , grupyZawodników)); 

			if (spotkanieBezŒwiadków(uruchomieniowe, zawodnicy[i]->getPo³o¿enie()))				//WARUNEK 4/5  jeœli 3 ¿ó³wie spotkaj¹ samotnego œlimaka i nie ma œwiadków tego zdarzenia, to rozgniot¹ mu domek
			{
				zawodnicy[i]->setStatus(-1);
				biegTrwa--;
				iloœæPoleg³ych++;
				zawodnicy[i]->z³e¯ó³wieRozgniot³yDomek();
			}

			if (zawodnicy[i]->getTyp() == 's')		//WARUNEK 2/5 i 3/5
			{
				if (samodzielneUszkodzenieNogi())
				{
					if (zawodnicy[i]->uszkodzenieNóg(1))
					{
						zawodnicy[i]->setStatus(-1);
						biegTrwa--;
						iloœæPoleg³ych++;
					}
					zawodnicy[i]->setPredkoœæ(zawodnicy[i]->getPrêdkoœæ()*0.95);
				}
				
				if (spotkanieZó³wStonoga(uruchomieniowe, zawodnicy[i]->getPo³o¿enie()))		//WARUNEK 5/5
				{
					if (¿ó³wieUszkodzenieNogi())
					{
						if (zawodnicy[i]->uszkodzenieNóg(3))
						{
							zawodnicy[i]->setStatus(-1);
							biegTrwa--;
							iloœæPoleg³ych++;
						}
						zawodnicy[i]->setPredkoœæ(zawodnicy[i]->getPrêdkoœæ()*0.95);
					}
				}
			}

			zawodnicy[i]->setPo³o¿enie(nowePo³o¿enie); //a potem inkrementujê jego po³o¿enie
		}
		else
		{
			if(zawodnicy[i]->getStatus() == 0) //jeœli dobieg³
			{
				zawodnicy[i]->setPo³o¿enie(nowePo³o¿enie);
				zawodnicy[i]->setStatus(1);
				fout << uruchomieniowe.getLiczbaUczestników() - (--biegTrwa) << ". miejsce zajmuje: " << endl;
				zawodnicy[i]->wypisz(fout);
			}
		}
	}

}
