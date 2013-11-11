#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H

#include <string>
#include <vector>
#include "GatterTyp.h"
#include "Flipflop.h"

using namespace std;

//! \brief class Bibliothek
//!  enthaelt die Informationen zu den Gattern und Flipflops
class Bibliothek{
private :
	vector<GatterTyp*> bibElemente;
	string datei;
	void openError();
	void readError();

public :
	string getPfad();
	GatterTyp* getBibElement(string typ);
	void dateiAusgabe();
	void dateiAuswerten();
	bool pfadEinlesen(string pfad);

	
};

#endif