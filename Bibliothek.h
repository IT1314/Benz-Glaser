#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H

#include <string>
#include <vector>

#include "Flipflop.h"

using namespace std;

#define BIBLIOTHEKSPFAD 1
#define BIBLIOTHEKSDATEI_AUSGABE 2
#define HAUPTMENUE_BIBLIOTHEK 3


//! \brief class Bibliothek
//!  enthaelt die Informationen zu den Gattern und Flipflops
class Bibliothek{
private :
	vector<GatterTyp*> bibElemente;
	string datei;
	void openError();
	void readError();

public :
	Bibliothek();
	Bibliothek( string pfad);
	~Bibliothek();
	string getPfad();
	GatterTyp* getBibElement(string typ);
	void dateiAusgabe();
	void dateiAuswerten();
	bool pfadEinlesen(string pfad);

	
};

#endif BIBLIOTHEK_H