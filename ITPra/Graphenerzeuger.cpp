#include "Graphenerzeuger.h"


void Graphenerzeuger :: createList(ListenElement* objekt){
	if(startElement == 0 ){
		startElement = objekt;
		endElement = objekt;

	}
	else{
		endElement ->setnextelement(objekt);
		endElement = objekt;
	}
}
void Graphenerzeuger :: createListElement(ListenElement* objekt){
	if(startElement == 0 && endElement == 0){
		startElement = objekt;
		endElement = objekt;

	}
	else{
		endElement ->setnextelement(objekt);
		endElement = objekt;
	}
}
ListenElement* Graphenerzeuger :: searchElement(Schaltwerk objekt){
		for(int i =0;i <anzahlSignale; i++){


		}

}