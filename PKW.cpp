/*
 * PKW.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "PKW.h"
#include "verhalten.h"
#include <iostream>
#include <iomanip>
#include "Fahrzeug.h"
#include "SimuClient.h"
#include "Weg.h"


using namespace std;


PKW::PKW(string name, double maxGeschwindigkeit, double Verbrauch, double Tankvolumen ):
		Fahrzeug(name, maxGeschwindigkeit), p_dVerbrauch(Verbrauch), p_dTankvolumen(Tankvolumen), p_dTankinhalt(0.5 * Tankvolumen){
}

double PKW::dTanken(double dMenge) {
    double whatNeeded = p_dTankvolumen - p_dTankinhalt; // Space left in the tank

    double fuelToAdd = 0.0;

    if (dMenge == numeric_limits<double>::infinity()) {
    	fuelToAdd = whatNeeded; // Refuel the tank to its full capacity
    } else {
        // Otherwise, refuel with the lesser of the requested amount or the space left
        if (dMenge <= whatNeeded) {
        	fuelToAdd = dMenge; // Add the requested amount if it fits
        } else {
        	fuelToAdd = whatNeeded; // Add only what the tank can take
        }
    }

    p_dTankinhalt += fuelToAdd;//Update the current fuel level

    return fuelToAdd; // Return the actual refueled amount
}

double PKW::dGeschwindigkeit() const {
	 if (p_pVerhalten){
		 double speedlimit = p_pVerhalten->getWeg().getTempolimit();
		 return min(p_dMaxGeschwindigkeit, speedlimit);
	 }
	 return p_dMaxGeschwindigkeit;
	}

void PKW::vSimulieren() {
    if (p_dTankinhalt > 0) {
        // Save the previous total distance before simulation
        double oldDis = p_dGesamtStrecke;

        // Call the base class simulation function to handle movement
        Fahrzeug::vSimulieren();

        double distanceCovered = p_dGesamtStrecke - oldDis; // Calculate distance covered in this step
        double fuelConsumed = distanceCovered * (p_dVerbrauch / 100); // Calculate fuel consumed
        p_dTankinhalt -= fuelConsumed; // Reduce fuel from the tank

        // Ensure the tank content doesn't drop below zero
        if (p_dTankinhalt < 0){
            p_dTankinhalt = 0;}
    }

    // Update the last simulation time to the global time
    p_dZeit = dGlobaleZeit;
}

void PKW::vAusgeben(ostream& to) const {
    Fahrzeug::vAusgeben(to) ; // Output base class data

    cout << setprecision(2) << setw(17) << p_dGesamtStrecke * p_dVerbrauch / 100 // Total fuel consumption
         << setw(20) << p_dTankinhalt // Current tank content

		 << setw(20) << dGeschwindigkeit()

		 << setw (20) << p_dVerbrauch;
}

// Override vZeichnen for PKW
void PKW::vZeichnen(const Weg& weg) const {
	double RealPosition= getAbschnittStrecke()/weg.getLaenge();
    // Call the function for drawing a car (PKW)
    bZeichnePKW(getName(), weg.getName(), RealPosition, this->dGeschwindigkeit(), p_dTankinhalt);
}

