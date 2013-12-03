


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
			GatterTyp* typus = bibliothek->getBibElement(Signale.at(a).getQuellenTyp()); //! Ermittelt den Gattertyp mittels der Bibliothek.			 
			SchaltwerkElement* object2 = new SchaltwerkElement(typus);
			object2->setName(Signale.at(a).getQuelle()); //! set Methoden werden aufgerufen
			uebergabe->setSchaltwerkElement(object2); 
			uebergabe->setNextElement(NULL); 
			createListElement(uebergabe);
			
		
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
    ListenElement *help1 = new ListenElement;
	ListenElement *help2= new ListenElement;
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
	ListenElement* start =   startElement;
	while( start != 0 ) {
		if(start->getSchaltwerkElement()->getName() == gattername)
			return start->getSchaltwerkElement();
		start = start->getNextElement();
	}
	return 0;
}
		




void Graphenerzeuger:: checksignal(){
	SchaltwerkElement* gatter;
	ListenElement* at = startElement;
	string pfad;
	string datei;
	cout <<"Pfad und Name der Schaltwerksdatei (ABBRUCH = 'EXIT')"<<endl<<endl;
	cin>>pfad;//! Schaltwerksdatei wird eingelesen und ueberprueft.
	cout<<pfad<<endl;
	
	

	ifstream in(pfad.c_str());
	if(in){
		
		in.close();
		
	} 
	else{ 
		cout << "Die Schaltwerksdatei kann nicht geoeffnet werden"<<endl;
		 
	}
	in.close();

		ifstream in1(datei.c_str());
		if(in1){
			datei = bibliothek->getPfad();
			in1.close();
		
		} 
		else{ 
			cout << "Die Bibliotheksdatei kann nicht geoeffnet werden"<<endl;
		 
		}
		in1.close();
	gatter = at->getSchaltwerkElement() ;
		while(at != 0){
			
			if(!(bibliothek->getBibElement(gatter->getName())->getEingaenge() == gatter->getAnzahlEingangssignale())){//! Detektion auf Fehler.
			cout <<"Es ist ein Fehler aufgetreten!"<<endl;
			cout <<"Anzahl Eingaenge laut Bibliothek: "<<bibliothek->getBibElement(gatter->getName())->getEingaenge()<<endl;
			cout <<"Anzahl Eingaenge laut Schaltwerk: "<<gatter->getAnzahlEingangssignale()<<endl;
		    }
			at = at->getNextElement();
		}
		

	
}
ListenElement* Graphenerzeuger :: createGraph(){
  
	if( ((bibliothek != NULL)) && (!Signale.empty()) ){ //! Sicherheitsabfrage ob alle Daten zur erzeugung vorliegen.
		
		if( startElement != NULL){
			destroyGraph(); //! Falls bereits ein Graph vorhanden ist im Speicher wird dieser ueber die destroy Methode zerstoert bevor der neue angelegt wird.
		} 
		
		createList();
		int a = 0;

 
			//! Ueberprueft ob die Signale benutzt werden oder nicht.
		
		auto it = Signale.begin();

		
			while( it  != Signale.end()){
			
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
				destroyGraph();
				return NULL; } 
			it ++;
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
	ListenElement* at = start;
	ListenElement* end   =   endElement;
	cout <<"Graphenstruktur"<<endl<<endl;
	int n = 0;
	while(at!=0){//! Durchlaeuft den Graph.
	
		 gatter = at->getSchaltwerkElement();
		cout <<"Gattername : "<<gatter->getName()<<endl;
		cout <<"Gattertyp : "<< gatter->getTyp()<<endl;
		cout <<"--> Das Gatter hat "<<gatter->getAnzahlNachfolger()<<"Ziel(e)"<<endl;
		cout <<"Angeschlossenen Gatter :"<<gatter->getNachfolger(n)->getName()<<endl<<endl<<endl;
		at = at->getNextElement();

	}//! Ausgabe des Graphen.


}
// ********************** METHODEN DEKLARATION END ********************

//***************************** END OF FILE *******************************************************

