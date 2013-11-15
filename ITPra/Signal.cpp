


#include "stdafx.h"
#include "Signal.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



Signal::Signal()
{
	this->signalTyp = unbekannt;
	/*
	this->quelle = NULL;
	this->quellenTyp = 0;
	this->ziele[5] = NULL;
	*/
	this->anzahlZiele = 0;
}

Signal::~Signal() {}

int Signal::getAnzahlZiele() { return this->anzahlZiele;}

string Signal::getZiel(int pos) {return this->ziele[pos];}

signalTypen Signal::getSignalTyp() {return this->signalTyp;}

string Signal::getQuelle() {return this->quelle;}

string Signal::getQuellenTyp() {return this->quellenTyp;}

void Signal::setAnzahlZiele (int nZiele) {this->anzahlZiele = nZiele;}

void Signal::setSignalTyp(signalTypen sigTyp) {this->signalTyp = sigTyp;}

void Signal::setQuelle(string gatterName) {this->quelle = gatterName;}

void Signal::setQuellenTyp(string gatterTyp) {this->quellenTyp = gatterTyp;}

void Signal::zielHinzufuegen(string gatterName, int pos) {this->ziele[pos] = gatterName;}

