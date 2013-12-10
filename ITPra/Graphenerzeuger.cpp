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

void Graphenerzeuger :: createList(){//! Erzeugt die Liste
		
	for( int a = 0; a< Signale.size();a++){  //! Durchlaeuft den Signalvector
	  		
		if(Signale.at(a).getQuellenTyp()!=""){	//! Es wird verhindert das Signale mit leerer Quelle  hinzugefuegt werden.

		    ListenElement* uebergabe = new ListenElement();				
			
			GatterTyp* typus = bibliothek->getBibElement(Signale.at(a).getQuellenTyp()); //! Ermittelt den Gattertyp mittels der Bibliothek.			 
			SchaltwerkElement* object2 = new SchaltwerkElement(typus);
			object2->setName(Signale.at(a).getQuelle()); //! set Methoden werden aufgerufen
			uebergabe->setSchaltwerkElement(object2); 
			uebergabe->setNextElement(NULL); 
			createListElement(uebergabe);

		}//! Ende der if-Schleife			
	} //! Ende der for-Schleife 
}

void Graphenerzeuger :: createListElement(ListenElement* objekt){//! Fügt ein Element an die Liste an.
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
			
		while( !(startElement == NULL)){//! Ueberprueft ob der Graph leer ist wenn nicht, loescht die Schleife die Elemente.
			ListenElement* loeschzeiger ;
			loeschzeiger = startElement;
			startElement = startElement->getNextElement();
			
			delete loeschzeiger;
			
		}//! Ende der while-Schleife
		startElement = NULL;
		endElement = NULL;
	
}

SchaltwerkElement* Graphenerzeuger:: searchListElement(string gattername){
	ListenElement* start =   startElement;
	while( start != 0 ) {//! Durchlaeuft die Liste.
		if(start->getSchaltwerkElement()->getName() == gattername){
			return start->getSchaltwerkElement();
		}
		start = start->getNextElement();
	}
	return 0;
}

void Graphenerzeuger:: checksignal(){
	//! Ueberprueft die Liste.
	for(ListenElement* laufzeiger = startElement; laufzeiger != NULL; laufzeiger = laufzeiger->getNextElement()){

		int anzahlgattereingaenge;
		int anzahleingangssignale;
		
		anzahleingangssignale =	laufzeiger->getSchaltwerkElement()->getAnzahlEingangssignale();
		anzahlgattereingaenge = laufzeiger->getSchaltwerkElement()->getTyp()->getEingaenge();//! Belaedt die Vergleichsvariablen.
		
		if( (anzahlgattereingaenge > anzahleingangssignale) || (anzahlgattereingaenge < anzahleingangssignale)){//! Vergleicht die Daten.
			//! Fehlermeldung wird ausgegeben.
			cout << "Es gibt ungenutzte Eingaenge der Gatter bzw. es gibt zu viele Eingangssignale" << endl;
			cout << " Deshalb wurde der Graph wieder geloescht, da nicht alles korrekt war" << endl;
			cout << " Lesen Sie bitte einen anderen Schaltplan ein" << endl;
			cout << " Fehler bei Gatter: " << laufzeiger->getSchaltwerkElement()->getName() << endl;
			cout << "Gattereingaengsignale: " << anzahleingangssignale << endl;
			cout << " Eingaenge laut Bibliothek: " << anzahlgattereingaenge << endl;
			cout << " Ihr Graph wurde geloescht" << endl;
			
			 //! Graph wird geloescht
			destroyGraph();
			break;
			
		} // Ende der if-Schleife

	}// Ende der for-Schleife
}

ListenElement* Graphenerzeuger :: createGraph(){
  
	if( ((bibliothek != NULL)) && (!Signale.empty()) ){ //! Sicherheitsabfrage ob alle Daten zur erzeugung vorliegen.
		
		if( startElement != NULL){
			destroyGraph(); //! Falls bereits ein Graph vorhanden ist im Speicher wird dieser ueber die destroy Methode zerstoert bevor der neue angelegt wird.
		} 
		
		createList();//! Die Liste der Schaltwerke wird erzeugt.
		int a = 0;
		
		for( auto it = Signale.begin(); it!= Signale.end() ; it++,a++){
									
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

void Graphenerzeuger :: outputGraph(){//! Gibt den Graphen auf der Konsole aus.
	if( startElement != NULL){

		for(ListenElement* laufzeiger = startElement; laufzeiger != NULL; laufzeiger = laufzeiger->getNextElement()){
		
		cout << "Gattername: " << laufzeiger->getSchaltwerkElement()->getName() << endl;
		cout << "Gattertyp: " << laufzeiger->getSchaltwerkElement()->getTyp()->getName() << endl;
		cout << "-->Das Gatter hat " << laufzeiger->getSchaltwerkElement()->getAnzahlNachfolger() << " Ziele" << endl;
		cout << "Angeschlossene Gatter: ";
		
		for( int e = 0; e< laufzeiger->getSchaltwerkElement()->getAnzahlNachfolger(); e++){//! gibt die Nachfolger des Gatters aus.

			cout << laufzeiger->getSchaltwerkElement()->getNachfolger(e)->getName() << "  " ;
		}
			cout << endl;
			
		if( laufzeiger->getSchaltwerkElement()->getIsAusgangsElement() ){//! gibt einen Boolwert zurueck.

		cout << " es ist ein ausgangselement" << endl;
		}

			if( laufzeiger->getSchaltwerkElement()->getIsEingangsElement() ){

		cout << " es ist ein eingangselement" << endl;

		}

			cout << endl << endl << endl;

		
		} // Ende der for-Schleife
	
		
	}
	else{ cout << endl << "Es wurde noch kein Graph erzeugt. Deshalb kann auch nichts ausgegeben werden. Ueberpruefen sie ihre Eingangsdaten." << endl;}// der ueberpruefungsifs

}
	
// ********************** METHODEN DEKLARATION END ********************

//***************************** END OF FILE *******************************************************

