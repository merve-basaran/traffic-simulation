/*
 * Fahrrad.cpp
 *
 *  Created on: 2 Jan 2026
 *      Author: mervebasaran
 */

#include "Fahrrad.h"
#include "SimuClient.h"
#include "Weg.h"
#include <iostream>
#include <iomanip>

using namespace std;

Fahrrad::Fahrrad(string name, double maxGeschwindigkeit)
    : Fahrzeug(name, maxGeschwindigkeit) {
}


void Fahrrad::vAusgeben(ostream& to) const  {
    Fahrzeug::vAusgeben(to) ;
    cout << setw(17) << 0.00
         << setw(20) << 0.00
		 << setw(20) << Fahrrad::dGeschwindigkeit()
		 << setw (20) << 0.00;
}

double Fahrrad::dGeschwindigkeit() const {
    // Calculate how many full 20 km segments have been traveled
    int count_20km = p_dGesamtStrecke / 20;

    // Start with the maximum speed
    double geschwindigkeit = p_dMaxGeschwindigkeit;

    // Apply a 10% reduction for each 20 km segment
    for (int i = 0; i < count_20km; ++i) {
        geschwindigkeit *= 0.9;
    }

    // Ensure the speed does not drop below 12 km/h
    if (geschwindigkeit < 12.0) {
        geschwindigkeit = 12.0;
    }

    return geschwindigkeit;
}

// Override vZeichnen
void Fahrrad::vZeichnen(const Weg& weg) const  {
	double RealPosition= getAbschnittStrecke()/weg.getLaenge();
    // Call the function for drawing
    bZeichneFahrrad(getName(), weg.getName(), RealPosition, this->dGeschwindigkeit());
}




