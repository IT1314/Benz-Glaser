#include"SchaltwerkElement.h"
#include <string>
using namespace std;
	
SchaltwerkElement schaltwerkElementKlasse;
		
SchaltwerkElement::SchaltwerkElement(GatterTyp gTyp){
	
	schaltwerkElementKlasse.name="";		
	schaltwerkElementKlasse.laufzeitEinzelgatter=0.0;
	schaltwerkElementKlasse.anzahlNachfolger=0;
	schaltwerkElementKlasse.isEingangsElement=0;
	schaltwerkElementKlasse.isAusgangsElement=0;
	schaltwerkElementKlasse.anzahlEingangssignale=0;
	
		schaltwerkElementKlasse.typ=NULL;
		schaltwerkElementKlasse.nachfolgerElemente=NULL;
		
}
SchaltwerkElement::~SchaltwerkElement(void){
}


SchaltwerkElement* SchaltwerkElement::getNachfolger(int pos){

}
SchaltwerkElement::getTyp(){	

}


string SchaltwerkElement::getName(){
	return schaltwerkElementKlasse.name; 
} 
double SchaltwerkElement::getLaufzeitEinzelgatter(){
	return schaltwerkElementKlasse.laufzeitEinzelgatter;
}
int SchaltwerkElement::getAnzahlNachfolger(){
	return schaltwerkElementKlasse.anzahlNachfolger;
}
short SchaltwerkElement::getAnzahlEingangssignale(){
	return schaltwerkElementKlasse.anzahlEingangssignale;
}
bool SchaltwerkElement::getIsEingangsElement(){	
	return schaltwerkElementKlasse.isEingangsElement;
}
bool SchaltwerkElement::getIsAusgagsElement(){
	return schaltwerkElementKlasse.isAusgangsElement;
}




void SchaltwerkElement::nachfolgerHinzufügen(SchaltwerkElement schaltwerkElement, int pos){	

}



void SchaltwerkElement::setName(string n){	
	schaltwerkElementKlasse.name=n;
}
void SchaltwerkElement::setAnzahlNachfolger(int anzahlN){
	schaltwerkElementKlasse.anzahlNachfolger=anzahlN;
}
void SchaltwerkElement::setAnzahlEingangssignale(short anzahlE){	
	schaltwerkElementKlasse.anzahlEingangssignale=anzahlE;
}
void SchaltwerkElement::setIsEingangsElement(bool isEingangsEl){
	schaltwerkElementKlasse.isEingangsElement=isEingangsEl;
}	
void SchaltwerkElement::setIsAusgangsElement(bool isAusgangsEl){
	schaltwerkElementKlasse.isAusgangsElement=isAusgangsEl;
}
void SchaltwerkElement::setLaufzeitEinzelgatter(double lfz){	
	schaltwerkElementKlasse.laufzeitEinzelgatter=lfz;
}
