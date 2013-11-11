#ifndef GATTERTYP_H
#define GATTERTYP_H

#include <string>

using namespace std;
//! \brief class GatterTyp
//!  enthaelt die Grundlegenden Funktionen und Grundwerte der Gatter
class GatterTyp{
protected:

	string name;
	double grundLaufzeit;
	short lastFaktor;
	short lastKapazitaet;
	short eingaenge;

public:

	GatterTyp();
	 ~GatterTyp();
	string getName(){ return name;}
	double getGrundlaufzeit(){ return grundLaufzeit;}
	short getLastFaktor(){return lastFaktor}
	short getLastKapazitaet(){return lastKapazitaet;}
	short getEingaege() {return eingaenge;}
	bool getIsFlipflop(){return false ;}//?
	void setName(string n){name = n;}
	void setGrundLaufzeit(double gl){grundLaufzeit = gl;}
	void setLastFaktor(short lf){lastFaktor = fl;}
	void setLastKapazitaet(short lk){lastKapazitaet = lk;}
	void setEingaenge(short ei){eingaenge = ei;}
	
	
};

#endif