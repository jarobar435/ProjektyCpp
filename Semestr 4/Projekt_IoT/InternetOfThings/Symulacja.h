#pragma once
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <vector>
#include "Pokoj.h"
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Symulacja
{
	std::vector <Pokoj*> pokoje;
	std::vector <sf::Text*> WypisywaneDaneSFML;
	std::vector <sf::Sprite*> GrafikiSFML;
	std::vector <sf::Text*> TekstyInterface;
	sf::Font Consolas;
	int pogoda;
	static int godzina;
	int poziomSwiatla;
	bool wniosekCzyWlaczacSwiatlo;
	static bool zakonczenieWatkow;
	

public:
	Symulacja(int ilosc = 4);
	~Symulacja();
	void wnioskowanie();
	static bool getZakonczenieWatkow();
	void changeZakonczenieWatkow();
	void DodawaniePokoi(int ilosc);
	void CzyscWektorGrafik();
	void CzyscWektorDanych();
	void DodawanieTekstuSFML(const int, const int, const int, const std::string, const wchar_t* tekst);
	void WypiszDane();
	void SymulujOkno();
	static int getGodzina();
	void setGodzina(int);
	void DodawanieGrafikiSFML(std::string zrodlo, int originX, int originY, int wspX, int wspY, int rotate);
	void WypiszPokojSFML(int wybrany_pokoj);
	void WypiszKontrolerSFML(int wybrany_pokoj);
	void WypiszListeModulowSFML(int wybrany_pokoj);
	void WypiszModulSFML(int wybrany_pokoj, int wybrany_modul);
	void WypiszPrzekaznik(int wybrany_pokoj, int wybrany_modul);
	void WypiszSensorSwiatla(int wybrany_pokoj, int wybrany_modul);
	void WypiszPrzelacznikDrzwi(int wybrany_pokoj, int wybrany_modul);
	void WypiszPrzelacznikSwiatla(int wybrany_pokoj, int wybrany_modul);
	void SymulacjaCzasu(int krokWmin);
	void tworzenieInterfejsu(int szerOkna, int wysOkna);
	void WyswietlGrafikeSwiatla(int wybrany_pokoj, int wybrany_modul);
	void ZmienPogode(int WspX, int WspY);
};

enum _NazwyPokojow
{
	sypialnia,
	goscinny,
	lazienka,
	pakamera
};

enum _LokalizacjeSypialnia
{
	LampaSufit,
	LampkaNocna1,
	LampkaNocna2,
	LampaTaras
};

enum _LokalizacjeGoscinny
{
	SwiatloSufit,
	SwiatloKuchnia,
	SwiatloTaras
};

enum _LokalizacjeLazienka
{
	Sufit,
	Lustro
};

enum _Pogoda
{
	_SLONECZNIE = -1,
	_NEUTRALNIE,
	_DESZCZOWO
};