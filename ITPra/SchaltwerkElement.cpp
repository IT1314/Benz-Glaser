#include"SchaltwerkElement.h"
#include <string>
using namespace std;
	
		
SchaltwerkElement::SchaltwerkElement(GatterTyp* gTyp){

	SchaltwerkElement::name="";		
	SchaltwerkElement::laufzeitEinzelgatter=0.0;
	SchaltwerkElement::anzahlNachfolger=0;
	SchaltwerkElement::isEingangsElement=0;
	SchaltwerkElement::isAusgangsElement=0;
	SchaltwerkElement::anzahlEingangssignale=0;
	
	SchaltwerkElement::typ=gTyp;
	SchaltwerkElement::nachfolgerElemente=NULL;
		
}
SchaltwerkElement::~SchaltwerkElement(void){
}


SchaltwerkElement* SchaltwerkElement::getNachfolger(int pos){
	//funktion mit der pos hinzfügen
	return SchaltwerkElement::nachfolgerElemente;

}
GatterTyp* SchaltwerkElement::getTyp(){	
	//typ welches im konstruktor übergeben wird richtig?
	return SchaltwerkElement::typ;
}


string SchaltwerkElement::getName(){
	return SchaltwerkElement::name; 
} 
double SchaltwerkElement::getLaufzeitEinzelgatter(){
	return SchaltwerkElement::laufzeitEinzelgatter;
}
int SchaltwerkElement::getAnzahlNachfolger(){
	return SchaltwerkElement::anzahlNachfolger;
}
short SchaltwerkElement::getAnzahlEingangssignale(){
	return SchaltwerkElement::anzahlEingangssignale;
}
bool SchaltwerkElement::getIsEingangsElement(){	
	return SchaltwerkElement::isEingangsElement;
}
bool SchaltwerkElement::getIsAusgagsElement(){
	return SchaltwerkElement::isAusgangsElement;
}




void SchaltwerkElement::nachfolgerHinzufügen(SchaltwerkElement* schaltwerkElement, int pos){
	//dynamisches array für anzahl der gatter erzeugen ?
	SchaltwerkElement::nachfolgerElemente=schaltwerkElement;

}



void SchaltwerkElement::setName(string n){	
	SchaltwerkElement::name=n;
}
void SchaltwerkElement::setAnzahlNachfolger(int anzahlN){
	SchaltwerkElement::anzahlNachfolger=anzahlN;
}
void SchaltwerkElement::setAnzahlEingangssignale(short anzahlE){	
	SchaltwerkElement::anzahlEingangssignale=anzahlE;
}
void SchaltwerkElement::setIsEingangsElement(bool isEingangsEl){
	SchaltwerkElement::isEingangsElement=isEingangsEl;
}	
void SchaltwerkElement::setIsAusgangsElement(bool isAusgangsEl){
	SchaltwerkElement::isAusgangsElement=isAusgangsEl;
}
void SchaltwerkElement::setLaufzeitEinzelgatter(double lfz){	
	SchaltwerkElement::laufzeitEinzelgatter=lfz;
}
