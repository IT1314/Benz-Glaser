#include "Laufzeitanalyse.h"
#include "Graphenerzeuger.h"
#include "GatterTyp.h"
#include "Faktoren.h"
#include "Bibliothek.h"
#include "SignalListeErzeuger.h"
#include "SchaltwerkElement.h"
#include "ListenElement.h"
#include "Menu.h"
#include "stdafx.h"
#include <iostream>

using namespace std;



LaufzeitAnalyse::LaufzeitAnalyse()
{
	this->ausgangspfad = "";
	this->faktoren = NULL;
	this->frequenz = 0;
	this->laufzeitAusgangspfad = 0;
	this->laufzeitUebergangspfad = 0;
	this->startElement = NULL;
	this->uebergangspfad = "";
	this->anzahl_knoten = 0;
	this->setuptime = 0;
	this->maxi_frequenz = 0;
	this->t_setup = 0;
}
LaufzeitAnalyse::~LaufzeitAnalyse()
{
}



void LaufzeitAnalyse::berechne_einzelgatter_laufzeiten(Faktoren faktoren)
{
	ListenElement* erstes_element;
	double prozess_faktor = faktoren.get_prozess_faktor();
	double spannungs_faktor = faktoren.get_spannungs_faktor();
	double temperatur_faktor = faktoren.get_temperatur_faktor();
	double gesamt_auesserer_faktor = prozess_faktor*spannungs_faktor*temperatur_faktor;

	erstes_element = this->startElement;	
	static short gesamt_kapazitaet = 0;


	// Berechnet für alle Schaltwerke des Graphen die Einzelgatterlaufzeiten. Diese ergeben sich aus den jeweiligen Faktoren
	for (ListenElement* listeniterator = this->startElement; listeniterator != NULL; listeniterator = listeniterator->getNextElement())
	{
		this->anzahl_knoten ++;
		double laufzeit_einzelgatter = 0;
		SchaltwerkElement* schaltwerk_element;
		schaltwerk_element = listeniterator->getSchaltwerkElement();

		double grundlaufzeit = schaltwerk_element->getTyp()->getGrundlaufzeit();
		double lastfaktor = schaltwerk_element->getTyp()->getLastFaktor();
		double lastkapazitaet = 0;
		for (int counter = 0; counter < schaltwerk_element->getAnzahlNachfolger(); counter++)
		{
			lastkapazitaet += schaltwerk_element->getNachfolger(counter)->getTyp()->getLastKapazitaet();
		}
		laufzeit_einzelgatter = ((lastfaktor*lastkapazitaet)/1000+grundlaufzeit)*gesamt_auesserer_faktor;	//   /1000 wegen den Einheiten ;)

		listeniterator->getSchaltwerkElement()->setLaufzeitEinzelgatter(laufzeit_einzelgatter);
	}
}



void LaufzeitAnalyse::pruefe_startknoten()		//erstellt einen Vektor mit allen möglichen Startpunkten
{
	for (ListenElement* listeniterator = this->startElement; listeniterator != NULL; listeniterator = listeniterator->getNextElement())
	{	
		if  (listeniterator->getSchaltwerkElement()->getTyp()->getName() == "dff")		// checkt ob das Schaltwerk ein Flipflop ist
		{
			this->startknoten.push_back(listeniterator);
			setuptime = listeniterator->getSchaltwerkElement()->getLaufzeitEinzelgatter();
		}
		if(listeniterator->getSchaltwerkElement()->getIsEingangsElement() == 1)
		{
			this->startknoten.push_back(listeniterator);
		}
	}
}


