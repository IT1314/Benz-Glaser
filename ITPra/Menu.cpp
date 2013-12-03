
// Menu.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

//***************** INCLUDE FILES ******************************
//#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>
#include "Menu.h"
#include "Faktoren.h"
#include "SignalListeErzeuger.h"
#include "Graphenerzeuger.h"
#include "Bibliothek.h"
#include "SchaltwerkElement.h"
#include "main.h"
using namespace std;
//***************** INCLUDE FILES END **************************



//***************** MODUL GLOBAL VARIABLES *********************
Menu meinMenu;
Faktoren meineFaktoren;
Bibliothek meineBibliothek("..\bib2.txt");
SignalListeErzeuger meinSignalListeErzeuger;

	double spannung_untermenue = 0;
	double temperatur_untermenue = 0;
	double prozess_untermenue = 0;
	string schaltnetzdatei_pfad;
	bool guterpfad = 0;
	bool guter_bibliotheks_pfad = 0;
//***************** MODUL GLOBAL VARIABLES END *****************



//***************** FUNCTIONS AND METHODS DECLARATIONS *********
Menu::Menu(void) 
{
//**** FUNKTIONSAUFGABE: Konstruktor, erzeugt die Objekte meine Faktoren, meine Bibliothek, meine SignalListeErzeuger, meinGraphErzeuger und meinLaufzeitAnalysator
/*
	Faktoren meineFaktoren;
	Bibliothek meineBibliothek;
	SignalListeErzeuger meinSignalListeErzeuger;
	GraphErzeuger meinGraphErzeuger;
	LaufzeitAnalysator meinLaufzeitAnalysator;
*/
}

Menu::~Menu(void) 
{
	// DESTRUCOR wird nicht verwendet

}


void Menu::faktorenMenue()
{

//**** FUNKTIONSAUFGABE: schreibt das Untermenü "Aeussere Faktoren" in die Konsole und navigiert dieses.
	while(1)
	{
		system("cls");
		meinMenu.menueKopf();
		cout << "Untermenue Aeussere Faktoren " << endl;
		cout << "(1) Spannung [Volt]: "; if(spannung_untermenue != NULL) { cout << spannung_untermenue;} cout << endl;
		cout << "(2) Temperatur [Grad Celsius]: "; if(temperatur_untermenue != NULL) { cout << temperatur_untermenue;} cout << endl;
		cout << "(3) Prozess (1=slow, 2=typical, 3=fast): "; if(prozess_untermenue != NULL) { cout << prozess_untermenue;} cout << endl;
		cout << "(4) Ausgabe errechneter Faktoren" << endl;
		cout << "(5) Hauptmenue:" << endl << endl << endl;
		cout << "Waehle einen Menuepunkt und bestaetige mit Enter: " << endl;
		string faktor_menue_eingabe;
		cin >> faktor_menue_eingabe;
		unsigned int faktor_menue_status = atoi(faktor_menue_eingabe.c_str());
		bool success_spannung = 0;
		bool success_temperatur = 0;
		bool success_prozess = 0;
		string spannungs_eingabe;
		string temperatur_eingabe;
		string prozess_eingabe;
		switch (faktor_menue_status)
		{
			case SPANNUNG:
				system("cls");
				cout << "Bitte Spannung eingeben: ";
				cin >> spannungs_eingabe;
				system("cls");
				success_spannung = meineFaktoren.berechneSpannungFaktor(atof(spannungs_eingabe.c_str()));
				if (success_spannung == 1)
				{
					spannung_untermenue = atof(spannungs_eingabe.c_str());
				}
				if (success_spannung == 0)
				{
					spannung_untermenue = 0;
				}
				break;

			case TEMPERATUR:
				system("cls");
				cout << "Bitte Temperatur eingeben: ";
				cin >> temperatur_eingabe;
				system("cls");
				success_temperatur = meineFaktoren.berechneTemperaturFaktor(atof(temperatur_eingabe.c_str()));
				if (success_temperatur == 1)
				{
					temperatur_untermenue = atof(temperatur_eingabe.c_str());
				}
				if (success_temperatur == 0)
				{
					temperatur_untermenue = 0;
				}
				break;

			case PROZESS:
				system("cls");
				cout << "Bitte Prozessgeschwindigkeit eingeben: ";
				cin >> prozess_eingabe;
				system("cls");
				success_prozess = meineFaktoren.berechneProzessFaktor(short(atof(prozess_eingabe.c_str()))); // input wird zu short gecastet um Schnittstelle anzupassen
				if (success_prozess == 1)
				{
					prozess_untermenue = atof(prozess_eingabe.c_str());
				}
				if (success_prozess == 0)
				{
					prozess_untermenue = 0;
				}
				break;

			case AUSGABE_ERRECHNETER_FAKTOREN:
				meineFaktoren.ausgabeFaktoren();
				break;

			case HAUPTMENUE:
				system("cls");
				return;
				break;

			default:
				break;
		}
	}
}

