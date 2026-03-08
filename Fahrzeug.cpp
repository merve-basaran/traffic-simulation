#include "Fahrzeug.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
#include "Weg.h"
#include "Streckenende.h"
#include <memory>
#include <list>
#include <iostream>
#include <string>
#include <iomanip>
#include <utility>

using namespace std;


// Define and initialize the global variable
double dGlobaleZeit = 0.0;

double Fahrzeug::getGesamtStrecke() const {
    return p_dGesamtStrecke;
}

// Constructor with string parameter
Fahrzeug::Fahrzeug(string name)
		: Simulationsobjekt(name) {
    cout << "Fahrzeug created: Name = " << p_sName << ", ID = " << p_iID << endl;
}

// Default constructor
Fahrzeug::Fahrzeug()
    : Simulationsobjekt("") {
    cout << "Fahrzeug created: Name = " << p_sName << ", ID = " << p_iID << endl;
}

// Destructor
Fahrzeug::~Fahrzeug() {
    cout << "Fahrzeug destroyed: Name = " << p_sName << ", ID = " << p_iID << endl;
}

// Constructor with name and max speed parameter
Fahrzeug::Fahrzeug(string name, double maxGeschwindigkeit)
				: Simulationsobjekt(name), p_dMaxGeschwindigkeit(maxGeschwindigkeit > 0 ? maxGeschwindigkeit : 0){
}


// function to output the table header
void Fahrzeug::vKopf() {
    cout << left
    		  << setw(10) << "ID"
              << setw(20) << "Name"
              << setw(25) << "MaxGeschwindigkeit"
              << setw(20) << "Gesamtstrecke";
    cout << setw(20) << "Gesamtverbrauch" ;
	cout << setw(20) << "Aktu_Tankinhalt"
		 << setw(20) << "Aktuelle Geschwind"
		 << setw(20) << "Verbrauch in L/100km";

    cout << "\n--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
// Member function to output specific vehicle data
void Fahrzeug::vAusgeben(ostream& to) const {
	 	 	 Simulationsobjekt::vAusgeben(to);
              to<< setw(31) << fixed << setprecision(2) << p_dMaxGeschwindigkeit
              << setw(20) << fixed << setprecision(2) << p_dGesamtStrecke
			  ;

}


void Fahrzeug::vSimulieren() {
    // Calculate the elapsed time since the last simulation
    double vergangeneZeit = dGlobaleZeit - p_dZeit;
    // Ensure the vehicle is updated only if time has actually passed
    if (vergangeneZeit > 0) {
        // Update the total motion time
        p_dGesamtZeit += vergangeneZeit;
        // Update the last simulation time
        p_dZeit = dGlobaleZeit;
        // Calculate the drivable distance based on the behavior
        double aktuelleStrecke = p_pVerhalten->dStrecke(*this, vergangeneZeit);
        // Calculate the distance traveled on the current path
        p_dAbschnittStrecke += aktuelleStrecke;
        // Ensure that the total distance (p_dGesamtStrecke) is also updated
        p_dGesamtStrecke += aktuelleStrecke;
		// Throw Streckenende exception if the end of the path is reached
		if (p_dAbschnittStrecke >= p_pVerhalten->getWeg().getLaenge()) {
				throw Streckenende(*this, p_pVerhalten->getWeg());
			}

    }
}


double Fahrzeug::dTanken(double dMenge) {
    // Vehicles without tanks do not refuel
    return 0.0;
}
double Fahrzeug::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit; // Return the maximum speed
}

/*
"1":
-Overloading << outside the class, so it can work for any derived class .

"2"
-Yes one definition works because the vAusgeben method is virtual.
It will automatically calls the appropriate function for each derived class.

"1":
-Überladen von << außerhalb der Klasse, sodass es für jede abgeleitete Klasse funktionieren kann.

"2"
-Ja eine Definition funktioniert, da die vAusgeben-Methode virtuell ist.
Sie ruft automatisch die entsprechende Funktion für jede abgeleitete Klasse auf.
*/





bool Fahrzeug::operator<(const Fahrzeug& TheOtherObjects) const {
    // Compare the total distance (p_dGesamtStrecke) of the current object (TheOtherObjects)
    return p_dGesamtStrecke < TheOtherObjects.p_dGesamtStrecke;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& TheOtherObjects) {
	if (this!=&TheOtherObjects){
		p_sName = TheOtherObjects.p_sName;// Copy the name
		p_dMaxGeschwindigkeit = TheOtherObjects.p_dMaxGeschwindigkeit; // Copy max speed
	}
    return *this;
}

// Function to set a new path and behavior
void Fahrzeug::vNeueStrecke(Weg& weg2) {
	p_pVerhalten = make_unique<Fahren>(weg2); // Assign Fahren behavior
    p_dAbschnittStrecke = 0.0; // Reset the section distance

}
void Fahrzeug::vNeueStrecke(Weg& weg, double startzeit ) {
    p_pVerhalten = make_unique<Parken>(weg, startzeit); // Assign Parken behavior
    p_dAbschnittStrecke = 0.0; // Reset section distance
}


void Fahrzeug::vZeichnen(const Weg&) const{
	return;
}

