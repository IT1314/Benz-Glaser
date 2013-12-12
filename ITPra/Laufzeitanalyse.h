#ifndef LAUFZEITANALYSE
#define LAUFZEITANALYSE

#include "GatterTyp.h"
#include "Faktoren.h"
#include "Graphenerzeuger.h"
#include <map>

class LaufzeitAnalyse
{
private:
	Faktoren* faktoren;
	ListenElement* startElement;
	long frequenz;
	double setuptime;
	string uebergangspfad;
	string ausgangspfad;
	double laufzeitUebergangspfad;
	double laufzeitAusgangspfad;
	struct DFS_Daten {SchaltwerkElement* VaterElement; double PfadLaufzeit;};
	map <SchaltwerkElement*, DFS_Daten> DFS_Zwischenspeicher;
	vector<ListenElement*> startknoten;
	short anzahl_knoten;
	bool analyse_status;
	double maxi_frequenz;
	double t_setup;



public:
	 LaufzeitAnalyse();
	 ~LaufzeitAnalyse();
	void berechne_einzelgatter_laufzeiten(Faktoren faktoren);
	void laufzeit_analyse(ListenElement* erstes_element,Faktoren* faktor, long frequenz);
	void pruefe_startknoten();
	void finde_max_laufzeit();		// Tiefensuchalgorithmus
	bool DFS_Visit(SchaltwerkElement* k, SchaltwerkElement* s);
};




#endif // !LAUFZEITANALYSE
