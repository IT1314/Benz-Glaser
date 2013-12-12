

//***************** INCLUDE FILES ******************************
#include "stdafx.h"
#include <vector>
#include <iostream>
#include "Faktoren.h"
#include "Menu.h"
#include "itiv_win_drv.h"

using namespace std;
//***************** INCLUDE FILES END **************************


// ********************** METHODEN DEKLARATION ************************



double Faktoren::interpolation(double wert, double x1, double x2, double y1, double y2)
{
	// lineare Interpolation ==> y = y1 + m(x-x1) mit m= y2-y1 / x2-x1
	double steigung = (y2-y1) / (x2-x1);
	return y1 + steigung*(wert-x1);
}


double Faktoren::berechneFaktor(double value, vector<vector<double>> arr, int laenge)
{
	for(int i = 0; i<=laenge; i++)			// prüft ob der übergebene Wert = dem Wert aus dem gegebenen Array ist, wenn wahr, wird der K fakor returned
	{
		if ( arr[i][0] == value)
		{
			return arr[i][1];
		}
		if ( arr[i][0] > value)				// Sobald der Wert kleiner als das Array Element ist, werden die x und y Werte von dem Element und dem Vorgänger übergeben
		{
			return this->interpolation(value,arr[i-1][0],arr[i][0],arr[i-1][1],arr[i][1]);
		}	
	}
	return 0;
}

bool Faktoren::berechneSpannungFaktor(double spg)
{
	this->spannung = spg;
	vector<vector<double> > spannungs_werte(7, vector<double>(2));
	spannungs_werte[0][0] = 1.08;		// Spannungswerte
	spannungs_werte[1][0] = 1.12;
	spannungs_werte[2][0] = 1.16;
	spannungs_werte[3][0] = 1.20;
	spannungs_werte[4][0] = 1.24;
	spannungs_werte[5][0] = 1.28;
	spannungs_werte[6][0] = 1.32;

	spannungs_werte[0][1] = 1.121557;	// K-Faktoren
	spannungs_werte[1][1] = 1.075332;
	spannungs_werte[2][1] = 1.035161;
	spannungs_werte[3][1] = 1.000000;
	spannungs_werte[4][1] = 0.968480;
	spannungs_werte[5][1] = 0.940065;
	spannungs_werte[6][1] = 0.914482;
	int array_laenge = spannungs_werte.size();

	if (spg < spannungs_werte[0][0] || spg > spannungs_werte[6][0])
	{
		system("cls");
		cout << "Der eingegebene Spannungswert liegt nicht im Intervall von 1.08 bis 1.32 Volt!" << endl << endl;
		system("pause");
		system("cls");
		return 0;
	}
	this->spannungFaktor = this->berechneFaktor(spg, spannungs_werte, array_laenge);
	return 1;
}

bool Faktoren::berechneTemperaturFaktor(double temp)
{
	this->temperatur = temp;
	vector<vector<double> > temperatur_werte(15, vector<double>(2));
	temperatur_werte[0][0] = -25;		// temperatur Werte
	temperatur_werte[1][0] = -15;
	temperatur_werte[2][0] = 0;
	temperatur_werte[3][0] = 15;
	temperatur_werte[4][0] = 25;
	temperatur_werte[5][0] = 35;
	temperatur_werte[6][0] = 45;
	temperatur_werte[7][0] = 55;		
	temperatur_werte[8][0] = 65;
	temperatur_werte[9][0] = 75;
	temperatur_werte[10][0] = 85;
	temperatur_werte[11][0] = 95;
	temperatur_werte[12][0] = 105;
	temperatur_werte[13][0] = 115;
	temperatur_werte[14][0] = 125;

	temperatur_werte[0][1] = 0.897498;		// K-Faktoren
	temperatur_werte[1][1] = 0.917532;
	temperatur_werte[2][1] = 0.948338;
	temperatur_werte[3][1] = 0.979213;
	temperatur_werte[4][1] = 1.000000;
	temperatur_werte[5][1] = 1.020305;
	temperatur_werte[6][1] = 1.040540;
	temperatur_werte[7][1] = 1.061831;		
	temperatur_werte[8][1] = 1.082983;
	temperatur_werte[9][1] = 1.103817;
	temperatur_werte[10][1] = 1.124124;
	temperatur_werte[11][1] = 1.144245;
	temperatur_werte[12][1] = 1.164563;
	temperatur_werte[13][1] = 1.184370;
	temperatur_werte[14][1] = 1.204966;
	int array_laenge = temperatur_werte.size();

	if (temp < temperatur_werte[0][0] || temp > temperatur_werte[14][0])
	{
		system("cls");
		cout << "Der eingegebene Temperaturwert liegt nicht im Intervall von -25 bis 125 Grad Celsius!" << endl << endl;
		system("pause");
		system("cls");
		return 0;
	}

	this->temperaturFaktor = this->berechneFaktor(temp, temperatur_werte, array_laenge);
	return 1;
}


