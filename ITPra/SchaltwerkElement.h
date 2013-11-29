#ifndef SCHALTWERK_H
#define SCHALTWERK_H

#include "GatterTyp.h"
#include <string>
#include <vector>
using namespace std;

class SchaltwerkElement
{




	private:

		string name;		
		double laufzeitEinzelgatter;
		int anzahlNachfolger;
		bool isEingangsElement;
		bool isAusgangsElement;
		short anzahlEingangssignale;
		vector <SchaltwerkElement*> nachfolgerElemente;
		~SchaltwerkElement();

		GatterTyp* typ;
		



	public:
		
		SchaltwerkElement(GatterTyp* gTyp);
		string getName() ;
		GatterTyp* getTyp();
		double getLaufzeitEinzelgatter();
		SchaltwerkElement* getNachfolger(int pos);
		int getAnzahlNachfolger();
		short getAnzahlEingangssignale();
		int getnachfolgerElementesize();
		bool getIsEingangsElement();
		bool getIsAusgagsElement();
		void setName(string n);
		void nachfolgerHinzufuegen(SchaltwerkElement* schaltwerkElement, int pos);
		void setAnzahlNachfolger(int anzahlN);
		void EingangsSignalZaehlen();
		void setAnzahlEingangssignale(short anzahlE);
		void setIsEingangsElement(bool isEingangsEl);
		void setIsAusgangsElement(bool isAusgangsEl);
		void setLaufzeitEinzelgatter(double lfz);
};
#endif SCHALTWERK_H