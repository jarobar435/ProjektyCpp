#pragma once
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
	static int godzina;
	static bool zakonczenieWatkow;

public:
	Symulacja(int ilosc = 4);
	~Symulacja();
	static bool getZakonczenieWatkow();
	void changeZakonczenieWatkow();
	void DodawaniePokoi(int ilosc);
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
	void ZmienPogode(int WspX, int WspY, int & pogoda);
};

enum NazwyPokojow
{
	sypialnia,
	goscinny,
	lazienka,
	pakamera
};

enum LokalizacjeSypialnia
{
	LampaSufit,
	LampkaNocna1,
	LampkaNocna2,
	LampaTaras
};

enum LokalizacjeGoscinny
{
	SwiatloSufit,
	SwiatloKuchnia,
	SwiatloTaras
};

enum LokalizacjeLazienka
{
	Sufit,
	Lustro
};