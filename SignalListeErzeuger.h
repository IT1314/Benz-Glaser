#include "Signal.h"


using namespace std;
class SignalListeErzeuger 
{
public:
	Signal signale;				// Signaltyp (Eingang, Intern, Ausgang, Unbekannt)
	short anzahlSignale;		// Anzahl der Elemente, an denen das Signal als Eingangssignal anliegt
	string datei;				// Dateipfad
	long frequenz;				//
};


bool check_pfad(string pfad_eingabe);
string enter_pfad(bool* guterpfad);
void Ausgabe_Schaltnetzdatei();
void Ausgabe_Signale();
void Ausgabe_Graphstruktur();