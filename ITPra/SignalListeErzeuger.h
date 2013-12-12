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

	bool check_for_gatter(string temp_str, vector<Signal>* signalliste);

public:
	SignalListeErzeuger();
	~SignalListeErzeuger();
	std::vector<Signal> signalliste;
	std::string enter_pfad(bool* guterpfad);

	void ausgabe_signale();
	void berechne_Signale();
	void ausgabe_Schaltnetzdatei();
	long get_frequenz () {return this->frequenz;}
	short get_anzahlSignale() {return this->anzahlSignale;}

};

#endif //SIGNALLISTEERZEUGER_H
