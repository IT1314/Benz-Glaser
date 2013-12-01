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
		SignalListeErzeuger* signallisteerzeug;
	
    // ########## Attribute  end #############	
public:
	// ######### Methoden ##############
	Graphenerzeuger(Bibliothek* bib,SignalListeErzeuger* signalliste) : bibliothek(bib),signallisteerzeug(signalliste) {}
	~Graphenerzeuger(){}
	ListenElement* getStartElement();
	void setSignale();
	void  createList();
	void destroyGraph();
	void createListElement(ListenElement* objekt);
	void checksignal();
	SchaltwerkElement* searchListElement(string gattername);
	ListenElement* createGraph();
	void outputGraph();
		// ######### Methoden end ##############




};

#endif //GRAPHENERZEUGER_H