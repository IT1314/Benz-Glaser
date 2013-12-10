


//***************** INCLUDE FILES ******************************
#include "Graphenerzeuger.h"
#include "SchaltwerkElement.h"
#include "SignalListeErzeuger.h"
#include "Bibliothek.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
//***************** INCLUDE FILES  end ******************************

// ********************** METHODEN DEKLARATION ************************


ListenElement*  Graphenerzeuger :: getStartElement(){
	return startElement;
}


void Graphenerzeuger :: createList(){
	
	
	for( int a = 0; a< Signale.size();a++){  
	  
		
		
			
			ListenElement* uebergabe = new ListenElement();	
			if(Signale.at(a).getQuellenTyp()!=""){
			string test = Signale.at(a).getQuellenTyp();
			GatterTyp* typus = bibliothek->getBibElement(Signale.at(a).getQuellenTyp()); //! Ermittelt den Gattertyp mittels der Bibliothek.			 
			SchaltwerkElement* object2 = new SchaltwerkElement(typus);
			object2->setName(Signale.at(a).getQuelle()); //! set Methoden werden aufgerufen
			uebergabe->setSchaltwerkElement(object2); 
			uebergabe->setNextElement(NULL); 
			createListElement(uebergabe);
			}
			else{
				cout<<"Fehler!"<<endl;
			}
		
	} //! Ende der for-Schleife 
}
void Graphenerzeuger :: createListElement(ListenElement* objekt){
	if(startElement ==NULL && endElement == NULL){//! Wenn die Liste leer ist wird sie angelegt.
		startElement = objekt;
		endElement = objekt;

	}
	else{ //! wird andernfalls hinten angefuegt.
		endElement ->setNextElement(objekt);
		endElement = objekt;
	}
}
void Graphenerzeuger:: destroyGraph(){

	// überprüft ob was im startelement drinnen steht.
	
		// löscht liste von oben nach unten bis zum letzten element
		while( !(startElement == NULL)){
			ListenElement* loeschzeiger ;
			loeschzeiger = startElement;
			startElement = startElement->getNextElement();
			
			delete loeschzeiger;
			
		}// while schleife
		startElement = NULL;
		endElement = NULL;
	
}

	

SchaltwerkElement* Graphenerzeuger:: searchListElement(string gattername){
	ListenElement* start =   startElement;
	while( start != 0 ) {
		if(start->getSchaltwerkElement()->getName() == gattername)
			return start->getSchaltwerkElement();
		start = start->getNextElement();
	}
	return 0;
}
		




