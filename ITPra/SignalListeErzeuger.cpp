
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


string enter_pfad(bool* guterpfad)
{
	string pfad;
	system("cls");
	cout << "Bitte geben sie den Pfad für die Schaltnetzdatei ein: " << endl;
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

void Ausgabe_Schaltnetzdatei()
{

}

void Ausgabe_Signale()
{


}

void Ausgabe_Graphstruktur()
{


}