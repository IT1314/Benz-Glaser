#include "SignalListeErzeuger.h"

#include "Bibliothek.h"
#include "Signal.h"
#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

double temp_frequenz = 0;
string schaltnetzpfad_local;


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
	schaltnetzpfad_local = schaltnetz_pfad;
	vector<Signal> signalliste;
	ifstream input (schaltnetz_pfad.c_str());
	string zeile;
	bool search_terminate = 0;
	int signalnummer = 0, temp = 5, signal_counter = 0;		// temp is start position für die zeilenweise Signalsuche im Enity Kopf
	while(zeile.find("INPUT") == string::npos && input.eof() == 0)	
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
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(eingang);
				signalliste.push_back(temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(";")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);
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
				temp_signal.setName(temp_substr);
				temp_signal.setSignalTyp(ausgang);
				signalliste.push_back(temp_signal);
			}
			else
			{
				temp_substr = zeile.substr(zeile.find("s",temp),zeile.find(";")-zeile.find("s"));
				Signal temp_signal;
				temp_signal.setName(temp_substr);
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
		static bool nur_einmal_anlegen = 0;
		
//********************* Clock Signal anlegen *****************************		
		if (nur_einmal_anlegen == 0)
		{
			Signal clk_signal;
			clk_signal.setSignalTyp(eingang);
			clk_signal.setName("clk");
			signalliste.push_back(clk_signal);
			nur_einmal_anlegen = 1;
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
				search_terminate = 1;
			}
		}
	}
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

	string gatter, quelle, ziel_i, ziel_i_plus_1;
	int komma = 0;
	gatter = temp_str.substr(temp_str.find("g"),temp_str.find(":")-temp_str.find("g"));

	komma = temp_str.find(",");
	// if temp_str if "g001:dff(s013,clk,s009); z.B. dann ist Quelle = s009, ziel_i = s013 und ziel_i_plus_1 = clk
	quelle = temp_str.substr(temp_str.find(",",komma+1)+1,temp_str.find(")")-temp_str.find(",",komma+1)-1);
	ziel_i = temp_str.substr(temp_str.find("(")+1,temp_str.find(",")-temp_str.find("(")-1);
	ziel_i_plus_1 = temp_str.substr(temp_str.find(",")+1,temp_str.find(",",temp_str.find(",")+1)-temp_str.find(",")-1);
	for (unsigned int counter = 0; counter < signalliste_local->size(); counter++)
	{
		if (signalliste_local->at(counter).getName() == quelle)
		{
			signalliste_local->at(counter).setQuelle(gatter);
			signalliste_local->at(counter).setQuellenTyp("dff");
		}
		if (signalliste_local->at(counter).getName() == ziel_i)
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


bool SignalListeErzeuger::check_for_and2(string temp_str, vector<Signal>* signalliste_local)
{
	if (temp_str.find("and2") == string::npos)
	{
		return 0;
	}

	string gatter, quelle, ziel_i, ziel_i_plus_1;
	int komma = 0;
	gatter = temp_str.substr(temp_str.find("g"),temp_str.find(":")-temp_str.find("g"));

	komma = temp_str.find(",");
	// if temp_str if "g001:and2(s001,s006,s002); z.B. dann ist Quelle = s002, ziel_i = s001 und ziel_i_plus_1 = s006
	quelle = temp_str.substr(temp_str.find(",",komma+1)+1,temp_str.find(")")-temp_str.find(",",komma+1)-1);
	ziel_i = temp_str.substr(temp_str.find("(")+1,temp_str.find(",")-temp_str.find("(")-1);
	ziel_i_plus_1 = temp_str.substr(temp_str.find(",")+1,temp_str.find(",",temp_str.find(",")+1)-temp_str.find(",")-1);
	for (unsigned int counter = 0; counter < signalliste_local->size(); counter++)
	{
		if (signalliste_local->at(counter).getName() == quelle)
		{
			signalliste_local->at(counter).setQuelle(gatter);
			signalliste_local->at(counter).setQuellenTyp("and2");
		}
		if (signalliste_local->at(counter).getName() == ziel_i)
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


bool SignalListeErzeuger::check_for_xor2(string temp_str, vector<Signal>* signalliste_local)
{
	if (temp_str.find("xor2") == string::npos)
	{
		return 0;
	}

	string gatter, quelle, ziel_i, ziel_i_plus_1;
	int komma = 0;
	gatter = temp_str.substr(temp_str.find("g"),temp_str.find(":")-temp_str.find("g"));

	komma = temp_str.find(",");
	// if temp_str if "g003:xor2(s003,s008,s012); z.B. dann ist Quelle = s012, ziel_i = s003 und ziel_i_plus_1 = s008
	quelle = temp_str.substr(temp_str.find(",",komma+1)+1,temp_str.find(")")-temp_str.find(",",komma+1)-1);
	ziel_i = temp_str.substr(temp_str.find("(")+1,temp_str.find(",")-temp_str.find("(")-1);
	ziel_i_plus_1 = temp_str.substr(temp_str.find(",")+1,temp_str.find(",",temp_str.find(",")+1)-temp_str.find(",")-1);
	for (unsigned int counter = 0; counter < signalliste_local->size(); counter++)
	{
		if (signalliste_local->at(counter).getName() == quelle)
		{
			signalliste_local->at(counter).setQuelle(gatter);
			signalliste_local->at(counter).setQuellenTyp("xor2");
		}
		if (signalliste_local->at(counter).getName() == ziel_i)
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


bool SignalListeErzeuger::check_for_inv1a(string temp_str, vector<Signal>* signalliste_local)
{
	if (temp_str.find("inv1a") == string::npos)
	{
		return 0;
	}

	string gatter, quelle, ziel;
	int komma = 0;
	gatter = temp_str.substr(temp_str.find("g"),temp_str.find(":")-temp_str.find("g"));

	quelle = temp_str.substr(temp_str.find(",")+1,temp_str.find(")")-temp_str.find(",")-1);
	ziel = temp_str.substr(temp_str.find("(")+1,temp_str.find(",")-temp_str.find("(")-1);
	for (unsigned int counter = 0; counter < signalliste_local->size(); counter++)
	{
		if (signalliste_local->at(counter).getName() == quelle)
		{
			signalliste_local->at(counter).setQuelle(gatter);
			signalliste_local->at(counter).setQuellenTyp("inv1a");
		}
		if (signalliste_local->at(counter).getName() == ziel)
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


void SignalListeErzeuger::Ausgabe_Graphstruktur()
{


}