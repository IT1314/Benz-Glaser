#include "SignalListeErzeuger.h"

#include "Bibliothek.h"
#include "Signal.h"
#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

double temp_frequenz = 0;

SignalListeErzeuger::SignalListeErzeuger()
{
	this->anzahlSignale = 0;
	this->datei = "";
	this->frequenz = 0;
}
SignalListeErzeuger::~SignalListeErzeuger()
{
}


string SignalListeErzeuger::enter_pfad(bool* guterpfad)
{
	string pfad;
	system("cls");
	cout << "Bitte geben sie den Pfad fuer die Schaltnetzdatei ein: " << endl;
	cin >> pfad;
	ifstream in(pfad.c_str());
	if (in)
	{ 
		*guterpfad = 1;												// Hilfe für das Menu, wenn True wird der Pfad im Menue angezeigt
		cout << endl << "Eingabe war erfolgreich!" << endl;
		this->datei = pfad;									// Pfad wird in Klassen String gespeichert gespeichert
		system ("pause");
		system ("csl");
		return this->datei;
	}
	*guterpfad = 0;
	cout << endl << "Eingabe war leider nicht erfolgreich!" << endl;
	system("pause");
	system("cls");
	string dummy_string = "";									// return dummy Wert, falls der Pfad nicht in Ordnung war. 
	return dummy_string;
}

void SignalListeErzeuger::ausgabe_Schaltnetzdatei()
{
	ifstream in (this->datei);
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

void SignalListeErzeuger::ausgabe_signale()
{
	cout << endl << "------------------------" << endl;
	cout << "Signale:" << endl << "-------" << endl;
	for (unsigned int counter = 0; counter <signalliste.size(); counter++)
	{
		cout << "Signalname : " << signalliste.at(counter).getName() << endl;
		cout << "Signaltyp : " << signalliste.at(counter).getQuellenTyp() << endl;
		cout << "Signalquelle : " << signalliste.at(counter).getQuelle() << endl;
		cout << "-->Das Signal hat " << signalliste.at(counter).getAnzahlZiele() << " Ziele" << endl;
		cout << "Ziel-Gatter : ";
		for (int counter2 = 0; counter2 < signalliste.at(counter).getAnzahlZiele(); counter2++)
		{
			cout << signalliste.at(counter).getZiel(counter2) << " ";
		}
		cout << endl << endl;
	}
	system("PAUSE");
	system("cls");
}

void SignalListeErzeuger::berechne_Signale()
{ 
	signalliste.clear();					// resette Signalliste
	ifstream input (this->datei.c_str());
	string zeile;
	bool search_terminate = 0;
	int signalnummer = 0, temp = 5, signal_counter = 0;		// temp is start position für die zeilenweise Signalsuche im Enity Kopf
	while(zeile.find("INPUT") == string::npos && input.eof() == 0)			// Liest so lange ein, bis er INPUT findet
	{ 
		getline (input,zeile);
	}
	while(search_terminate == 0)
	{
//********************************************* Input Signalerkennung und speichern in signalliste **********************************
		if (zeile.find("s",temp) != string::npos && zeile.find("INPUT") != string::npos)
		{
			string temp_substr;
			if(zeile.find(",",temp) != string::npos)
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(",")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);		// Eingangssignale speichern vom Typ "sxxx,"
				temp_signal.setSignalTyp(eingang);
				signalliste.push_back(temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(";")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);		// Eingangssignale speichern vom Typ "sxxx;" (letztes Signal)
				temp_signal.setSignalTyp(eingang);
				signalliste.push_back(temp_signal);
			}
			signal_counter++;
			temp = zeile.find("s",temp) + 1;
		}
//********************************************* Output Signalerkennung und speichern in signalliste **********************************
		if (zeile.find("s",temp) != string::npos && zeile.find("OUTPUT") != string::npos)
		{
			string temp_substr;
			if(zeile.find(",",temp) != string::npos)
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(",")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);		//Ausgangssignale speichern "sxxx,"
				temp_signal.setSignalTyp(ausgang);
				signalliste.push_back(temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(";")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);		// Ausgangssignale speichern "sxxx;"
				temp_signal.setSignalTyp(ausgang);
				signalliste.push_back(temp_signal);
			}
			signal_counter++;
			temp = zeile.find("s",temp) + 1;
		}
//********************************************* interne Signalerkennung und speichern in signalliste **********************************
		if (zeile.find("s",temp) != string::npos && zeile.find("SIGNALS") != string::npos)
		{
			string temp_substr;
			if(zeile.find(",",temp) != string::npos)
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(",")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(intern);
				signalliste.push_back(temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(";")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(intern);
				signalliste.push_back(temp_signal);
			}
			signal_counter++;
			temp = zeile.find("s",temp) + 1;
		}