void LaufzeitAnalyse::finde_max_laufzeit()		
{
	DFS_Daten daten;
	// erstellt eine Map mit Schaltwerkselementen als Index. Enthält die struct, die Informationen über Pfadlaufzeit und Vaterelement enthält
	for (ListenElement* listeniterator = this->startElement; listeniterator != NULL; listeniterator = listeniterator->getNextElement())
	{
		daten.VaterElement = NULL;														// Füllt die Map mit 0 bzw. NULL
		daten.PfadLaufzeit = 0;
		DFS_Zwischenspeicher[listeniterator->getSchaltwerkElement()] = daten;
	} 

	for (unsigned int counter = 0; counter < startknoten.size(); counter++)
	{	
		SchaltwerkElement* temp_schalt = startknoten[counter]->getSchaltwerkElement();
		bool success = this->DFS_Visit(temp_schalt,temp_schalt);
		if (success == 0)
		{
			cout << endl << "Es ist ein Fehler aufgetreten! Überprüfen Sie die Daten" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	

	this->maxi_frequenz = 1/((this->laufzeitUebergangspfad + this->t_setup)/1000000000000);

	cout << endl << endl;
	cout << "Laengster Pfad im Ueberfuehrungsschaltnetz:" << endl << this->uebergangspfad << endl;
	cout << "Maximale Laufzeit der Pfade im Ueberfuehrungsschaltnetz: " << this->laufzeitUebergangspfad << " ps" << endl << endl;
	cout << "Laengster Pfad im Ausgangsschaltnetz:" << endl << this->ausgangspfad << endl;
	cout << "Maximale Laufzeit der Pfade im Ausgangsschaltnetz: " << this->laufzeitAusgangspfad << " ps" << endl << endl;
	cout << "------------------------------------------------" << endl << endl;
	cout << "Die maximal zulaessige Frequenz fuer das Schaltnetz/-werk betraegt: " << long(maxi_frequenz/1000000) << " MHz" <<  endl << endl;
	if (this->frequenz > this->maxi_frequenz)
	{
		cout << "Bedingung fuer die Taktfrequenz vom Schaltnetz/-werk ist nicht erfuellt!" << endl;
		cout << "die Taktfrequenz " << this->frequenz/1000000 << " MHz ist groesser als die maximale Frequenz!" << endl << endl;
	}
	else
	{
		cout << "Bedingung fuer die Taktfrequenz vom Schaltnetz/-werk ist erfuellt!" << endl;
		cout << "die Taktfrequenz " << this->frequenz/1000000 << " MHz ist kleiner als die maximale Frequenz!" << endl << endl;
	}
	system("pause");

}


bool LaufzeitAnalyse::DFS_Visit(SchaltwerkElement* temp_knoten, SchaltwerkElement* start_knoten)
{
	for(int counter = 0; counter < temp_knoten->getAnzahlNachfolger(); counter++)		//Z.19
	{
		SchaltwerkElement* folge_knoten = temp_knoten->getNachfolger(counter);
		if (folge_knoten->getTyp()->getName() == "dff")						//falls Nachfolger x = Flipflop... Z.20
		{
			if(this->laufzeitUebergangspfad < temp_knoten->getLaufzeitEinzelgatter() + DFS_Zwischenspeicher[temp_knoten].PfadLaufzeit)	//Z.21
			{
				//if (this->t_setup == 0)
				//{  // Speichern von t_setup für erstes Flipflop
					this->t_setup = (( Flipflop* ) ( folge_knoten->getTyp()))->getSetupTime();
				//}
				this->uebergangspfad = folge_knoten->getName();
				this->laufzeitUebergangspfad = temp_knoten->getLaufzeitEinzelgatter() + DFS_Zwischenspeicher[temp_knoten].PfadLaufzeit;	//Z.22
				for (SchaltwerkElement* temp = temp_knoten; temp != NULL; temp = DFS_Zwischenspeicher[temp].VaterElement)
				{
					// string zusammenbasteln
					this->uebergangspfad += "-->" + temp->getName();		//Z.23
				}	
			}
		}															//Z.24
		else if(DFS_Zwischenspeicher[folge_knoten].PfadLaufzeit < DFS_Zwischenspeicher[temp_knoten].PfadLaufzeit + temp_knoten->getLaufzeitEinzelgatter())
		{
			if(((DFS_Zwischenspeicher[folge_knoten].PfadLaufzeit != 0) || (folge_knoten == temp_knoten)) && DFS_Zwischenspeicher[folge_knoten].VaterElement != temp_knoten)
			{
				DFS_Zwischenspeicher[folge_knoten].VaterElement = temp_knoten;
				
//***************************************************** Zyklensuche ***********************************************************************************		
				for(SchaltwerkElement* zyklus_knoten = temp_knoten; zyklus_knoten != NULL; zyklus_knoten = DFS_Zwischenspeicher[zyklus_knoten].VaterElement)
				{
					if (zyklus_knoten == folge_knoten)
					{
						cout << "Zyklus wurde entdeckt! Bitte überprüfen Sie Ihr Schaltnetz/Schaltwerk" << endl << endl;
						return 0;
					}

				}
			}
			DFS_Zwischenspeicher[folge_knoten].PfadLaufzeit = DFS_Zwischenspeicher[temp_knoten].PfadLaufzeit + temp_knoten->getLaufzeitEinzelgatter();
			DFS_Zwischenspeicher[folge_knoten].VaterElement = temp_knoten;
			DFS_Visit(folge_knoten, start_knoten);
		}
	}
	if ((temp_knoten->getIsAusgangsElement()) && (this->laufzeitAusgangspfad < DFS_Zwischenspeicher[temp_knoten].PfadLaufzeit + temp_knoten->getLaufzeitEinzelgatter())) 
	{
		this->laufzeitAusgangspfad = DFS_Zwischenspeicher[temp_knoten].PfadLaufzeit + temp_knoten->getLaufzeitEinzelgatter();
		//************************************HIER NOCH DEN STRING ERSTELLEN*********************************************** 

		// String zusammenbasteln
		this->ausgangspfad = "";
		for(SchaltwerkElement* tempi_schalt = temp_knoten; tempi_schalt != NULL; tempi_schalt = DFS_Zwischenspeicher[tempi_schalt].VaterElement)
		{
			this->ausgangspfad += tempi_schalt->getName() + "-->";
		}
	}
	return 1;
}


void LaufzeitAnalyse::laufzeit_analyse(ListenElement* erstes_element,Faktoren* faktor, long frequenz)
{
	this->faktoren = faktor;
	this->frequenz = frequenz;
	this->startElement = erstes_element;
	berechne_einzelgatter_laufzeiten(*faktoren);
	pruefe_startknoten();
	finde_max_laufzeit();

}



