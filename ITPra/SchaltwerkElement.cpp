#include"SchaltwerkElement.h"
#include <string>
#include "Bibliothek.h"

using namespace std;
	
		
SchaltwerkElement::SchaltwerkElement(GatterTyp* gTyp){

	name=(*gTyp).getName();		
	laufzeitEinzelgatter;
	anzahlNachfolger;
	isEingangsElement;
	isAusgangsElement;
	anzahlEingangssignale=(*gTyp).getEingaenge();
	
	typ=gTyp;
	vector <SchaltwerkElement*> nachfolgerElemente;
		
}
SchaltwerkElement::~SchaltwerkElement(void){
}


SchaltwerkElement* SchaltwerkElement::getNachfolger(int pos){
	
	//funktion mit der pos hinzfügen
	return nachfolgerElemente[pos];//! liefert direkt den wert tipp vom tutor

}
GatterTyp* SchaltwerkElement::getTyp(){	
	//typ welches im konstruktor übergeben wird 
	return typ;
}


string SchaltwerkElement::getName(){
	return name; 
} 
double SchaltwerkElement::getLaufzeitEinzelgatter(){
	return laufzeitEinzelgatter;
}
int SchaltwerkElement::getAnzahlNachfolger(){
	return anzahlNachfolger;
}
short SchaltwerkElement::getAnzahlEingangssignale(){
	return anzahlEingangssignale;
}
bool SchaltwerkElement::getIsEingangsElement(){	
	return isEingangsElement;
}
bool SchaltwerkElement::getIsAusgagsElement(){
	return isAusgangsElement;
}

void SchaltwerkElement::nachfolgerHinzufuegen(SchaltwerkElement* schaltwerkElement, int pos){
	nachfolgerElemente.emplace ( nachfolgerElemente.begin()+pos, schaltwerkElement );

	//Element wird in vector eingefuegt
}

void SchaltwerkElement:: EingangsSignalZaehlen(){
	anzahlEingangssignale ++;
}

void SchaltwerkElement::setName(string n){	
	name=n;
}
void SchaltwerkElement::setAnzahlNachfolger(int anzahlN){
	anzahlNachfolger=anzahlN;
}
void SchaltwerkElement::setAnzahlEingangssignale(short anzahlE){	
	anzahlEingangssignale=anzahlE;
}
void SchaltwerkElement::setIsEingangsElement(bool isEingangsEl){
	isEingangsElement=isEingangsEl;
}	
void SchaltwerkElement::setIsAusgangsElement(bool isAusgangsEl){
	isAusgangsElement=isAusgangsEl;
}
void SchaltwerkElement::setLaufzeitEinzelgatter(double lfz){	
	laufzeitEinzelgatter=lfz;
}
int SchaltwerkElement::getnachfolgerElementesize(){
	return nachfolgerElemente.size();
}