//********************** Frequenz Ermittlung ****************************
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
					temp_frequenz = stod(versuch.c_str())*1000000;
				}
				pos2 = zeile.find("kHz");
				if(pos2 != string::npos)
				{
					string versuch = zeile.substr(pos1+1, pos2-pos1);
					temp_frequenz = stod(versuch.c_str())*1000;
				}
				pos2 = zeile.find(" Hz");
				if(pos2 != string::npos)
				{
					string versuch = zeile.substr(pos1+1, pos2-pos1);
					temp_frequenz = stod(versuch.c_str());
				}
				this->frequenz = temp_frequenz;
				search_terminate = 1;
			}
		}
	}

// ******************** Speichern der Frequenz in signalliste Elementen ****************************
	for(auto it = signalliste.begin(); it != signalliste.end(); it++)
	{
		it->set_Frequenz(temp_frequenz);
	}
	
// ********************* Quelle, Ziele und Anzahl der Ziele Erkennung ******************************
	while ( zeile.find("g001") == string::npos)	// get to line after BEGIN
	{
		getline(input,zeile);
	}
// ********************* Geht das Dokument durch und sucht nach D-Flip-Flop, Und- Oder Gatter und Invertern
	while (zeile.find("END") == string::npos)
	{
		check_for_gatter(zeile, &signalliste);
		getline(input,zeile);
	}

//********************** Kurzschluss überprüfen *************************(ist Quelle und Ziel eines Signals identisch?)
	for (unsigned int element = 0; element < signalliste.size(); element++)
	{
		for (int ziel_nummer = 0; ziel_nummer < signalliste.at(element).getAnzahlZiele();ziel_nummer++)
		{
			if (signalliste.at(element).getQuelle() == signalliste.at(element).getZiel(ziel_nummer))
			{
				cout << "ERROR: Kurzschluss wurde entdeckt!" << endl;
				system("PAUSE");
				system("cls");
				signalliste.clear();
				return;
			}
		}
	}
		
	this->anzahlSignale = signalliste.size();		// speichern der Anzahle der Signale in der Klasse
	cout << "SUCCESS!" << endl;
}

bool SignalListeErzeuger::check_for_gatter(string temp_str, vector<Signal>* signalliste_local)
{	
	string gatter, gatter_art, quelle, ziel_i, ziel_i_plus_1;
	
	gatter_art = temp_str.substr(temp_str.find(":")+1,temp_str.find("(")-temp_str.find(":")-1);		// Art des Gatters: dff, and2, xor2....
	int komma = 0;
	gatter = temp_str.substr(temp_str.find("g"),temp_str.find(":")-temp_str.find("g"));				// Gattername: g001, g002,....

	komma = temp_str.find(",");
	// Falls temp_str = "g001:dff(s013,clk,s009);" z.B. dann ist Quelle = s009, ziel_i = s013 und ziel_i_plus_1 = clk
	if (temp_str.find(",",komma+1) == string::npos)			//Falls nur 1 Eingang vorhanden ist, wie bei den Invertern
	{
		quelle = temp_str.substr(temp_str.find(",")+1,temp_str.find(")")-temp_str.find(",")-1);
		ziel_i = temp_str.substr(temp_str.find("(")+1,temp_str.find(",")-temp_str.find("(")-1);	
		ziel_i_plus_1 = "";
	}
	else
	{
	quelle = temp_str.substr(temp_str.find(",",komma+1)+1,temp_str.find(")")-temp_str.find(",",komma+1)-1);		
	ziel_i = temp_str.substr(temp_str.find("(")+1,temp_str.find(",")-temp_str.find("(")-1);
	ziel_i_plus_1 = temp_str.substr(temp_str.find(",")+1,temp_str.find(",",temp_str.find(",")+1)-temp_str.find(",")-1);
	}


//************************** Geht die Signalliste durch und sucht nach der Quelle und den Zielen **********************
	for (unsigned int counter = 0; counter < signalliste_local->size(); counter++)
	{
		if (signalliste_local->at(counter).getName() == quelle)
		{
			signalliste_local->at(counter).setQuelle(gatter);
			signalliste_local->at(counter).setQuellenTyp(gatter_art);
		}
		if (signalliste_local->at(counter).getName() == ziel_i)
		{
			int counter2 = 0;
			bool found_place = 0;
			while (counter2 < 5 && found_place == 0)
			{
				if (signalliste_local->at(counter).getZiel(counter2) == "")		// Speichert das Ziel nur, wenn der String noch leer ist
				{
					signalliste_local->at(counter).setZiel(gatter,counter2);
					signalliste_local->at(counter).setAnzahlZiele(signalliste_local->at(counter).getAnzahlZiele()+1);
					found_place = 1;
				}
				else
				{
					counter2++;
				}
			}
		}
		if (signalliste_local->at(counter).getName() == ziel_i_plus_1)
		{
			int counter2 = 0;
			bool found_place = 0;
			while (counter2 < 5 && found_place == 0)
			{
				if (signalliste_local->at(counter).getZiel(counter2) == "")
				{
					signalliste_local->at(counter).setZiel(gatter,counter2);
					signalliste_local->at(counter).setAnzahlZiele(signalliste_local->at(counter).getAnzahlZiele()+1);
					found_place = 1;
				}
				else
				{
					counter2++;
				}
			}
		}
	}
	return 1;
}

