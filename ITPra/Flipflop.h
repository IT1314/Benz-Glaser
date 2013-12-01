#ifndef FLIPFLOP_H
#define FLIPFLOP_H
//***************** INCLUDE FILES ******************************
#include"GatterTyp.h"
//***************** INCLUDE FILES END **************************

//! \brief class Flipflop
//!  erweitert die Klasse GatterTyp um die Flipflops.
class Flipflop : public GatterTyp{
private:
	// ########## Attribute  #############	
	short setupTime;
	short holdTime;
	short lastKapazitaetClock;
	// ########## Attribute end #############	

public:
	// ######### Methoden ##############
	Flipflop(){};
	virtual~ Flipflop(){};
	virtual  bool getIsFlipflop(){return true;}
	short getSetupTime(){return setupTime;}
	short getHoldTime(){ return holdTime;}
	short getLastKapazitaetClock(){return lastKapazitaetClock;}
	void setSetupTime( short st){ setupTime = st;}
	void setHoldTime(short ht) { holdTime = ht;}
	void setlastKapazitaetClock( short lkc) { lastKapazitaetClock = lkc;}
	// ######### Methoden end ##############
};

#endif //FLIPFLOP_H