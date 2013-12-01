#ifndef SIGNALLISTENERZEUGER_H
#define SIGNALLISTENERZEUGER_H

#include "Signal.h"
#include <string>
#include <vector>

class SignalListeErzeuger 
{
private:
			
	short anzahlSignale;		 
	std::string datei;			
	long frequenz;				

public:
	std::vector<Signal> signalliste;
	bool check_pfad(string pfad_eingabe);
	std::string enter_pfad(bool* guterpfad);

	void Ausgabe_Schaltnetzdatei(std::string schaltnetz_pfad);
	void Ausgabe_Signale(std::string schaltnetz_pfad);
	void Ausgabe_Graphstruktur();
	bool check_for_dff(string temp_str, vector<Signal>* signalliste);
	bool check_for_and2(string temp_str, vector<Signal>* signalliste_local);
	bool check_for_xor2(string temp_str, vector<Signal>* signalliste_local);
	bool check_for_inv1a(string temp_str, vector<Signal>* signalliste_local);
};

#endif //SIGNALLISTEERZEUGER_H
