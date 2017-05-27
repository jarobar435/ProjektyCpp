//my
#include "Symulacja.h"
#include "Pokoj.h"
#include "Modul.h"
//sfml
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//typ.
#include <iostream>
#include <string>
#include <vector>
#include <thread> 
#include <Windows.h>//dla sleep

using namespace std; 

//definizja zmiennej statycznej symulacji:
bool Symulacja::zakonczenieWatkow = false;
int Symulacja::godzina = 12;

Symulacja::Symulacja(int ilosc)
{
	//tworzenie pokoi/kontrolerów/modu³ów
	DodawaniePokoi(ilosc);

	//test poprawnoœci danych w konsoli
	//WypiszDane();

	//zarz¹dzanie oknem:
	SymulujOkno();
}
Symulacja::~Symulacja()
{

}
void Symulacja::wnioskowanie()
{
	double *poziomSwiatla = new double;
	*poziomSwiatla = 0;

	for (int i = 0; i < 2; i++)
	{
		*poziomSwiatla += pokoje[0]->Moduly[11+i]->getValue() + pokoje[1]->Moduly[8 + i]->getValue();
	}
	
	if ((*poziomSwiatla / 4) + (2 * pogoda) > 10)
	{
		wniosekCzyWlaczacSwiatlo = false;
		TekstyInterface[16]->setString(L"Œwita");
	}
	else
	{
		wniosekCzyWlaczacSwiatlo = true;
		TekstyInterface[16]->setString(L"Zmierzcha");
	}

	delete poziomSwiatla;
}
bool Symulacja::getZakonczenieWatkow()
{
	return zakonczenieWatkow;
}
void Symulacja::changeZakonczenieWatkow()
{
	zakonczenieWatkow = !zakonczenieWatkow;
}
void Symulacja::DodawaniePokoi(int ilosc)
{
	Pokoj* dodawany;
	for (int i = 0; i < ilosc; i++ )
	{
		int wybor = i % 7;
		switch (wybor)
		{
		case 1:
			dodawany = new Goscinny;
			break;
		case 2:
			dodawany = new Lazienka;
			break;
		case 3:
			dodawany = new Pakamera;
			break;
		default:
			dodawany = new Sypialnia;
		}
		pokoje.push_back(dodawany);
	}
}
void Symulacja::DodawanieTekstuSFML(const int pozX, const int pozY, const int rozm, const string kolor, const wchar_t* tekst)
{
	sf::Text* dodawany = new sf::Text;
	dodawany->setFont(Consolas);
	dodawany->setPosition(pozX, pozY);
	dodawany->setCharacterSize(rozm);
	if(kolor == "White")
		dodawany->setFillColor(sf::Color::White);
	if(kolor == "Blue")
		dodawany->setFillColor(sf::Color::Blue);
	if (kolor == "Cyan")
		dodawany->setFillColor(sf::Color::Cyan);
	dodawany->setString(tekst);

	TekstyInterface.push_back(dodawany);
}
void Symulacja::DodawanieGrafikiSFML(string zrodlo, int originX, int originY, int wspX, int wspY, int rotate)
{
	sf::Texture* dodawany = new sf::Texture;
	dodawany->loadFromFile("grafiki/" + zrodlo);
	dodawany->setSmooth(true);
	sf::Sprite* add = new sf::Sprite;
	add->setTexture(*dodawany);
	add->setOrigin(originX, originY);
	add->setPosition(wspX, wspY);
	add->rotate(rotate);

	GrafikiSFML.push_back(add);
}
void Symulacja::WypiszDane()
{
	int ilosc = pokoje.size();
	cout << "Iloœæ pokoi: " << ilosc << endl << endl;
	for (int i = 0; i < ilosc; i++)
	{
		cout << "Pokój: " << endl;
		pokoje[i]->WypiszDane();
	}
}
void Symulacja::WypiszKontrolerSFML(int wybrany_pokoj)
{
	//czyszczê bufor
	WypisywaneDaneSFML.clear();
	//zmieniam istniej¹ce napisy
	(*TekstyInterface[11]).setString("Kontroler:"); 
	(*TekstyInterface[12]).setString("");
	(*TekstyInterface[13]).setString("");
	int space = 0;
	for (int i = 0; i < 6; i++)
	{
		sf::Text* dodawany = new sf::Text; //tworzê nowy obiekt do wypisania
		dodawany->setFont(Consolas); //formatujê go w odpowiedni sposób
		dodawany->setPosition(1200, 220 + space);
		dodawany->setCharacterSize(20);
		dodawany->setFillColor(sf::Color::White);
		space += 30;
		switch (i)
		{
		case 0:
			dodawany->setString("Numer ID: " + to_string(pokoje[wybrany_pokoj]->Kontrolery[0]->getID()));
			break;
		case 1:
			dodawany->setString("Nazwa: " + pokoje[wybrany_pokoj]->Kontrolery[0]->getName());
			break;
		case 2:
			dodawany->setString("Napiecie zasilania: " + to_string(pokoje[wybrany_pokoj]->Kontrolery[0]->getVcc()) + "[V]");
			break;
		case 3:
			dodawany->setString("Ilosc pamieci: " + to_string(pokoje[wybrany_pokoj]->Kontrolery[0]->getMemory()) + "[MB]");
			break;
		case 4:
			dodawany->setString("Czestotliwosc taktowania: " + to_string(pokoje[wybrany_pokoj]->Kontrolery[0]->getClock()) + "[MHz]");
			break;
		case 5:
			dodawany->setString("Ilosc dostepnych pinow: " + to_string(pokoje[wybrany_pokoj]->Kontrolery[0]->getPins()));
			break;
		}
		WypisywaneDaneSFML.push_back(dodawany); //i dodajê do vectora tekstów
	}
}
void Symulacja::WypiszPokojSFML(int wybrany_pokoj)
{
	//czyszczê bufor
	WypisywaneDaneSFML.clear();
	//zmieniam istniej¹ce napisy
	(*TekstyInterface[11]).setString("Pokój:");
	(*TekstyInterface[12]).setString("");
	(*TekstyInterface[13]).setString("");
	int space = 0;
	for (int i = 0; i < 8; i++)
	{
		sf::Text* dodawany = new sf::Text; //tworzê nowy obiekt do wypisania
		dodawany->setFont(Consolas); //formatujê go w odpowiedni sposób
		dodawany->setPosition(1200, 220 + space);
		dodawany->setCharacterSize(20);
		dodawany->setFillColor(sf::Color::White);
		space += 30;
		switch (i)
		{
		case 0:
			dodawany->setString("Numer ID: " + to_string(pokoje[wybrany_pokoj]->getID()));
			break;
		case 1:
			dodawany->setString("Typ pokju: " + pokoje[wybrany_pokoj]->getType());
			break;
		case 2:
			dodawany->setString("Ilosc przekaznikow: " + to_string(pokoje[wybrany_pokoj]->getIlPrzekaznik()));
			break;
		case 3:
			dodawany->setString("Ilosc przelacznikow drzwi: " + to_string(pokoje[wybrany_pokoj]->getIlDrzwi()));
			break;
		case 4:
			dodawany->setString("Ilosc przelacznikow swiatla: " + to_string(pokoje[wybrany_pokoj]->getIlPrzelacznik()));
			break;
		case 5:
			dodawany->setString("Ilosc sensorow swiatla: " + to_string(pokoje[wybrany_pokoj]->getIlSensorSwiatla()));
			break;
		case 6:
			dodawany->setString("Modulow lacznie: " + to_string(pokoje[wybrany_pokoj]->getIlModul()));
			break;
		case 7:
			dodawany->setString("Kontrolerow lacznie: " + to_string(pokoje[wybrany_pokoj]->getIlKontroler()));
			break;
		}
		WypisywaneDaneSFML.push_back(dodawany); //i dodajê do vectora tekstów
	}
}
void Symulacja::WypiszListeModulowSFML(int wybrany_pokoj)
{
	//czyszczê bufor
	WypisywaneDaneSFML.clear();
	(*TekstyInterface[11]).setString(L"Modu³y:"); //zmieniam istniej¹ce napisy
	(*TekstyInterface[12]).setString("");
	(*TekstyInterface[13]).setString("");
	int space = 0;
	for (int i = 0; i < pokoje[wybrany_pokoj]->getIlModul(); i++)
	{
		sf::Text* dodawany = new sf::Text; //tworzê nowy obiekt do wypisania
		dodawany->setFont(Consolas); //formatujê go w odpowiedni sposób
		dodawany->setPosition(1200, 220 + space);
		dodawany->setCharacterSize(20);
		dodawany->setFillColor(sf::Color::White);
		space += 30;
		dodawany->setString("->" + pokoje[wybrany_pokoj]->Moduly[i]->getName() + " ID: " + to_string(pokoje[wybrany_pokoj]->Moduly[i]->getID()));
		WypisywaneDaneSFML.push_back(dodawany); //i dodajê do vectora tekstów
	}
}
void Symulacja::WypiszModulSFML(int wybrany_pokoj, int wybrany_modul)
{
		string nazwa = pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getName();
		if (nazwa == "Przekaznik")
			WypiszPrzekaznik(wybrany_pokoj, wybrany_modul);
		if (nazwa == "Sensor natezenia swiatla")
			WypiszSensorSwiatla(wybrany_pokoj, wybrany_modul);
		if (nazwa == "Przelacznik drzwi")
			WypiszPrzelacznikDrzwi(wybrany_pokoj, wybrany_modul);
		if (nazwa == "Przelacznik swiatla")
			WypiszPrzelacznikSwiatla(wybrany_pokoj, wybrany_modul);
}
void Symulacja::WypiszPrzekaznik(int wybrany_pokoj, int wybrany_modul)
{
	int space = 0;
	//czyszczenie vectora
	WypisywaneDaneSFML.clear();

	for (int i = 0; i < 5; i++)
	{
		sf::Text* dodawany = new sf::Text; //tworzê nowy obiekt do wypisania
		dodawany->setFont(Consolas); //formatujê go w odpowiedni sposób
		dodawany->setPosition(1200, 220 + space);
		dodawany->setCharacterSize(20);
		dodawany->setFillColor(sf::Color::White);
		space += 30;
		switch (i)
		{
		case 0:
			dodawany->setString("Numer ID: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getID()));
			break;
		case 1:
			dodawany->setString("Nazwa: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getName());
			break;
		case 2:
			dodawany->setString("Ilosc pinow: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getPins()));
			break;
		case 3:
			dodawany->setString("Rodzaj urzadzenia: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getType());
			break;
		case 4:
			if (pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getState() == true)
			{
				dodawany->setString(L"Obecny stan: W³¹czony");
				dodawany->setFillColor(sf::Color::Green);
			}
			else
			{
				dodawany->setString(L"Obecny stan: Wy³¹czony");
				dodawany->setFillColor(sf::Color::Red);
			}
			break;
		}
		WypisywaneDaneSFML.push_back(dodawany); //i dodajê do vectora tekstów
	}
}
void Symulacja::WypiszSensorSwiatla(int wybrany_pokoj, int wybrany_modul)
{
	int space = 0;
	//czyszczenie vectora
	WypisywaneDaneSFML.clear();

	for (int i = 0; i < 6; i++)
	{
		sf::Text* dodawany = new sf::Text; //tworzê nowy obiekt do wypisania
		dodawany->setFont(Consolas); //formatujê go w odpowiedni sposób
		dodawany->setPosition(1200, 220 + space);
		dodawany->setCharacterSize(20);
		dodawany->setFillColor(sf::Color::White);
		space += 30;
		switch (i)
		{
		case 0:
			dodawany->setString("Numer ID: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getID()));
			break;
		case 1:
			dodawany->setString("Nazwa: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getName());
			break;
		case 2:
			dodawany->setString("Ilosc pinow: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getPins()));
			break;
		case 3:
			dodawany->setString("Rodzaj urzadzenia: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getType());
			break;
		case 4:
			dodawany->setString("Obecny poziom swiatla: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getValue()));
		}
		WypisywaneDaneSFML.push_back(dodawany); //i dodajê do vectora tekstów
	}
}
void Symulacja::WypiszPrzelacznikDrzwi(int wybrany_pokoj, int wybrany_modul)
{
	int space = 0;
	//czyszczenie vectora
	WypisywaneDaneSFML.clear();

	for (int i = 0; i < 5; i++)
	{
		sf::Text* dodawany = new sf::Text; //tworzê nowy obiekt do wypisania
		dodawany->setFont(Consolas); //formatujê go w odpowiedni sposób
		dodawany->setPosition(1200, 220 + space);
		dodawany->setCharacterSize(20);
		dodawany->setFillColor(sf::Color::White);
		space += 30;
		switch (i)
		{
		case 0:
			dodawany->setString("Numer ID: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getID()));
			break;
		case 1:
			dodawany->setString("Nazwa: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getName());
			break;
		case 2:
			dodawany->setString("Ilosc pinow: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getPins()));
			break;
		case 3:
			dodawany->setString("Rodzaj urzadzenia: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getType());
			break;
		case 4:
			if (pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getState() == true)
			{
				dodawany->setString(L"Obecny stan: W³¹czony");
				dodawany->setFillColor(sf::Color::Green);
			}
			else 
			{
				dodawany->setString(L"Obecny stan: Wy³¹czony");
				dodawany->setFillColor(sf::Color::Red);
			}
			break;
		}
		WypisywaneDaneSFML.push_back(dodawany); //i dodajê do vectora tekstów
	}
}
void Symulacja::WypiszPrzelacznikSwiatla(int wybrany_pokoj, int wybrany_modul)
{
	int space = 0;
	//czyszczenie vectora
	WypisywaneDaneSFML.clear();

	for (int i = 0; i < 5; i++)
	{
		sf::Text* dodawany = new sf::Text; //tworzê nowy obiekt do wypisania
		dodawany->setFont(Consolas); //formatujê go w odpowiedni sposób
		dodawany->setPosition(1200, 220 + space);
		dodawany->setCharacterSize(20);
		dodawany->setFillColor(sf::Color::White);
		space += 30;
		switch (i)
		{
		case 0:
			dodawany->setString("Numer ID: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getID()));
			break;
		case 1:
			dodawany->setString("Nazwa: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getName());
			break;
		case 2:
			dodawany->setString("Ilosc pinow: " + to_string(pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getPins()));
			break;
		case 3:
			dodawany->setString("Rodzaj urzadzenia: " + pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getType());
			break;
		case 4:
			if (pokoje[wybrany_pokoj]->Moduly[wybrany_modul]->getState() == true)
			{
				dodawany->setString(L"Obecny stan: W³¹czony");
				dodawany->setFillColor(sf::Color::Green);
			}
			else
			{
				dodawany->setString(L"Obecny stan: Wy³¹czony");
				dodawany->setFillColor(sf::Color::Red);
			}
			break;
		}
		WypisywaneDaneSFML.push_back(dodawany); //i dodajê do vectora tekstów
	}
}
void Symulacja::SymulacjaCzasu(int krokWmin)
{
	int minuty = 0;
	while (!getZakonczenieWatkow())
	{
		if (minuty != 0)
			TekstyInterface[9]->setString(to_string(getGodzina()) + ":" + to_string(minuty));
		else
			TekstyInterface[9]->setString(to_string(getGodzina()) + ":" + to_string(minuty) + "0");

		//zmien godzine:
		if (minuty + krokWmin >= 60)
		{
			setGodzina(getGodzina() + (minuty + krokWmin) / 60);
			minuty %= (minuty + krokWmin) / 60;
		}
		else
		{
			minuty += krokWmin;
		}
		this_thread::sleep_for(chrono::seconds(3));

		if (getGodzina() >= 24)
			setGodzina(0);
	}
}
void Symulacja::tworzenieInterfejsu(int szerOkna, int wysOkna)
{
	//deklaracje grafik
	DodawanieGrafikiSFML("arduinologo.png", 280, 160, 750, 425, 15);
	DodawanieGrafikiSFML("planBudynku.png", 140, 180, 690, 360, 0);

	//deklaracja czcionki
	Consolas.loadFromFile("fonts/consola.ttf");

	//deklaracje nag³ówków:
	DodawanieTekstuSFML(50, 75, 36, "White", L"    Dane \nœrodowiskowe:");
	DodawanieTekstuSFML(600, 50, 36, "White", L"Plan budynku:");
	DodawanieTekstuSFML(1250, 105, 36, "White", L"Urz¹dzenia:"); //2

																 //DEKLARACJE PODNAG£ÓWKÓW:
	DodawanieTekstuSFML(50, 220, 20, "White", L"Godzina:");
	DodawanieTekstuSFML(50, 340, 20, "White", L"Pogoda:");
	DodawanieTekstuSFML(50, 460, 20, "White", L"Wnioskowanie:");
	DodawanieTekstuSFML(50, 580, 20, "White", L"Zapalone œwiat³a:");
	DodawanieTekstuSFML(50, 700, 20, "White", L"Otwarte drzwi:");
	DodawanieTekstuSFML(610, 730, 20, "White", L"Obecnie wybrany pokój:"); //8

																		   //DEKLARACJE WYŒWIETLANYCH ZMIENNYCH
	DodawanieTekstuSFML(135, 260, 50, "Blue", L""); //Godzina
	DodawanieTekstuSFML(640, 760, 50, "Blue", L"#Wybierz klikaj¹c powy¿ej#"); //WybranyPokój
	DodawanieTekstuSFML(1200, 150, 30, "White", L"#Nie wybrano"); //Pokoje
	DodawanieTekstuSFML(1200, 200, 30, "White", L"¿adnego pokoju#"); //Kontrolery
	DodawanieTekstuSFML(1200, 250, 30, "White", L""); //Modu³y
	DodawanieTekstuSFML(1170, 190, 20, "Blue", L""); //Wstecz
	DodawanieTekstuSFML(100, 380, 50, "Cyan", L"NEUTRALNA"); //Pogoda ind.15
	DodawanieTekstuSFML(120, 500, 50, "White", L"Œwita"); //Wnioskowanie
	DodawanieTekstuSFML(150, 620, 50, "White", L"0"); //otwarte drzwi
	DodawanieTekstuSFML(150, 740, 50, "White", L"0"); //otwarte okna
}

//switch w switchu wygl¹da okropnie, dodaæ chocia¿ enumy na pokoje i moduly
void Symulacja::WyswietlGrafikeSwiatla(int wybrany_pokoj, int wybrany_modul)
{
	switch (wybrany_pokoj)
	{
	case sypialnia:
		switch (wybrany_modul)
		{
		case LampaSufit:
			DodawanieGrafikiSFML("DuzeSwiatlo.png", 66, 77, 723, 396, 0);
			break;
		case LampkaNocna1:
			DodawanieGrafikiSFML("MaleSwiatlo.png", 37, 40, 670, 335, 0);
			break;
		case LampkaNocna2:
			DodawanieGrafikiSFML("MaleSwiatlo.png", 37, 40, 670, 450, 0);
			break;
		case LampaTaras:
			DodawanieGrafikiSFML("MaleSwiatlo.png", 37, 40, 720, 510, 0);
			break;
		}
		break;
	case goscinny:
		switch (wybrany_modul)
		{
		case SwiatloSufit:
			DodawanieGrafikiSFML("DuzeSwiatlo.png", 66, 77, 898, 429, 0);
			break;
		case SwiatloKuchnia:
			DodawanieGrafikiSFML("MaleSwiatlo.png", 37, 40, 930, 300, 0);
			break;
		case SwiatloTaras:
			DodawanieGrafikiSFML("MaleSwiatlo.png", 37, 40, 850, 570, 0);
			break;
		}
		break;
	case lazienka:
		switch (wybrany_modul)
		{
		case Sufit:
			DodawanieGrafikiSFML("DuzeSwiatlo.png", 66, 77, 725, 276, 0);
			break;
		case Lustro:
			DodawanieGrafikiSFML("MaleSwiatlo.png", 37, 40, 725, 232, 0);
			break;
		}
		break;
	case pakamera:
		DodawanieGrafikiSFML("DuzeSwiatlo.png", 66, 77, 605, 450, 0);
		break;
	}
}

void Symulacja::ZmienPogode(int WspX, int WspY)
{
	if (WspX >= 100 && WspY >= 380 && WspX <= 300 && WspY <= 430)
	{
		switch (pogoda)
		{
		case 0:
			TekstyInterface[15]->setFillColor(sf::Color::Cyan);
			TekstyInterface[15]->setString("NEUTRALNA");
			pogoda++;
			break;
		case 1:
			TekstyInterface[15]->setFillColor(sf::Color::Yellow);
			TekstyInterface[15]->setString(L"S£ONECZNA");
			pogoda -= 2;
			break;
		case -1:
			TekstyInterface[15]->setFillColor(sf::Color::Blue);
			TekstyInterface[15]->setString("DESZCZOWA");
			pogoda++;
			break;
		}
	}
}

void Symulacja::SymulujOkno()
{
	//tworzenie okna o rodzielczoœci u¿ytkownika (Fullscreen)
	sf::RenderWindow oknoAplikacji(sf::VideoMode().getDesktopMode(), L"Projekt IoT - Jaroslaw Bartoszuk", sf::Style::Fullscreen);
	oknoAplikacji.setVerticalSyncEnabled(true);

	//rozmiary stworzonego okna 
	int szerokoscOkna = oknoAplikacji.getSize().x,
		wysokoscOkna = oknoAplikacji.getSize().y;

	//metoda dodaj¹ca teksty interfejsu do wektora
	tworzenieInterfejsu(szerokoscOkna, wysokoscOkna);

	//otwórz w¹tek z godzin¹:
	thread watekGodzina(&Symulacja::SymulacjaCzasu, this, 30);
	//oraz w¹tki z symulacjami sensorów:
	thread wSensor1Sypialnia(&Modul::simulation, ref(pokoje[0]->Moduly[11]), 1);
	thread wSensor2Sypialnia(&Modul::simulation, ref(pokoje[0]->Moduly[12]), 1);
	thread wSensor1Goscinny(&Modul::simulation, ref(pokoje[1]->Moduly[8]), 1);
	thread wSensor2Goscinny(&Modul::simulation, ref(pokoje[1]->Moduly[9]), 1);

	//obs³uga zdarzeñ
	sf::Event zdarzenie;

	//zmienne do zarz¹dzania symulacj¹ okna
	int WspX = 0, //wspó³rzêdne klikniêcia
		WspY = 0,
		wybor_pokoju = -1, //identyfikatory 
		wybor_modulu = -1,
		menu = -1,
		pogoda = 0, //zmienne do zliczania wystapien
		drzwi = 0,
		przekazniki = 0,
		swiatla = 0,
		dayTime = 0,
		iterator = 0,
		spaceBtwHover = 30; 
	
	while (oknoAplikacji.isOpen())
	{
		while (oknoAplikacji.pollEvent(zdarzenie))
		{
			//sprawdŸ, czy zamkniêto okno krzyzykiem - w FulLscreen niepotrzebne
			//if (zdarzenie.type == sf::Event::Closed)
			//{
			//	changeZakonczenieWatkow();
			//	watekGodzina.join();
			//	oknoAplikacji.close();
			//}

			//sprawdŸ, czy zamkniêto okno klawiszem Esc
			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
			{
				changeZakonczenieWatkow();
				watekGodzina.join();
				wSensor1Sypialnia.join();
				wSensor2Sypialnia.join();
				wSensor1Goscinny.join();
				wSensor2Goscinny.join();
				oknoAplikacji.close();
			}

			//sprawdŸ, czy klikniêto LPM
			if (zdarzenie.type == sf::Event::MouseButtonReleased && zdarzenie.mouseButton.button == sf::Mouse::Left) //jeœli klikniêto LPM to sprawdz pozycjê i wyk. akcjê
			{
				WspY = zdarzenie.mouseButton.y;
				WspX = zdarzenie.mouseButton.x;

				//cout << endl << "X: " << WspX << "  Y: " << WspY;

				//klikniêcie W³¹cz/Wy³¹cz modu³u
				if (menu == 4 && WspX >= 1200 && WspY >= 340 && WspX <= 1450 && WspY <= 370)
				{
					pokoje[wybor_pokoju]->Moduly[wybor_modulu]->changeState();
				}
				//-------------------------------------------------------------------

				//klikniêcie w pogodê:
				ZmienPogode(WspX, WspY);
				//-------------------------------------------------------------------

				//klikniêcie w modul
				if (menu == 3)
				{
					for (int i = 0; i < pokoje[wybor_pokoju]->Moduly.size(); i++)
					{
						if (WspX >= 1200 && WspY >= 220 + i*spaceBtwHover && WspX <= 1500 && WspY <= 220 + (i + 1)*spaceBtwHover)
						{
							wybor_modulu = i;
							menu++;
							break;
						}
					}
				}
				//-------------------------------------------------------------------

				//klikniêcie w pokoje/kontrolery/moduly
				if (menu == 0)
				{
					//klikn¹³em Pokoje
					if (WspX >= 1200 && WspY >= 150 && WspX <= 1360 && WspY <= 180)
					{
						menu = 1;
					}

					//klikn¹³em Kontrolery
					if (WspX >= 1200 && WspY >= 200 && WspX <= 1510 && WspY <= 230)
					{
						menu = 2;
					}

					//klikn¹³em Modu³y
					if (WspX >= 1200 && WspY >= 250 && WspX <= 1360 && WspY <= 280)
					{
						menu = 3;
					}
				}
				//-------------------------------------------------------------------

				//klikniêto w plan budynku:
				{
					//klikniêcie pola sypialni
					if (WspX >= 650 && WspX <= 790 && WspY >= 300 && WspY <= 435)				//sypialnia
					{
						(*TekstyInterface[10]).setString(L"Sypialnia");
						wybor_pokoju = 0;
						menu = 0;
					}

					//klikniêcie pola pokoju goœcinnego
					if (WspX >= 800 && WspX <= 1000 && WspY >= 205 && WspY <= 500)				//goœcinny
					{
						(*TekstyInterface[10]).setString(L"Goœcinny");
						wybor_pokoju = 1;
						menu = 0;
					}

					//klikniêcie pola ³azienki
					if (WspX >= 647 && WspX <= 795 && WspY >= 235 && WspY <= 320)				//³azienka - 647 235 795 320 
					{
						(*TekstyInterface[10]).setString(L"£azienka");
						wybor_pokoju = 2;
						menu = 0;
					}

					//klikniêcie pola pakamery
					if (WspX >= 570 && WspX <= 650 && WspY >= 355 && WspY <= 485)				//pakamera
					{
						(*TekstyInterface[10]).setString(L"Pakamera");
						wybor_pokoju = 3;
						menu = 0;
					}
				}
				//-------------------------------------------------------------------

				//klikniêcie wstecz:
				if (menu > 0 && WspX >= 1170 && WspY >= 190 && WspX <= 1270 && WspY <= 215)
				{
					if (menu < 4)
						menu = 0;
					else
						menu = 3;
				}

				//wypisywanie wstecz:
				if (menu > 0)
				{
					(*TekstyInterface[14]).setString("<--WSTECZ");
				}
				else
				{
					(*TekstyInterface[14]).setString("");
				}

				//wypisywane menu:
				switch (menu)
				{
				case 0:
					WypisywaneDaneSFML.clear();
					(*TekstyInterface[11]).setString("-> Pokoje");
					(*TekstyInterface[12]).setString("-> Mikrokontrolery");
					(*TekstyInterface[13]).setString(L"-> Modu³y");
					break;
				case 1:
					WypiszPokojSFML(wybor_pokoju);
					break;
				case 2:
					WypiszKontrolerSFML(wybor_pokoju);
					break;
				case 3:
					WypiszListeModulowSFML(wybor_pokoju);
					break;
				case 4:
					WypiszModulSFML(wybor_pokoju, wybor_modulu);
					break;
				}

				//zmiejszam vector, ¿eby usun¹æ wszystkie elem. o ind >=2
				GrafikiSFML.resize(2);
				
				//resetujê wypisywane zmienne
				przekazniki = drzwi = swiatla = 0;

				//zliczanie zmiennych i rysowanie sprajtów
				for (int i = 0; i < pokoje.size(); i++) //przechodzê po pokojach
				{
					for (int j = pokoje[i]->Moduly.size() - 1; j >= 0; j--)
					{
						string nazwa = pokoje[i]->Moduly[j]->getName();

						if (nazwa == "Przelacznik swiatla")
						{
							if ((!(pokoje[i]->Moduly[j]->getChanged()) && pokoje[i]->Moduly[j]->getState()) || (pokoje[i]->Moduly[j]->getChanged() && !(pokoje[i]->Moduly[j]->getState())))//jeœli nie byl zmieniony ostatnio
							{	//to zmien stan przekaznika
								swiatla++;
								pokoje[i]->Moduly[j]->setChanged(); //i zaznacz ze zmieniasz
								switch (i)
								{
								case sypialnia:
									pokoje[i]->Moduly[j - 6]->changeState();
									break;
								case goscinny:
									pokoje[i]->Moduly[j - 5]->changeState();
									break;
								case lazienka:
									pokoje[i]->Moduly[j - 3]->changeState();
									break;
								case pakamera:
									pokoje[i]->Moduly[j - 2]->changeState();
									break;
								}
							}
							continue;
						}
						if (nazwa == "Przekaznik")
						{
							if (pokoje[i]->Moduly[j]->getState())
							{//jeœli zmieniono stan przekaŸnika - z automatu zmieniam œwiat³o
								przekazniki++;
								WyswietlGrafikeSwiatla(i, j);
							}
							continue;
						}
						if (nazwa == "Sensor natezenia swiatla")
						{
							continue;
						}
						if (nazwa == "Przelacznik drzwi")
						{//jeœli zmieniono stan przelacznika drzwi - sprawdzam pogodê i stan sensora i wnioskujê czy zmieniæ stan przekaŸnika
							if (!pokoje[i]->Moduly[j]->getState()) //jeœli prze³. wy³¹czony 
							{		//i zmierzcha				//i œwieci siê w pokoju	
								if (wniosekCzyWlaczacSwiatlo && (pokoje[i]->Moduly[0]->getState()))
									pokoje[i]->Moduly[0]->changeState();
							}

							if (pokoje[i]->Moduly[j]->getState())
							{
								if (wniosekCzyWlaczacSwiatlo && !(pokoje[i]->Moduly[0]->getState()))
									pokoje[i]->Moduly[0]->changeState();
								drzwi++;
							}
							continue;
						}
					}
				}
					TekstyInterface[17]->setString(to_string(przekazniki));
					TekstyInterface[18]->setString(to_string(drzwi));
			}
		}

		oknoAplikacji.clear(sf::Color::Black);
		if (iterator<200)
			oknoAplikacji.draw(*GrafikiSFML[0]);

		//----------------------------------------------------------------------
		//rysowanie okna g³ównego 
		else
		{
			for (int i = 0; i < TekstyInterface.size(); i++)
			{
				oknoAplikacji.draw(*TekstyInterface[i]);
			}

			for (int i = 0; i < WypisywaneDaneSFML.size(); i++)
			{
				oknoAplikacji.draw(*WypisywaneDaneSFML[i]);
			}

			for (int i = 0; i < GrafikiSFML.size(); i++)
			{
				oknoAplikacji.draw(*GrafikiSFML[i]);
			}
			wnioskowanie();
		}

		oknoAplikacji.display();

		//animacja pocz¹tkowa - postój
		if (iterator < 100)	
		{
			iterator++;
		}

		//animacja pocz¹tkowa - skalowanie w dó³
		else if (iterator < 200)
		{
			(*GrafikiSFML[0]).setScale(1 - (iterator - 100)*0.01, 1 - (iterator - 100)*0.01);
			iterator++;
		}
	}
}

int Symulacja::getGodzina()
{
	return godzina;
}

void Symulacja::setGodzina(int godz)
{
	godzina = godz;
}
