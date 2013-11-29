//***************** INCLUDE FILES ******************************
#include "stdafx.h"
#include "Bibliothek.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>


using namespace std;
//***************** INCLUDE FILES END **************************

// ********************** METHODEN DEKLARATION ************************
Bibliothek :: Bibliothek(){}//! Konstruktor

Bibliothek :: Bibliothek(string pfad){//! Setze Funktion
	datei = pfad;
}

Bibliothek :: ~Bibliothek(){}//! Destruktor

string Bibliothek :: getPfad (){
	return datei;
}

GatterTyp* Bibliothek :: getBibElement( string typ){//! Übergibt einen Zeiger auf das Gatterelement
	for (auto it = std::begin(bibElemente); it!=std::end(bibElemente); ++it){//! Durchlaeuft alle Elemente
		if ((*it)->getName() == typ){
			return *it;
		}
		else{
			cout << " Ist nicht im Speicher"<<endl;
		}
		
	}
	
	return 0;	
}
void Bibliothek ::dateiAusgabe(){//! Ausgabe
	ifstream in (datei.c_str());
	if(in){
		string zeile;
		int line = 1;
		if(!in.eof()){
			while (!(in.eof()) ){
				getline ( in , zeile );//!Zeilenweise einlesen
				if(in.bad() == false){
					cout << line << ". "<< zeile <<endl;
					line++;
				}
				else{
					readError();
					}
			}
		}
		
	}
	else {
		openError();
	}
	in.close();
}
void Bibliothek ::dateiAuswerten(){

	   GatterTyp* Bauteil = new GatterTyp;
	    Flipflop* Flip = new Flipflop;
	int blockcounter = 0;//! blockcounter ueberprueft die blocklaenge.

	if( !bibElemente.empty ()){ //! Bibliothek wird nur erzeugt wenn die Bibliothek nicht schon erstellt ist.

	ifstream in (datei.c_str());
	if(in){
		string zeile;
		string flip = "dff";
		while (!(in.eof()) ){

			if(in.bad() == false){
				getline ( in , zeile );//!Zeilenweise einlesen
				zeile.find("#begin");
				zeile.find("[[ Bausteine]]");
				if(zeile.substr(zeile.find("[") +1,zeile.find("]"))== flip){
					Flip->setName(flip);
					blockcounter ++;

					if(zeile.find("ed:")){
				
					string ed =zeile.substr(zeile.find("ed:") +1);
					int  help;
					help =stoi(ed);
					Flip->setEingaenge(help);
					blockcounter ++;
			
					}
					if(zeile.find("tsetup:")){
				
					string tsetup =zeile.substr(zeile.find("tsetup:") +1);
					int  help;
					help =stoi(tsetup);
					Flip->setSetupTime(help);
					blockcounter ++;
			
					}
					if(zeile.find("thold:")){
				
					string thold =zeile.substr(zeile.find("thold:") +1);
					int  help;
					help =stoi(thold);
					Flip->setHoldTime(help);
					blockcounter ++;
			
					}
					if(zeile.find("cd:")){
				
					string cd =zeile.substr(zeile.find("cd:") +1);
					int  help;
					help =stoi(cd);
					Flip->setLastKapazitaet(help);
					blockcounter ++;
			
					}
					if(zeile.find("et:")){

					blockcounter ++;
			
					}
					if(zeile.find("tpdt:")){
				
					string tpdt =zeile.substr(zeile.find("tpdt:") +1);
					double  help;
					help =stod(tpdt);
					Flip->setGrundLaufzeit(help);
					blockcounter ++;
			
					}
					if(zeile.find("kl:")){
				
					string kl =zeile.substr(zeile.find("kl:") +1);
					int  help;
					help =stoi(kl);
					Flip->setLastFaktor(help);
					blockcounter ++;
			
					}
					if(zeile.find("ct:")){
				
					string ct =zeile.substr(zeile.find("ct:") +1);
					int  help;
					help =stoi(ct);
					Flip->setLastKapazitaet(help);
					blockcounter ++;
			
					}
					if(blockcounter == 9){
					bibElemente.push_back(Flip);
					blockcounter = 0;
				}
				}
			else{
					if(zeile.find("[")){
						Bauteil->setName(zeile.substr(zeile.find("[") +1,zeile.find("]")));
						blockcounter ++;
					}
					if(zeile.find("ei:")){
				
						string ei =zeile.substr(zeile.find("ei:") +1);
						int  help;
						help =stoi(ei);
						Bauteil->setEingaenge(help);
						blockcounter ++;
					}
					if(zeile.find("tpd0:")){
				
						string tpd =zeile.substr(zeile.find("tpd0:") +1);
						double  help;
						help =stod(tpd);
						Bauteil->setGrundLaufzeit(help);
						blockcounter ++;
					}
					if(zeile.find("kl:")){
				
						string kl =zeile.substr(zeile.find("kl:") +1);
						int  help;
						help =stoi(kl);
						Bauteil->setLastFaktor(help);
						blockcounter ++;
					}
					if(zeile.find("cl:")){
				
						string cl =zeile.substr(zeile.find("cl:") +1);
						int  help;
						help =stoi(cl);
						Bauteil->setEingaenge(help);
						blockcounter ++;
					}
					if(blockcounter == 5){
						bibElemente.push_back(Bauteil);
						blockcounter = 0;
					}
	        }
			}
	 else{
			readError();
	   	}
    }
  }
  in.close();
  }
  else{
	  bibElemente.clear(); //! wenn die Bibliothek bereits besteht und erneut erstellt wird wird die alte Bibliothek geloescht.
  }
}
bool Bibliothek :: pfadEinlesen( string pfad) {
	
	ifstream in(pfad.c_str());

	if(in){
		datei = pfad;
		in.close();
		return true;
	} 
	else{ 
		openError();
		return false; 
	}
	in.close();
}
void Bibliothek :: openError(){
	     //! Die Bibliotheksdatei existiert nicht
		cout << "Die Bibliotheksdatei kann nicht geoeffnet werden"<<endl;
        
    

}
void Bibliothek :: readError(){	
         //! Die Bibliotheksdatei kann nicht gelesen werden.
		cout << "Die Bibliotheksdatei kann nicht gelesen werden"<<endl;        
}
// ********************** METHODEN DEKLARATION END ********************







//***************************** END OF FILE *******************************************************
