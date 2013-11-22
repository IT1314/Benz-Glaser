


#include "stdafx.h"
#include "Signal.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



Signal::Signal()
{
	this->signalTyp = unbekannt;
	this->quelle = "";
	this->quellenTyp = "";
	this->anzahlZiele = 0;
	this->frequenz = 0;
}

Signal::~Signal() {}


int Signal::getAnzahlZiele() { return this->anzahlZiele;}

string Signal::getZiel(int pos) {return this->ziele[pos];}

signalTypen Signal::getSignalTyp() {return this->signalTyp;}

string Signal::getQuelle() {return this->quelle;}

string Signal::getQuellenTyp() {return this->quellenTyp;}

string Signal::getName() {return this->name;}

void Signal::setName(string name) {this->name = name;}

void Signal::setAnzahlZiele (int nZiele) {this->anzahlZiele = nZiele;}

void Signal::setSignalTyp(signalTypen sigTyp) {this->signalTyp = sigTyp;}

void Signal::setQuelle(string gatterName) {this->quelle = gatterName;}

void Signal::setQuellenTyp(string gatterTyp) {this->quellenTyp = gatterTyp;}

void Signal::zielHinzufuegen(string gatterName, int pos) {this->ziele[pos] = gatterName;}

