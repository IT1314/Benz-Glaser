#ifndef SIGNAL_H
#define SIGNAL_H

#include "stdafx.h"
#include <string>

#define PFAD 1
#define AUSGABE_SCHALTNETZDATEI 2
#define AUSGABE_SIGNALE_MENU 3
#define AUSGABE_GRAPHSTRUKTUR 4
#define HAUPTMENUE 5

using namespace std;

enum signalTypen 
{
	eingang,
	intern,
	ausgang,
	unbekannt
};

class Signal 
{
private:
	signalTypen signalTyp;
	string quelle;
	string quellenTyp;
	string ziele[5];
	string name;
	int anzahlZiele;
	double frequenz;

public:
	Signal();
	~Signal();
	int getAnzahlZiele();
	signalTypen getSignalTyp();
	string getQuelle();
	string getQuellenTyp();
	string getZiel(int pos);
	string getName();
	double get_Frequenz() {return this->frequenz;};
	void set_Frequenz(double freq) {this->frequenz = freq;};
	void setName(string name);
	void setAnzahlZiele (int nZiele);
	void setSignalTyp(signalTypen sigTyp);
	void setQuelle(string gatterName);
	void setQuellenTyp(string gatterTyp);
	void zielHinzufuegen(string gatterName, int pos);
};

#endif SIGNAL_H
