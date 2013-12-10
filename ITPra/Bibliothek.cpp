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
GatterTyp* Bibliothek::getBibElement( string typ){//! Übergibt einen Zeiger auf das Gatterelement

	GatterTyp* back = NULL;

	for( unsigned int a= 0; a<bibElemente.size(); a++){//! Durchlaeuft alle Elemente

		if( bibElemente.at(a)->getName() == typ){

			back = bibElemente.at(a);
			break;
		}
		
	}

	return back;
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
	int blockcounter = 0;//! blockcounter ueberprueft die blocklaenge.
  bibElemente.clear();

	
ifstream in (datei.c_str());
	if(in){
		
		string zeile;
		string flip = "dff";
		if (!(in.eof()) && in.good()){
			
			

			do{
					getline ( in , zeile );

					}while(!((zeile.find("dff"))!= string::npos));
				
		}
		while (!(in.eof()) && in.good()){
			
			

			
			if(in.bad() == false){
        getline ( in , zeile );//!Zeilenweise einlesen

	           

				if(zeile.find("[") != string::npos){

				if(zeile.substr(zeile.find("[") +1,zeile.find("]")-1)== flip){

					Flipflop* Flip = new Flipflop;
				    do{
							getline ( in , zeile );//!Zeilenweise einlesen
							Flip->setName(flip);
												

					if(zeile.find("ed:")!= string::npos){
				     string ed0 =zeile.substr(zeile.find(":") +1);
					 double  ed = atof(ed0.c_str());
					 Flip->setEingaenge(ed);
                     blockcounter ++;
			
					}
					if(zeile.find("tsetup:")!= string::npos){
				    string tsetup0 =zeile.substr(zeile.find(":") +1);
					 double tsetup = atof(tsetup0.c_str());
                     Flip->setSetupTime(tsetup);
                     blockcounter ++;
			
					}
					if(zeile.find("thold:")!= string::npos){
				     string thold0 =zeile.substr(zeile.find(":") +1);
					 double thold = atof(thold0.c_str());
                     Flip->setHoldTime(thold);
                     blockcounter ++;
			
					}
					if(zeile.find("cd:")!= string::npos){
				    string cd0 =zeile.substr(zeile.find(":") +1);
					double cd = atof(cd0.c_str());
                    Flip->setLastKapazitaet(cd);
                    blockcounter ++;
			
					}
					if(zeile.find("et:")!= string::npos){

					blockcounter ++;
			
					}
					if(zeile.find("tpdt:")!= string::npos){
				     string tpdt0 =zeile.substr(zeile.find(":") +1);
					 double tpdt = atof(tpdt0.c_str());
                     Flip->setGrundLaufzeit(tpdt);
                     blockcounter ++;

					}
					if(zeile.find("kl:")!= string::npos){
				    string kl0 =zeile.substr(zeile.find(":") +1);
					double kl = atof(kl0.c_str());
                    Flip->setLastFaktor(kl);
                    blockcounter ++;
			
					}
					if(zeile.find("ct:")!= string::npos){
				    string ct0 =zeile.substr(zeile.find(":") +1);
					double ct = atof(ct0.c_str());
                    Flip->setLastKapazitaet(ct);
                    blockcounter ++;
			
					}
						  }	
					while((blockcounter < 8) && !(in.eof()));
					bibElemente.push_back(Flip);
					blockcounter = 0;
				}
			else{
					GatterTyp* Bauteil = new GatterTyp;
					if(zeile.find("[") != string::npos){
											Bauteil->setName(zeile.substr(zeile.find("[") +1,zeile.find("]")-1));
											blockcounter ++;
					}
					do{
					getline ( in , zeile );//!Zeilenweise einlesen
						
					
					
					
					if(zeile.find("ei:") != string::npos){
						string ei0 =zeile.substr(zeile.find(":")+1);
						double ei = atof(ei0.c_str());
						Bauteil->setEingaenge(ei);
						blockcounter ++;
					}
					if(zeile.find("tpd0:") != string::npos){
						
						string tpd0 = zeile.substr(zeile.find(":")+1);
						double tpd = atof( tpd0.c_str());											 
						Bauteil->setGrundLaufzeit(tpd);
						blockcounter ++;
					}
					if(zeile.find("kl:") != string::npos){
						string kl0 = zeile.substr(zeile.find(":") +1);
						double kl = atof( kl0.c_str());
						Bauteil->setLastFaktor(kl);
						blockcounter ++;
					}
					if(zeile.find("cl:") != string::npos){
						string cl0 = zeile.substr(zeile.find(":") +1);
						double cl = atof(cl0.c_str());
						Bauteil->setLastKapazitaet(cl);
						blockcounter ++;
					}
					}while((blockcounter < 5) && !(in.eof()));
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
