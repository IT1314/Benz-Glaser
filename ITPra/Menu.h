#ifndef MENU_H
#define MENU_H

//***************** DEFINITIONS ********************************
#define FAKTOREN 1
#define BIBLIOTHEK 2
#define SCHALTWERK 3
#define ANALYSE 4
#define BEENDEN 5
//***************** DEFINITIONS END ****************************

#include "Graphenerzeuger.h"
#include "Listenelement.h"


//***************** CLASS DECLARATIONS *************************
class Menu{
	public:
		Menu();
		~Menu();
		void start();
		string auswahl;
		int auswahlzuint;
		double spannung_untermenue;
		double temperatur_untermenue;
		double prozess_untermenue;
		string schaltnetzdatei_pfad;
		bool guterpfad;
		bool guter_bibliotheks_pfad;
		ListenElement* erstes_element;
	private:
		Graphenerzeuger* meinGraphenerzeuger;
		void faktorenMenue();
		void bibliothekMenue();
		void schaltwerkMenue();
		void analyse();
		void menueKopf();


};
//***************** CLASS DECLARATIONS END *********************
#endif // MENU_H