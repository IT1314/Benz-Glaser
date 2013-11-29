#include "SignalListeErzeuger.h"

#include "Bibliothek.h"
#include "Signal.h"
#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

<<<<<<< HEAD
double temp_frequenz = 0;
string schaltnetzpfad_local;

=======
>>>>>>> 3c7d2be9dc539633cfc035e5c8e65dc693093b6b
string SignalListeErzeuger::enter_pfad(bool* guterpfad)
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

void SignalListeErzeuger::Ausgabe_Schaltnetzdatei(string schaltnetz_pfad)
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

void SignalListeErzeuger::Ausgabe_Signale(string schaltnetz_pfad)
{ 
<<<<<<< HEAD
	schaltnetzpfad_local = schaltnetz_pfad;
=======
	vector<Signal*> signalliste;
>>>>>>> 3c7d2be9dc539633cfc035e5c8e65dc693093b6b
	ifstream input (schaltnetz_pfad.c_str());
	string zeile;
	bool search_terminate = 0;
	int signalnummer = 0, temp = 5, signal_counter = 0;		// temp is start position f�r die zeilenweise Signalsuche im Enity Kopf
	while(zeile.find("INPUT") == string::npos && input.eof() == 0)	
	{ 
		getline (input,zeile);
	}
	int pos;
	while(search_terminate == 0)
	{
		if (zeile.find("s",temp) != string::npos && zeile.find("INPUT") != string::npos)
		{
			string temp_substr;
			if(zeile.find(",",temp) != string::npos)
			{
				temp_substr = zeile.substr(zeile.find("s",temp)+1,zeile.find(",")-zeile.find("s")-1);
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(eingang);
				signalliste.push_back(&temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp)+1,zeile.find(";")-zeile.find("s")-1);
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(eingang);
				signalliste.push_back(&temp_signal);
			}
			signal_counter++;
			temp = zeile.find("s",temp) + 1;
		}
		if (zeile.find("s",temp) != string::npos && zeile.find("OUTPUT") != string::npos)
		{
			string temp_substr;
			if(zeile.find(",",temp) != string::npos)
			{
				temp_substr = zeile.substr(zeile.find("s",temp)+1,zeile.find(",")-zeile.find("s")-1);
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(ausgang);
				signalliste.push_back(&temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp)+1,zeile.find(";")-zeile.find("s")-1);
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(ausgang);
				signalliste.push_back(&temp_signal);
			}
			signal_counter++;
			temp = zeile.find("s",temp) + 1;
		}
		if (zeile.find("s",temp) != string::npos && zeile.find("SIGNALS") != string::npos)
		{
			string temp_substr;
			if(zeile.find(",",temp) != string::npos)
			{
				temp_substr = zeile.substr(zeile.find("s",temp)+1,zeile.find(",")-zeile.find("s")-1);
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(intern);
				signalliste.push_back(&temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp)+1,zeile.find(";")-zeile.find("s")-1);
				Signal temp_signal;
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(intern);
				signalliste.push_back(&temp_signal);
			}
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
<<<<<<< HEAD
// ******************** Speichern der Frequenz in signalliste Elementen ****************************
	for (unsigned int counter = 0; counter < signalliste.size(); counter++)
	{
		Signal temp_signal;
		signalliste.at(counter).set_Frequenz(temp_frequenz);
	}
// ********************* Quelle, Ziele und Anzahl der Ziele Erkennung ******************************
	while ( zeile.find("g001") == string::npos)	// get to line after BEGIN
	{
		getline(input,zeile);
	}
	while (zeile.find("END") == string::npos)
	{
		check_for_dff(zeile, &signalliste);
		check_for_and2(zeile, &signalliste);
		check_for_xor2(zeile, &signalliste);
		check_for_inv1a(zeile, &signalliste);
		getline(input,zeile);
	}
}

bool SignalListeErzeuger::check_for_dff(string temp_str, vector<Signal>* signalliste_local)
{
	if (temp_str.find("dff") == string::npos)
	{
		return 0;
	}
=======
>>>>>>> 3c7d2be9dc539633cfc035e5c8e65dc693093b6b

	signalliste[signal_counter];
	ifstream input2 (schaltnetz_pfad.c_str());
	string temp_substr;
	getline(input2,zeile);
	while(input2.eof()== 0)
	{
		if(zeile.find("INPUT") != string::npos && zeile.find("s") != string::npos)
		{
			int temp_pos = zeile.find(",");
			if (temp_pos == string::npos)
			{
				temp_substr = (zeile, zeile.find(";")-zeile.find("s"));
			}
		}

	}
}


void SignalListeErzeuger::Ausgabe_Graphstruktur()
{


}