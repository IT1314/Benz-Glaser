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
		SchaltwerkElement(GatterTyp* gTyp);
		~SchaltwerkElement();

		GatterTyp* typ;
		vector <SchaltwerkElement*> nachfolgerElemente;



	public:

		string getName() ;
		GatterTyp* getTyp();
		double getLaufzeitEinzelgatter();
		SchaltwerkElement* getNachfolger(int pos);
		int getAnzahlNachfolger();
		short getAnzahlEingangssignale();
		bool getIsEingangsElement();
		bool getIsAusgagsElement();
		void setName(string n);
		void nachfolgerHinzufügen(SchaltwerkElement* schaltwerkElement);
		void setAnzahlNachfolger(int anzahlN);
		void setAnzahlEingangssignale(short anzahlE);
		void setIsEingangsElement(bool isEingangsEl);
		void setIsAusgangsElement(bool isAusgangsEl);
		void setLaufzeitEinzelgatter(double lfz);
};
#endif SCHALTWERK_H