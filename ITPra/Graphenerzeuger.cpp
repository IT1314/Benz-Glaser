

/*
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
		endElement ->setNextElement(objekt);
		endElement = objekt;
	}
}
void Graphenerzeuger :: createListElement(ListenElement* objekt){
	if(startElement == 0 && endElement == 0){
		startElement = objekt;
		endElement = objekt;

	}
	else{
		endElement ->setNextElement(objekt);
		endElement = objekt;
	}
}
ListenElement* Graphenerzeuger :: searchElement(SchaltwerkElement objekt){
		for(int i =0;i < objekt.getnachfolgerElementesize(); i++){



		}
		ListenElement* dummy;
		return dummy;

}
bool Graphenerzeuger:: checksignal(){

}
void Graphenerzeuger :: createGraph(){

}
void Graphenerzeuger :: outputGraph(){

}
// ********************** METHODEN DEKLARATION END ********************


//***************************** END OF FILE *******************************************************
*/