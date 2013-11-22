#ifndef GRAPHENERZEUGER_H
#define GRAPHENERZEUGER_H

#include "Bibliothek.h"
#include "SignalListeErzeuger.h"
#include "ListenElement.h"
#include "SchaltwerkElement.h"

using namespace std;

class Graphenerzeuger{
private:
	// ########## Attribute #############	
		Bibliothek* bibliothek;
		ListenElement* startElement;
		ListenElement* endElement;
		Signal* signale;
		short anzahlSignale;
    // ########## Attribute  end #############	
public:
	// ######### Methoden ##############
	Graphenerzeuger(){}
	~Graphenerzeuger(){}
		void setSignale();

		void createList(ListenElement* objekt);
		void createListElement(ListenElement* objekt);
		bool checksignal();
		void createGraph();
		void outputGraph();
		// ######### Methoden end ##############




};

#endif GRAPHENERZEUGER_H