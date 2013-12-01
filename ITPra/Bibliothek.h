#ifndef BIBLIOTHEK_H
#define BIBLIOTHEK_H

//***************** INCLUDE FILES ******************************
#include <string>
#include <vector>

#include "Flipflop.h"

using namespace std;

//***************** INCLUDE FILES END **************************

#define BIBLIOTHEKSPFAD 1
#define BIBLIOTHEKSDATEI_AUSGABE 2
#define HAUPTMENUE_BIBLIOTHEK 3


//! \brief class Bibliothek
//!  enthaelt die Informationen zu den Gattern und Flipflops
class Bibliothek{
private :
	// ########## Attribute #############	
	vector<GatterTyp*> bibElemente;
	string datei;
	// ########## Attribute end #########

	// ######### Methoden ##############
	void openError();
	void readError();
	// ######### Methoden end ##########

public :
	// ######### Methoden ##############
	Bibliothek();
	Bibliothek( string pfad);
	~Bibliothek();
	string getPfad();
	GatterTyp* getBibElement(string typ);
	void dateiAusgabe();
	void dateiAuswerten();
	bool pfadEinlesen(string pfad);
	// ######### Methoden end ##########
	
};

#endif // BIBLIOTHEK_H