//***************** INCLUDE FILES ******************************
#include "Graphenerzeuger.h"
//***************** INCLUDE FILES  end ******************************

// ********************** METHODEN DEKLARATION ************************
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
bool Graphenerzeuger:: checksignal(){

}
void Graphenerzeuger :: createGraph(){

}
void Graphenerzeuger :: outputGraph(){

}
// ********************** METHODEN DEKLARATION END ********************







//***************************** END OF FILE *******************************************************
