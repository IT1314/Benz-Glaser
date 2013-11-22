#ifndef SIGNALLISTEERZEUGER_H
#define SIGNALLISTEERZEUGER_H

#include "Signal.h"
#include <string>

class SignalListeErzeuger 
{
private:
	Signal* signale;			// Signaltyp (Eingang, Intern, Ausgang, Unbekannt)
	short anzahlSignale;		// Anzahl der Elemente, an denen das Signal als Eingangssignal anliegt
	std::string datei;			// Dateipfad
	long frequenz;				//

public:
	bool check_pfad(string pfad_eingabe);
	std::string enter_pfad(bool* guterpfad);

	void Ausgabe_Schaltnetzdatei(std::string schaltnetz_pfad);
	void Ausgabe_Signale(std::string schaltnetz_pfad);
	void Ausgabe_Graphstruktur();
};

#endif SIGNALLISTEERZEUGER_H
