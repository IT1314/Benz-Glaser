#ifndef GATTERTYP_H
#define GATTERTYP_H
//***************** INCLUDE FILES ******************************
#include <string>

using namespace std;
//***************** INCLUDE FILES END **************************

//! \brief class GatterTyp
//!  enthaelt die Grundlegenden Funktionen und Grundwerte der Gatter
class GatterTyp{
protected:
	// ########## Attribute #############	
	string name;
	double grundLaufzeit;
	short lastFaktor;
	short lastKapazitaet;
	short eingaenge;
	// ########## Attribute end #############	
public:

	// ######### Methoden ##############
	GatterTyp(){};
	~GatterTyp(){};
	string getName(){ return name;}
	double getGrundlaufzeit(){ return grundLaufzeit;}
	short getLastFaktor(){return lastFaktor;}
	short getLastKapazitaet(){return lastKapazitaet;}
	short getEingaenge() {return eingaenge;}
	bool getIsFlipflop(){return false ;}//?
	void setName(string n){name = n;}
	void setGrundLaufzeit(double gl){grundLaufzeit = gl;}
	void setLastFaktor(short lf){lastFaktor = lf;}
	void setLastKapazitaet(short lk){lastKapazitaet = lk;}
	void setEingaenge(short ei){eingaenge = ei;}
	
	// ######### Methoden end ##############
};

#endif //GATTERTYP_H