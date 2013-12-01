#include "Laufzeitanalyse.h"
#include "Graphenerzeuger.h"
#include "GatterTyp.h"
#include "Faktoren.h"

using namespace std;
/*
Graphenerzeuger meinGraphenerzeuger(Bibliothek* bib,SignalListeErzeuger* signalliste);

void LaufzeitAnalyse::berechne_einzelgatter_laufzeiten(Faktoren faktoren)
{
	ListenElement* erstes_element;
	SchaltwerkElement* schaltwerk_element;
	double prozess_faktor = faktoren.get_prozess_faktor();
	double spannungs_faktor = faktoren.get_spannungs_faktor();
	double temperatur_faktor = faktoren.get_temperatur_faktor();
	double gesamt_auesserer_faktor = prozess_faktor*spannungs_faktor*temperatur_faktor;


	schaltwerk_element = erstes_element->getSchaltwerkElement;
	short lastfaktor = schaltwerk_element->getTyp()->getLastFaktor();
	short lastkapazitaet = schaltwerk_element->getTyp()->getLastKapazitaet();
	double grundlaufzeit = schaltwerk_element->getLaufzeitEinzelgatter();

	for (ListenElement* listeniterator = meinGraphenerzeuger.getStartElement(); listeniterator != NULL; listeniterator = listeniterator->getNextElement())
	{
		static short gesamt_kapazitaet = 0;

		double laufzeit_einzelgatter = listeniterator->getSchaltwerkElement()->getLaufzeitEinzelgatter();
		short last_faktor = listeniterator->getSchaltwerkElement()->getTyp()->getLastFaktor();
		gesamt_kapazitaet += listeniterator->getSchaltwerkElement()->getTyp()->getLastKapazitaet();

		double gesamtlaufzeit = laufzeit_einzelgatter + last_faktor*gesamt_kapazitaet;
		gesamtlaufzeit *= gesamt_auesserer_faktor;

		listeniterator->getSchaltwerkElement()->setLaufzeitEinzelgatter(gesamtlaufzeit);
	}

}*/