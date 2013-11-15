#ifndef FLIPFLOP_H
#define FLIPFLOP_H

#include"GatterTyp.h"
//! \brief class Flipflop
//!  erweitert die Klasse GatterTyp um die Flipflops.
class Flipflop : public GatterTyp{
private:

	short setupTime;
	short holdTime;
	short lastKapazitaetClock;

public:

	Flipflop();
	virtual~ Flipflop();
	virtual  bool getIsFlipflop(){return true;}
	short getSetupTime(){return setupTime;}
	short getHoldTime(){ return holdTime;}
	short getLastKapazitaetClock(){return lastKapazitaetClock;}
	void setSetupTime( short st){ setupTime = st;}
	void setHoldTime(short ht) { holdTime = ht;}
	void setLastKapazitaetClock( short lkc) { lastKapazitaetClock = lkc;}
		
};

#endif