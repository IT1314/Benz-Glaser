

#include "stdafx.h"
#include <string>


#define PFAD 1
#define AUSGABE_SCHALTNETZDATEI 2
#define AUSGABE_SIGNALE 3
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
	int anzahlZiele;

public:
	Signal();
	~Signal();
	int getAnzahlZiele();
	signalTypen getSignalTyp();
	string getQuelle();
	string getQuellenTyp();
	string getZiel(int pos);
	void setAnzahlZiele (int nZiele);
	void setSignalTyp(signalTypen sigTyp);
	void setQuelle(string gatterName);
	void setQuellenTyp(string gatterTyp);
	void zielHinzufuegen(string gatterName, int pos);
};

