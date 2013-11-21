#ifndef GRAPHENERZEUGER_H
#define GRAPHENERZEUGER_H

#include "Bibliothek.h"
#include "SignalListeErzeuger.h"

using namespace std;

class Graphenerzeuger{
private:
		Bibliothek* bibliothek();
		ListenElement* startElement();
		ListenElement* endElement();
		Signal* signale();
		short anzahlSignale();

public:
	Graphenerzeuger(){}
	~Graphenerzeuger(){}
		void setSignale();

		void createList(ListenElement* objekt);
		void createListElement(ListenElement* objekt);
		ListenElement* searchElement(Schaltwerk objekt);
		bool checksignal();
		void createGraph();
		void outputGraph();
		




};
#endif GRAPHENERZEUGER_H