bool Faktoren::berechneProzessFaktor(short prz)
{
	this->prozess = prz;
	vector<vector<double> > prozess_werte(3, vector<double>(2));
	prozess_werte[0][0] = SLOW;		// Prozess Modi
	prozess_werte[1][0] = TYPICAL;
	prozess_werte[2][0] = FAST;

	prozess_werte[0][1] = 1.174235;	// K-Faktoren
	prozess_werte[1][1] = 1.000000;
	prozess_werte[2][1] = 0.876148;
	int array_laenge = prozess_werte.size();

	if (!(prz == prozess_werte[0][0] || prz == prozess_werte[1][0] || prz == prozess_werte[2][0]))
	{
		system("cls");
		cout << "Der eingegebene Prozess ist nicht definiert!" << endl << endl;
		system("pause");
		system("cls");
		return 0;
	}

	this->prozessFaktor = this->berechneFaktor(prz, prozess_werte, array_laenge);
	return 1;
}

double Faktoren::getSpannung() {return this->spannung;}

double Faktoren::getTemperatur() {return this->temperatur;}//verändert

short Faktoren::getProzess() {return short(this->prozess);}

bool Faktoren::setSpannung(double spannung) {this->spannung = spannung; return 1;}

bool Faktoren::setTemperatur(double temp) {this->temperatur = temp; return 1;}

bool Faktoren::setProzess(short prz) {this->prozess = prz; return 1;}

void Faktoren::ausgabeFaktoren()
{
	cout << endl << "----------------------------------------" << endl << endl;
	cout << "Faktoren: KV: " << this->spannungFaktor << " |KT: " << this->temperaturFaktor << " |KP: " << this->prozessFaktor << endl << endl;
	system("pause");
	system("cls");
	return;
}

void Faktoren::setItiv(int ch){

	bool beendensVar=true;
	ItivDev_Config* DevPtr;																	
	DevPtr = ItivDev_GetConfigByName("Global\\ITIV_WindowsDevice");									//Initialisieren vom itiv device
		
	switch(ch)
	{
		case 1:																						// für Spannung
			
			while (beendensVar)
			{
				
				*(DevPtr->BaseAddress + CTRL_REG + 1) = 0;											//START =0
				while(*(DevPtr->BaseAddress + STAT_REG + 3) ==0)									//Wenn READY=0 warten an der stelle
				{										
				
				}
					
				*(DevPtr->BaseAddress + CTRL_REG ) = 1;												//CH =1 für Spannung
				*(DevPtr->BaseAddress + CTRL_REG + 1) = 1;											//START = 1
					
				while(*(DevPtr->BaseAddress + STAT_REG + 2) == 0)									//Wenn DONE=0 warten an der stelle
				{
						
				}	
			
				if(*(DevPtr->BaseAddress + STAT_REG ) == 0)											//Wenn ERR =0 dann soll es die daten auslesen
				{ 
					
					beendensVar=false;	
					double voltage = *((double*)(DevPtr->BaseAddress + DATA_REG));					//Spannugswert wird unter voltage gespeichert
					setSpannung(voltage);
					ItivDev_ReleaseDevice(DevPtr);

				}

	
			}
			break;
		case 2:																						// für Temperatur
			
			while (beendensVar)
			{
				cout<< "programm hier";
				*(DevPtr->BaseAddress + CTRL_REG + 1) = 0;											//START =0
						
				while(*(DevPtr->BaseAddress + STAT_REG + 3) ==0)									//Wenn READY=0 warten an der stelle
				{										
					
				}
					
				*(DevPtr->BaseAddress + CTRL_REG ) = 2;												//CH =2 für Temperatur
				*(DevPtr->BaseAddress + CTRL_REG + 1) = 1;											//START = 1
					
				while(*(DevPtr->BaseAddress + STAT_REG + 2) == 0)									//Wenn DONE=0 warten an der stelle
				{
						
				}	
				
				if(*(DevPtr->BaseAddress + STAT_REG ) == 0)											//Wenn ERR =0 dann soll es die daten auslesen
				{ 
					
					beendensVar=false;	
					int temperaturdevice = *((int*)(DevPtr->BaseAddress + DATA_REG));				//Temperaturwert wird unter temp gespeichert
					double temper= temperaturdevice*1.0;
					setTemperatur(temper);
					ItivDev_ReleaseDevice(DevPtr);
				}
		
			}	
			break;
		case 3:																						//für Prozess
		
			while (beendensVar)
			{
				
				*(DevPtr->BaseAddress + CTRL_REG + 1) = 0;											//START =0
						
				while(*(DevPtr->BaseAddress + STAT_REG + 3) ==0)									//Wenn READY=0 warten an der stelle
				{										
					
				}
					
				*(DevPtr->BaseAddress + CTRL_REG ) = 3;												//CH =3 für Prozess
				*(DevPtr->BaseAddress + CTRL_REG + 1) = 1;											//START = 1
					
				while(*(DevPtr->BaseAddress + STAT_REG + 2) == 0)									//Wenn DONE=0 warten an der stelle
				{
						
				}	
		
				if(*(DevPtr->BaseAddress + STAT_REG ) == 0)											//Wenn ERR =0 dann soll es die daten auslesen
				{ 
					
					beendensVar=false;	
					short prozess = *((short*)(DevPtr->BaseAddress + DATA_REG));					//Prozesswert wird unter prozess gespeichert
					
					setProzess(prozess+1);
					ItivDev_ReleaseDevice(DevPtr);
				}
		
			}	
			break;

	}
}
 

// ********************** METHODEN DEKLARATION END ********************







//***************************** END OF FILE *******************************************************