void Menu::bibliothekMenue()
{
//**** FUNKTIONSAUFGABE: schreibt das Untermenü "Bibliothek" in die Konsole und navigiert dieses.
	while (1)
	{
		system("cls");
		menueKopf();
		cout << "Untermenue Bibliothek" << endl;
		cout << "(1) Pfad zur Bibliotheksdatei: "; if(guter_bibliotheks_pfad == 1) { cout << meineBibliothek.getPfad();} cout << endl;
		cout << "(2) Ausgabe der Bibliotheksdatei" << endl;
		cout << "(3) Hauptmenue" << endl << endl;
		cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";
		unsigned int zustand = 0;
		string eingabe;
		string pfad_eingabe;
		cin >> eingabe;
		zustand = atoi(eingabe.c_str());
		switch (zustand)
		{
			case BIBLIOTHEKSPFAD:
				system("cls");
				cout << "Bitte geben Sie den Pfad zur Bibliotheksdatei ein: " << endl;
				cin >> pfad_eingabe;
				guter_bibliotheks_pfad = meineBibliothek.pfadEinlesen(pfad_eingabe);

				break;
			case BIBLIOTHEKSDATEI_AUSGABE:
				meineBibliothek.dateiAuswerten();
				meineBibliothek.dateiAusgabe();
				system("pause");
				break;
			case HAUPTMENUE_BIBLIOTHEK:
				system("cls");
				return;
			default:
				break;
		}
	}
	meineBibliothek.dateiAuswerten();
}







void Menu::schaltwerkMenue()
{
//**** FUNKTIONSAUFGABE: schreibt das Untermenü "Schaltwerk" in die Konsole und navigiert dieses.
	while(1)
	{
		system("cls");
		meinMenu.menueKopf();
		cout << "Untermenue Schaltwerk" << endl;
		cout << "(1) Pfad zur Schaltnetzdatei: "; if (guterpfad == 1) {cout << schaltnetzdatei_pfad;} cout << endl;
		cout << "(2) Ausgabe der Schaltnetzdatei" << endl;
		cout << "(3) Ausgabe der Signale" << endl;
		cout << "(4) Ausgabe der Graphstruktur" << endl;
		cout << "(5) Hauptmenue" << endl << endl;
		cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";
		meineBibliothek.dateiAuswerten();
		Graphenerzeuger Graph (&meineBibliothek,meinSignalListeErzeuger.signalliste);
		unsigned int zustand = 0;
		string eingabe;
		cin >> eingabe;
		zustand = atoi(eingabe.c_str());
		switch (zustand)
		{
			case PFAD:
				schaltnetzdatei_pfad = meinSignalListeErzeuger.enter_pfad(&guterpfad);
				break;
			case AUSGABE_SCHALTNETZDATEI:
				if (guterpfad == 1){meinSignalListeErzeuger.Ausgabe_Schaltnetzdatei(schaltnetzdatei_pfad);}
				system("PAUSE");
				break;
			case AUSGABE_SIGNALE_MENU:
				if (guterpfad == 1 ) 
				{
					meinSignalListeErzeuger.Ausgabe_Signale(schaltnetzdatei_pfad);
				}
				system("pause");
				break;
			case AUSGABE_GRAPHSTRUKTUR:
				
				
				Graph.createGraph();
				Graph.outputGraph();
				system("pause");
				break;
			case HAUPTMENUE:
				system("cls");
				return;
			default:
				break;
		}
					
	}
}