void Graphenerzeuger:: checksignal(){
	// geht liste durch
	for(ListenElement* laufzeiger = startElement; laufzeiger != NULL; laufzeiger = laufzeiger->getNextElement()){

		int anzahlgattereingaenge;
		int anzahleingangssignale;
		// holt sich die information, die zu vergleichen sind
		anzahleingangssignale =	laufzeiger->getSchaltwerkElement()->getAnzahlEingangssignale();
		anzahlgattereingaenge = laufzeiger->getSchaltwerkElement()->getTyp()->getEingaenge();
		// vergleicht die dateneingänge
		if( (anzahlgattereingaenge > anzahleingangssignale) || (anzahlgattereingaenge < anzahleingangssignale)){
			// gibt feldermeldung aus
			cout << "Es gibt ungenutzte Eingaenge der Gatter bzw. es gibt zu viele Eingangssignale" << endl;
			cout << " Deshalb wurde der Graph wieder geloescht, da nicht alles korrekt war" << endl;
			cout << " Lesen Sie bitte einen anderen Schaltplan ein" << endl;
			cout << " Fehler bei Gatter: " << laufzeiger->getSchaltwerkElement()->getName() << endl;
			cout << "Gattereingaengsignale: " << anzahleingangssignale << endl;
			cout << " Eingaenge laut Bibliothek: " << anzahlgattereingaenge << endl;
			cout << " Ihr Graph wurde geloescht" << endl;
			
			 // löscht Graph
			destroyGraph();
			break;
			
		} // ende der ifschleife

	}// ende der forschleife
}
ListenElement* Graphenerzeuger :: createGraph(){
  
	if( ((bibliothek != NULL)) && (!Signale.empty()) ){ //! Sicherheitsabfrage ob alle Daten zur erzeugung vorliegen.
		
		if( startElement != NULL){
			destroyGraph(); //! Falls bereits ein Graph vorhanden ist im Speicher wird dieser ueber die destroy Methode zerstoert bevor der neue angelegt wird.
		} 
		
		createList();
		int a = 0;

 		

		for( auto it = Signale.begin(); it!= Signale.end() ; it++){
			
			//! Ueberprueft ob die Signale benutzt werden oder nicht.
			if(!((it->getAnzahlZiele() == 0) && (it->getQuelle() == "") && (it->getQuellenTyp() == "") )){ //! Die Eingangssignale werden hier erkannt und als solche in die Eingangselemente abgelegt.
				if( it->getSignalTyp() == eingang ){ 
					int anzahl = it->getAnzahlZiele(); 
					SchaltwerkElement* object; 
					for( int b = 0; b<anzahl; b++){ 
						object = searchListElement( it->getZiel(b)); 
						object->setIsEingangsElement(true); 
						object->EingangsSignalZaehlen(); //! zaehlt  die Eingangssignale hoch. 
					}
				}//! Ende der 1. if-Schleife
				 
				if( it->getSignalTyp() == ausgang){//! Die Ausgangssignale werden hier erkannt und als solche in die Ausgangselemente abgelegt.
					SchaltwerkElement* object;
					object = searchListElement( it->getQuelle());
					object->setIsAusgangsElement(true); 
				} //! Ende der 2. if-Schleife
			
				
				if(it->getSignalTyp() == intern){//! Hier werden die Internen Signale erkannt und die entsprechenden Elemente befuellt.

					int anzahl = it->getAnzahlZiele(); 
					SchaltwerkElement* quelle; //! Quellgatter
					SchaltwerkElement* ziel; //! Zielgatter				 
					quelle = searchListElement(it->getQuelle()); //! Sucht das Quellgatter in der liste der Namen. 
					for( int n = 0; n<anzahl; n++){ 
						ziel = searchListElement(it->getZiel(n)); //! findet n-te ziel des quellgatters
						ziel -> EingangsSignalZaehlen(); //! zaehlt das Eingangssignal hoch fuer das Zielgatters // muss ich noch ins Schaltwerk schreiben.
						quelle -> nachfolgerHinzufuegen(ziel,n); //! fuegt dem Quellgatter sein Zielgatter hinzu 
					} //! Ende der for-Schleife 
					quelle -> setAnzahlNachfolger(anzahl); 
				}  //! Ende der 3. if-Schleife
				if(it->getSignalTyp() == unbekannt){ 
					cout << " Es wurde ein unbekanntes Signal entdeckt" << endl; 
				} 
			}else{ 
				cout << " Das Signal s " << a+1 << " ist ein unbenutzes Signal. " << endl; 
				cout << " Ihr Graph wurde geloescht auf grund dieses Fehlers" << endl;
				destroyGraph();//Fehler?
				return NULL; } 
			it ++;
		}  //! Ende der for-Schleife
		 //! Ueberpruefung auf offene Eingaenge 
		 checksignal();
		return startElement; 
	}
	else{
		cout << "Der Graph konnte nicht erzeugt werden, da keine Daten zur Bibliothek oder Signalliste gefunden wurden." << endl;
	} 
	return NULL; //! Es wird ein Nullzeiger zurueckgegeben wenn kein Graph erzeugt werden konnte. 
}
void Graphenerzeuger :: outputGraph(){
	if( startElement != NULL){

		for(ListenElement* laufzeiger = startElement; laufzeiger != NULL; laufzeiger = laufzeiger->getNextElement()){
		// gibt schaltwerkdaten aus
		cout << "Gattername: " << laufzeiger->getSchaltwerkElement()->getName() << endl;
		cout << "Gattertyp: " << laufzeiger->getSchaltwerkElement()->getTyp()->getName() << endl;
		cout << "-->Das Gatter hat " << laufzeiger->getSchaltwerkElement()->getAnzahlNachfolger() << " Ziele" << endl;
		cout << "Angeschlossene Gatter: ";
		// gibt nachfolger aus
		for( int e = 0; e< laufzeiger->getSchaltwerkElement()->getAnzahlNachfolger(); e++){

			cout << laufzeiger->getSchaltwerkElement()->getNachfolger(e)->getName() << "  " ;
		}
			cout << endl;
			// gibt boolwerte aus
		if( laufzeiger->getSchaltwerkElement()->getIsAusgangsElement() ){

		cout << " es ist ein ausgangselement" << endl;
		}

			if( laufzeiger->getSchaltwerkElement()->getIsEingangsElement() ){

		cout << " es ist ein eingangselement" << endl;

		}

			cout << endl << endl << endl;

		
		} // ende der forschleife
	
		
	}
	else{ cout << endl << "Es wurde noch kein Graph erzeugt. Deshalb kann auch nichts ausgegeben werden. Ueberpruefen sie ihre Eingangsdaten." << endl;}// der ueberpruefungsifs

}
	
// ********************** METHODEN DEKLARATION END ********************

//***************************** END OF FILE *******************************************************

