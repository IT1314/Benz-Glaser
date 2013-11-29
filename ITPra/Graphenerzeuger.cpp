


//***************** INCLUDE FILES ******************************
#include "Graphenerzeuger.h"
#include "SchaltwerkElement.h"
#include "SignalListeErzeuger.h"
#include "Bibliothek.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
//***************** INCLUDE FILES  end ******************************

// ********************** METHODEN DEKLARATION ************************





void Graphenerzeuger :: createList(){
	Signal* forlauf = signale; //! Forlauf durchlaeuft das Signalarry um die Signale abzugreifen.
	for( int a= 0; a<anzahlSignale ; forlauf++, a++){ 
		
		if(!(forlauf->getQuelle() == "")){ //! Verhindert das Einfuegen wenn die Quelle leer ist.
			
			ListenElement* uebergabe = new ListenElement();			
			GatterTyp* typus = bibliothek->getBibElement(forlauf->getQuellenTyp()); //! Ermittelt den Gattertyp mittels der Bibliothek.			 
			SchaltwerkElement* object2 = new SchaltwerkElement(typus);
			object2->setName(forlauf->getQuelle()); //! set Methoden werden aufgerufen
			uebergabe->setSchaltwerkElement(object2); 
			uebergabe->setNextElement(NULL); 
			createListElement(uebergabe);
		} //! Ende der if-Schleife
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
	ListenElement *first = startElement;
    ListenElement *help1;
	ListenElement *help2;
	ListenElement *last = endElement;
    help1 = first;
	while(help1 != NULL){//! Standard delete-Schleife fuer Zeiger
	help2 = help1 ++;
	delete help1;
	help1 = help2;
	}
	help1 = help2 = last = first = NULL;

}

SchaltwerkElement* Graphenerzeuger:: searchListElement(string gattername){
	SchaltwerkElement* result;
	ListenElement* start =   startElement;
	ListenElement* end   =   endElement;
	for (ListenElement* at = start; at!=end; ++at){//! for-Schleife die, die Suche nach dem spezifischen Element realisiert.
		result = at->getSchaltwerkElement() ;
		if(result->getName() == gattername){
			return result;
		}

		
	}
		

		
	}
		




void Graphenerzeuger:: checksignal(){
	SchaltwerkElement* gatter;
	
	string pfad;
	string datei;
	cout <<"Pfad und Name der Schaltwerksdatei (ABBRUCH = 'EXIT')"<<endl<<endl;
	cin>>pfad;//! Schaltwerksdatei wird eingelesen und ueberprueft.
	cout<<pfad<<endl;
	ifstream in(pfad.c_str());

	if(in){
		datei = pfad;
		in.close();
		
	} 
	else{ 
		cout << "Die Bibliotheksdatei kann nicht geoeffnet werden"<<endl;
		 
	}
	in.close();
	

	int n = 0;
	for(ListenElement* at = startElement; at!=endElement; ++at,n++){//! Durchlaeuft alle Elemente
		gatter = at->getSchaltwerkElement() ;
		if(!(bibliothek->getBibElement(gatter->getName())->getEingaenge() == gatter->getAnzahlEingangssignale())){//! Detektion auf Fehler.
			cout <<"Es ist ein Fehler aufgetreten!"<<endl;
			cout <<"Anzahl Eingaenge laut Bibliothek: "<<bibliothek->getBibElement(gatter->getName())->getEingaenge()<<endl;
			cout <<"Anzahl Eingaenge laut Schaltwerk: "<<gatter->getAnzahlEingangssignale()<<endl;
		}

	}
}
ListenElement* Graphenerzeuger :: createGraph(){
  
	if( ((bibliothek != NULL)) && (signale != NULL) && (anzahlSignale != 0) ){ //! Sicherheitsabfrage ob alle Daten zur erzeugung vorliegen.
		
		if( startElement != NULL){
			destroyGraph(); //! Falls bereits ein Graph vorhanden ist im Speicher wird dieser ueber die destroy Methode zerstoert bevor der neue angelegt wird.
		} 

		createList();
		Signal* lauf = signale; //! Zeiger der die Signale durchlaeuft
		for( int a= 0; a<anzahlSignale ; lauf++, a++){ 
			//! Ueberprueft ob die Signale benutzt werden oder nicht.
			if(!((lauf->getAnzahlZiele() == 0) && (lauf->getQuelle() == "") && (lauf->getQuellenTyp() == "") )){ //! Die Eingangssignale werden hier erkannt und als solche in die Eingangselemente abgelegt.
				if( lauf->getSignalTyp() == eingang ){ 
					int anzahl = lauf->getAnzahlZiele(); 
					SchaltwerkElement* object; 
					for( int b = 0; b<anzahl; b++){ 
						object = searchListElement( lauf->getZiel(b)); 
						object->setIsEingangsElement(true); 
						object->EingangsSignalZaehlen(); //! zaehlt  die Eingangssignale hoch. 
					}
				}//! Ende der 1. if-Schleife
				 
				if( lauf->getSignalTyp() == ausgang){//! Die Ausgangssignale werden hier erkannt und als solche in die Ausgangselemente abgelegt.
					SchaltwerkElement* object;
					object = searchListElement( lauf->getQuelle());
					object->setIsAusgangsElement(true); 
				} //! Ende der 2. if-Schleife

				
				if(lauf->getSignalTyp() == intern){//! Hier werden die Internen Signale erkannt und die entsprechenden Elemente befuellt.

					int anzahl = lauf->getAnzahlZiele(); 
					SchaltwerkElement* quelle; //! Quellgatter
					SchaltwerkElement* ziel; //! Zielgatter				 
					quelle = searchListElement(lauf->getQuelle()); //! Sucht das Quellgatter in der liste der Namen. 
					for( int n = 0; n<anzahl; n++){ 
						ziel = searchListElement(lauf->getZiel(n)); //! findet n-te ziel des quellgatters
						ziel -> EingangsSignalZaehlen(); //! zaehlt das Eingangssignal hoch fuer das Zielgatters // muss ich noch ins Schaltwerk schreiben.
						quelle -> nachfolgerHinzufuegen(ziel,n); //! fuegt dem Quellgatter sein Zielgatter hinzu 
					} //! Ende der for-Schleife 
					quelle -> setAnzahlNachfolger(anzahl); 
				}  //! Ende der 3. if-Schleife
				if(lauf->getSignalTyp() == unbekannt){ 
					cout << " Es wurde ein unbekanntes Signal entdeckt" << endl; 
				} 
			}else{ 
				cout << " Das Signal s " << a+1 << " ist ein unbenutzes Signal. " << endl; 
				cout << " Ihr Graph wurde geloescht auf grund dieses Fehlers" << endl;
				destroyGraph();
				return NULL; } 
		}  //! Ende der for-Schleife
		 //! Ueberpruefung ob offene Eingaenge vorhanden sind
		 checksignal();
		return startElement; 
	}
	else{
		cout << "Der Graph konnte nicht erzeugt werden, da er keine Daten zur Bibliothek oder Signalliste gefunden hat." << endl;
	} 
	return NULL; //! Es wird ein Nullzeiger zurueckgegeben wenn kein Graph erzeugt werden konnte. 
}
void Graphenerzeuger :: outputGraph(){
	SchaltwerkElement* gatter;
	ListenElement* start =   startElement;
	ListenElement* end   =   endElement;
	cout <<"Graphenstruktur"<<endl<<endl;
	int n = 0;
	for(ListenElement* at = start; at!=end; ++at,n++){//! Durchlaeuft den Graph.
		 gatter = at->getSchaltwerkElement();
		cout <<"Gattername : "<<gatter->getName()<<endl;
		cout <<"Gattertyp : "<< gatter->getTyp()<<endl;
		cout <<"--> Das Gatter hat "<<gatter->getAnzahlNachfolger()<<"Ziel(e)"<<endl;
		cout <<"Angeschlossenen Gatter :"<<gatter->getNachfolger(n)->getName()<<endl<<endl<<endl;
	}//! Ausgabe des Graphen.


}
// ********************** METHODEN DEKLARATION END ********************

//***************************** END OF FILE *******************************************************

