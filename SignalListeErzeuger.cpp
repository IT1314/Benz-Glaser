
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Bibliothek.h"
#include "Signal.h"

using namespace std;

double frequenz = 0;
Signal* p_signal_liste;

string enter_pfad(bool* guterpfad)
{
	string pfad;
	system("cls");
	cout << "Bitte geben sie den Pfad fuer die Schaltnetzdatei ein: " << endl;
	cin >> pfad;
	ifstream in(pfad.c_str());
	if (in)
	{ 
		*guterpfad = 1;
		cout << endl << "Eingabe war erfolgreich!" << endl;
		system ("pause");
		system ("csl");
		return pfad;
	}
	*guterpfad = 0;
	cout << endl << "Eingabe war leider nicht erfolgreich!" << endl;
	system("pause");
	system("cls");
	string dummy_string = "dummy";
	return dummy_string;
}

void Ausgabe_Schaltnetzdatei(string schaltnetz_pfad)
{
	ifstream in (schaltnetz_pfad.c_str());
	if(in)
	{
		string zeile;
		int line = 1;
			while (!(in.eof()) )
			{
				getline ( in , zeile );		// Zeilenweise einlesen
				if(in.bad() == false)
				{
					cout << line << ". "<< zeile <<endl;
					line++;
				}
			}
	}
}

void Ausgabe_Signale(string schaltnetz_pfad)
{
	ifstream input (schaltnetz_pfad.c_str());
	string zeile;
	bool search_terminate = 0;
	int signalnummer = 0, temp = 5, signal_counter = 0;		// temp is start position für die zeilenweise Signalsuche im Enity Kopf
	while(zeile.find("INPUT") == string::npos && input.eof() == 0)		// signal_counter startet bei -2 wegen den 2 s in SIGNALS!
	{ 
		getline (input,zeile);
	}
	int pos;
	while(search_terminate == 0)
	{
		if (zeile.find("s",temp) != string::npos)
		{
			signal_counter++;
			temp = zeile.find("s",temp) + 1;
		}
		if (zeile.find("s",temp) == string::npos )
		{
			getline (input,zeile);
			temp = 0;
			if (zeile.find("CLOCK") != string::npos)
			{
				int pos1, pos2;
				pos1 = zeile.find(",");
				pos2 = zeile.find ("MHz");
				if(pos2 != string::npos)
				{
					string versuch = zeile.substr(pos1+1, pos2-pos1);
					frequenz = stod(versuch.c_str())*1000000;
				}
				pos2 = zeile.find("kHz");
				if(pos2 != string::npos)
				{
					string versuch = zeile.substr(pos1+1, pos2-pos1);
					frequenz = stod(versuch.c_str())*1000;
				}
				pos2 = zeile.find(" Hz");
				if(pos2 != string::npos)
				{
					string versuch = zeile.substr(pos1+1, pos2-pos1);
					frequenz = stod(versuch.c_str());
				}
				search_terminate = 1;
			}
		}
	}
	p_signal_liste = new Signal[signal_counter]; 
	p_signal_liste->setSignalTyp(eingang);

	

}


void Ausgabe_Graphstruktur()
{


}