void Menu::analyse()
{
//**** FUNKTIONSAUFGABE: Enthält alle Funktionen/Methoden für die Analyse

	system("cls");
	cout << "ANALYSE" << endl << endl << endl;	//Der ganze Block wird durch das Analyse Modul ersetzt!!!
	system("pause");
	system("cls");

	
}

void Menu::menueKopf()
{
//**** FUNKTIONSAUFGABE: Gibt den Menuekopf auf dem Bildschirm aus

	cout << "*******************************************" << endl;
	cout << "*     IT_Projektpraktikum WS2013/2014     *" << endl;
	cout << "*  Laufzeitanalyse synchroner Schaltwerke *" << endl;
	cout << "*******************************************" << endl << endl << endl;
}

void Menu::start()
{
// FUNKTIONSAUFGABE: schreibt das Hauptmenue in die KOnsole und startet die Hauptschleife, in der durch das Hauptmenue navigiert wird.

	while(1) 
	{
		meinMenu.menueKopf();
		cout << "(1) aeussere Faktoren" << endl;
		cout << "Spannung [Volt]:"; if(spannung_untermenue != NULL) { cout << spannung_untermenue;} cout << endl; //!geandert /*Hier kommt der Wert if (Wert == 0)  {keine Anzeige}*/ 
		cout << "Temperatur [Grad Celsius]:" ;if(temperatur_untermenue != NULL) { cout << temperatur_untermenue;} cout << endl;//!geandert /*Hier kommt der Wert  if (Wert == 0)  {keine Anzeige}*/  
		cout << "Prozess (1=slow, 2=typical, 3=fast):" ; if(prozess_untermenue != NULL) { cout << prozess_untermenue;} cout << endl;//!geandert /*Hier kommt der Wert if (Wert == 0)  {keine Anzeige}*/ 
		cout << endl;
		cout << "(2) Bibliothek" << endl;
		cout << "Pfad zur Bibliotheksdatei:" << endl << endl;
		cout << "(3) Schaltwerk" << endl;
		cout << "Pfad zur Schaltwerksdatei:" << endl << endl;
		cout << "(4) Analyse starten" << endl << endl;
		cout << "(5) Programm beenden" << endl << endl <<endl;
		cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";
		unsigned int zustand = 0;
		string eingabe;
		cin >> eingabe;
		zustand = atoi(eingabe.c_str());

		switch (zustand)
		{
			case FAKTOREN:
				meinMenu.faktorenMenue();
				break;
			case BIBLIOTHEK:
				meinMenu.bibliothekMenue();
				break;
			case SCHALTWERK:
				meinMenu.schaltwerkMenue();
				break;
			case ANALYSE:
				meinMenu.analyse();
				break;
			case BEENDEN:
				return;	// return to main, beended das Programm
				break;
			default:
				system("cls");
				cout << "nicht definierter Menupunkt! Bitte wählen Sie einen Menuepunkt indem Sie die Zahlen 1 bis 5 eingeben!" << endl << endl << endl;
				system("pause");
				system("cls");
				break;
			zustand = 0;
		}
	}
}


//***************** FUNCTIONS AND METHODS DECLARATIONS END *****
/*
int _tmain(int argc, _TCHAR* argv[])
{
// FUNKTIONSAUFGABE: Main funktion, startet Menue und dient zum beenden des Programms.
	Menu startmenue;
	startmenue.start();
	return 0;
}
*/






//***************************** END OF FILE *******************************************************