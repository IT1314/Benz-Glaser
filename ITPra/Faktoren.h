#ifndef FAKTOREN_H
#define FAKTOREN_H

using namespace std;

#define SPANNUNG 1
#define TEMPERATUR 2
#define PROZESS 3
#define SLOW 1
#define TYPICAL 2
#define FAST 3
#define AUSGABE_ERRECHNETER_FAKTOREN 4
#define HAUPTMENUE 5




class Faktoren 
{
	private:
	// ########## Attribute #############	
		double spannung;
		double temperatur;
		double prozess;
		double spannungFaktor;
		double temperaturFaktor;
		double prozessFaktor;
	// ########## Attribute end #########

	// ######### Methoden ##############
		double berechneFaktor(double value, vector<vector<double>> arr, int laenge);
	// ######### Methoden end ##########
	
	public:
	// ######### Methoden ##############

		bool berechneSpannungFaktor(double spg);
		bool berechneTemperaturFaktor(double temp);
		bool berechneProzessFaktor(short prz);
		
		double interpolation(double value, double x1, double x2, double y1, double y2);
		double getSpannung();
		double getTemperatur();
		short getProzess();
		void getFaktore(double spgFaktor, double tmpFaktor, double przFaktor);
		bool setSpannung(double spannung);
		bool setTemperatur(double temperatur);
		bool setProzess(short prozess);
		void ausgabeFaktoren();
	// ######### Methoden end ##########
};

#endif FAKTOREN_H