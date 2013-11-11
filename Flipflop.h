#ifndef FLIPFLOP_H
#define FLIPFLOP_H

#include"GatterTyp.h"

class Flipflop : public GatterTyp{
private:

	short setupTime;
	short holdTime;
	short lastKapazitaetClock;

public:

	Flipflop() : GatterTyp();
	virtual~ Flipflop();
	bool getIsFlipflop(){return true;}
	short getSetupTime(){return setupTime;}
	short getHoldTime(){ return holdTime;}
	short getLastKapazitaetClock(){return lastKapazitaetClock;}
	void setSetupTime( short st){ setupTime = st;}
	void setHoldTime(short ht) { holdTime = ht;}
	void lastKapazitaetClock( short lkc) { lastKapazitaetClock = lkc;}
		
};

#endif