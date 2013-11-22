
//***************** INCLUDE FILES ******************************
#include "Graphenerzeuger.h"
#include "SchaltwerkElement.h"
#include "SignalListeErzeuger.h"
#include "Bibliothek.h"

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

bool Graphenerzeuger:: checksignal(){

}
void Graphenerzeuger :: createGraph(){
	vector<SchaltwerkElement>Graph;
	
	for (auto it = std::begin(signalliste); it!=std::end(signalliste); ++it){

		string name = (*it)->getQuelleTyp() ;
		GatterTyp* Uebergabe = getBibElement(name);
		 Graph.push_back( SchaltwerkElement(Uebergabe)) ;
			
		
	}

}
void Graphenerzeuger :: outputGraph(){

}
// ********************** METHODEN DEKLARATION END ********************


//***************************** END OF FILE *******************************************************
